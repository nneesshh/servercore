//------------------------------------------------------------------------------
//  ServerCore.cpp
//  (C) 2016 n.lee
//------------------------------------------------------------------------------
#include "ServerCore.h"

#include <future>
#include "base/MyMacros.h"

#include "TimeoutEventHub.h"
#include "Heartbeat.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__,__LINE__)
#endif
#endif

static thread_local kj::Own<kj::TaskSet> thread_local_evalLaterFuncTaskSet;

static kj::Promise<void>
pipe_trunk_read_loop(kj::AsyncIoStream& pipe, void *buf, size_t bufsize, std::function<void(size_t amount)> readcb) {

	return pipe.tryRead(buf, 1, bufsize)
		.then([&pipe, buf, bufsize, readcb](size_t amount) {

		readcb(amount);
		return pipe_trunk_read_loop(pipe, buf, bufsize, readcb);
	});
}

//------------------------------------------------------------------------------
/**

*/
CServerCore::CServerCore(servcercore_param_t *param)
	: _param(*param)
	, _refSimpleTimer(static_cast<CSimpleTimer *>(_param._timer))
	, _tsCommon(NewTaskSet(*this)) {

#ifdef WIN32
	WSADATA WSAData;
	DWORD Ret;
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &WSAData)) != 0) {
		fprintf(stderr, "WSAStartup failed with error %d!!!\n", Ret);
		exit(-1);
	}
#endif

	//
	servcercore_init_root_ctx();
	servcercore_init_log(&_param);

	_timeoutEventHub = new CTimeoutEventHub();
	_heartbeat = new CHeartbeat(_param._sAppPath, *_refSimpleTimer, *this);
}

//------------------------------------------------------------------------------
/**

*/
CServerCore::~CServerCore() noexcept {

	SAFE_DELETE(_timeoutEventHub);
	SAFE_DELETE(_heartbeat);

	// clean for main thread of servercore
	thread_local_evalLaterFuncTaskSet = nullptr;

	//
	servcercore_cleanup_root_ctx();
	servcercore_cleanup_log();

#ifdef WIN32
	DWORD Ret;
	if ((Ret = WSACleanup()) != 0) {
		fprintf(stderr, "WSACleanup failed with error %d!!!\n", Ret);
	}
#endif
}

//------------------------------------------------------------------------------
/**

*/
void
CServerCore::Shutdown() {
	if (!_bShutdown) {
		_bShutdown = true;

		// wait until all endpoint threads are terminated
		for (auto& iter : _mapPipeWorker) {
			svrcore_pipeworker_t& pipeworker = iter.second;
			while (!pipeworker.endpointThreadIsTerminated) {
				util_sleep(10);
			}
		}
	}
}

//------------------------------------------------------------------------------
/**

*/
void
CServerCore::ScheduleTask(kj::TaskSet& taskset, kj::Promise<void>&& task) {
	taskset.add(kj::mv(task));
}

//------------------------------------------------------------------------------
/**

*/
svrcore_pipeworker_t *
CServerCore::NewPipeWorker(
	const char *sPipeName,
	void *buf,
	size_t bufsize,
	std::function<void(size_t)> readcb,
	std::function<void(svrcore_pipeworker_t *)> workercb) {

	std::lock_guard<std::mutex> lock(_mutexPipeWorker);

	svrcore_pipeworker_t *worker = nullptr;

	uint64_t uId = ++_uNextPipeWorkerId;
	worker = &_mapPipeWorker[uId];
	worker->uId = uId;
	worker->sName = sPipeName;

	worker->endpointThreadIsTerminated = false;

	// create pipe thread
	KjIoContext *context = static_cast<KjIoContext *>(servcercore_get_root_ctx());

	// wait until pipe ready
	auto prms = std::make_shared<std::promise<void>>();
	auto readycb = [&prms]() {
		prms->set_value();
	};
	auto pipeThreadStartFunc = [this, worker, workercb, readycb](kj::AsyncIoProvider& provider, kj::AsyncIoStream& stream, kj::WaitScope& waitScope) {

		worker->endpointContext = kj::refcounted<KjPipeEndpointIoContext>(provider, stream, waitScope);

		readycb();
		workercb(worker);

		worker->endpointContext = nullptr;
		worker->endpointThreadIsTerminated = true;
	};

	worker->pipeThread = context->NewPipeThread(kj::mv(pipeThreadStartFunc));

	prms->get_future().get();

	// schedule pipe trunk read cb
	if (!thread_local_evalLaterFuncTaskSet) {
		thread_local_evalLaterFuncTaskSet = NewTaskSet(*this);
	}
	ScheduleTask(*thread_local_evalLaterFuncTaskSet.get(),
		pipe_trunk_read_loop(*worker->pipeThread.pipe.get(), buf, bufsize, readcb));
	return worker;
}

//------------------------------------------------------------------------------
/**

*/
void
CServerCore::PipeNotify(kj::AsyncIoStream& pipe, char opcode) {
	StdLog *pLog = servcercore_get_log();

	// pipe write maybe trigger exception at once, so we must catch it manually
	KJ_IF_MAYBE(e, kj::runCatchingExceptions([&pipe, opcode]() {
		pipe.write((const void *)&opcode, 1);
	})) {
		if (pLog)
			pLog->logprint(LOG_LEVEL_ALERT, "[CServerCore::PipeNotify()] desc(%s) -- crashed!!!!\n",
				e->getDescription().cStr());

		fprintf(stderr, "[CServerCore::PipeNotify()] desc(%s) -- crashed!!!!\n", e->getDescription().cStr());
		kj::throwFatalException(kj::mv(*e));
	}
}

//------------------------------------------------------------------------------
/**

*/
void
CServerCore::ScheduleEvalLaterFunc(kj::Function<void()>&& evalLaterFunc) {
	if (!thread_local_evalLaterFuncTaskSet) {
		thread_local_evalLaterFuncTaskSet = NewTaskSet(*this);
	}
	thread_local_evalLaterFuncTaskSet->add(kj::evalLater(kj::mv(evalLaterFunc)));
}

//------------------------------------------------------------------------------
/**

*/
void
CServerCore::taskFailed(kj::Exception&& exception) {
	// fatal
	StdLog *pLog = servcercore_get_log();
	if (pLog)
		pLog->logprint(LOG_LEVEL_FATAL, "\n\n\n!!![CServerCore::taskFailed()] exception_desc(%s)!!!\n\n\n",
			exception.getDescription().cStr());

	fprintf(stderr, "\n\n\n!!![CServerCore::taskFailed()] exception_desc(%s)!!!\n\n\n",
		exception.getDescription().cStr());

	kj::throwFatalException(kj::mv(exception));
}

/** -- EOF -- **/
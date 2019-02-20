#pragma once
//------------------------------------------------------------------------------
/**
	@class CServerCore

	(C) 2016 n.lee
*/
#include <string>
#include <unordered_map>
#include <mutex>

#include "base/servercore_service_def.h"
#include "base/IServerCore.h"

#include "ServerCoreRootContextDef.hpp"

//------------------------------------------------------------------------------
/**
@brief CServerCore
*/
class MY_SERVERCORE_EXTERN  CServerCore : public IServerCore, public kj::TaskSet::ErrorHandler {
public:
	CServerCore(servcercore_param_t *param);
	virtual ~CServerCore() noexcept;

public:
	virtual void				OnUpdate() override {
		//_heartbeat->OnStats()
	}

	virtual void *				GetCtx() override {
		return servcercore_get_root_ctx();
	}

	virtual StdLog *			GetLogHandler() override {
		return servcercore_get_log();
	}

	virtual CSimpleTimer&		SimpleTimer() override {
		return *_refSimpleTimer;
	}

	virtual ITimeoutEventHub&	TimeoutEventHub() override {
		return *_timeoutEventHub;
	}

	virtual IHeartbeat&			Heartbeat() override {
		return *_heartbeat;
	}

	///
	virtual void				Shutdown() override;

	///
	virtual kj::Own<kj::TaskSet> NewTaskSet(kj::TaskSet::ErrorHandler& errorHandler) override {
		return kj::heap<kj::TaskSet>(errorHandler);
	}

	///
	virtual kj::Own<kj::TaskSet> NewTaskSet() override {
		return kj::heap<kj::TaskSet>(*this);
	}

	virtual void				ScheduleTask(kj::TaskSet& taskset, kj::Promise<void>&& task) override;

	virtual svrcore_pipeworker_t *	NewPipeWorker(
		const char *sPipeName,
		void *buf,
		size_t bufsize,
		std::function<void(size_t)> readcb,
		std::function<void(svrcore_pipeworker_t *)> workercb) override;

	virtual void				PipeNotify(kj::AsyncIoStream& pipe, char opcode) override;

	virtual void				ScheduleEvalLaterFunc(kj::Function<void()>&& evalLaterFunc) override;

private:
	void taskFailed(kj::Exception&& exception) override;

private:
	bool				  _bShutdown = false;

	servcercore_param_t   _param;
	CSimpleTimer         *_refSimpleTimer; // singleton can't cross dll (so), so we must keep the timer reference

	kj::Own<kj::TaskSet>  _tsCommon;

	mutable std::mutex    _mutexPipeWorker;
	uint64_t              _uNextPipeWorkerId = 0;
	std::unordered_map<uint64_t, svrcore_pipeworker_t> _mapPipeWorker; // workerid 2 worker

	ITimeoutEventHub     *_timeoutEventHub;
	IHeartbeat           *_heartbeat;

};

/*EOF*/
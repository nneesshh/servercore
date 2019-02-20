#pragma once
//------------------------------------------------------------------------------
/**
	@class IServerCore

	(C) 2016 n.lee
*/
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <stdint.h>

#include "../UsingCapnp.h"
#include "../log/StdLog.h"

#include "SimpleTimer.h"
#include "ITimeoutEventHub.h"
#include "IHeartbeat.h"
#include "../io/KjPipeEndpointIoContext.hpp"

#include "servercore_extern.h"

struct svrcore_pipeworker_t {
	uint64_t uId;
	std::string sName;
	
	kj::AsyncIoProvider::PipeThread pipeThread;
	kj::Own<KjPipeEndpointIoContext> endpointContext;
	bool endpointThreadIsTerminated;
};

#ifdef _WIN32
#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "Wldap32.Lib")
#pragma comment(lib, "IPHlpApi.Lib")
#pragma comment(lib, "Psapi.Lib")
#pragma comment(lib, "UserEnv.Lib")
#endif

//------------------------------------------------------------------------------
/**
@brief IServerCore
*/
class MY_SERVERCORE_EXTERN IServerCore {
public:
	virtual ~IServerCore() noexcept {};

	virtual void				OnUpdate() = 0;

	///
	virtual void *				GetCtx() = 0;
	virtual StdLog *			GetLogHandler() = 0;
	virtual CSimpleTimer&		SimpleTimer() = 0;
	virtual IHeartbeat&			Heartbeat() = 0;
	virtual ITimeoutEventHub&	TimeoutEventHub() = 0;

	///
	virtual void				Shutdown() = 0;

	///
	virtual kj::Own<kj::TaskSet> NewTaskSet(kj::TaskSet::ErrorHandler& errorHandler) = 0;
	virtual kj::Own<kj::TaskSet> NewTaskSet() = 0;

	virtual void				ScheduleTask(kj::TaskSet& taskset, kj::Promise<void>&& task) = 0;

	virtual svrcore_pipeworker_t *	NewPipeWorker(
		const char *sPipeName,
		void *buf,
		size_t bufsize,
		std::function<void(size_t)> readcb,
		std::function<void(svrcore_pipeworker_t *)> workercb) = 0;

	virtual void				PipeNotify(kj::AsyncIoStream& pipe, char opcode) = 0;
	
	virtual void				ScheduleEvalLaterFunc(kj::Function<void()>&& evalLaterFunc) = 0;

};

/*EOF*/
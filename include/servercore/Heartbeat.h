#pragma once
//------------------------------------------------------------------------------
/**
	@class CHeartbeat

	(C) 2016 n.lee
*/
#include <signal.h>
#include <vector>

#include "io/KjIoContext.hpp"

#include "base/IServerCore.h"
#include "base/IHeartbeat.h"

#include "ServerCoreRootContextDef.hpp"

#define HEARTBEAT_FRAME_TIME_IN_MS	30

//------------------------------------------------------------------------------
/**
@brief CHeartbeat
*/
class MY_SERVERCORE_EXTERN CHeartbeat : public IHeartbeat, public kj::TaskSet::ErrorHandler {
public:
	CHeartbeat(const std::string& appname, CSimpleTimer& timer, IServerCore& servercore);
	virtual ~CHeartbeat() noexcept;

	///
	virtual void				OnStats(int nConnectionCount, int nAccountCount, int nRecvBytes, int nSendBytes) override;

	///
	virtual void				Run(std::function<void(unsigned int, uint64_t)> cbUpdate) override;

	virtual struct stats_t *	Stats() override {
		return &_stats;
	}

	virtual void				Quit() override {
		_quit = 1;
	}

	virtual void				StartDaemon() override;

	virtual CSimpleTimer&		SimpleTimer() override {
		return _refTimer;
	}
	
	virtual CSimpleCalendar&	SimpleCalendar() override {
		return _calendar;
	}

private:
	kj::Promise<void>			MainUpdateLoop(kj::PromiseFulfiller<void> *fulfiller);

	uint64_t					StatsNowSystemTimeInMs() {
		return _stats._now_system_time_in_ms;
	}

	unsigned int				StatsTotalElapsedInMs() {
		return _stats._total_elapsed_in_ms;
	}

	void						TimeCorrection(int offsetAddInMs) {
		_correctionOffsetInMs += offsetAddInMs;
	}

	///
	void						BeforeHeartbeat();
	void						AfterHeartbeat();

	kj::Promise<void>			Daemon();

private:
	void taskFailed(kj::Exception&& exception) override;

private:
	volatile sig_atomic_t _quit = 0;

	std::string      _appname;
	CSimpleTimer&	 _refTimer;
	IServerCore&     _refServercore;

	CSimpleCalendar  _calendar;

	std::function<void(unsigned int, uint64_t)> _cbUpdate;

	kj::Own<kj::TaskSet> _tsCommon;
	kj::Own<kj::TaskSet> _tsDaemon;

	unsigned int _statsOutputIntervalInMs = 0;
	int64_t _baseDiffInMs = 0;
	int _diffOffsetInMs = 0;
	int _correctionOffsetInMs = 0;
	char _nowformat[32];
	struct stats_t _stats;

	int _lastRecvBytes = 0;
	int _lastSendBytes = 0;
};

/*EOF*/
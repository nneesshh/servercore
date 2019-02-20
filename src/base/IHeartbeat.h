#pragma once
//------------------------------------------------------------------------------
/**
	@class IHeartbeat

	(C) 2016 n.lee
*/
#include <stdint.h>
#include <functional>

#include "../UsingCapnp.h"
#include "SimpleTimer.h"

#include "servercore_extern.h"

//------------------------------------------------------------------------------
/**
	@brief IHeartbeat
*/
class MY_SERVERCORE_EXTERN IHeartbeat {
public:
	virtual ~IHeartbeat() noexcept { }

	struct stats_t {
		uint64_t _now_system_time_in_ms;
		unsigned int _total_elapsed_in_ms;

		unsigned int _elapsed_in_ms;
		unsigned int _sleep_in_ms;

		float _fps;
		float _spf;
	};

	///
	virtual void				OnStats(int nConnectionCount, int nAccountCount, int nRecvBytes, int nSendBytes) = 0;

	///
	virtual void				Run(std::function<void(unsigned int, uint64_t)> cbUpdate) = 0;
	virtual struct stats_t *	Stats() = 0;

	virtual void				Quit() = 0;

	virtual void				StartDaemon() = 0;
};

/*EOF*/
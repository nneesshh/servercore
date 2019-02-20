#pragma once
//------------------------------------------------------------------------------
/**
	@class ITimeoutEventHub

	(C) 2016 n.lee
*/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "timingwheel/timeout/timeout.h"

#ifdef __cplusplus
}
#endif

#include "servercore_extern.h"

//------------------------------------------------------------------------------
/**
	@brief ITimeoutEventHub
*/
class ITimeoutEventHub {
public:
	virtual ~ITimeoutEventHub() noexcept {}

public:
	virtual void				AdjustStartPoint(uint64_t start_point_in_ms) = 0;
	virtual uint64_t			GetStartPointInMs() = 0;

	virtual void				AdvanceTo(uint64_t new_time_in_ms) = 0;

	virtual bool				IsTimeoutTicking(struct timeout *to) = 0;

	virtual struct timeout *	AddTimeoutAbs(struct timeout *to, uint64_t abstime_in_ms) = 0;
	virtual struct timeout *	AddTimeout(struct timeout *to, unsigned int time_in_ms) = 0;

	virtual void				InitExpireTimeout(struct timeout *to) = 0;

#ifndef TIMEOUT_DISABLE_INTERVALS
	virtual void				InitIntervalTimeout(struct timeout *to) = 0;
#endif

	virtual void				DelTimeout(struct timeout *to) = 0;

};

/*EOF*/
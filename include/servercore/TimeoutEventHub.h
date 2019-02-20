#pragma once
//------------------------------------------------------------------------------
/**
	@class CTimeoutEventHub

	(C) 2016 n.lee
*/
#include <assert.h>
#include <vector>

#include "base/ITimeoutEventHub.h"

//------------------------------------------------------------------------------
/**
@brief CTimeoutEventHub
*/
class CTimeoutEventHub : public ITimeoutEventHub {
public:
	CTimeoutEventHub();
	virtual ~CTimeoutEventHub() noexcept;

public:
	virtual void				AdjustStartPoint(uint64_t start_point_in_ms) override;

	virtual uint64_t			GetStartPointInMs() override {
		return _startPointInMs;
	}

	virtual void				AdvanceTo(uint64_t new_time_in_ms) override;

	virtual bool				IsTimeoutTicking(struct timeout *to) override {
		return (NULL != to->pending);
	}

	virtual struct timeout *	AddTimeoutAbs(struct timeout *to, uint64_t abstime_in_ms) override {

		assert(!IsTimeoutTicking(to));

		timeouts_sched_abs(_tos, to, abstime_in_ms);
		return to;
	}

	virtual struct timeout *	AddTimeout(struct timeout *to, unsigned int time_in_ms) override {

		assert(!IsTimeoutTicking(to));

		timeouts_addf(_tos, to, time_in_ms);
		return to;
	}

	virtual void				InitExpireTimeout(struct timeout *to) override {
		timeout_init(to, 0); // expire
	}

#ifndef TIMEOUT_DISABLE_INTERVALS
	virtual void				InitIntervalTimeout(struct timeout *to) override {
		timeout_init(to, TIMEOUT_INT); // interval
	}
#endif

	virtual void				DelTimeout(struct timeout *to) override {
		timeouts_del(_tos, to);
	}

private:
	struct timeouts *_tos;

	uint64_t _startPointInMs;
};

/*EOF*/
#pragma  once
//------------------------------------------------------------------------------
/**
	@class CSimpleCalendar

	(C) 2016 n.lee
*/
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "MyMacros.h"
#include "mysnprintf.h"

#include "servercore_extern.h"

//
struct calendar_rule_t {
	char	_chYesterday[32];
	time_t	_yesterday;

	char	_chToday[32];
	time_t	_today;
	int		_today_mon_in_year;
	int		_today_day_in_month;

	char	_chTomorrow[32];
	time_t	_tomorrow;

	char	_chWeekday[32];
	time_t	_weekday;

	char	_chWeekdayPre[32];
	time_t	_weekdayPre;

	char	_chWeekdayPost[32];
	time_t	_weekdayPost;

	char	_chMonthday[32];
	time_t	_monthday;

	char	_chMonthdayPre[32];
	time_t	_monthdayPre;

	char	_chMonthdayPost[32];
	time_t	_monthdayPost;
};

//------------------------------------------------------------------------------
/**
@brief CSimpleCalendar
*/
class MY_SERVERCORE_EXTERN CSimpleCalendar {
public:
	CSimpleCalendar();
	CSimpleCalendar(time_t tmNow);
	~CSimpleCalendar();

	void						Init(time_t tmNow);

	void						Update(time_t tmNow) {
		if (tmNow - _rule._today >= DAY_SECONDS) {
			Init(_rule._today + DAY_SECONDS);
		}
	}

	void						UpdateInMs(uint64_t nowInMs) {
		if (nowInMs - _rule._today * 1000 >= DAY_SECONDS * 1000) {
			Init(_rule._today + DAY_SECONDS);
		}
	}

	calendar_rule_t *			GetCalendarRule() {
		return &_rule;
	}

	bool						IsYesterday(const char *sDay);
	bool						IsYesterday(time_t day) {
		return (day == _rule._yesterday);
	}

	bool						IsToday(const char *sDay);
	bool						IsToday(time_t day) {
		return (day == _rule._today);
	}

	bool						IsTomorrow(const char *sDay);
	bool						IsTomorrow(time_t day) {
		return (day == _rule._tomorrow);
	}

public:
	static int					MonthFrom1970(time_t tmDaypoint) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif
		return (tp.tm_year - 70) * 12 + tp.tm_mon;
	}

	static int					MonthInYear(time_t tmDaypoint) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif
		return tp.tm_mon + 1;
	}

	static int					DayInMonth(time_t tmDaypoint) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif
		return tp.tm_mday;
	}

	static time_t				WeekDay(time_t tmDaypoint) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif

		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;
		time_t theday = mktime(&tp);

		// wday -- Sunday is the tm_wday beginning, but we use Monday as our week beginning
		int wday = ((tp.tm_wday - 1) + 7) % 7;
		return theday - wday * DAY_SECONDS;
	}

	static void					MonthDay(time_t tmDaypoint, time_t& outMonthDay, time_t& outMonthDayPre, time_t& outMonthDayPost) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif

		int year = tp.tm_year;
		int mon = tp.tm_mon;
		int mday = 1;

		tp.tm_year = year;
		tp.tm_mon = mon;
		tp.tm_mday = mday;
		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;
		outMonthDay = mktime(&tp);

		tp.tm_year = year;
		tp.tm_mon = mon - 1;
		tp.tm_mday = mday;
		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;
		outMonthDayPre = mktime(&tp);

		tp.tm_year = year;
		tp.tm_mon = mon + 1;
		tp.tm_mday = mday;
		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;
		outMonthDayPost = mktime(&tp);
	}

	static time_t				DatetimeToDate(time_t tmDaypoint) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif

		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;
		return mktime(&tp);
	}

	static time_t				StringToDate(const char *str) {
		struct tm tp;
		int year = 0, month = 1, day = 1;
		sscanf(str, "%d-%d-%d", &year, &month, &day);
		tp.tm_year = year - 1900;
		tp.tm_mon = month - 1;
		tp.tm_mday = day;
		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;
		tp.tm_isdst = -1;

		time_t t_ = mktime(&tp);
		return t_;
	}

	static time_t				StringToDatetime(const char *str) {
		struct tm tp;
		int year = 0, month = 1, day = 1, hour = 0, minute = 0, second = 0;
		sscanf(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		tp.tm_year = year - 1900;
		tp.tm_mon = month - 1;
		tp.tm_mday = day;
		tp.tm_hour = hour;
		tp.tm_min = minute;
		tp.tm_sec = second;
		tp.tm_isdst = -1;

		time_t t_ = mktime(&tp);
		return t_;
	}

	static struct tm			FormatDate(time_t tmDay, char *chFormat, size_t szFormatLen) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDay);
#else
		localtime_r(&tmDay, &tp);
#endif

		tp.tm_hour = 0;
		tp.tm_min = 0;
		tp.tm_sec = 0;

		o_snprintf(
			chFormat
			, szFormatLen
			, "%04d-%02d-%02d"
			, tp.tm_year + 1900
			, tp.tm_mon + 1
			, tp.tm_mday);
		return tp;
	}

	static struct tm			FormatDatetime(time_t tmDaypoint, char *chFormat, size_t szFormatLen) {
		struct tm tp;
#ifdef _WIN32
		localtime_s(&tp, &tmDaypoint);
#else
		localtime_r(&tmDaypoint, &tp);
#endif

		o_snprintf(
			chFormat
			, szFormatLen
			, "%04d-%02d-%02d %02d:%02d:%02d"
			, tp.tm_year + 1900
			, tp.tm_mon + 1
			, tp.tm_mday
			, tp.tm_hour
			, tp.tm_min
			, tp.tm_sec);
		return tp;
	}

private:
	calendar_rule_t			_rule;

};

/*EOF*/
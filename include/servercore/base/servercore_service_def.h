#pragma once

#include <string>

struct servcercore_param_t {
	std::string  _sAppName;
	std::string  _sAppPath;

	int          _nLogLevel;

	void		*_timer;
};

/*EOF*/
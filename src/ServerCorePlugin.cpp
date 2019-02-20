//------------------------------------------------------------------------------
//  ServerCorePlugin.cpp
//  (C) 2016 n.lee
//------------------------------------------------------------------------------
#include "ServerCore.h"

#include "base/servercore_extern.h"

#ifdef _MSC_VER
# ifdef _DEBUG
#  include <vld.h>
# endif
#endif

#ifdef _MSC_VER
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__,__LINE__)
#endif
#endif

extern "C" {

	MY_SERVERCORE_EXTERN IServerCore *
		GetPlugin(servcercore_param_t *param) {
		return new CServerCore(param);
	}

	MY_SERVERCORE_EXTERN IServerCore *
		GetClass(servcercore_param_t *param) {
		return GetPlugin(param);
	}
}

/** -- EOF -- **/
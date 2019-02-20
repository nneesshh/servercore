#ifndef _SERVERCORE_ROOT_CONTEXT_DEF_HPP__
#define _SERVERCORE_ROOT_CONTEXT_DEF_HPP__

//------------------------------------------------------------------------------
/**
	@class CServerCoreRootContextDef

	(C) 2016 n.lee
*/
#include "base/servercore_service_def.h"
#include "log/StdLog.h"

extern "C" void servcercore_init_root_ctx();
extern "C" void servcercore_cleanup_root_ctx();
extern "C" void * servcercore_get_root_ctx();

extern "C" void servcercore_init_log(servcercore_param_t *param);
extern "C" void servcercore_cleanup_log();
extern "C" StdLog * servcercore_get_log();

#endif /* _SERVERCORE_ROOT_CONTEXT_DEF_HPP__ */
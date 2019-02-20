#include "ServerCoreRootContextDef.hpp"

#include "io/KjIoContext.hpp"
#include "log/StdPanLog.h"

static kj::Own<KjIoContext> s_rootContext;
static StdLog *s_log;

void 
servcercore_init_root_ctx() {
	if (!s_rootContext) {
		s_rootContext = kj::refcounted<KjIoContext>();
	}
}

void 
servcercore_cleanup_root_ctx() {
	if (s_rootContext) {
		s_rootContext = nullptr;
	}
}

void *
servcercore_get_root_ctx() {
	return s_rootContext.get();
}

void
servcercore_init_log(servcercore_param_t *param) {
	if (!s_log) {
		s_log = new CStdPanLog(param->_nLogLevel, param->_sAppName.c_str());
	}
}

void
servcercore_cleanup_log() {
	delete s_log;
	s_log = nullptr;
}

StdLog *
servcercore_get_log() {
	return s_log;
}

/* -- EOF -- */
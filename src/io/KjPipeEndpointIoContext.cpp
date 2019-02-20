//------------------------------------------------------------------------------
//  KjPipeEndpointIoContext.cpp
//  (C) 2016 n.lee
//------------------------------------------------------------------------------
#include "KjPipeEndpointIoContext.hpp"

#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__,__LINE__)
#endif
#endif

//------------------------------------------------------------------------------
/**

*/
KjPipeEndpointIoContext::KjPipeEndpointIoContext(kj::AsyncIoProvider& provider, kj::AsyncIoStream& stream, kj::WaitScope& waitScope)
	: _refProvider(provider)
	, _refStream(stream)
	, _refWaitScope(waitScope) {

}

/* -- EOF -- */
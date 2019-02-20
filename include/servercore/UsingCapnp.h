#pragma once
//------------------------------------------------------------------------------
/**
    @class CUsingCapnp
    (C) 2016 n.lee
*/
#pragma push_macro("ERROR")
#undef ERROR
#pragma push_macro("VOID")
#undef VOID

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#include "capnp/kj/async.h"
#include "capnp/kj/async-io.h"

#pragma pop_macro("min")
#pragma pop_macro("max")

#pragma pop_macro("ERROR")
#pragma pop_macro("VOID")

#ifdef _WIN32
#pragma comment(lib, "WS2_32.Lib")
#endif

/*EOF*/
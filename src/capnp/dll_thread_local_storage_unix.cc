#include "dll_thread_local_storage_win32.h"

#pragma push_macro("ERROR")
#undef ERROR
#pragma push_macro("VOID")
#undef VOID

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#include "kj/threadlocal.h"
#include "kj/exception.h"

#pragma pop_macro("min")
#pragma pop_macro("max")

#pragma pop_macro("ERROR")
#pragma pop_macro("VOID")

KJ_THREADLOCAL_PTR(kj::EventLoop) threadLocalEventLoop = nullptr;
KJ_THREADLOCAL_PTR(kj::ExceptionCallback) threadLocalCallback = nullptr;

kj::EventLoop * WINAPI
thread_local_event_loop_Get()
{
	return threadLocalEventLoop;
}

void WINAPI
thread_local_event_loop_Set(kj::EventLoop *p)
{
	threadLocalEventLoop = p;
}

kj::ExceptionCallback * WINAPI
thread_local_callback_Get()
{
	return threadLocalCallback;
}


void WINAPI
thread_local_callback_Set(kj::ExceptionCallback *p)
{
	threadLocalCallback = p;
}
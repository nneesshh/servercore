#include "dll_thread_local_storage.h"

#include "kj/threadlocal.h"
#include "kj/exception.h"

KJ_THREADLOCAL_PTR(kj::EventLoop) threadLocalEventLoop = nullptr;
KJ_THREADLOCAL_PTR(kj::ExceptionCallback) threadLocalCallback = nullptr;

kj::EventLoop *
thread_local_event_loop_Get()
{
	return threadLocalEventLoop;
}

void
thread_local_event_loop_Set(kj::EventLoop *p)
{
	threadLocalEventLoop = p;
}

kj::ExceptionCallback *
thread_local_callback_Get()
{
	return threadLocalCallback;
}

void
thread_local_callback_Set(kj::ExceptionCallback *p)
{
	threadLocalCallback = p;
}
#ifndef DLL_THREAD_LOCAL_STORAGE_WIN32_H
#define DLL_THREAD_LOCAL_STORAGE_WIN32_H

#include "../UsingCapnp.h"

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include "kj/windows-sanity.h"

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif


__declspec(dllexport) kj::EventLoop * WINAPI thread_local_event_loop_Get();
__declspec(dllexport) void WINAPI thread_local_event_loop_Set(kj::EventLoop *);

__declspec(dllexport) kj::ExceptionCallback * WINAPI thread_local_callback_Get();
__declspec(dllexport) void WINAPI thread_local_callback_Set(kj::ExceptionCallback *);


#ifdef __cplusplus
}
#endif

#endif /* DLL_THREAD_LOCAL_STORAGE_WIN32_H */

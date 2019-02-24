#ifndef DLL_THREAD_LOCAL_STORAGE_H
#define DLL_THREAD_LOCAL_STORAGE_H

#include "base/servercore_extern.h"
#include "../UsingCapnp.h"

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif


MY_SERVERCORE_EXTERN kj::EventLoop * thread_local_event_loop_Get();
MY_SERVERCORE_EXTERN void thread_local_event_loop_Set(kj::EventLoop *);

MY_SERVERCORE_EXTERN kj::ExceptionCallback * thread_local_callback_Get();
MY_SERVERCORE_EXTERN void thread_local_callback_Set(kj::ExceptionCallback *);


#ifdef __cplusplus
}
#endif

#endif /* DLL_THREAD_LOCAL_STORAGE_H */

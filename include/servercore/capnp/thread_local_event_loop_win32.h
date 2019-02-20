#ifndef THREAD_LOCAL_STORAGE_WIN32_H
#define THREAD_LOCAL_STORAGE_WIN32_H

#include <stdint.h>

#pragma push_macro("ERROR")
#undef ERROR
#pragma push_macro("VOID")
#undef VOID

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#pragma pop_macro("min")
#pragma pop_macro("max")

#pragma pop_macro("ERROR")
#pragma pop_macro("VOID")

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

	__declspec(dllexport) DWORD WINAPI thread_local_event_loop_GetTlsSlotIndex();

	__declspec(dllexport) DWORD WINAPI thread_local_event_loop_ProcessAttach();
	__declspec(dllexport) BOOL WINAPI thread_local_event_loop_ThreadAttach();
	__declspec(dllexport) void WINAPI thread_local_event_loop_ThreadDetach();
	__declspec(dllexport) void WINAPI thread_local_event_loop_ProcessDetach();

	__declspec(dllexport) BOOL WINAPI thread_local_event_loop_StoreData(DWORD dwSlotIndex, uintptr_t ptr);
	__declspec(dllexport) BOOL WINAPI thread_local_event_loop_GetData(DWORD dwSlotIndex, uintptr_t *ptr);

#ifdef __cplusplus
}
#endif

#endif /* THREAD_LOCAL_STORAGE_WIN32_H */

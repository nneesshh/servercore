#include <objbase.h>

#include "capnp/thread_local_event_loop_win32.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // DLL module handle
	DWORD fdwReason,                    // reason called
	LPVOID lpvReserved)                 // reserved
{
	switch (fdwReason)
	{
		// The DLL is loading due to process 
		// initialization or a call to LoadLibrary. 

	case DLL_PROCESS_ATTACH:

		// Allocate a TLS index.
// 		if (thread_local_event_loop_ProcessAttach() == TLS_OUT_OF_INDEXES)
// 			return FALSE;

		// No break: Initialize the index for first thread.

		// The attached process creates a new thread. 

	case DLL_THREAD_ATTACH:

		// Initialize the TLS index for this thread.
//		thread_local_event_loop_ThreadAttach();
		break;

		// The thread of the attached process terminates.

	case DLL_THREAD_DETACH:

		// Release the allocated memory for this thread.
//		thread_local_event_loop_ThreadDetach();
		break;

		// DLL unload due to process termination or FreeLibrary. 

	case DLL_PROCESS_DETACH:

		// Release the allocated memory for this thread.
//		thread_local_event_loop_ProcessDetach();
		break;

	default:
		break;
	}

	return TRUE;

	UNREFERENCED_PARAMETER(hinstDLL);
	UNREFERENCED_PARAMETER(lpvReserved);

}
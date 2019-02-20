#include "thread_local_event_loop_win32.h"

static DWORD s_dwTlsSlotIndex = 0xFF; // address of shared memory

DWORD WINAPI
thread_local_event_loop_GetTlsSlotIndex()
{
	return s_dwTlsSlotIndex;
}

DWORD WINAPI
thread_local_event_loop_ProcessAttach()
{
	s_dwTlsSlotIndex = TlsAlloc();
	return s_dwTlsSlotIndex;
}

BOOL WINAPI
thread_local_event_loop_ThreadAttach()
{
	LPVOID lpvData;

	lpvData = (LPVOID)LocalAlloc(LPTR, 256);
	if (lpvData != NULL)
		return TlsSetValue(s_dwTlsSlotIndex, lpvData);

	return FALSE;
}

void WINAPI
thread_local_event_loop_ThreadDetach()
{
	LPVOID lpvData;

	lpvData = TlsGetValue(s_dwTlsSlotIndex);
	if (lpvData != NULL)
		LocalFree((HLOCAL)lpvData);
}

void WINAPI
thread_local_event_loop_ProcessDetach()
{
	LPVOID lpvData;
	
	lpvData = TlsGetValue(s_dwTlsSlotIndex);
	if (lpvData != NULL)
		LocalFree((HLOCAL)lpvData);

	// Release the TLS index.
	TlsFree(s_dwTlsSlotIndex);
}

BOOL WINAPI
thread_local_event_loop_StoreData(DWORD dwSlotIndex, uintptr_t ptr)
{
	LPVOID lpvData;
	uintptr_t * pData;  // The stored memory pointer 
	DWORD dwIndex;

	lpvData = TlsGetValue(dwSlotIndex);
	if (lpvData == NULL)
	{
		lpvData = (LPVOID)LocalAlloc(LPTR, 256);
		if (lpvData == NULL)
			return FALSE;
		if (!TlsSetValue(dwSlotIndex, lpvData))
			return FALSE;
	}

	pData = (uintptr_t *)lpvData; // Cast to my data type.
								  // In this example, it is only a pointer to a DWORD
								  // but it can be a structure pointer to contain more complicated data.

	(*pData) = ptr;
	return TRUE;
}

BOOL WINAPI
thread_local_event_loop_GetData(DWORD dwSlotIndex, uintptr_t *pptr)
{
	LPVOID lpvData;
	uintptr_t * pData;  // The stored memory pointer
	DWORD dwIndex;

	dwIndex = thread_local_event_loop_GetTlsSlotIndex();

	lpvData = TlsGetValue(dwSlotIndex);
	if (lpvData == NULL)
		return FALSE;

	pData = (uintptr_t *)lpvData;
	(*pptr) = (*pData);
	return TRUE;
}
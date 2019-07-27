// RuntimeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RuntimeDll.h"

#include <string>
#include <windows.h>

__declspec(thread) DWORD dll_tls_var = 1024;

// This is an example of an exported function.
int __stdcall RuntimeDll(void)
{

	printf("tls: %d\n", dll_tls_var);

	return 0;
}

LPVOID __stdcall AllocateMem(void)
{
	LPVOID lpAlloc = new (std::nothrow) BYTE[100];
	if (lpAlloc)
	{
		return lpAlloc;
	}
	return NULL;
}

VOID __stdcall FreeMem(LPVOID lpBuf)
{
	if (lpBuf)
	{
		delete [] lpBuf;
	}

	return ;
}
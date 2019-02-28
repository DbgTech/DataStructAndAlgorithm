// RuntimeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RuntimeDll.h"

#include <string>
#include <windows.h>

// This is an example of an exported function.
int RuntimeDll(void)
{


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
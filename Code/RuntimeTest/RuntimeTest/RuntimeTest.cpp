// RuntimeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Shlwapi.h>

#include <string>

#pragma comment(lib, "Shlwapi.lib")


typedef LPVOID (__stdcall *Fn_AllocateMem)(void);
typedef VOID (__stdcall *Fn_FreeMem)(LPVOID lpBuf);

int _tmain(int argc, _TCHAR* argv[])
{

	CHAR szModule[MAX_PATH + 1] = {};
	if (0 == GetModuleFileNameA(NULL, szModule, MAX_PATH))
	{
		printf("Get Module Path Error!\n");
		return 1;
	}
	PathAppendA(szModule, "..\\RuntimeDll.dll");
	if (!PathFileExistsA(szModule))
	{
		printf("Module Not Exist: %s!\n", szModule);
		return 1;
	}

	printf("Load Module: %s\n", szModule);
	LPVOID lpDllAlloc = NULL;
	HMODULE hDll = LoadLibraryA(szModule);
	if (hDll)
	{
		Fn_AllocateMem lpAllocate = (Fn_AllocateMem)GetProcAddress(hDll, "AllocateMem");
		if (lpAllocate)
		{
			lpDllAlloc = lpAllocate();
			if (lpDllAlloc)
			{
				printf("DLL Alloc Buffer: 0x%p\n", lpDllAlloc);
			}

		}
	}

	LPVOID lpExeAlloc = new (std::nothrow) BYTE[200];
	if (lpExeAlloc)
	{
		printf("Exe Alloc Buffer: 0x%p\n", lpExeAlloc);
	}

	Fn_FreeMem lpFreeMem = (Fn_FreeMem)GetProcAddress(hDll, "FreeMem");
	if (lpFreeMem)
	{
		lpFreeMem(lpExeAlloc);
	}

	delete [] lpDllAlloc;	

	system("pause");

	if (hDll)
		FreeLibrary(hDll);

	return 0;
}


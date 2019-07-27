// RuntimeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Shlwapi.h>

#include <string>

#include "../StaticImportDll/StaticImportDll.h"

#pragma comment(lib, "StaticImportDll.lib")

#pragma comment(lib, "Shlwapi.lib")

#pragma comment(linker, "/INCLUDE:__tls_used") 

__declspec(thread) DWORD exe_tls_var = 4096;
__declspec(thread) DWORD exe_tls_var1 = 8192;

void NTAPI my_tls_callback(PVOID h, DWORD reason, PVOID pv)
{
	/*一共有四个选项 DLL_PROCESS_ATTACH、DLL_THREAD_ATTACH、
	DLL_THREAD_DETACH 和 DLL_PROCESS_DETACH。
	DLL_PROCESS_ATTACH，是指新进程创建时，在初始化主线程时执行
	DLL_THREAD_ATTACH，是指在新进程初始化时执行，但是不包括主线程
	DLL_THREAD_DETACH，是指在所有的线程终止时执行，但是同样不包括主线程
	DLL_PROCESS_DETACH，是指在进程终止时执行。
	详见微软发布的《Microsoft Portable Executable and Common Object File
	Format Specification v8》*/
	//仅在进程初始化创建主线程时执行的代码
	if( reason == DLL_PROCESS_ATTACH ){
		printf("hi,this is exe tls callback\t");

		printf("exe_tls_var: %d\n", exe_tls_var);
	}
	return;
} 

void NTAPI my_tls_callback_2(PVOID h, DWORD reason, PVOID pv)
{
	/*一共有四个选项 DLL_PROCESS_ATTACH、DLL_THREAD_ATTACH、
	DLL_THREAD_DETACH 和 DLL_PROCESS_DETACH。
	DLL_PROCESS_ATTACH，是指新进程创建时，在初始化主线程时执行
	DLL_THREAD_ATTACH，是指在新进程初始化时执行，但是不包括主线程
	DLL_THREAD_DETACH，是指在所有的线程终止时执行，但是同样不包括主线程
	DLL_PROCESS_DETACH，是指在进程终止时执行。
	详见微软发布的《Microsoft Portable Executable and Common Object File
	Format Specification v8》*/
	//仅在进程初始化创建主线程时执行的代码
	if( reason == DLL_PROCESS_ATTACH ){
		printf("hi,this is exe tls callback 2>>>> %d\n", exe_tls_var1);
	}
	return;
} 

#pragma data_seg(".CRT$XLB")
/*如果要定义多个 TLS_CallBack 函数，可以把下面这句写成：
PIMAGE_TLS_CALLBACK p_thread_callback [] = {tls_callback_A,
tls_callback_B, tls_callback_C,0};
其中 tls_callback_B 和 tls_callback_C 应该是你定义好的其他
TLS_callBack 函数，这些函数会被依次执行
*/
PIMAGE_TLS_CALLBACK p_thread_callback [] = {my_tls_callback, my_tls_callback_2, 0};
#pragma data_seg() 


typedef LPVOID (__stdcall *Fn_AllocateMem)(void);
typedef VOID (__stdcall *Fn_FreeMem)(LPVOID lpBuf);

typedef int (__stdcall *Fn_RuntimeDll)(void);

DWORD __stdcall ThreadProc(LPVOID lpParam)
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

	Fn_RuntimeDll lpRuntimeDll = (Fn_RuntimeDll)GetProcAddress(hDll, "RuntimeDll");
	if (lpRuntimeDll)
	{
		lpRuntimeDll();
	}

	Fn_FreeMem lpFreeMem = (Fn_FreeMem)GetProcAddress(hDll, "FreeMem");
	if (lpFreeMem && lpDllAlloc)
	{
		lpFreeMem(lpDllAlloc);
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	//CHAR szModule[MAX_PATH + 1] = {};
	//if (0 == GetModuleFileNameA(NULL, szModule, MAX_PATH))
	//{
	//	printf("Get Module Path Error!\n");
	//	return 1;
	//}
	//PathAppendA(szModule, "..\\RuntimeDll.dll");
	//if (!PathFileExistsA(szModule))
	//{
	//	printf("Module Not Exist: %s!\n", szModule);
	//	return 1;
	//}

	//printf("Load Module: %s\n", szModule);
	//LPVOID lpDllAlloc = NULL;
	//HMODULE hDll = LoadLibraryA(szModule);
	//if (hDll)
	//{
	//	Fn_AllocateMem lpAllocate = (Fn_AllocateMem)GetProcAddress(hDll, "AllocateMem");
	//	if (lpAllocate)
	//	{
	//		lpDllAlloc = lpAllocate();
	//		if (lpDllAlloc)
	//		{
	//			printf("DLL Alloc Buffer: 0x%p\n", lpDllAlloc);
	//		}

	//	}
	//}

	//Fn_FreeMem lpFreeMem = (Fn_FreeMem)GetProcAddress(hDll, "FreeMem");
	//if (lpFreeMem && lpDllAlloc)
	//{
	//	lpFreeMem(lpDllAlloc);
	//}
	StaticImport();

	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	if (hThread)
	{
		CloseHandle(hThread);
		Sleep(3000);
	}

	HMODULE hDll = GetModuleHandleW(L"RuntimeDll.dll");
	if (hDll)
	{
		Fn_RuntimeDll lpRuntimeDll = (Fn_RuntimeDll)GetProcAddress(hDll, "RuntimeDll");
		if (lpRuntimeDll)
		{
			lpRuntimeDll();
		}
	}


	system("pause");

	if (hDll)
		FreeLibrary(hDll);

	return 0;
}


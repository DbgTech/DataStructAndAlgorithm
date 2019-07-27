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
	/*һ�����ĸ�ѡ�� DLL_PROCESS_ATTACH��DLL_THREAD_ATTACH��
	DLL_THREAD_DETACH �� DLL_PROCESS_DETACH��
	DLL_PROCESS_ATTACH����ָ�½��̴���ʱ���ڳ�ʼ�����߳�ʱִ��
	DLL_THREAD_ATTACH����ָ���½��̳�ʼ��ʱִ�У����ǲ��������߳�
	DLL_THREAD_DETACH����ָ�����е��߳���ֹʱִ�У�����ͬ�����������߳�
	DLL_PROCESS_DETACH����ָ�ڽ�����ֹʱִ�С�
	���΢�����ġ�Microsoft Portable Executable and Common Object File
	Format Specification v8��*/
	//���ڽ��̳�ʼ���������߳�ʱִ�еĴ���
	if( reason == DLL_PROCESS_ATTACH ){
		printf("hi,this is exe tls callback\t");

		printf("exe_tls_var: %d\n", exe_tls_var);
	}
	return;
} 

void NTAPI my_tls_callback_2(PVOID h, DWORD reason, PVOID pv)
{
	/*һ�����ĸ�ѡ�� DLL_PROCESS_ATTACH��DLL_THREAD_ATTACH��
	DLL_THREAD_DETACH �� DLL_PROCESS_DETACH��
	DLL_PROCESS_ATTACH����ָ�½��̴���ʱ���ڳ�ʼ�����߳�ʱִ��
	DLL_THREAD_ATTACH����ָ���½��̳�ʼ��ʱִ�У����ǲ��������߳�
	DLL_THREAD_DETACH����ָ�����е��߳���ֹʱִ�У�����ͬ�����������߳�
	DLL_PROCESS_DETACH����ָ�ڽ�����ֹʱִ�С�
	���΢�����ġ�Microsoft Portable Executable and Common Object File
	Format Specification v8��*/
	//���ڽ��̳�ʼ���������߳�ʱִ�еĴ���
	if( reason == DLL_PROCESS_ATTACH ){
		printf("hi,this is exe tls callback 2>>>> %d\n", exe_tls_var1);
	}
	return;
} 

#pragma data_seg(".CRT$XLB")
/*���Ҫ������ TLS_CallBack ���������԰��������д�ɣ�
PIMAGE_TLS_CALLBACK p_thread_callback [] = {tls_callback_A,
tls_callback_B, tls_callback_C,0};
���� tls_callback_B �� tls_callback_C Ӧ�����㶨��õ�����
TLS_callBack ��������Щ�����ᱻ����ִ��
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


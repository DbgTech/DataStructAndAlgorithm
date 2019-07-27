// ThreadCreateTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#include <stdlib.h>

DWORD __stdcall ThreadProc(LPVOID lpParam)
{

	Sleep(3000);

	printf("Thread Running...\n");

	return 0L;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	if (hThread)
	{
		printf("Create Thread Success!\n");
		CloseHandle(hThread);
	}
	else
	{
		printf("Create Thread Failed!\n");
	}	

	system("pause");
	return 0;
}


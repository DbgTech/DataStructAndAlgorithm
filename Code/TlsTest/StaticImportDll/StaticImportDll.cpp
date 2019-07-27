// StaticImportDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

__declspec(thread) DWORD static_dll_tls_var = 2048;

// This is an example of an exported function.
DWORD __stdcall StaticImport(void)
{

	printf("StaticImport tls: %d\n", static_dll_tls_var);

	return 0;
}

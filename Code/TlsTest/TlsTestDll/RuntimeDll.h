// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RUNTIMEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RUNTIMEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RUNTIMEDLL_EXPORTS
#define RUNTIMEDLL_API __declspec(dllexport)
#else
#define RUNTIMEDLL_API __declspec(dllimport)
#endif



RUNTIMEDLL_API int fnRuntimeDll(void);

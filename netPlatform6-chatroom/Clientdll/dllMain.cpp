// dllTest.cpp : Defines the entry point for the DLL application.
//

#include "windows.h"
#include "stdio.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch(ul_reason_for_call){
	case DLL_PROCESS_ATTACH:
		//printf("\n DLL_PROCESS_ATTACH");
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
	//	printf("\n DLL_PROCESS_DETACH");
		break;
	}

    return TRUE;
}


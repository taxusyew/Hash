#include "stdio.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

void main()
{
	HANDLE hprocSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32  pe;
	MODULEENTRY32 me32;
	
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL existProc = Process32First(hprocSnap, &pe);
	TCHAR*   shortpath = new TCHAR[256];

	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	
	me32.dwSize = sizeof(MODULEENTRY32);
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pe.th32ProcessID );
	int n = 0;
	
	 do{ 
		n++;

		printf("PID: %d\n", pe.th32ProcessID);

		hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pe.th32ProcessID );
		if( hModuleSnap == INVALID_HANDLE_VALUE )
		{
			printf("can not find module");
			continue;
		}

		if (!Module32First(hModuleSnap, &me32))
		{
			printf("can not find module");
			continue;
		}

		while (Module32Next(hModuleSnap, &me32))
		{
			_tprintf( TEXT("     Executable     = %s\n"),     me32.szExePath );
		}
		
	 }while (Process32Next(hprocSnap,&pe));
	

	CloseHandle(hprocSnap);
	CloseHandle(hModuleSnap);

	printf("Total Process: %d\n", n);

	system("pause");

}

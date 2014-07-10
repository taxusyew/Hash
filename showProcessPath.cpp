// 项目charset设置为unicode

#include "psapi.h"

    TCHAR szModulePath[0x200];
	TCHAR szProcessName[MAX_PATH] ;

	TCHAR mcafeePath[MAX_PATH] = TEXT("c:\\Program Files\\sinosoft\\ave\\scan.exe");
	int len = 0;

	wcscpy(szModulePath, TEXT("scan.exe"));
	
	printf("PID: %d\n", pe.th32ProcessID);
	
	if(wcsncmp(pe.szExeFile, szModulePath, 8)==0)
	{
		printf("find\n");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,  FALSE,  pe.th32ProcessID );
		//取得进程名称
		if ( hProcess )
		{
			
			GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);            
			
			len = lstrlen(szProcessName);
			if (wcsncmp(szProcessName, mcafeePath, len) != 0)
			{
				TerminateProcess(hProcess, 0);
			}
			CloseHandle(hProcess);
		}
	}

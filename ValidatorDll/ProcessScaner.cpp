#include"ProcessScaner.h"
#include <Windows.h>
#include<stdio.h>
#include <WtsApi32.h>   // for the WTS* functions
#include <sddl.h>
#include<conio.h>

#pragma comment(lib, "Wtsapi32.lib")


bool scanForProcess(const wchar_t* process) {

	PWTS_PROCESS_INFOW procInfo;
	DWORD dwCount = 0;
	LPSTR sid;
	INT nrOfProcesses = 0;
	char a = 'a';

	//call function

	if (WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &procInfo, &dwCount)) {
#ifdef _DEBUG
		//wprintf_s(L"Success to Enumerate process \n");
#endif // _DEBUG
	}
	else {
#ifdef _DEBUG
		//wprintf_s(L"Failed to Enumerate process \n");
#endif // _DEBUG
		return 0;
	}

	//print resoults

	for (int i = 0; i < dwCount; i++) {
		//wprintf_s(L"|__________________________________________________________________________________\n");
		//wprintf(L"|Session ID: %-5u |Process ID: %-5u          |Process Name: %s\n", procInfo[i].SessionId, procInfo[i].ProcessId, procInfo[i].pProcessName);
		nrOfProcesses = i;
		//wprintf(L"|User Sid: %p \n", procInfo[i].pUserSid);
		if (wcscmp(procInfo[i].pProcessName, process) == 0) {
			wprintf_s(L"I have found a proces that you were looking for, nammed: %s\n",process);
			WTSFreeMemory(procInfo);
			return 1;
		}


	}
	//wprintf_s(L"Number of processes = %d \n", nrOfProcesses + 1);

	//free the memory
	WTSFreeMemory(procInfo);

	return 0;
}

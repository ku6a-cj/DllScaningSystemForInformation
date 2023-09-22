#include"SaveProcessToFile.h"
#include <Windows.h>
#include<stdio.h>
#include <WtsApi32.h>   // for the WTS* functions
#include <sddl.h>
#include<conio.h>
#include<atlstr.h>
#pragma comment(lib, "Wtsapi32.lib")
#include <sstream>
#include <iostream>
#include <vector>
#include"SaveProcessToFile.h"
#include <fstream>

typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI* NtResumeProcess)(IN HANDLE ProcessHandle);



void 
SaveProcessToFilee() {

	std::ofstream myfile2("C:\\*");
	myfile2.open("SystemInformation.txt", std::ios_base::app);

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
		//return 0;
	}

	//print resoults

	for (int i = 0; i < dwCount; i++) {
		wprintf_s(L"|__________________________________________________________________________________\n");
		myfile2 << "|__________________________________________________________________________________\n";
		wprintf(L"|Session ID: %-5u |Process ID: %-5u          |Process Name: %s\n", procInfo[i].SessionId, procInfo[i].ProcessId, procInfo[i].pProcessName);
		myfile2 << "|Session ID:" << (" % -5u", procInfo[i].SessionId) << "| Process ID :" << ("% -5u", procInfo[i].ProcessId) <<"|Process Name : " << (" %s", CW2A(procInfo[i].pProcessName)) << "\n";
		nrOfProcesses = i;
		wprintf(L"|User Sid: %p \n", procInfo[i].pUserSid);
		myfile2 << ("|User Sid: %p", procInfo[i].pUserSid)<<" \n";
		/*
		if (wcscmp(procInfo[i].pProcessName, process) == 0) {
			wprintf_s(L"I have found a proces that you were looking for, nammed: %s\n", process);
			WTSFreeMemory(procInfo);
			return 1;
		}
		*/

	}
	wprintf_s(L"Number of processes = %d \n", nrOfProcesses + 1);
	myfile2<< "Number of processes =" << nrOfProcesses + 1 <<"\n";

	//free the memory
	WTSFreeMemory(procInfo);
	myfile2.close();
}
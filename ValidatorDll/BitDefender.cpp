#include<Windows.h>
#include"BitDefender.h"
#include"FileExproler.h"
#include <strsafe.h>
#include <atlstr.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <conio.h>
#include<string.h>
#include"ProcessScaner.h"
#include"EnumerateDevieceDrivers.h"

bool BitDefenderCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"Bitdefender Antivirus Free";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Bitdefender directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"bdredline.exe",
		L"vsserv.exe",
		L"vsservppl.exe",
		L"updatesrv.exe",
		L"bdagent.exe "
	};


	const wchar_t* descriptionsProcesses[] = {
		L"BitDefender redline update ",
		L"BitDefender Security Service",
		L"BitDefender Correlation Service",
		L"BitDefender Update Service",
		L"BitDefender bdagent.exe"
	};



	for (int i = 0; i < 5; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"atc.sys",
		L"gemma.sys",
	//	L"fvevol.sys" // a process associated with Bitlocker encryption it might be seen on PC without BitDefender as well
	};

	const wchar_t* descriptionsDrivers[] = {
		L"BitDefender Active Threat Controller",
		L"BitDefender Generic Exploit Mitigation",
	//	L"BitDefender Drive Encryption Driver"
	};



	for (int i = 0; i < 2; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
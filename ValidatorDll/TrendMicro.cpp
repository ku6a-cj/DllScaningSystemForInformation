#include<Windows.h>
#include"TrendMicro.h"
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

bool TrendMicroCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"TrendMicro";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("F-Secure directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"coreFrameworkHost.exe",
		L"uiWatchDog.exe",
		L"uiSeAgnt.exe",
		L"uiWinMgr.exe",
		L"Tmsalntance64.exe",
		L"AMSPTelemetryService.exe"
	};


	const wchar_t* descriptionsProcesses[] = {
		L"Trend Micro Anti-Malware Solution ",
		L"Trend Micro Client Session Agent Monitor",
		L"Client Session Agent ",
		L"Trend Micro Client Main Console",
		L"Trend Micro Browser Exploit Detection Engine",
		L"Trend Micro Anti-Malware Solution"
	};



	for (int i = 0; i < 6; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"tmeyes.sys",
		L"TMUMH.sys",
		L"tmusa.sys",
		L"tmnciesc.sys",
		L"TMEBC64.sys",
		L"tmeevw.sys",
	};

	const wchar_t* descriptionsDrivers[] = {
		L"TrendMicro Eyes driver Module",
		L"Trend Micro UMH Driver x64 ",
		L"Trend Micro Osprey Scanner Driver",
		L"Trend Micro NCIE Scanner",
		L"Trend Micro early boot driver",
		L"Trend Micro EagleEye Driver (VW)"
	};



	for (int i = 0; i < 6; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}


	return 0;
}
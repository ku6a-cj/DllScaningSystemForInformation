#include<Windows.h>
#include"WebRoot.h"
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

bool WebRootCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"WebRoot";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("WebRoot directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"WRSA.exe",
		L"WRSkyClient.x64.exe",
		L"WRCoreService.x64.exe"
	};


	const wchar_t* descriptionsProcesses[] = {
		L"WebRoot Secure Anywhere",
		L"WebRoot Secure Anywhere ",
		L"WebRoot Secure Anywhere Core Service"
	};



	for (int i = 0; i < 3; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"WRCore.x64.sys",
		L"WRkrn.sys"
	};

	const wchar_t* descriptionsDrivers[] = {
		L"WebRoot Secure Anywhere ",
		L"WebRoot Secure Anywhere "
	};



	for (int i = 0; i < 2; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
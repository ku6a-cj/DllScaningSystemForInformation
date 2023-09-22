#include<Windows.h>
#include"Adaware.h"
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

bool AdawareCheck() {
	const wchar_t* dir = L"C:\\Program Files (x86)\\*";
	wchar_t filename[260] = L"adaware";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Adaware  directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"AdawareDesktop.exe",
		L"AdawareTray.exe",
		L"AdawareService.exe"
	};


	const wchar_t* descriptionsProcesses[] = {
		L" Adaware Desktop ",
		L" Adaware Tray ",
		L" Adaware service "
	};



	for (int i = 0; i < 3; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"atc.sys",
		L"gzflt.sys"
	};

	const wchar_t* descriptionsDrivers[] = {
		L"BitDefender Active Threat Control Filesystem Minifilter ",
		L"Bit Defender Gonzales Filesystem Driver"
	};



	for (int i = 0; i < 2; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
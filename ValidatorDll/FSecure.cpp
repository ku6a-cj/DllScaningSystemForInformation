#include<Windows.h>
#include"FSecure.h"
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

bool FSecureCheck() {
	const wchar_t* dir = L"C:\\Program Files (x86)\\*";
	wchar_t filename[260] = L"F-Secure";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("F-Secure directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"fshoster32.exe",
		L"fsorsp64.exe",
		L"fshoster64.exe",
		L"fsulprothoster.exe",
	};


	const wchar_t* descriptionsProcesses[] = {
		L"F-Secure plugin hosting service",
		L"F-Secure ORSP Service 32-bit (Release)",
		L"F-Secure plugin hosting service",
		L"F-Secure plugin hosting service",
	};

	

	for (int i = 0; i < 4; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"fshs.sys",
		L"fsulgk.sys",
		L"nif2s64.sys",
	};

	const wchar_t* descriptionsDrivers[] = {
		L"DG 64-bit kernel module",
		L"F-Secure Gatekeeper 64 bit",
		L"F-Secure NIF2 Core Driver",
	};



	for (int i = 0; i < 3; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}


	return 0;
}
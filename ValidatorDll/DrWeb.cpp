#include<Windows.h>
#include"DrWeb.h"
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

bool DrWebCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"DrWeb";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("DrWeb directory found\n");
		return 1;
	}

	//proceses

	const wchar_t* processes[] = {
		L"dwnetfilter.exe",
		L"dwservice.exe",
		L"dwantispam.exe",
		L"dwarkdameon.exe",
		L"dwscanner.exe "
	};


	const wchar_t* descriptionsProcesses[] = {
		L"Dr. Web Net Filtering Service",
		L"Dr. Web Control Service",
		L"Dr. Web Anti Spam",
		L"Dr. Web Anti-Rootkit Service ",
		L"Dr. Web Scanner SE "
	};



	for (int i = 0; i < 5; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	//drivers

	const wchar_t* drivers[] = {
		L"dwprot.sys",
		L"A4B1FF85CA.sys",
		L"spiderg3.sys",
		L"wdg.sys"
	};

	const wchar_t* descriptionsDrivers[] = {
		L"Dr.Web Protection for Windows",
		L"Dr.Web Protection for Windows",
		L"Dr.Web File System Monitor ",
		L"Dr.Web device Guard for Windows"
	};



	for (int i = 0; i < 4; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
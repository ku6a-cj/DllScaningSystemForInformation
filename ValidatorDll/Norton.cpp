#include<Windows.h>
#include"Norton.h"
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
#include <list>

bool NortonCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"Norton Internet Security";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Norton directory found\n");
		return 1;
	}

	const wchar_t* process1 = L"NortonSecurity.exe";

	if (scanForProcess(process1) == 1) {
		wprintf_s(L"%s is a  NortonSecurity  \n", process1);
		return 1;
	}

	const wchar_t* process2 = L"nsWscSvc.exe";

	if (scanForProcess(process2) == 1) {
		wprintf_s(L"%s is a NortonSecurity WSC Service \n", process2);
		return 1;
	}

	const wchar_t* drivers[] = {
		L"SYMEFASI64.sys", 
		L"SymEvnt.sys",
		L"SYMEVENT64x86.sys",
		L"SRTSPX64.sys",
		L"SRTSP.sys"
	};

	const wchar_t* descriptionsDrivers[] = {
		L"Symantec Extended File Attributes",
		L"Symantec Eventing Platform",
		L"Symantec Event Library ",
		L"Symantec Auto Protect ",
		L"Symantec Auto Protect "
	};



	for (int i = 0; i < 5; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}


	return 0;
}
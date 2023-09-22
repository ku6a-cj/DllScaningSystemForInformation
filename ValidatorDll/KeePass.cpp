#include<Windows.h>
#include"KeePass.h"
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

bool KeePassCheck() {
	
	const wchar_t* dir = L"C:\\Program Files (x86)\\*";
	wchar_t filename[260] = L"KeePass Password Safe";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Bitdefender directory found\n");
		return 1;
	}
	
	//proceses

	const wchar_t* processes[] = {
		L"KeePass.exe"
	};


	const wchar_t* descriptionsProcesses[] = {
		L"process in Windows Task Manager The process known as KeePass or KeePass Password Safe"
	};



	for (int i = 0; i < 1; i++) { // lenght hardcoded to do later 
		if (scanForProcess(processes[i]) == 1) {
			wprintf_s(L"%s is a %s\n", processes[i], descriptionsProcesses[i]);
			return 1;
		}
	}

	return 0;
}
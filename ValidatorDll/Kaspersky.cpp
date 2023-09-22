#include<Windows.h>
#include"Kaspersky.h"
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

bool KasperskyCheck() {
	const wchar_t* dir = L"C:\\Program Files (x86)\\*";
	wchar_t filename[260] = L"Kaspersky Lab";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Kaspersky directory found\n");
		return 1;
	}

	const wchar_t* process1 = L"avp.exe";

	if (scanForProcess(process1) == 1) {
		wprintf_s(L"%s is a Kaspersky Anti-Virus \n", process1);
		return 1;
	}

	const wchar_t* process2 = L"avpui.exe";

	if (scanForProcess(process2) == 1) {
		wprintf_s(L"%s is a Kaspersky Anti-Virus \n", process2);
		return 1;
	}

	const wchar_t* process3 = L"kpm.exe ";

	if (scanForProcess(process3) == 1) {
		wprintf_s(L"%s is a Kaspersky Password Manager \n", process3);
		return 1;
	}


	const wchar_t* process4 = L"ksdeui.exe ";

	if (scanForProcess(process4) == 1) {
		wprintf_s(L"%s is a Kaspersky Secure Connection  \n", process4);
		return 1;
	}

	const wchar_t* process5 = L"ksde.exe ";

	if (scanForProcess(process5) == 1) {
		wprintf_s(L"%s is a Kaspersky Secure Connection\n", process5);
		return 1;
	}

	//drivers 


	const wchar_t* drivers[] = {
		L"klupd_klif_klark.sys",
		L"klupd_klif_mark.sys",
		L"klupd_klif_arkmon.sys",
		L"kldisk.sys ",
		L"klflt.sys",
		L"klgse.sys",
		L"klhk.sys",
		L"klids.sys",
		L"klif.sys",
		L"klim6.sys",
		L"klkbdflt2.sys",
		L"klpd.sys",
		L"kltap.sys",
		L"klupd_klif_kimul.sys "
	};

	const wchar_t* descriptionsDrivers[] = {
		L"Kaspersky Lab Anti-Rootkit",
		L"Kaspersky Lab Anti-Rootkit Memory Driver",
		L"Kaspersky Lab Anti-Rootkit Monitor Driver ",
		L"Virtual Disk",
		L"Filter Core",
		L"Security Extender",
		L"klhk",
		L"Network Processor",
		L"Core System Interceptors",
		L"Packet Network Filter",
		L"Light Keyboard Device Filter",
		L"Format Recognizer",
		L"TAP-Windows Virtual Network Driver",
		L" Kaspersky Lab Anti-Rootkit Monitor Driver"
	};



	for (int i = 0; i < 12; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
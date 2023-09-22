#include<Windows.h>
#include"Avast.h"
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

bool AvastCheck() {
	const wchar_t* dir = L"C:\\Program Files\\*";
	wchar_t filename[260] = L"AvastSoftware";

	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Avast directory found\n");
		return 1;
	}

	const wchar_t* process1 = L"wsc_proxy.exe ";

	if (scanForProcess(process1) == 1) {
		wprintf_s(L"%s is a Avast Remediation exe  \n", process1);
		return 1;
	}

	const wchar_t* process2 = L"Avast Remediation exe ";

	if (scanForProcess(process2) == 1) {
		wprintf_s(L"%s is a Avast Service \n", process2);
		return 1;
	}

	const wchar_t* process3 = L"aswEngSrv.exe ";

	if (scanForProcess(process3) == 1) {
		wprintf_s(L"%s is a Avast Antivirus engine server  \n", process3);
		return 1;
	}


	const wchar_t* process4 = L"aswToolsSvc.exe";

	if (scanForProcess(process4) == 1) {
		wprintf_s(L"%s is a Avast Antivirus \n", process4);
		return 1;
	}

	const wchar_t* process5 = L"aswidsagent.exe ";

	if (scanForProcess(process5) == 1) {
		wprintf_s(L"%s is a Avast Software Analyzer \n", process5);
		return 1;
	}

	const wchar_t* process6 = L"AvastUI.exe ";

	if (scanForProcess(process6) == 1) {
		wprintf_s(L"%s is a Avast Antivirus \n", process6);
		return 1;
	}

	//drivers

	const wchar_t* drivers[] = {
	L"aswArPot.sys",
	L"aswbidsdriver.sys",
	L"aswbidsh.sys",
	L"aswbuniv.sys",
	L"aswKbd.sys",
	L"aswMonFlt.sys",
	L"aswNetHub.sys",
	L"aswRdr2.sys",
	L"aswSnx.sys",
	L"aswSP.sys",
	L"aswStm.sys",
	L"aswVmm.sys"
	};

	const wchar_t* descriptionsDrivers[] = {
		L"Avast Anti Rootkit",
		L"Avast IDS Application Activity Monitor Driver",
		L"Avast Application Activity Monitor Helper Driver",
		L"Avast Universal Driver",
		L"Avast Keyboard Filter Driver",
		L"Avast File System Filter",
		L"Avast Network Security Driver",
		L"Avast Antivirus",
		L"Avast Antivirus",
		L"Avast Self Protection",
		L"Avast Stream Filter",
		L"Avast VM Monitor"
	};



	for (int i = 0; i < 12; i++) { // lenght hardcoded to do later 
		if (scanForDriver(drivers[i]) == 1) {
			wprintf_s(L"%s is a %s\n", drivers[i], descriptionsDrivers[i]);
			return 1;
		}
	}

	return 0;
}
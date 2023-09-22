#include<Windows.h>
#include"Avira.h"
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

bool AviraCheck() {
	//DIR SCANNER
	const wchar_t *dir = L"C:\\Program Files (x86)\\*";
	wchar_t filename[260] = L"Avira";
	
	if (FileExplor(filename, dir) == 1) {
		//while instaling it is not asking to install at another direcotry 
		printf("Avira directory found\n");
		return 1;
	}

	//PROCESS SCANNING
	const wchar_t* process1 = L"Avira.ServiceHost.exe";

	if (scanForProcess(process1) == 1) {
		wprintf_s(L"%s is a Avira Service Host \n",process1);
		return 1;
	}

	const wchar_t* process2 = L"Avira.Systray.exe";

	if (scanForProcess(process2) == 1) {
		wprintf_s(L"%s is a Avira \n", process2);
		return 1;
	}

	const wchar_t* process3 = L"Avira.OptimizerHost.exe";

	if (scanForProcess(process3) == 1) {
		wprintf_s(L"%s is a Avira  Optimizer Host \n", process3);
		return 1;
	}


	const wchar_t* process4 = L"Avira.VpnService.exe";

	if (scanForProcess(process4) == 1) {
		wprintf_s(L"%s is a Avira VpnService  \n", process4);
		return 1;
	}

	const wchar_t* process5 = L"Avira.SoftwareUpdater.ServiceHost.exe";

	if (scanForProcess(process5) == 1) {
		wprintf_s(L"%s is a Avira Updater Service Host\n", process5);
		return 1;
	}

	const wchar_t* process6 = L"Avira.Spotlight.Service.exe";

	if (scanForProcess(process6) == 1) {
		wprintf_s(L"%s is a Avira Avira Security \n", process6);
		return 1;
	}

	const wchar_t* process7 = L"avguard.exe";

	if (scanForProcess(process7) == 1) {
		wprintf_s(L"%s is a Avira Antivirus Host Framework Service \n", process7);
		return 1;
	}

	const wchar_t* process8 = L"avshadow.exe";

	if (scanForProcess(process8) == 1) {
		wprintf_s(L"%s is a Avira Anti vir Shadow copy Service \n", process8);
		return 1;
	}

	const wchar_t* process9 = L"protectedservice.exe";

	if (scanForProcess(process9) == 1) {
		wprintf_s(L"%s is a Avira Protected Antimalware Service \n", process9);
		return 1;
	}


	//DRIVER SCANNING

	const wchar_t* driver1 = L"avipbb.sys";

	if (scanForProcess(driver1) == 1) {
		wprintf_s(L"%s is a Avira Driver for Security Enhancement \n", driver1);
		return 1;
	}

	const wchar_t* driver2 = L"avnetflt.sys";

	if (scanForProcess(driver2) == 1) {
		wprintf_s(L"%s is a Avira WFP Network Driver \n", driver2);
		return 1;
	}
	const wchar_t* driver3 = L"avkmgr.sys";

	if (scanForProcess(driver3) == 1) {
		wprintf_s(L"%s is a Avira Manager Driver \n", driver3);
		return 1;
	}
	const wchar_t* driver4 = L"avgntflt.sys";

	if (scanForProcess(driver4) == 1) {
		wprintf_s(L"%s is a Avira Minifilter Driver \n", driver4);
		return 1;
	}
	const wchar_t* driver5 = L"avdevprot.sys";

	if (scanForProcess(driver5) == 1) {
		wprintf_s(L"%s is a Avira USB Feature Driver \n", driver5);
		return 1;
	}
	const wchar_t* driver6 = L"avusbflt.sys";

	if (scanForProcess(driver6) == 1) {
		wprintf_s(L"%s is a Avira USB Filter Driver \n", driver6);
		return 1;
	}


	return 0;
}
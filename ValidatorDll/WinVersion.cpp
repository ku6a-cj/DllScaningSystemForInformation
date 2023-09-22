// system includes
#include <WinSock2.h>
#include <iphlpapi.h>
#include <time.h>
#include <iostream>
#include <WS2tcpip.h>
#define __MODULE__ "Ipconfig"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")
#include<atlstr.h>
#include "WinVersion.h"
#include<string.h>

#define WIDTH 7
#define DIV 1024


void windowsVersionE() {
	PFIXED_INFO FixedInfo = nullptr;
	DWORD		FixedInfoSize = 0;
	PIP_ADAPTER_INFO AdapterInfo = nullptr;
	PIP_ADAPTER_INFO Adapter = nullptr;
	PIP_ADDR_STRING  AddrString = nullptr;

	DWORD AdapterInfoSize = 0;
	UINT  Index = 0;


	CStringA Buffer = "";
	Buffer.GetBuffer(32);


	DWORD LastError = 0;
	DWORD Ret = 0;
	//CStringA Message = "[*] This module will discover mock ipconfig utility\n";

	Ret = GetNetworkParams(nullptr, &FixedInfoSize);
	if (0 != Ret)
	{
		if (ERROR_BUFFER_OVERFLOW != Ret)
		{
			//return  GetLastError();
		}
	}


	FixedInfo = (PFIXED_INFO)GlobalAlloc(GPTR, FixedInfoSize);
	if (NULL == FixedInfo)
	{
		//return  GetLastError();
	}

	Ret = GetNetworkParams(FixedInfo, &FixedInfoSize);
	if (0 != Ret)
	{
		if (ERROR_BUFFER_OVERFLOW != Ret)
		{
			//return  GetLastError();
		}
	}
	SYSTEM_INFO sysinfoo;
	// the address of KUSER_SHARED_DATA
	auto KSharedData = (PBYTE)0x7ffe0000;
	// calling the function with the address of the sysInfo variable
	GetNativeSystemInfo(&sysinfoo);

	//printf("Host Name: %s\n", FixedInfo->HostName);
	switch (*(PULONG)(KSharedData + 0x26c)) {
	case 6:
		switch (*(PULONG)(KSharedData + 0x270)) {
		case 0:
			printf("OS Name: Microsoft Windows Vista\n");
			break;
		case 1:
			printf("OS Name: Microsoft Windows 7\n");
			break;
		case 2:
			printf("OS Name: Microsoft Windows 8\n");
			break;
		case 3:
			printf("OS Name: Microsoft Windows 8.1\n");
			break;
		default:
			printf("Unknown system version\n");
			break;
		}
		break;
	case 10:
		printf("OS Name: Microsoft Windows 10\n");
		break;
	case 11:
		printf("OS Name: Microsoft Windows 11\n");
		break;
	default:
		printf("Unknown system version\n");
		break;
	}

}
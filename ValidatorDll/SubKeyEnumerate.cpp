#include"SubKeyEnumerate.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include<string.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
typedef std::basic_string<TCHAR> tstring;

VOID QueryKey(HKEY hKey)
{
    std::ofstream myfile2("C:\\*");
    myfile2.open("SystemInformation.txt", std::ios_base::app);
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys = 0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf("\nNumber of subkeys: %d\n", cSubKeys);
        myfile2 << ("\nNumber of subkeys: %d\n", cSubKeys);

        for (i = 0; i < cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {

                tstring myString(achKey);
                std::string myStdString(myString.begin(), myString.end());
                _tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
                myfile2 << "(" << i << ")" << myStdString << "\n";
            }
        }
    }

    // Enumerate the key values. 

    if (cValues)
    {
        printf("\nNumber of values: %d\n", cValues);

        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
    myfile2.close();
}

INT QueryKey()
{
    HKEY hTestKey;

    if (RegOpenKeyEx(HKEY_CURRENT_USER,
        TEXT("SOFTWARE\\Microsoft"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    {
        QueryKey(hTestKey);
    }

    RegCloseKey(hTestKey);

    return ERROR_SUCCESS;

}
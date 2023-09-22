# DllScaningSystemForInformation
Dll that scan a system for instaled AV and get informations about PC and OS using WinApi, then save it to txt. 
Dll hooks a ReadFile process (WinApi), so every time user opens a file we are geting informations to txt, tested on notepad.


List of AV scanned by this DLL:
1) Adaware
2) Avast
3) Avira
4) BitDefender
5) DrWeb
6) Fsecure
7) Kaspersky
8) Keepass
9) Norton
10) MalwareBytes
11) WebRoot
12) TrendMicro

Other informations:
1) Check if kepass is instaled on pc
2) Check if Dll is in process on VM based on virtual graphic card
3) Windows version (with minor and major index)
4) Host name
5) Procesor name, type, architecture
6) Dir of sys root
7) TimeZone of PC
8) Phisical Memory information - total, used
9) Virtual Memory information - total, used (not wothing properly to do)
10) All list of all processes working on pc (ID, Name, Sesion ID, User ID) + number of them
11) List of drivers instaled on PC
12) List of subkeys

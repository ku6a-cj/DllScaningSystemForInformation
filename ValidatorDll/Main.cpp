#include<Windows.h>
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
#include"SystemInfoGetting2.h"

int
main() {
	/*
	//based on  https://github.com/ethereal-vx/Antivirus-Artifacts/tree/main //
	////////////////////////////ANTIVISUS SECTION///////////////////
	*/

	//Avira Check
	if (AviraCheck()==1) {
		printf("Avira installed on Pc\n");
	}
	else {
		printf("Avira not installed on Pc\n");
	}

	//F-Secure
	if (FSecureCheck() == 1) {
		printf("F-Secure installed on Pc\n");
	}
	else {
		printf("F-Secure not installed on Pc\n");
	}


	//Norton Check
	if (NortonCheck() == 1) {
		printf("Norton installed on Pc\n");
	}
	else {
		printf("Norton not installed on Pc\n");
	}

	//TrendMicro
	if (TrendMicroCheck() == 1) {
		printf("TrendMicro installed on Pc\n");
	}
	else {
		printf("TrendMicro not installed on Pc\n");
	}

	//WebRoot
	if (WebRootCheck() == 1) {
		printf("WebRoot installed on Pc\n");
	}
	else {
		printf("WebRoot not installed on Pc\n");
	}

	//BitDefender
	if (BitDefenderCheck() == 1) {
		printf("BitDefender installed on Pc\n");
	}
	else {
		printf("BitDefender not installed on Pc\n");
	}

	//MalwareBytes
	if (MalwareBytesCheck() == 1) {
		printf("MalwareBytes installed on Pc\n");
	}
	else {
		printf("MalwareBytes not installed on Pc\n");
	}

	//Adaware
	if (AdawareCheck() == 1) {
		printf("Adaware installed on Pc\n");
	}
	else {
		printf("Adaware not installed on Pc\n");
	}

	//Avast Check
	if (AvastCheck() == 1) {
		printf("Avast installed on Pc\n");
	}
	else {
		printf("Avast not installed on Pc\n");
	}

	//DrWeb
	if (DrWebCheck() == 1) {
		printf("DrWeb installed on Pc\n");
	}
	else {
		printf("DrWeb not installed on Pc\n");
	}


	//Kaspersky Check
	if (KasperskyCheck() == 1) {
		printf("Kaspersky installed on Pc\n");
	}
	else {
		printf("Kaspersky not installed on Pc\n");
	}


	////////////////////////////HARDWARE SECTION///////////////////
	if (VMCheck() == 1) {
		printf("We are on virual machine (based on Graphic card analise)\n");
	}
	else { 
		printf("We are not on virtual machine (based on Graphic card analise)\n");
	}
	
	/////////////////////////OS SECTION//////////////////////////
	windowsVersionE();


	/////////////////////////KEEPASS SECTION////////////////////

	if (KeePassCheck() == 1) {
		printf("KeePassCheck installed on Pc\n");
	}
	else {
		printf("KeePassCheck not installed on Pc\n");
	}



	return 0;
}
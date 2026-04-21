// OneClickInstallPkgIniHelper.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Ini.h"

/*
argv[1]:读入的ini
argv[2]:被写入的ini
argv[3]:节
argv[4]:键

*/
int main(int argc,char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]=%s\n", i, argv[i]);
	}
	if (argc != 5)
	{
		printf("argc invalid\n");
		return -1;
	}


	CIni ini1;
	CIni ini2;
	ini1.m_sPath = argv[1];
	ini2.m_sPath = argv[2];
	std::string sSection = argv[3];
	std::string sKey = argv[4];
	std::string sValue;
	sValue = ini1.GetVal(sSection, sKey, "");
	//printf("sValue=%s\n", sValue.c_str());
	ini2.SetVal(sSection,sKey,sValue);
    return 0;
}


// stdafx.cpp : 只包括标准包含文件的源文件
// AirPrintInjectDll.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")

#if 0

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

void CreateDir()
{
	if (!PathIsDirectory("c:\\airlog"))
	{
		system("md \"c:\\airlog\"");
	}
}


void WriteFileLog(char* szFormat, ...)
{
	CreateDir();
	char LogText[1024 + 1];
	memset(LogText, 0, sizeof(LogText));
	va_list argList;


	va_start(argList, szFormat);
	int offset = _vsnprintf_s(LogText, sizeof(LogText) - 1, szFormat, argList);
	LogText[offset] = 0;
	va_end(argList);

	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char cfile[260] = { 0 };
	sprintf(cfile, "c:\\airlog\\AirPrintInjectDll_%02d%02d%02d.Log", timeinfo->tm_year - 100, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE *pFile = fopen(cfile, "a+");
	if (pFile)
	{
		fprintf(pFile, "%04d-%02d-%02d %02d:%02d:%02d,\t%s\n"
			, (timeinfo->tm_year + 1900), timeinfo->tm_mon + 1, timeinfo->tm_mday
			, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, LogText);
		fclose(pFile);
	}
}

#endif
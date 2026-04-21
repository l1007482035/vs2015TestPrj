#include "log.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

static CRITICAL_SECTION g_critical;
static int g_nInit = 0;

void WriteFileLog(char* szFormat, ...)
{
	if (!g_nInit)
	{
		InitializeCriticalSection(&g_critical);
	}
	EnterCriticalSection(&g_critical);

	char LogText[1024 + 1];
	memset(LogText, 0, sizeof(LogText));
	va_list argList;
	va_start(argList, szFormat);
	int offset = _vsnprintf_s(LogText, sizeof(LogText) - 1, sizeof(LogText) - 1, szFormat, argList);
	LogText[offset] = 0;
	va_end(argList);

	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	//char cfile[260] = { 0 };
	//sprintf(cfile, "%s\\PdfHelper_%02d%02d%02d.Log", GetLogDir(), timeinfo->tm_year - 100, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE *pFile = fopen("ippeveprinter.log", "a+");
	if (pFile)
	{
		fprintf(pFile, "%04d-%02d-%02d %02d:%02d:%02d,\t%s\n"
			, (timeinfo->tm_year + 1900), timeinfo->tm_mon + 1, timeinfo->tm_mday
			, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, LogText);
		fclose(pFile);
	}
	LeaveCriticalSection(&g_critical);
}

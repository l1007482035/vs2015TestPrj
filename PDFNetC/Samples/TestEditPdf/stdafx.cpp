// stdafx.cpp : 只包括标准包含文件的源文件
// TestEditPdf.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

char g_szLogDir[260] = { 0 };

//获取日志目录
char* GetLogDir()
{
	if (strlen(g_szLogDir) <= 0)
	{
		OutputDebugString("##GetLogDir");
		TCHAR path[MAX_PATH];
		if (GetModuleFileName(0, path, MAX_PATH))
		{
			TCHAR *pdest;
			pdest = strrchr(path, '\\');
			if (pdest)
				*pdest = 0;
			strcpy_s(g_szLogDir, path);
			strcat_s(g_szLogDir, "\\xlog");
		}

		if (strlen(g_szLogDir) <= 0)
		{
			strcpy_s(g_szLogDir, ".\\xlog");
		}

		OutputDebugString(g_szLogDir);
	}

	return g_szLogDir;
}

void WriteFileLog(char* szFormat, ...)
{
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
	sprintf(cfile, "%s\\PdfTronHelper_%02d%02d%02d.Log", GetLogDir(), timeinfo->tm_year - 100, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE *pFile = fopen(cfile, "a+");
	if (pFile)
	{
		fprintf(pFile, "%04d-%02d-%02d %02d:%02d:%02d,\t%s\n"
			, (timeinfo->tm_year + 1900), timeinfo->tm_mon + 1, timeinfo->tm_mday
			, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, LogText);
		fclose(pFile);
	}
}

std::string MultiByteToUTF8(const char* puszSource)
{
	std::string szRetA = "";
	if (puszSource)
	{
		int len = MultiByteToWideChar(936, 0, (LPCSTR)puszSource, -1, NULL, 0);
		wchar_t* wszText = new wchar_t[len + 1];
		memset(wszText, 0, len * 2 + 2);
		MultiByteToWideChar(936, 0, (LPCSTR)puszSource, -1, wszText, len);

		len = WideCharToMultiByte(CP_UTF8, 0, wszText, -1, NULL, 0, NULL, NULL);
		char *szText = new char[len + 1];
		memset(szText, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wszText, -1, szText, len, NULL, NULL);

		szRetA = szText;
		delete[] wszText;
		delete[] szText;
	}
	return szRetA;
}

std::string UnicodeToMultiByte(const wchar_t* pwszSource)
{
	std::string szRetA = "";
	if (pwszSource)
	{
		DWORD dwNum = WideCharToMultiByte(936, NULL, pwszSource, -1, NULL, 0, NULL, FALSE);
		char* pszText = new char[dwNum];
		memset(pszText, 0x0, sizeof(char)*dwNum);
		WideCharToMultiByte(936, NULL, pwszSource, -1, pszText, dwNum, NULL, FALSE);
		szRetA = pszText;
		delete[] pszText;
	}

	return szRetA;
}

std::wstring MultiByteToUnicode(const char* pszSource)
{
	std::wstring szRetW = L"";
	if (pszSource)
	{
		DWORD dwNum = MultiByteToWideChar(936, NULL, pszSource, -1, NULL, 0);
		wchar_t* pwszText = new wchar_t[dwNum];
		memset(pwszText, 0x0, sizeof(wchar_t)*dwNum);
		MultiByteToWideChar(936, NULL, pszSource, -1, pwszText, dwNum);
		szRetW = pwszText;
		delete[] pwszText;
	}

	return szRetW;
}

std::string UTF8ToMultiByte(const char* puszSource)
{
	std::string szRetA = "";
	if (puszSource)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)puszSource, -1, NULL, 0);
		wchar_t* wszText = new wchar_t[len];
		memset(wszText, 0, len * sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)puszSource, -1, wszText, len);

		len = WideCharToMultiByte(936, 0, wszText, -1, NULL, 0, NULL, NULL);
		char *szText = new char[len];
		memset(szText, 0, len);
		WideCharToMultiByte(936, 0, wszText, -1, szText, len, NULL, NULL);

		szRetA = szText;
		delete[] wszText;
		delete[] szText;
	}
	return szRetA;
}

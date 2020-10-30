// XpsHelper.h : XpsHelper DLL ����ͷ�ļ�
//

#pragma once

#ifdef  _AA_DLL_
#define _AA_DLL_EXPORT_		__declspec(dllexport)
#define _AA_DLL_EXPORT_C_ 	extern "C" __declspec(dllexport)
#else
#define _AA_DLL_EXPORT_		__declspec(dllimport)
#define _AA_DLL_EXPORT_C_	extern "C" __declspec(dllimport)
#endif

#include <windows.h>
#include <shlwapi.h>
#include <cstdio>

#include "PrintProcessDef.h"

class _AA_DLL_EXPORT_ CXpsHelper
{
public:
	CXpsHelper();
	~CXpsHelper();

	//��ӡxps��ָ����ӡ��cPrinterName
	BOOL PrintToPrinter(const TCHAR *cPrinterName,const TCHAR *cDocName,const TCHAR *cXpsFilePath,
		int nBeginPage = -1, int nEndPage = -1, int nPagesPerPaper = 1,
		WORD wColor = DMCOLOR_MONOCHROME, WORD wPaperSize = DMPAPER_A4,
		WORD wOrientation = DMORIENT_PORTRAIT, WORD wCopies = 1,
		WORD wDuplex = DMDUP_SIMPLEX, BOOL bCollate = TRUE, WORD wPaperSource = DMBIN_AUTO,
		FPrintProcessCallBack callBack = NULL, 
		PrintProcessCallBackData* pCallBackData = NULL);

	void PrintProcess(BOOL bError, int nPrintedPage, BOOL bPrintComplete);

	//��ȡָ����xps�ļ�ҳ��
	int GetPageCount(const TCHAR *cXpsFilePath);

	//��ȡָ����xps��ӡ����
	BOOL GetPrintParam(const TCHAR *cXpsFilePath, int& nCopy, int& nPages, int& nColor
		, int& nOrientation, int& nPaperSize, int& nDuplex, BOOL& bCollate);

private:
	FPrintProcessCallBack m_pCallBack;
	PrintProcessCallBackData* m_pCallBackData;
};

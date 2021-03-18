/****************************************************************************
 *
 * File:            pdf2pdfconvert.c
 *
 * Usage:           pdf2pdfconvert <inputPDF> <outputPDFA>
 *
 * Title:           Convert PDF document to PDF/A and do a post-validation
 *
 * Description:     Define which conversion should yield a conversion error,
 *                  e.g. removing an action or converting a signed document.
 *                  Then convert a PDF document to PDF/A and create a log
 *                  file with a detailed description of the pre-analysis and
 *                  post-validation. Throw a conversion error according to
 *                  the previously defined rules.
 *
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2020 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include "pdf2pdfapi_c.h"

#include <locale.h>


int Usage()
{
	printf("Usage: pdf2pdfconvert <inputPDF> <outputPDFA>.\n");
	printf("return codes:\n");
	printf("    0: Successful completion\n");
	printf("    1: Execution failed\n");

	return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
	TPdf2Pdf* pConverter;
	TCHAR* szInputPath;
	TCHAR* szOutputPath;
	TCHAR* szLogFileName;
	TCHAR szCopyFile[256];
	TCHAR str[100];
	int iReturnValue = 0;

	setlocale(LC_CTYPE, "");


	// Check command line parameters
	if (argc < 3 || argc > 3)
	{
		return Usage();
	}

	// Initialize library
	Pdf2PdfInitialize();
	Pdf2PdfSetLicenseKeyA("1-L4AA0-PGXFC-E8FXW-43T17-KLB49-ETH7V-A8LP2");
	//Pdf2PdfAddFontDirectory("D:\\MyProject\\vs2015TestPrj\\Pdf2Pdf-API-6.12.1.11-Windows\\samples\\C\\pdf2pdfconvert\\Win32\\Release\\fonts");
	Pdf2PdfAddFontDirectory("C:\\test\\fonts");

	// Check license
	if (!Pdf2PdfGetLicenseIsValid())
	{
		_tprintf(_T("No valid license found.\n"));
		return 1;
	}

	szInputPath = argv[1];
	szOutputPath = argv[2];

	// Create the converter
	pConverter = Pdf2PdfCreateObject();

	Pdf2PdfSetCompliance(pConverter, ePDFA2b);
	Pdf2PdfSetReportSummary(pConverter, 1);

	// The ConversionErrorMask property defines what is crucial to your process and 
	// should lead to a conversion error
	Pdf2PdfSetConversionErrorMask(pConverter, (int)ePDFConversionErrorVisualDiff + (int)ePDFConversionErrorActionRemoved +
		(int)ePDFConversionErrorCorrupt + (int)ePDFConversionErrorDocSigned + (int)ePDFConversionErrorEFRemoved +
		(int)ePDFConversionErrorFontSubst + (int)ePDFConversionErrorStructureRemoved);

	// Get logfile name
	_tcscpy(szCopyFile, szOutputPath);
	szLogFileName = _tcstok(szCopyFile, _T("."));
	_tcscat(szLogFileName, _T("-log.txt"));

	// Convert input file to PDF/A
	if (!Pdf2PdfConvert(pConverter, szInputPath, _T(""), szOutputPath, szLogFileName))
	{
		int nErrCode = Pdf2PdfGetErrorCode(pConverter);
		printf("====errcode=0x%x\n", nErrCode);
		if (nErrCode == PDF_E_POSTANALYSIS)
		{
			// A post analysis error indicates that the output file is not PDF/A.
			// A detailed description why the post analysis failed can be found in the log file.
			_tprintf(_T("The output file %s is not PDF/A compliant. %s (ErrorCode: 0x%08x).\n"), szOutputPath, Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
			iReturnValue = 1;
			goto cleanup;
		}
		else if (nErrCode == PDF_E_CONVERSION)
		{
			int errors = Pdf2PdfGetConversionErrors(pConverter);

			// Print all conversion errors that occurred during conversion
			_tprintf(_T("File converted to PDF/A, but the following conversion errors occurred (see TPDFConversionError):\n"));

			for (int i = 1; i <= errors; i = 2 * i)
			{
				if ((i & errors) != 0)
				{
					_tprintf(_T("- 0x%05x\n"), i);
				}
			}

			// Decide if the errors are acceptable
			_tprintf(_T("\nPlease review the output file and confirm whether it is acceptable: [y/n] \n"));

			scanf("%s", str);
			if (_tcscmp(str, _T("y")) != 0)
			{
				_tprintf(_T("The conversion result was rejected due to conversion errors.\n"));
				iReturnValue = 1;
				goto cleanup;
			}
		}
		else
		{
			_tprintf(_T("Input file %s could not be converted to PDF/A. %s (ErrorCode: 0x%08x).\n"), szInputPath, Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
			iReturnValue = 1;
			goto cleanup;
		}
	}

	_tprintf(_T("Execution successful,errcode=%d,msg=%s.\n"), Pdf2PdfGetErrorCode(pConverter), Pdf2PdfGetErrorMessage(pConverter));

cleanup:
	Pdf2PdfDestroyObject(pConverter);
	Pdf2PdfUnInitialize();
	return iReturnValue;
}

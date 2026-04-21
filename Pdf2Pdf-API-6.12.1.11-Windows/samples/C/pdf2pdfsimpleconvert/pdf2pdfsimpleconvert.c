/****************************************************************************
 *
 * File:            pdf2pdfsimpleconvert.c
 *
 * Usage:           pdf2pdfsimpleconvert <inputPDF> <outputPDFA> [<compliance>]
 *                  compliance (default pdfa-2b):
 *                  pdfa-1b
 *                  pdfa-1a
 *                  pdfa-2b
 *                  pdfa-2u
 *                  pdfa-2a
 *                  pdfa-3b
 *                  pdfa-3u
 *                  pdfa-3a
 *                  
 * Title:           Convert PDF document to PDF/A
 *                  
 * Description:     Convert a PDF document to a specific PDF/A compliance
 *                  level such as PDF/A-2u. Allow for automatic downgrade,
 *                  e.g. to PDF/A-2b, if the input file cannot be converted
 *                  otherwise.
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
    printf("Usage: pdf2pdfsimpleconvert <inputPDF> <outputPDFA> [<compliance>].\n");
    printf("       compliance (default pdfa-2b):\n");
    printf("       pdfa-1b\n");
    printf("       pdfa-1a\n");
    printf("       pdfa-2b\n");
    printf("       pdfa-2u\n");
    printf("       pdfa-2a\n");
    printf("       pdfa-3b\n");
    printf("       pdfa-3u\n");
    printf("       pdfa-3a\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
    TPdf2Pdf* pConverter;
    TPDFCompliance eCompliance;
    TCHAR* szInputPath;
    TCHAR* szOutputPath;
    int iReturnValue = 0;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 3 || argc > 4)
    {
        return Usage();
    }

    // Initialize library
    Pdf2PdfInitialize();

    // Check license
    if (!Pdf2PdfGetLicenseIsValid())
    {
        _tprintf(_T("No valid license found.\n"));
        return 1;
    }

    szInputPath = argv[1];
    szOutputPath = argv[2];

    eCompliance = ePDFA2b;
    if (argc == 4)
    {
        if (_tcscmp(argv[3], _T("pdfa-1a")) == 0)
            eCompliance = ePDFA1a;
        else if (_tcscmp(argv[3], _T("pdfa-1b")) == 0)
            eCompliance = ePDFA1b;
        else if (_tcscmp(argv[3], _T("pdfa-2b")) == 0)
            eCompliance = ePDFA2b;
        else if (_tcscmp(argv[3], _T("pdfa-2u")) == 0)
            eCompliance = ePDFA2u;
        else if (_tcscmp(argv[3], _T("pdfa-2a")) == 0)
            eCompliance = ePDFA2a;
        else if (_tcscmp(argv[3], _T("pdfa-3b")) == 0)
            eCompliance = ePDFA3b;
        else if (_tcscmp(argv[3], _T("pdfa-3u")) == 0)
            eCompliance = ePDFA3u;
        else if (_tcscmp(argv[3], _T("pdfa-3a")) == 0)
            eCompliance = ePDFA3a;
        else
        {
            _tprintf(_T("Compliance %s is not supported."), argv[3]);
            iReturnValue = 1;
            goto cleanup;
        }
    }

    // Create the converter
    pConverter = Pdf2PdfCreateObject();

    // Set compliance level
    Pdf2PdfSetCompliance(pConverter, eCompliance);
    Pdf2PdfSetAllowDowngrade(pConverter, 1);

    // Convert to PDF/A
    if (!Pdf2PdfConvert(pConverter, szInputPath, _T(""), szOutputPath, _T("")))
    {
        _tprintf(_T("Input file %s could not be converted. %s (ErrorCode: 0x%08x).\n"), szInputPath, Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
        iReturnValue = 1;
    }
    else
    {
        _tprintf(_T("Execution successful.\n"));
    }

cleanup:
    Pdf2PdfDestroyObject(pConverter);
    Pdf2PdfUnInitialize();
    return iReturnValue;
}
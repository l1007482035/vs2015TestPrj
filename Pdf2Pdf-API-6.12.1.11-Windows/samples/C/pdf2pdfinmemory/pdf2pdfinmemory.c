/****************************************************************************
 *
 * File:            pdf2pdfinmemory.c
 *
 * Usage:           pdf2pdfinmemory <inputPDF> <outputPDFA> [<logFile>]
 *                  
 * Title:           Convert PDF document to PDF/A in memory
 *                  
 * Description:     Read a PDF from a byte stream and convert it to PDF/A as
 *                  byte stream. For demonstration purpose, the PDF byte
 *                  stream is created from file and the PDF/A byte stream is
 *                  written back to a file.
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
#include <stdlib.h>
#include "pdf2pdfapi_c.h"

#include <locale.h>


int Usage()
{
    printf("Usage: pdf2pdfinmemory <inputPDF> <outputPDFA> [<logFile>].\n");
    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
    TPdf2Pdf* pConverter;
    TCHAR szCopyFile[256];
    TCHAR* szInputPath;
    TCHAR* szLogPath;
    TCHAR* szOutputPath;
    FILE* pStream;
    FILE* pData;
    FILE* pLog;
    unsigned char* pInputBuffer;
    unsigned char* pOutputBuffer;
    unsigned char* pLogBuffer;
    size_t nLength;
    size_t nOutLength;
    size_t nLogLength;
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

    if (argc == 4)
        szLogPath = argv[3];
    else
    {
        // Get log file name
        _tcscpy(szCopyFile, szOutputPath);
        szLogPath = _tcstok(szCopyFile, _T("."));
        _tcscat(szLogPath, _T("-log.txt"));
    }

    // Read the file and write PDF to memory
    pStream = _tfopen(szInputPath, _T("rb"));
    fseek(pStream, 0, SEEK_END);
    nLength = ftell(pStream);
    pInputBuffer = malloc(nLength);
    fseek(pStream, 0, SEEK_SET);
    fread(pInputBuffer, 1, nLength, pStream);
    fclose(pStream);

    // Create the converter
    pConverter = Pdf2PdfCreateObject();

    // Convert input PDF byte array to output PDF/A byte array, get log file as byte array
    if (!Pdf2PdfConvertMem(pConverter, pInputBuffer, nLength, _T(""), &pOutputBuffer, &nOutLength, &pLogBuffer, &nLogLength))
    {
        _tprintf(_T("File could not be converted to PDF/A. %s (ErrorCode: 0x%08x).\n"), Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
        iReturnValue = 1;
        goto cleanup;
    }

    // Write bytes to output file
    pData = _tfopen(szOutputPath, _T("wb"));
    fwrite(pOutputBuffer, 1, nOutLength, pData);
    fclose(pData);

    // Write bytes to log file
    pLog = _tfopen(szLogPath, _T("wb"));
    fwrite(pLogBuffer, 1, nLogLength, pLog);
    fclose(pLog);

    _tprintf(_T("Execution successful.\n"));

cleanup:
    Pdf2PdfDestroyObject(pConverter);
    Pdf2PdfUnInitialize();
    return iReturnValue;
}
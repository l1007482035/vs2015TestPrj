/****************************************************************************
 *
 * File:            pdf2pdfzugferd.c
 *
 * Usage:           pdf2pdfzugferd <invoiceXML> <inputPDF> <outputPDFA>
 *                  Example: ZUGFeRD-invoice.xml in.pdf out.pdf
 *                  
 * Title:           Create a ZUGFeRD invoice
 *                  
 * Description:     Convert a PDF document to PDF/A-3 and embed conforming
 *                  XML data to create a ZUGFeRD compliant invoice.
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
#include "pdf2pdfapi_c.h"

#include <locale.h>


int Usage()
{
    printf("Usage: pdf2pdfzugferd <invoiceXML> <inputPDF> <outputPDFA>.\n");
    printf("       Example: ZUGFeRD-invoice.xml in.pdf out.pdf\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
    TPdf2Pdf* pConverter;
    TCHAR* szInvoicePath;
    TCHAR* szInputPath;
    TCHAR* szOutputPath;
    int iReturnValue = 0;

    setlocale(LC_CTYPE, "");


    // Check command line parameters
    if (argc < 4 || argc > 4)
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

    szInvoicePath = argv[1];
    szInputPath = argv[2];
    szOutputPath = argv[3];

    // Create the converter
    pConverter = Pdf2PdfCreateObject();

    // A ZUGFeRD invoice has to be PDF/A-3 compliant
    Pdf2PdfSetCompliance(pConverter, ePDFA3u);
    Pdf2PdfSetAllowDowngrade(pConverter, 1);

    // Add ZUGFeRD invoice
    if (!Pdf2PdfAddInvoiceXml(pConverter, ePDFInvoiceZugferd, szInvoicePath, NULL))
    {
        _tprintf(_T("ZUGFeRD invoice %s could not be added. %s (ErrorCode: 0x%08x).\n"), szInvoicePath, Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
        iReturnValue = 1;
        goto cleanup;
    }

    // Convert PDF to PDF/A
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
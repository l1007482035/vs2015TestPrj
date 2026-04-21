/****************************************************************************
 *
 * File:            pdf2pdfsign.c
 *
 * Usage:           pdf2pdfsign <inputPDF> <certificate> <outputPDFA>
 *                  certificate: Name of the certificate.
 *                  Example: input.pdf \"My Certificate Name\" output.pdf
 *                  
 * Title:           Convert PDF document to PDF/A and add a signature
 *                  
 * Description:     Prepare PDF documents for long-term archiving. For that
 *                  purpose, convert a PDF to an electronically signed PDF/A
 *                  document. The signature is created using a certificate
 *                  that contains a private key. Use the Windows
 *                  Cryptographic Provider to access the certificate via its
 *                  common name (CN) and to get necessary cryptographic
 *                  algorithms.
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
    printf("Usage: pdf2pdfsign <inputPDF> <certificate> <outputPDFA>.\n");
    printf("       certificate: Name of the certificate.\n");
    printf("       Example: input.pdf \"My Certificate Name\" output.pdf\n");

    printf("return codes:\n");
    printf("    0: Successful completion\n");
    printf("    1: Execution failed\n");

    return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
    TPdf2Pdf* pConverter;
    TPdf2PdfSignature* pSignature;
    TCHAR* szInputPath;
    TCHAR* szOutputPath;
    TCHAR* szCertificate;
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

    szInputPath = argv[1];
    szCertificate = argv[2];
    szOutputPath = argv[3];

    // Create the converter
    pConverter = Pdf2PdfCreateObject();

    // Set compliance
    Pdf2PdfSetCompliance(pConverter, ePDFA2b);

    // Begin session with Windows cryptographic provider
    if (!Pdf2PdfBeginSession(pConverter, ""))
    {
        _tprintf(_T("Unable to connect to Windows cryptographic provider. %s (ErrorCode: 0x%08x).\n"), Pdf2PdfGetErrorMessage(pConverter), Pdf2PdfGetErrorCode(pConverter));
        iReturnValue = 1;
        goto cleanup;
    }

    // Create signature object
    pSignature = Pdf2PdfSignatureCreateObject();

    Pdf2PdfSignatureSetName(pSignature, szCertificate);
    Pdf2PdfAddSignature(pConverter, pSignature);
    Pdf2PdfSignatureDestroyObject(pSignature);

    // Create PDF/A and sign it
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
    Pdf2PdfEndSession(pConverter);
    Pdf2PdfTerminate();
    Pdf2PdfDestroyObject(pConverter);
    Pdf2PdfUnInitialize();
    return iReturnValue;
}
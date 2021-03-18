 
/****************************************************************************
 *
 * File:            pdffiledecl.h
 *
 * Description:     The PDF file compliance definition.
 *
 * Author:          Dr. Hans Bärfuss, PDF Tools AG   
 * 
 * Copyright:       Copyright (C) 2001 - 2017 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *                  
 ***************************************************************************/

#ifndef _PDFDOCUMENTDECL_INCLUDED
#define _PDFDOCUMENTDECL_INCLUDED

typedef enum TPDFCompliance
{
    ePDFUnk = 0x0000,
    ePDF10  = 0x1000,
    ePDF11  = 0x1100,
    ePDF12  = 0x1200,
    ePDF13  = 0x1300,
    ePDF14  = 0x1400,
    ePDF15  = 0x1500,
    ePDF16  = 0x1600,
    ePDF17  = 0x1700,
    ePDF20  = 0x2000,
    ePDFA1b = 0x1401,
    ePDFA1a = 0x1402,
    ePDFA2b = 0x1701,
    ePDFA2u = 0x1702,
    ePDFA2a = 0x1703,
    ePDFA3b = 0x1711,
    ePDFA3u = 0x1712,
    ePDFA3a = 0x1713,
} TPDFCompliance;

// New interfaces
typedef enum TPdfConformance
{
    ePdfUnk = ePDFUnk,
    ePdf10  = ePDF10,
    ePdf11  = ePDF11,
    ePdf12  = ePDF12,
    ePdf13  = ePDF13,
    ePdf14  = ePDF14,
    ePdf15  = ePDF15,
    ePdf16  = ePDF16,
    ePdf17  = ePDF17,
    ePdf20  = ePDF20,
    ePdfA1b = ePDFA1b,
    ePdfA1a = ePDFA1a,
    ePdfA2b = ePDFA2b,
    ePdfA2u = ePDFA2u,
    ePdfA2a = ePDFA2a,
    ePdfA3b = ePDFA3b,
    ePdfA3u = ePDFA3u,
    ePdfA3a = ePDFA3a
} TPdfConformance;

#endif /* _PDFDOCUMENTDECL_INCLUDED */

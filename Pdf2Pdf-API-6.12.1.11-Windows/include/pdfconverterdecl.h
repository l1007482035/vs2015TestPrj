 
/****************************************************************************
 *
 * File:            pdfconverterdecl.h
 *
 * Description:     The PDF conversion error definition.
 *
 * Author:          Dr. Hans Bärfuss, PDF Tools AG   
 * 
 * Copyright:       Copyright (C) 2001 - 2016 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *                  
 ***************************************************************************/

#ifndef _PDFCONVERTERDECL_INCLUDED
#define _PDFCONVERTERDECL_INCLUDED

#ifndef __EMSCRIPTEN__

typedef enum TPDFConversionError
{
    ePDFConversionErrorNone             = 0x00000,   /* None. */
    ePDFConversionErrorVisualDiff       = 0x00004,   /* Visual differences in output file. */
    ePDFConversionErrorColorants        = 0x00008,   /* Resolve name collisions of colorants (PDF/A-2 and PDF/A-3 only). */
    ePDFConversionErrorOCGRemoved       = 0x00010,   /* Remove optional content groups (layers) (PDF/A-1 only). */
    ePDFConversionErrorTranspRemoved    = 0x00020,   /* Remove transparency (PDF/A-1 only). */
    ePDFConversionErrorEFRemoved        = 0x00040,   /* Remove embedded files. */
    ePDFConversionErrorXMPRemoved       = 0x00080,   /* Remove non convertible XMP metadata. */
    ePDFConversionErrorDocSigned        = 0x00200,   /* Conversion of signed document forced removal of signatures. */
    ePDFConversionErrorCorrupt          = 0x01000,   /* The input document is corrupt. */
    ePDFConversionErrorFontSubst        = 0x04000,   /* Font substituted. */
    ePDFConversionErrorActionRemoved    = 0x08000,   /* Remove interactive elements such as actions or annotations. */
    ePDFConversionErrorStructureRemoved = 0x10000,   /* Remove logical structure information. */
    ePDFConversionErrorReserved         = 0x02D03    /* Reserved bits that must be set to 0. */
} TPDFConversionError;

typedef enum TPDFInvoiceType
{
    ePDFInvoiceZugferd = 516351,/* ZUGFeRD (version and profile is determined automatically) */
    ePDFInvoiceFacturX = 7936, /* Factur-X (version and profile is determined automatically) */
    
    ePDFInvoiceZugferd1p0Basic    = 1,    /* ZUGFeRD 1.0 BASIC */
    ePDFInvoiceZugferd1p0Comfort  = 2,    /* ZUGFeRD 1.0 COMFORT */
    ePDFInvoiceZugferd1p0Extended = 4,    /* ZUGFeRD 1.0 EXTENDED */
    ePDFInvoiceZugferd2p0Minimum  = 8,    /* ZUGFeRD 2.0 MINIMUM */
    ePDFInvoiceZugferd2p0BasicWL  = 16,   /* ZUGFeRD 2.0 BASIC WL */
    ePDFInvoiceZugferd2p0Basic    = 32,   /* ZUGFeRD 2.0 BASIC */
    ePDFInvoiceZugferd2p0EN16931  = 64,   /* ZUGFeRD 2.0 EN 16931 */
    ePDFInvoiceZugferd2p0Extended = 128,  /* ZUGFeRD 2.0 EXTENDED */
    ePDFInvoiceFacturX1p0Minimum  = 256,  /* Factur-X 1.0 MINIMUM */
    ePDFInvoiceFacturX1p0BasicWL  = 512,  /* Factur-X 1.0 BASIC WL */
    ePDFInvoiceFacturX1p0Basic    = 1024, /* Factur-X 1.0 BASIC */
    ePDFInvoiceFacturX1p0EN16931  = 2048, /* Factur-X 1.0 EN 16931 */
    ePDFInvoiceFacturX1p0Extended = 4096, /* Factur-X 1.0 EXTENDED */
    ePDFInvoiceZugferd2p1Minimum  = 8192, /* ZUGFeRD 2.1 MINIMUM */
    ePDFInvoiceZugferd2p1BasicWL  = 16384,/* ZUGFeRD 2.1 BASIC WL */
    ePDFInvoiceZugferd2p1Basic    = 32768,/* ZUGFeRD 2.1 BASIC */
    ePDFInvoiceZugferd2p1EN16931  = 65536,/* ZUGFeRD 2.1 EN 16931 */
    ePDFInvoiceZugferd2p1Extended = 131072,/* ZUGFeRD 2.1 EXTENDED */
    ePDFInvoiceZugferd2p1XRechnung= 262144,/* ZUGFeRD 2.1 XRECHNUNG */
} TPDFInvoiceType;

#endif //__EMSCRIPTEN__
#endif /* _PDFCONVERTERDECL_INCLUDED */


/****************************************************************************
 *
 * File:            pdfdecl.h
 *
 * Description:     The basic header file for native C interfaces.
 *
 * Author:          Dr. Hans Bärfuss, PDF Tools AG   
 * 
 * Copyright:       Copyright (C) 2001 - 2012 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *                  
 ***************************************************************************/

#ifndef _PDFCDECL_INCLUDED
#define _PDFCDECL_INCLUDED

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif

/* Character strings on Windows can be either WinAnsi (CP1252) or Unicode (UTF16). */
/* On Unix only char strings (8-bit, ISO encoded) are used for OS interfaces. */
/* WCHAR strings are always UTF16 and may be different to wchar_t. */
/* This simplifies interoperability with Java. */
#if defined(WIN32)
#include <tchar.h>
#ifndef WCHAR
#define WCHAR wchar_t
#endif
#ifndef CDECL
#define CDECL __cdecl
#endif
#ifndef STDCALL
#define STDCALL __stdcall
#endif
typedef __int64 pos_t;
#else
#include <stdlib.h>
#ifndef WCHAR
typedef unsigned short WCHAR;
#endif
#ifndef CDECL
#define CDECL
#endif
#ifndef STDCALL
#define STDCALL
#endif
typedef long long pos_t;
#endif /* defined(WIN32) */

#include <stdarg.h>

typedef struct TPDFByteArray
{
    unsigned char*  m_pData;
    size_t          m_nLength;
} TPDFByteArray;

typedef struct TPDFFloatArray
{
    float*			m_pData;
    size_t          m_nLength;
} TPDFFloatArray;

typedef pos_t(STDCALL *TGetLength)(void* handle);
typedef int(STDCALL *TSeek)(void* handle, pos_t iPos);
typedef pos_t(STDCALL *TTell)(void* handle);
typedef size_t(STDCALL *TRead)(void* handle, void* pData, size_t nSize);
typedef size_t(STDCALL *TWrite)(void* handle, const void* pData, size_t nSize);
typedef void(STDCALL *TRelease)(void* handle);

typedef struct TPDFStreamDescriptor
{
    /** \brief Get length of stream in bytes */
    TGetLength pfGetLength;
 
    /** \brief Set position
     *  \param iPos byte position, -1 for end of stream
     *  \return 1 on success, 0 on failure
     */
    TSeek pfSeek;
 
    /** \brief Get current byte position
     *  \return byte position, -1 if position unknown
     */
    TTell pfTell;
 
    /** \brief Read nSize bytes from stream
     *  \return number of bytes read, 0 for end of stream, -1 for an error
     */
    TRead pfRead;
 
    /** \brief Write nSize bytes to stream
     *  \return number of bytes written, -1 for error (0 is interpreted as error too)
     */
    TWrite pfWrite;
 
    /** \brief Release handle */
    TRelease pfRelease;
 
    /** \brief Stream handle */
    void* m_handle;
} TPDFStreamDescriptor;

typedef TPDFStreamDescriptor TPdfStreamDescriptor;

/******************************************************************************
 * Stream descriptor for FILE*
 * (always use binary mode to fopen file!)
 *****************************************************************************/

static pos_t STDCALL PdfFILEPtrGetLength__(void* handle)
{
    pos_t iPos, nLen;
    iPos = ftell((FILE*)handle);
    if (iPos == -1)
        return -1;
    if (fseek((FILE*)handle, 0L, SEEK_END) != 0)
        return -1;
    nLen = ftell((FILE*)handle);
    if (fseek((FILE*)handle, (long)iPos, SEEK_SET) != 0)
        return -1;
    return nLen;
}

static int STDCALL PdfFILEPtrSeek__(void* handle, pos_t iPos)
{
    return fseek((FILE*)handle, (long)iPos, SEEK_SET) == 0 ? 1 : 0;
}

static pos_t STDCALL PdfFILEPtrTell__(void* handle)
{
    return ftell((FILE*)handle);
}

static size_t STDCALL PdfFILEPtrRead__(void* handle, void* pData, size_t nSize)
{
    size_t nRead = fread(pData, 1, nSize, (FILE*)handle);
    if (nRead != nSize && ferror((FILE*)handle) != 0)
        return (size_t)-1;
    return nRead;
}

static size_t STDCALL PdfFILEPtrWrite__(void* handle, const void* pData, size_t nSize)
{
    if (fwrite(pData, 1, nSize, (FILE*)handle) != nSize)
        return (size_t)-1;
    return nSize;
}

static void STDCALL PdfFILEPtrRelease__(void* handle)
{
    fclose((FILE*)handle);
}

static void PdfCreateFILEStreamDescriptor(TPdfStreamDescriptor* pDescriptor, FILE* handle, int bCloseOnRelease)
{
    pDescriptor->m_handle = handle;
    pDescriptor->pfGetLength = &PdfFILEPtrGetLength__;
    pDescriptor->pfSeek = &PdfFILEPtrSeek__;
    pDescriptor->pfTell = &PdfFILEPtrTell__;
    pDescriptor->pfRead = &PdfFILEPtrRead__;
    pDescriptor->pfWrite = &PdfFILEPtrWrite__;
    pDescriptor->pfRelease = bCloseOnRelease ? &PdfFILEPtrRelease__ : NULL;
}


#endif /* _PDFCDECL_INCLUDED */

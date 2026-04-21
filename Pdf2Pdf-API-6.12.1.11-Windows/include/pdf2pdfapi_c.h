
#ifndef _PDF2PDFAPI_H
#define _PDF2PDFAPI_H

#include "pdfcdecl.h"
#include "pdferror.h"
#include "pdfcommondecl.h"
#include "pdffiledecl.h"
#include "pdfconverterdecl.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PDF2PDFAPI
#   if defined(WIN32)
#       ifdef PDF2PDF_EXPORTS
#           define PDF2PDFAPI
#       else
#           define PDF2PDFAPI __declspec(dllimport)
#       endif
#   else
#       define PDF2PDFAPI
#   endif
#endif

#ifndef PDF2PDFCALL
#   if defined(WIN32)
#       define PDF2PDFCALL __stdcall
#   else
#       define PDF2PDFCALL
#   endif
#endif

#ifdef _UNICODE

#define Pdf2PdfSetLicenseKey            Pdf2PdfSetLicenseKeyW
#define Pdf2PdfGetProductVersion        Pdf2PdfGetProductVersionW
#define Pdf2PdfGetErrorMessage          Pdf2PdfGetErrorMessageW
#define Pdf2PdfSetOutputIntentProfile   Pdf2PdfSetOutputIntentProfileW
#define Pdf2PdfSetColorSpaceProfile     Pdf2PdfSetColorSpaceProfileW
#define Pdf2PdfBeginSession             Pdf2PdfBeginSessionW
#define Pdf2PdfSetSessionPropertyString Pdf2PdfSetSessionPropertyStringW
#define Pdf2PdfSetSessionPropertyBytes  Pdf2PdfSetSessionPropertyBytesW
#define Pdf2PdfConvert                  Pdf2PdfConvertW
#define Pdf2PdfConvertMem               Pdf2PdfConvertMemW
#define Pdf2PdfConvertStream            Pdf2PdfConvertStreamW
#define Pdf2PdfSetMetadata              Pdf2PdfSetMetadataW
#define Pdf2PdfGetCategoryText          Pdf2PdfGetCategoryTextW
#define Pdf2PdfAddFontDirectory         Pdf2PdfAddFontDirectoryW
#define Pdf2PdfGetInfoEntry             Pdf2PdfGetInfoEntryW
#define Pdf2PdfSetInfoEntry             Pdf2PdfSetInfoEntryW
#define Pdf2PdfSetOCREngine             Pdf2PdfSetOCREngineW
#define Pdf2PdfSetOCRLanguages          Pdf2PdfSetOCRLanguagesW
#define Pdf2PdfSetOCRParams             Pdf2PdfSetOCRParamsW
#define Pdf2PdfGetOCRPluginName         Pdf2PdfGetOCRPluginNameW
#define Pdf2PdfExportText               Pdf2PdfExportTextW
#define Pdf2PdfSetToUnicodeFile         Pdf2PdfSetToUnicodeFileW
#define Pdf2PdfAddEmbeddedFile          Pdf2PdfAddEmbeddedFileW
#define Pdf2PdfAddAssociatedFile        Pdf2PdfAddAssociatedFileW
#define Pdf2PdfAddAssociatedFileMem     Pdf2PdfAddAssociatedFileMemW
#define Pdf2PdfAddZUGFeRDXml            Pdf2PdfAddZUGFeRDXmlW
#define Pdf2PdfAddInvoiceXml            Pdf2PdfAddInvoiceXmlW
#define Pdf2PdfAddInvoiceXmlMem         Pdf2PdfAddInvoiceXmlMemW

#define Pdf2PdfSignatureGetImageFileName    Pdf2PdfSignatureGetImageFileNameW
#define Pdf2PdfSignatureSetImageFileName    Pdf2PdfSignatureSetImageFileNameW
#define Pdf2PdfSignatureGetName             Pdf2PdfSignatureGetNameW
#define Pdf2PdfSignatureSetName             Pdf2PdfSignatureSetNameW
#define Pdf2PdfSignatureGetIssuer           Pdf2PdfSignatureGetIssuerW
#define Pdf2PdfSignatureSetIssuer           Pdf2PdfSignatureSetIssuerW
#define Pdf2PdfSignatureGetSerialNumber     Pdf2PdfSignatureGetSerialNumberW
#define Pdf2PdfSignatureSetSerialNumber     Pdf2PdfSignatureSetSerialNumberW
#define Pdf2PdfSignatureGetSignerFingerprintStr Pdf2PdfSignatureGetSignerFingerprintStrW
#define Pdf2PdfSignatureSetSignerFingerprintStr Pdf2PdfSignatureSetSignerFingerprintStrW
#define Pdf2PdfSignatureGetProvider         Pdf2PdfSignatureGetProviderW
#define Pdf2PdfSignatureSetProvider         Pdf2PdfSignatureSetProviderW
#define Pdf2PdfSignatureGetStore            Pdf2PdfSignatureGetStoreW
#define Pdf2PdfSignatureSetStore            Pdf2PdfSignatureSetStoreW
#define Pdf2PdfSignatureGetTimeStampURL     Pdf2PdfSignatureGetTimeStampURLW
#define Pdf2PdfSignatureSetTimeStampURL     Pdf2PdfSignatureSetTimeStampURLW
#define Pdf2PdfSignatureGetTimeStampCredentials Pdf2PdfSignatureGetTimeStampCredentialsW
#define Pdf2PdfSignatureSetTimeStampCredentials Pdf2PdfSignatureSetTimeStampCredentialsW
#define Pdf2PdfSignatureGetReason           Pdf2PdfSignatureGetReasonW
#define Pdf2PdfSignatureSetReason           Pdf2PdfSignatureSetReasonW
#define Pdf2PdfSignatureGetContactInfo      Pdf2PdfSignatureGetContactInfoW
#define Pdf2PdfSignatureSetContactInfo      Pdf2PdfSignatureSetContactInfoW
#define Pdf2PdfSignatureGetLocation         Pdf2PdfSignatureGetLocationW
#define Pdf2PdfSignatureSetLocation         Pdf2PdfSignatureSetLocationW
#define Pdf2PdfSignatureGetFontName1        Pdf2PdfSignatureGetFontName1W
#define Pdf2PdfSignatureSetFontName1        Pdf2PdfSignatureSetFontName1W
#define Pdf2PdfSignatureGetFontName2        Pdf2PdfSignatureGetFontName2W
#define Pdf2PdfSignatureSetFontName2        Pdf2PdfSignatureSetFontName2W
#define Pdf2PdfSignatureGetText1            Pdf2PdfSignatureGetText1W
#define Pdf2PdfSignatureSetText1            Pdf2PdfSignatureSetText1W
#define Pdf2PdfSignatureGetText2            Pdf2PdfSignatureGetText2W
#define Pdf2PdfSignatureSetText2            Pdf2PdfSignatureSetText2W
#define Pdf2PdfSignatureGetSubFilter        Pdf2PdfSignatureGetSubFilterW
#define Pdf2PdfSignatureSetSubFilter        Pdf2PdfSignatureSetSubFilterW

#else

#define Pdf2PdfSetLicenseKey            Pdf2PdfSetLicenseKeyA
#define Pdf2PdfGetProductVersion        Pdf2PdfGetProductVersionA
#define Pdf2PdfGetErrorMessage          Pdf2PdfGetErrorMessageA
#define Pdf2PdfSetOutputIntentProfile   Pdf2PdfSetOutputIntentProfileA
#define Pdf2PdfSetColorSpaceProfile     Pdf2PdfSetColorSpaceProfileA
#define Pdf2PdfBeginSession             Pdf2PdfBeginSessionA
#define Pdf2PdfSetSessionPropertyString Pdf2PdfSetSessionPropertyStringA
#define Pdf2PdfSetSessionPropertyBytes  Pdf2PdfSetSessionPropertyBytesA
#define Pdf2PdfConvert                  Pdf2PdfConvertA
#define Pdf2PdfConvertMem               Pdf2PdfConvertMemA
#define Pdf2PdfConvertStream            Pdf2PdfConvertStreamA
#define Pdf2PdfSetMetadata              Pdf2PdfSetMetadataA
#define Pdf2PdfGetCategoryText          Pdf2PdfGetCategoryTextA
#define Pdf2PdfAddFontDirectory         Pdf2PdfAddFontDirectoryA
#define Pdf2PdfGetInfoEntry             Pdf2PdfGetInfoEntryA
#define Pdf2PdfSetInfoEntry             Pdf2PdfSetInfoEntryA
#define Pdf2PdfSetOCREngine             Pdf2PdfSetOCREngineA
#define Pdf2PdfSetOCRLanguages          Pdf2PdfSetOCRLanguagesA
#define Pdf2PdfSetOCRParams             Pdf2PdfSetOCRParamsA
#define Pdf2PdfGetOCRPluginName         Pdf2PdfGetOCRPluginNameA
#define Pdf2PdfExportText               Pdf2PdfExportTextA
#define Pdf2PdfSetToUnicodeFile         Pdf2PdfSetToUnicodeFileA
#define Pdf2PdfAddEmbeddedFile          Pdf2PdfAddEmbeddedFileA
#define Pdf2PdfAddAssociatedFile        Pdf2PdfAddAssociatedFileA
#define Pdf2PdfAddAssociatedFileMem     Pdf2PdfAddAssociatedFileMemA
#define Pdf2PdfAddZUGFeRDXml            Pdf2PdfAddZUGFeRDXmlA
#define Pdf2PdfAddInvoiceXml            Pdf2PdfAddInvoiceXmlA
#define Pdf2PdfAddInvoiceXmlMem         Pdf2PdfAddInvoiceXMLMemW

#define Pdf2PdfSignatureGetImageFileName    Pdf2PdfSignatureGetImageFileNameA
#define Pdf2PdfSignatureSetImageFileName    Pdf2PdfSignatureSetImageFileNameA
#define Pdf2PdfSignatureGetName             Pdf2PdfSignatureGetNameA
#define Pdf2PdfSignatureSetName             Pdf2PdfSignatureSetNameA
#define Pdf2PdfSignatureGetIssuer           Pdf2PdfSignatureGetIssuerA
#define Pdf2PdfSignatureSetIssuer           Pdf2PdfSignatureSetIssuerA
#define Pdf2PdfSignatureGetSerialNumber     Pdf2PdfSignatureGetSerialNumberA
#define Pdf2PdfSignatureSetSerialNumber     Pdf2PdfSignatureSetSerialNumberA
#define Pdf2PdfSignatureGetSignerFingerprintStr Pdf2PdfSignatureGetSignerFingerprintStrA
#define Pdf2PdfSignatureSetSignerFingerprintStr Pdf2PdfSignatureSetSignerFingerprintStrA
#define Pdf2PdfSignatureGetProvider         Pdf2PdfSignatureGetProviderA
#define Pdf2PdfSignatureSetProvider         Pdf2PdfSignatureSetProviderA
#define Pdf2PdfSignatureGetStore            Pdf2PdfSignatureGetStoreA
#define Pdf2PdfSignatureSetStore            Pdf2PdfSignatureSetStoreA
#define Pdf2PdfSignatureGetTimeStampURL     Pdf2PdfSignatureGetTimeStampURLA
#define Pdf2PdfSignatureSetTimeStampURL     Pdf2PdfSignatureSetTimeStampURLA
#define Pdf2PdfSignatureGetTimeStampCredentials Pdf2PdfSignatureGetTimeStampCredentialsA
#define Pdf2PdfSignatureSetTimeStampCredentials Pdf2PdfSignatureSetTimeStampCredentialsA
#define Pdf2PdfSignatureGetReason           Pdf2PdfSignatureGetReasonA
#define Pdf2PdfSignatureSetReason           Pdf2PdfSignatureSetReasonA
#define Pdf2PdfSignatureGetContactInfo      Pdf2PdfSignatureGetContactInfoA
#define Pdf2PdfSignatureSetContactInfo      Pdf2PdfSignatureSetContactInfoA
#define Pdf2PdfSignatureGetLocation         Pdf2PdfSignatureGetLocationA
#define Pdf2PdfSignatureSetLocation         Pdf2PdfSignatureSetLocationA
#define Pdf2PdfSignatureGetFontName1        Pdf2PdfSignatureGetFontName1A
#define Pdf2PdfSignatureSetFontName1        Pdf2PdfSignatureSetFontName1A
#define Pdf2PdfSignatureGetFontName2        Pdf2PdfSignatureGetFontName2A
#define Pdf2PdfSignatureSetFontName2        Pdf2PdfSignatureSetFontName2A
#define Pdf2PdfSignatureGetText1            Pdf2PdfSignatureGetText1A
#define Pdf2PdfSignatureSetText1            Pdf2PdfSignatureSetText1A
#define Pdf2PdfSignatureGetText2            Pdf2PdfSignatureGetText2A
#define Pdf2PdfSignatureSetText2            Pdf2PdfSignatureSetText2A
#define Pdf2PdfSignatureGetSubFilter        Pdf2PdfSignatureGetSubFilterA
#define Pdf2PdfSignatureSetSubFilter        Pdf2PdfSignatureSetSubFilterA

#endif

typedef struct TPdf2Pdf TPdf2Pdf;
typedef struct TPdf2PdfSignature TPdf2PdfSignature;

PDF2PDFAPI void PDF2PDFCALL Pdf2PdfInitialize();
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfUnInitialize();
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfTerminate();

PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetLicenseKeyA(const char* szLicenseKey);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetLicenseKeyW(const WCHAR* szLicenseKey);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetLicenseIsValid();

PDF2PDFAPI const char* PDF2PDFCALL Pdf2PdfGetProductVersionA();
PDF2PDFAPI const WCHAR* PDF2PDFCALL Pdf2PdfGetProductVersionW();

PDF2PDFAPI TPdf2Pdf* 
                PDF2PDFCALL Pdf2PdfCreateObject();
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfDestroyObject(TPdf2Pdf* handle); 

PDF2PDFAPI TPDFErrorCode
                PDF2PDFCALL Pdf2PdfGetErrorCode(TPdf2Pdf* handle);
PDF2PDFAPI const char*
                PDF2PDFCALL Pdf2PdfGetErrorMessageA(TPdf2Pdf* handle);
PDF2PDFAPI const WCHAR*
                PDF2PDFCALL Pdf2PdfGetErrorMessageW(TPdf2Pdf* handle);

PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetEmbedAllFonts(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetEmbedAllFonts(TPdf2Pdf* handle, int bEmbedAllFonts);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetSubsetFonts(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetSubsetFonts(TPdf2Pdf* handle, int bSubsetFonts);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetEmbedT1asCFF(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetEmbedT1asCFF(TPdf2Pdf* handle, int bEmbedT1asCFF);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetRemoveSignatures(TPdf2Pdf* handle);   /** deprecated, use ConversionErrorMask property */
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetRemoveSignatures(TPdf2Pdf* handle, int bRemoveSignatures);    /** deprecated, use ConversionErrorMask property */
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetColorSpaceProfileA(TPdf2Pdf* handle, const char* szColorSpaceProfile);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetColorSpaceProfileW(TPdf2Pdf* handle, const WCHAR* szColorSpaceProfile);
PDF2PDFAPI const char*
                PDF2PDFCALL Pdf2PdfGetColorSpaceProfileA(TPdf2Pdf* handle);
PDF2PDFAPI const WCHAR*
                PDF2PDFCALL Pdf2PdfGetColorSpaceProfileW(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOutputIntentProfileA(TPdf2Pdf* handle, const char* szOutputIntentProfile);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOutputIntentProfileW(TPdf2Pdf* handle, const WCHAR* szOutputIntentProfile);
PDF2PDFAPI const char*
                PDF2PDFCALL Pdf2PdfGetOutputIntentProfileA(TPdf2Pdf* handle);
PDF2PDFAPI const WCHAR*
                PDF2PDFCALL Pdf2PdfGetOutputIntentProfileW(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetImageQuality(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetImageQuality(TPdf2Pdf* handle, int iQuality);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetAnalyzeOnly(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetAnalyzeOnly(TPdf2Pdf* handle, int bOn);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetConvertAlways(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetConvertAlways(TPdf2Pdf* handle, int bOn);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetPostAnalyze(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetPostAnalyze(TPdf2Pdf* handle, int bOn);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetReportDetails(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetReportDetails(TPdf2Pdf* handle, int bOn);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetReportSummary(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetReportSummary(TPdf2Pdf* handle, int bOn);
PDF2PDFAPI TPDFCompliance
                PDF2PDFCALL Pdf2PdfGetCompliance(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetCompliance(TPdf2Pdf* handle, TPDFCompliance iCompliance);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetAllowDowngrade(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetAllowDowngrade(TPdf2Pdf* handle, int bAllow);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetAllowUpgrade(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetAllowUpgrade(TPdf2Pdf* handle, int bAllow);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetConversionErrors(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetConversionErrorMask(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetConversionErrorMask(TPdf2Pdf* handle, int iMask);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetFlattenSignatures(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetFlattenSignatures(TPdf2Pdf* handle, int bFlattenSignatures);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfBeginSessionA(TPdf2Pdf* handle, const char* szProvider);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfBeginSessionW(TPdf2Pdf* handle, const WCHAR* szProvider);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfEndSession(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetSessionPropertyStringA(TPdf2Pdf* handle, const char* szName, const char* szValue);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetSessionPropertyStringW(TPdf2Pdf* handle, const WCHAR* szName, const WCHAR* szValue);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetSessionPropertyBytesA(TPdf2Pdf* handle, const char* szName, const unsigned char* pData, size_t nSize);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetSessionPropertyBytesW(TPdf2Pdf* handle, const WCHAR* szName, const unsigned char* pData, size_t nSize);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfTestSession(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddSignature(TPdf2Pdf* handle, TPdf2PdfSignature* hSignature);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetNoCache(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetNoCache(TPdf2Pdf* handle, int bNoCache);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetMetadataA(TPdf2Pdf* handle, const char* szFileName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetMetadataW(TPdf2Pdf* handle, const WCHAR* szFileName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetMetadataStream(TPdf2Pdf* handle, TPDFStreamDescriptor* pStream);
PDF2PDFAPI const char*
                PDF2PDFCALL Pdf2PdfGetCategoryTextA(TPdf2Pdf* handle, TPDFConformanceCategory iCategory);
PDF2PDFAPI const WCHAR*
                PDF2PDFCALL Pdf2PdfGetCategoryTextW(TPdf2Pdf* handle, TPDFConformanceCategory iCategory);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertA(TPdf2Pdf* handle, const char* szInputFileName,
                                                              const char* szPassword,
                                                              const char* szOutputFileName,
                                                              const char* szLogFileName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertW(TPdf2Pdf* handle, const WCHAR* szInputFileName,
                                                              const WCHAR* szPassword,
                                                              const WCHAR* szOutputFileName,
                                                              const WCHAR* szLogFileName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertMemA(TPdf2Pdf* handle, const unsigned char* pIn, size_t nInSize,
                                                                 const char* szPassword,
                                                                 unsigned char** ppOut, size_t* pOutSize,
                                                                 unsigned char** ppLog, size_t* pLogSize);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertMemW(TPdf2Pdf* handle, const unsigned char* pIn, size_t nInSize,
                                                                 const WCHAR* szPassword,
                                                                 unsigned char** ppOut, size_t* pOutSize,
                                                                 unsigned char** ppLog, size_t* pLogSize);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertStreamA(TPdf2Pdf* handle, TPDFStreamDescriptor* pInputStream,
                                                                    const char* szPassword,
                                                                    TPDFStreamDescriptor* pOutputStream,
                                                                    TPDFStreamDescriptor* pLogStream);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfConvertStreamW(TPdf2Pdf* handle, TPDFStreamDescriptor* pInputStream,
                                                                    const WCHAR* szPassword,
                                                                    TPDFStreamDescriptor* pOutputStream,
                                                                    TPDFStreamDescriptor* pLogStream);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfFreeMem(void* pData);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddFontDirectoryA(const char* szDirectory);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddFontDirectoryW(const WCHAR* szDirectory);
PDF2PDFAPI const char*
                PDF2PDFCALL Pdf2PdfGetInfoEntryA(TPdf2Pdf* handle, const char* szKey);
PDF2PDFAPI const WCHAR*
                PDF2PDFCALL Pdf2PdfGetInfoEntryW(TPdf2Pdf* handle, const WCHAR* szKey);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetInfoEntryA(TPdf2Pdf* handle, const char* szKey, const char* szValue);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetInfoEntryW(TPdf2Pdf* handle, const WCHAR* szKey, const WCHAR* szValue);

PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCREngineA(TPdf2Pdf* handle, const char* szEngine);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCREngineW(TPdf2Pdf* handle, const WCHAR* szEngine);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRLanguagesA(TPdf2Pdf* handle, const char* szLanguages);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRLanguagesW(TPdf2Pdf* handle, const WCHAR* szLanguages);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRParamsA(TPdf2Pdf* handle, const char* szParams);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRParamsW(TPdf2Pdf* handle, const WCHAR* szParams);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRPluginCount(TPdf2Pdf* handle);
PDF2PDFAPI const char* PDF2PDFCALL Pdf2PdfGetOCRPluginNameA(TPdf2Pdf* handle, int iPlugin);
PDF2PDFAPI const WCHAR* PDF2PDFCALL Pdf2PdfGetOCRPluginNameW(TPdf2Pdf* handle, int iPlugin);
PDF2PDFAPI float PDF2PDFCALL Pdf2PdfGetOCRResolutionDPI(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRResolutionDPI(TPdf2Pdf* handle, float fDPI);
PDF2PDFAPI float PDF2PDFCALL Pdf2PdfGetOCRThresholdDPI(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRThresholdDPI(TPdf2Pdf* handle, float fDPI);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRBitonalRecognition(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRBitonalRecognition(TPdf2Pdf* handle, int bBitonal);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRMode(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetOCRMode(TPdf2Pdf* handle, int iMode);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfExportTextW(TPdf2Pdf* handle, const WCHAR* szFile);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfExportTextA(TPdf2Pdf* handle, const char* szFile);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCREmbedBarcodes(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCREmbedBarcodes(TPdf2Pdf* handle, int bEmbed);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRRotatePage(TPdf2Pdf* handle);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfSetOCRRotatePage(TPdf2Pdf* handle, int bRotate);

PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRReembedImages(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetOCRReembedImages(TPdf2Pdf* handle, int bValue); /*default is true (1)*/
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetOCRDeskewImage(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetOCRDeskewImage(TPdf2Pdf* handle, int bValue); /*default is true (1)*/
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetLinearize(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetLinearize(TPdf2Pdf* handle, int bValue); /* default is false (0)*/
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetTryConvertEmbPDF(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetTryConvertEmbPDF(TPdf2Pdf* handle, int bValue);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetToUnicodeFileA(TPdf2Pdf* handle, const char* szFileName);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetToUnicodeFileW(TPdf2Pdf* handle, const WCHAR* szFileName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddEmbeddedFileA(TPdf2Pdf* handle, const char* szFileName, const char* szName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddEmbeddedFileW(TPdf2Pdf* handle, const WCHAR* szFileName, const WCHAR* szName);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddAssociatedFileA(TPdf2Pdf* handle, const char* szFileName, const char* szName, int iAssociation, const char* szAFRelationship, const char* szMimeType, const char* szDescription, TPDFDate* pModDate);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddAssociatedFileW(TPdf2Pdf* handle, const WCHAR* szFileName, const WCHAR* szName, int iAssociation, const WCHAR* szAFRelationship, const WCHAR* szMimeType, const WCHAR* szDescription, TPDFDate* pModDate);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddAssociatedFileMemA(TPdf2Pdf* handle, const void* pData, size_t nSize, const char* szName, int iAssociation, const char* szAFRelationship, const char* szMimeType, const char* szDescription, TPDFDate* pModDate);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddAssociatedFileMemW(TPdf2Pdf* handle, const void* pData, size_t nSize, const WCHAR* szName, int iAssociation, const WCHAR* szAFRelationship, const WCHAR* szMimeType, const WCHAR* szDescription, TPDFDate* pModDate);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddZUGFeRDXmlA(TPdf2Pdf* handle, const char* szFileName); /** deprecated: use Pdf2PdfAddInvoiceXmlA instead */
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddZUGFeRDXmlW(TPdf2Pdf* handle, const WCHAR* szFileName); /** deprecated: use Pdf2PdfAddInvoiceXmlW instead */
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddZUGFeRDXmlMem(TPdf2Pdf* handle, const void* pData, size_t nSize); /** deprecated: use Pdf2PdfAddInvoiceXmlMem instead */
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddInvoiceXmlA(TPdf2Pdf* handle, TPDFInvoiceType iType, const char* szFileName, const char* szAFRelationship);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddInvoiceXmlW(TPdf2Pdf* handle, TPDFInvoiceType iType, const WCHAR* szFileName, const WCHAR* szAFRelationship);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddInvoiceXmlMemA(TPdf2Pdf* handle, TPDFInvoiceType iType, const void* pData, size_t nSize, const char* szAFRelationship);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfAddInvoiceXmlMemW(TPdf2Pdf* handle, TPDFInvoiceType iType, const void* pData, size_t nSize, const WCHAR* szAFRelationship);
PDF2PDFAPI int  PDF2PDFCALL Pdf2PdfGetForceEmbeddingOfCMaps(TPdf2Pdf* handle);
PDF2PDFAPI void PDF2PDFCALL Pdf2PdfSetForceEmbeddingOfCMaps(TPdf2Pdf* handle, int bValue);


PDF2PDFAPI TPdf2PdfSignature*
                   PDF2PDFCALL Pdf2PdfSignatureCreateObject();
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureDestroyObject(TPdf2PdfSignature* handle);

PDF2PDFAPI TPdf2PdfSignature*
				  PDF2PDFCALL  Pdf2PdfSignatureDupObject(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureFreeObject(TPdf2PdfSignature* handle);

PDF2PDFAPI int   PDF2PDFCALL Pdf2PdfSignatureGetPageNo(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetPageNo(TPdf2PdfSignature* handle, int iPageNo);
PDF2PDFAPI int   PDF2PDFCALL Pdf2PdfSignatureGetStrokeColor(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetStrokeColor(TPdf2PdfSignature* handle, int iColor);
PDF2PDFAPI int   PDF2PDFCALL Pdf2PdfSignatureGetFillColor(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFillColor(TPdf2PdfSignature* handle, int iColor);
PDF2PDFAPI float PDF2PDFCALL Pdf2PdfSignatureGetFontSize1(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontSize1(TPdf2PdfSignature* handle, float fFontSize);
PDF2PDFAPI float PDF2PDFCALL Pdf2PdfSignatureGetFontSize2(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontSize2(TPdf2PdfSignature* handle, float fFontSize);
PDF2PDFAPI float PDF2PDFCALL Pdf2PdfSignatureGetLineWidth(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetLineWidth(TPdf2PdfSignature* handle, float fLineWidth);
PDF2PDFAPI const TPDFRect*
                   PDF2PDFCALL Pdf2PdfSignatureGetRect(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetRect(TPdf2PdfSignature* handle, const TPDFRect* pRect);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetImageFileNameA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetImageFileNameW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetImageFileNameA(TPdf2PdfSignature* handle, const char* szFileName);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetImageFileNameW(TPdf2PdfSignature* handle, const WCHAR* szFileName);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetNameA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetNameW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetNameA(TPdf2PdfSignature* handle, const char* szName);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetNameW(TPdf2PdfSignature* handle, const WCHAR* szName);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetIssuerA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetIssuerW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetIssuerA(TPdf2PdfSignature* handle, const char* szIssuer);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetIssuerW(TPdf2PdfSignature* handle, const WCHAR* szIssuer);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetSerialNumberA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetSerialNumberW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSerialNumberA(TPdf2PdfSignature* handle, const char* szSerialNumber);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSerialNumberW(TPdf2PdfSignature* handle, const WCHAR* szSerialNumber);
PDF2PDFAPI int   PDF2PDFCALL Pdf2PdfSignatureGetEmbedRevocationInfo(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetEmbedRevocationInfo(TPdf2PdfSignature* handle, int bEmbed);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetProviderA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetProviderW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetProviderA(TPdf2PdfSignature* handle, const char* szStore);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetProviderW(TPdf2PdfSignature* handle, const WCHAR* szStore);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetStoreA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetStoreW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetStoreA(TPdf2PdfSignature* handle, const char* szStore);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetStoreW(TPdf2PdfSignature* handle, const WCHAR* szStore);
PDF2PDFAPI int   PDF2PDFCALL Pdf2PdfSignatureGetStoreLocation(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetStoreLocation(TPdf2PdfSignature* handle, int iLocation);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetTimeStampURLA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetTimeStampURLW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetTimeStampURLA(TPdf2PdfSignature* handle, const char* szTimeStampURL);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetTimeStampURLW(TPdf2PdfSignature* handle, const WCHAR* szTimeStampURL);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetTimeStampCredentialsA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetTimeStampCredentialsW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetTimeStampCredentialsA(TPdf2PdfSignature* handle, const char* szTimeStampCredentials);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetTimeStampCredentialsW(TPdf2PdfSignature* handle, const WCHAR* szTimeStampCredentials);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetReasonA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetReasonW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetReasonA(TPdf2PdfSignature* handle, const char* szReason);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetReasonW(TPdf2PdfSignature* handle, const WCHAR* szReason);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetContactInfoA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetContactInfoW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetContactInfoA(TPdf2PdfSignature* handle, const char* szContactInfo);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetContactInfoW(TPdf2PdfSignature* handle, const WCHAR* szContactInfo);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetLocationA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetLocationW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetLocationA(TPdf2PdfSignature* handle, const char* szLocation);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetLocationW(TPdf2PdfSignature* handle, const WCHAR* szLocation);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetFontName1A(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetFontName1W(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontName1A(TPdf2PdfSignature* handle, const char* szFontName);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontName1W(TPdf2PdfSignature* handle, const WCHAR* szFontName);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetFontName2A(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetFontName2W(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontName2A(TPdf2PdfSignature* handle, const char* szFontName);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFontName2W(TPdf2PdfSignature* handle, const WCHAR* szFontName);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFont1Mem(TPdf2PdfSignature* handle, const unsigned char* pData, size_t nSize);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetFont2Mem(TPdf2PdfSignature* handle, const unsigned char* pData, size_t nSize);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetText1A(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetText1W(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetText1A(TPdf2PdfSignature* handle, const char* szText);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetText1W(TPdf2PdfSignature* handle, const WCHAR* szText);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetText2A(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetText2W(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetText2A(TPdf2PdfSignature* handle, const char* szText);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetText2W(TPdf2PdfSignature* handle, const WCHAR* szText);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetSubFilterA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetSubFilterW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSubFilterA(TPdf2PdfSignature* handle, const char* szSubFilter);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSubFilterW(TPdf2PdfSignature* handle, const WCHAR* szSubFilter);
PDF2PDFAPI const TPDFByteArray* PDF2PDFCALL Pdf2PdfSignatureGetSignerFingerprint(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSignerFingerprint(TPdf2PdfSignature* handle, const unsigned char* pData, size_t nLength);
PDF2PDFAPI const char*
                   PDF2PDFCALL Pdf2PdfSignatureGetSignerFingerprintStrA(TPdf2PdfSignature* handle);
PDF2PDFAPI const WCHAR*
                   PDF2PDFCALL Pdf2PdfSignatureGetSignerFingerprintStrW(TPdf2PdfSignature* handle);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSignerFingerprintStrA(TPdf2PdfSignature* handle, const char* szHexString);
PDF2PDFAPI void  PDF2PDFCALL Pdf2PdfSignatureSetSignerFingerprintStrW(TPdf2PdfSignature* handle, const WCHAR* szHexString);

#ifdef __cplusplus
}
#endif

#endif /* _PDF2PDFAPI_H */

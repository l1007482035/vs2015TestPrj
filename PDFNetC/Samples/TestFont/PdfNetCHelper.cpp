#include "stdafx.h"
#include "PdfNetCHelper.h"


#include <SDF/Obj.h>
#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementBuilder.h>
#include <PDF/ElementWriter.h>
#include <PDF/ElementReader.h>

#include <Filters/MappedFile.h>
#include <Filters/FilterReader.h>

#include <SDF/SDFDoc.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")
#include<dwrite.h>
#pragma comment(lib,"dwrite.lib")
#include <sstream>

using namespace std;

BOOL CPdfNetCHelper::m_bHasInit = FALSE;


CPdfNetCHelper::CPdfNetCHelper()
{
}


CPdfNetCHelper::~CPdfNetCHelper()
{
}

BOOL CPdfNetCHelper::InitLib()
{
	if (m_bHasInit)
	{
		return TRUE;
	}
	BOOL bRet = TRUE;
	try
	{
		pdftron::PDFNet::Initialize();
	}
	catch (pdftron::Common::Exception& e)
	{
		bRet = FALSE;
		//theLog.Write("!!CPdfTronHelper::Init,fail,errmsg=%s", e.ToString().c_str());
	}
	m_bHasInit = TRUE;
	return bRet;
}

BOOL CPdfNetCHelper::ReleaseLib()
{
	if (!m_bHasInit)
	{
		return TRUE;
	}

	BOOL bRet = TRUE;
	try
	{
		pdftron::PDFNet::Terminate();
	}
	catch (pdftron::Common::Exception& e)
	{
		bRet = FALSE;
		//theLog.Write("!!CPdfTronHelper::ReleaseLib,fail,errmsg=%s", e.ToString().c_str());
	}
	m_bHasInit = FALSE;
	return bRet;

}

BOOL CPdfNetCHelper::GetSysFontInfoByName(std::wstring& wsFontNameZh, std::wstring& wsFontNameEn, std::wstring& wsFontPath, const std::wstring wsFontName)
{
	BOOL bRet = FALSE;
	IDWriteFontCollection* pFontCollection = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteFontFamily* pFontFamily = NULL;
	IDWriteLocalizedStrings* pFamilyNames = NULL;
	HRESULT hr = S_OK;
	do 
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory));
		if (FAILED(hr) || !pDWriteFactory)
		{
			break;
		}

		hr = pDWriteFactory->GetSystemFontCollection(&pFontCollection);
		if (FAILED(hr) || !pFontCollection)
		{
			break;
		}
		UINT32 nIdx = -1;
		BOOL bExist = FALSE;
		hr = pFontCollection->FindFamilyName(wsFontName.c_str(), &nIdx, &bExist);
		if (FAILED(hr) || !bExist)
		{
			break;
		}
		
		hr = pFontCollection->GetFontFamily(nIdx, &pFontFamily);

		if (FAILED(hr) || !pFontFamily)
		{
			break;
		}
		
		hr = pFontFamily->GetFamilyNames(&pFamilyNames);
		if (FAILED(hr) || !pFamilyNames)
		{
			break;
		}
		UINT32 nLength = 0;
		UINT32 nLangIdex = 0;
		hr = pFamilyNames->GetStringLength(nLangIdex, &nLength);
		wchar_t* pNameEn = new wchar_t[nLength + 1];
		pFamilyNames->GetString(nLangIdex, pNameEn, nLength + 1);
		wsFontNameEn = pNameEn;
		delete[] pNameEn;
		pNameEn = NULL;
		//wprintf(L"===============wsFontNameEn=%s\n", wsFontNameEn.c_str());

		bExist = FALSE;
		wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
		// Get the default locale for this user.
		int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
		if (!defaultLocaleSuccess)
		{
			break;
		}
		hr = pFamilyNames->FindLocaleName(localeName, &nLangIdex, &bExist);
		if (FAILED(hr) || !bExist)
		{
			hr = pFamilyNames->FindLocaleName(L"en-us", &nLangIdex, &bExist);
		}
		if (!bExist)
		{
			nLangIdex = 0;
		}
		nLength = 0;

		if (FAILED(hr))
		{
			break;
		}
		hr = pFamilyNames->GetStringLength(nLangIdex, &nLength);
		if (FAILED(hr))
		{
			break;
		}

		wchar_t* pNameZh = new wchar_t[nLength + 1];

		hr = pFamilyNames->GetString(nLangIdex, pNameZh, nLength + 1);
		wsFontNameZh = pNameZh;
		//wprintf(L"===============wsFontNameZh=%s\n", wsFontNameZh.c_str());
		delete[] pNameZh;
		pNameZh = NULL;

		if (!GetSysFontPathByName(wsFontPath, wsFontNameEn))
		{
			if (!GetSysFontPathByName(wsFontPath, wsFontNameZh))
			{
			}
			
		}
		if (wsFontPath.empty())
		{
			break;
		}

		bRet = TRUE;

	} while (0);

	if (pFamilyNames)
	{
		pFamilyNames->Release();
		pFamilyNames = NULL;
	}
	if (pFontFamily)
	{
		pFontFamily->Release();
		pFontFamily = NULL;
	}
	if (pFontCollection)
	{
		pFontCollection->Release();
		pFontCollection = NULL;
	}
	if (pDWriteFactory)
	{
		pDWriteFactory->Release();
		pDWriteFactory = NULL;
	}

	return bRet;
}

BOOL CPdfNetCHelper::GetSysFontPathByName(std::wstring& wsFontPath, const std::wstring wsFontName)
{

	wsFontPath.clear();
	BOOL bRet = FALSE;
	LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;

	// Open Windows font registry key
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		return bRet;
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS) {
		return bRet;
	}

	DWORD valueIndex = 0;
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD valueNameSize, valueDataSize, valueType;

	// Look for a matching font name
	do {

		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ) {
			continue;
		}

		std::wstring wsValueName(valueName, valueNameSize);

		// Found a match
		if (_wcsnicmp(wsFontName.c_str(), wsValueName.c_str(), wsFontName.length()) == 0) {

			wsFontPath.assign((LPWSTR)valueData, valueDataSize);
			break;
		}
	} while (result != ERROR_NO_MORE_ITEMS);

	delete[] valueName;
	delete[] valueData;

	RegCloseKey(hKey);

	if (wsFontPath.empty()) {
		return bRet;
	}

	// Build full font file path
	WCHAR winDir[MAX_PATH];
	GetWindowsDirectory(winDir, MAX_PATH);

	std::wstringstream ss;
	ss << winDir << "\\Fonts\\" << wsFontPath;
	wsFontPath = ss.str();
	bRet = TRUE;

	return bRet;
}

BOOL CPdfNetCHelper::Pdf2EmbeddedFontPdf(const std::string sInPdfPath, const std::string sOutPdfPath)
{

}

BOOL CPdfNetCHelper::IsPdfA(const std::string sPdfPath)
{

}

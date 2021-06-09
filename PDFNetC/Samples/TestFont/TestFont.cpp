// TestFont.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestFont.h"

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
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include "PdfNetCHelper.h"


#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")


using namespace std;
using namespace pdftron;
using namespace SDF;
using namespace PDF;
using namespace Filters;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
static map<Unicode, string> fontmap;

wstring ConvertToUnicodeStr(string sStrOri);
wstring s2ws(const string& s);
string& replace_str(string& str, const string& to_replaced, const string& newchars);

std::vector<std::string> split(std::string s, std::string delimiter)
{
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	if (int(s.length()) > 0)
	{
		tokens.push_back(s);
	}
	return tokens;
}

void LoadGlyphlist(map<Unicode, string>& fontmapTmp)
{
	ifstream in("glyphlist.txt");
	string line;

	if (in) // 有该文件
	{
		while (getline(in, line)) // line中不包括每行的换行符
		{
			//cout << line << endl;

			if (line.find("#") == string::npos)
			{
				//cout <<"========"<< line << endl;
				std::vector<std::string> sArry = split(line, ";");
				//printf("=========size=%d\n", sArry.size());
				if (sArry.size() == 2)
				{
					//printf("=========ary[0]=%s,ary[1]=%s\n", sArry.at(0).c_str(), sArry.at(1).c_str());

					char* str;
					Unicode i = strtol(sArry.at(1).c_str(), &str, 16);
					map<Unicode, string>::iterator itr = fontmap.find(i);
					if (itr == fontmap.end())
					{
						fontmap.insert(make_pair(i, sArry.at(0)));
					}


				}


			}

		}
	}
}

string GetGlyphname(Unicode sUniWithU)
{
	string sName = "";
	map<Unicode, string>::iterator itr = fontmap.find(sUniWithU);
	if (itr != fontmap.end())
	{
		sName = itr->second;
	}
	return sName;
}

string& replace_str(string& str, const string& to_replaced, const string& newchars)
{
	for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
	return   str;
}


Obj RemapFontEncoding(PDFDoc& doc,Font fontOld)
{
	Obj encoding_dict = doc.CreateIndirectDict();
	Obj diffs = encoding_dict.PutArray("Differences");
	for (int i = 0; i < 256; ++i)
	{
		UString usUnicode = fontOld.MapToUnicode(i);
		string sUnicode = usUnicode.ConvertToAscii();

		printf("RemapFontEncoding,sUnicode=%s\n", sUnicode.c_str());

		if (sUnicode.find("\\U") != string::npos)
		{
			string sUnicodeNew = replace_str(sUnicode, "\\U", "");
			Unicode uni = strtol(sUnicodeNew.c_str(), NULL, 16);
			if (uni == 0xfffd)
			{
				continue;
			}
			string glyph_name = GetGlyphname(uni);
			printf("========RemapFontEncoding,3.1,glyph_name=%s\n", glyph_name.c_str());
			diffs.PushBackNumber(uni);
			diffs.PushBackName(glyph_name.c_str());
		}
		else if (sUnicode.length() == 1)
		{
			char cAscii = sUnicode.at(0);
			string glyph_name = GetGlyphname(cAscii);
			printf("========RemapFontEncoding,3.2,cAscii=%c,cAscii=0x%x,glyph_name=%s\n", cAscii, cAscii, glyph_name.c_str());
			diffs.PushBackNumber(cAscii);
			diffs.PushBackName(glyph_name.c_str());
		}



	}
	printf("========RemapFontEncoding,4\n");
	return diffs;
}



void ProcessDict(Obj obj)
{
#if 1
	if (obj.IsStream() || obj.IsDict())
	{
		DictIterator itr = obj.Find("Subtype");
		if (itr.HasNext())
		{
			const char*pKeyName = itr.Key().GetName();
			const char*pName = itr.Value().GetName();
			printf("=============Subtype,pKeyName=%s,pName=%s\n", pKeyName, pName);
		}
		itr = obj.Find("Type");
		if (itr.HasNext())
		{
			const char*pKeyName = itr.Key().GetName();
			const char*pName = itr.Value().GetName();
			printf("=============Type,pKeyName=%s,pName=%s\n", pKeyName, pName);
		}
	}
	

#endif
#if 1
	if (obj.GetType() == Obj::e_dict || obj.GetType() == Obj::e_stream)
	{
		DictIterator itr = obj.GetDictIterator();
		for (itr;itr.HasNext();itr.Next())
		{
			Obj objKey = itr.Key();
			Obj obj1 = itr.Value();
			int nKeyType = objKey.GetType();
			//printf("nKeyType=%d\n", nKeyType);
			if (nKeyType == Obj::e_name)
			{
				const char*pKeyName = objKey.GetName();
				printf("KeyName=%s\n", pKeyName);

				if (strcmp(pKeyName, "Font") == 0)
				{
					//Font font = Font(obj);
					//const char* pFontName = font.GetName();
					//printf("================pFontName=%s\n", pFontName);
				}
			}
			
			ProcessDict(obj1);
		}
	
	}
	else if (obj.GetType() == Obj::e_name)
	{
		const char* pName = obj.GetName();
		printf("================pName=%s\n", pName);
		
	}
#endif

}

#define  TESTFONT 1

int CALLBACK EnumFontFamProc(LPENUMLOGFONT lpelf, LPNEWTEXTMETRIC lpntm, DWORD nFontType, long lparam)
{
	wchar_t *pFontName = lpelf->elfLogFont.lfFaceName;
	wchar_t *pFontNameFull = lpelf->elfFullName;
	wchar_t *pFontNameStyle = lpelf->elfStyle ;

	wprintf(L"font name=%s,pFontNameFull=%s,pFontNameStyle=%s\n",pFontName, pFontNameFull, pFontNameStyle);
	return 1;
}

int CALLBACK NEnumFontNameProc(LOGFONT* plf, TEXTMETRIC* /*ptm*/, INT /*nFontType*/, LPARAM lParam/**/)
{
	
	wchar_t *pName2 = plf->lfFaceName;

	wprintf(L"NEnumFontNameProc,font pName2=%s\n", pName2);

	return 1; //EnumFontFamilies 返回值由此回调返回决定
}

void GetFont()
{
	LOGFONT lf;
	//lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfCharSet = ANSI_CHARSET;
	wcscpy(lf.lfFaceName, L"");
	//CClientDC dc(this);   
	CClientDC dc(NULL);
	HDC DD;

	static std::map<std::string, std::string> mapLocToEnglish;

	::EnumFontFamiliesEx((HDC)dc, NULL,(FONTENUMPROC)EnumFontFamProc, 0, 0);

	//::EnumFonts((HDC)dc, (LPTSTR)NULL, (FONTENUMPROC)NEnumFontNameProc, 0);
	
}

#include<dwrite.h>
#pragma comment(lib,"dwrite.lib")
#include <sstream>


std::wstring GetSystemFontFile(const std::wstring &faceName) 
{

	std::wstring wsFontFile;

	static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;
	std::wstring wsFaceName(faceName.begin(), faceName.end());

	// Open Windows font registry key
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		return L"";
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS) {
		return L"";
	}

	DWORD valueIndex = 0;
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD valueNameSize, valueDataSize, valueType;

	// Look for a matching font name
	do {

		wsFontFile.clear();
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ) {
			continue;
		}

		std::wstring wsValueName(valueName, valueNameSize);

		// Found a match
		if (_wcsnicmp(wsFaceName.c_str(), wsValueName.c_str(), wsFaceName.length()) == 0) {

			wsFontFile.assign((LPWSTR)valueData, valueDataSize);
			break;
		}
	} while (result != ERROR_NO_MORE_ITEMS);

	delete[] valueName;
	delete[] valueData;

	RegCloseKey(hKey);

	if (wsFontFile.empty()) {
		return L"";
	}

	// Build full font file path
	WCHAR winDir[MAX_PATH];
	GetWindowsDirectory(winDir, MAX_PATH);

	std::wstringstream ss;
	ss << winDir << "\\Fonts\\" << wsFontFile;
	wsFontFile = ss.str();

	return wsFontFile;
}

void GetSystemFont() {
	std::map<std::wstring, std::wstring> m_systemFonts;
	m_systemFonts.clear();

	IDWriteFontCollection* pFontCollection = NULL;

	// Get the system font collection.
	HRESULT hr = S_OK;
	IDWriteFactory* pDWriteFactory = NULL;

	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory));
	}

	// Get the system font collection.
	if (SUCCEEDED(hr))
	{
		hr = pDWriteFactory->GetSystemFontCollection(&pFontCollection);
	}
	UINT32 familyCount = 0;
	// Get the number of font families in the collection.
	if (SUCCEEDED(hr))
	{
		familyCount = pFontCollection->GetFontFamilyCount();
	}

	for (UINT32 i = 0; i < familyCount; ++i) {
		IDWriteFontFamily* pFontFamily = NULL;
		// Get the font family.
		if (SUCCEEDED(hr))
		{
			//if (i != 300)
			//{
			//	continue;
			//}
			wprintf(L"=======i=%d\n",i);
			IDWriteLocalizedStrings* pFamilyNames = NULL;
			hr = pFontCollection->GetFontFamily(i, &pFontFamily);
			// Get a list of localized strings for the family name.
			if (SUCCEEDED(hr))
			{
				hr = pFontFamily->GetFamilyNames(&pFamilyNames);
			}

			UINT32 index = 0;
			BOOL exists = false;
			if (!exists)
				index = 0;

			UINT32 length = 0;
			// Get the string length.
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetStringLength(index, &length);
				wprintf(L"====================1,index=%d,length=%d\n", index, length);
			}

			// Allocate a string big enough to hold the name.
			wchar_t* name = new wchar_t[length + 1];
			std::wstring sname;
			std::wstring sname_unicode;
			std::wstring fpath;
			// Get the family name.
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetString(index, name, length + 1);
				wprintf(L"====================2,index=%d,length=%d,name=%s\n", index, length, name);
				//sname 为英文名
				sname = std::wstring(name);

				wprintf(L"====================3,name=%s,sname=%s\n",name, sname.c_str());
				fpath = GetSystemFontFile(sname);
				wprintf(L"====================4,fpath=%s\n", fpath.c_str());
// 				if (fpath.empty()) {
// 					continue;
// 				} //todol
			}

			wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
			if (SUCCEEDED(hr))
			{
				// Get the default locale for this user.
				int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
				wprintf(L"====================5,localeName=%s,defaultLocaleSuccess=%d\n", localeName, defaultLocaleSuccess);
				//If the default locale is returned, find that locale name, otherwise use "en-us".
				if (defaultLocaleSuccess)
				{
					hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
				}
				wprintf(L"====================5,localeName=%s,index=%d,exist=%d\n", localeName, index, exists);
				if (SUCCEEDED(hr) && !exists) // if the above find did not find a match, retry with US English
				{
					hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
				}

			}
			// If the specified locale doesn't exist, select the first on the list.
			if (!exists)
				index = 0;

			length = 0;
			// Get the string length.
			wprintf(L"====================6,index=%d,length=%d\n", index, length);
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetStringLength(index, &length);
			}
			wprintf(L"====================7,index=%d,length=%d\n", index, length);
			// Get the family name.
			if (SUCCEEDED(hr))
			{
				wprintf(L"====================8,index=%d,length=%d,name=%s\n", index, length, name);
				hr = pFamilyNames->GetString(index, name, length + 1);
				wprintf(L"====================9,name=%s\n", name);
				//sname_unicode为对应的中文名
				sname_unicode = std::wstring(name);

				if (fpath.empty())
				{
					fpath = GetSystemFontFile(sname);
				}
				

				wprintf(L"====================10,sname_unicode=%s\n", sname_unicode.c_str());
				m_systemFonts[sname_unicode] = fpath;

			}
			wprintf(L"====================11,sname_unicode=%s,fpath=%s\n", sname_unicode.c_str(),fpath.c_str());
			delete[]name;


			if (pFontFamily)
			{
				pFontFamily->Release();
				pFontFamily = NULL;
			}
			if (pFamilyNames)
			{
				pFamilyNames->Release();
				pFamilyNames = NULL;
			}
		}
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
}









int main()
{
	setlocale(LC_ALL, "chs");
    int nRetCode = 0;
	LoadGlyphlist(fontmap);

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
			
            // TODO: 在此处为应用程序的行为编写代码。
			string input_path = "./";
			string output_path = "./";
			string input_filename = "ori.pdf";
			string output_filename = "ori_edit.pdf";

			try
			{
				PDFNet::Initialize();
				PDFNet::AddFontSubst(PDFNet::e_Identity, "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/AdobeSongStd-Light.otf");
				PDFNet::AddFontSubst("ddddddd", "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/AdobeSongStd-Light.otf");
				PDFNet::AddFontSubst(PDFNet::e_GB1, "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/fangzheng_GBK.TTF");

				

				PDFDoc doc(input_path + input_filename);
				doc.InitSecurityHandler();

				//Font font1 = Font::CreateCIDTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str(),true,false);  //乱码
				//Font font1 = Font::CreateTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);//adobe不乱码 福昕乱码
				//Font font1 = Font::CreateTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str(), true, true);
				//Font font1 = Font::CreateCIDTrueTypeFont(doc, (input_path + "fangzheng_GBK.TTF").c_str(), true, false);
				//Font fontnew = Font::CreateCIDTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
#if TESTFONT
			Font fontnew = Font::CreateCIDTrueTypeFont(doc, (input_path + "fangzheng_GBK.TTF").c_str(), true, false);

			printf("======fontname=%s\n", fontnew.GetName());

			//GetSystemFont();
#if 0
			{//test
				wstring wsZH;
				wstring wsEN;
				wstring wsPath;
				BOOL bRet1 = CPdfNetCHelper::GetSysFontInfoByName(wsZH, wsEN, wsPath, L"方正黑体_GBK");
				wprintf(L"===========1,bRet1=%d,wsZH=%s,wsPath=%s,wsPath=%s\n", bRet1, wsZH.c_str(), wsEN.c_str(), wsPath.c_str());
				BOOL bRet2 = CPdfNetCHelper::GetSysFontInfoByName(wsZH, wsEN, wsPath, L"FZHei-B01");
				wprintf(L"===========2,bRet2=%d,wsZH=%s,wsPath=%s,wsPath=%s\n", bRet2, wsZH.c_str(), wsEN.c_str(), wsPath.c_str());
				BOOL bRet3 = CPdfNetCHelper::GetSysFontInfoByName(wsZH, wsEN, wsPath, L"宋体");
				wprintf(L"===========2,bRet3=%d,wsZH=%s,wsPath=%s,wsPath=%s\n", bRet3, wsZH.c_str(), wsEN.c_str(), wsPath.c_str());

				
			
			}

#endif
			printf("==============1\n");
			GetFont();
			printf("==============2\n");

			return 0;


#if 0
				unsigned int max_char_code = fontnew.IsSimple() ? 0xFF : 0XFFFF;

				for (int i = 0; i < max_char_code; i++)
				{
					UString usStr = fontnew.MapToUnicode(i);
					printf("=============new,usStr=%s\n", usStr.ConvertToAscii().c_str());
				}



				const char*pFontName1 = fontnew.GetName();
				int nFontType1 = fontnew.GetType();
				printf("===========pFontName1=%s,nFontType1=%d\n", pFontName1, nFontType1);


				if (nFontType1 != Font::e_Type0)
				{
					const char** pEncoded = fontnew.GetEncoding();

					if (pEncoded)
					{
						for (int i = 0; i < 256; i++)
						{
							printf("=============new font,encoding,pEncoded[%d]=%s\n", i,pEncoded[i]);
						}
					}
					
				}

				Common::Iterator<UInt32> itr1 = fontnew.GetCharCodeIterator();

				for (; itr1.HasNext(); itr1.Next())
				{
					int nCharCode = itr1.Current();
					printf("=============nCharCode=0x%x\n", nCharCode);
					
				}
				printf("============end,1\n");
#endif

				SDFDoc& cos_doc1 = doc.GetSDFDoc();
				int num_objs1 = cos_doc1.XRefSize();
				for (int i = 1; i < num_objs1; ++i)
				{
					Obj obj0 = cos_doc1.GetObj(i);
					if (obj0 != NULL && !obj0.IsFree() && (obj0.IsDict() || obj0.IsStream()))
					{
					

						DictIterator itr = obj0.Find("Type");
						if (!itr.HasNext())
						{
							continue;
						}
						if (!itr.Value().IsName())
						{
							continue;
						}
						const char *pValName = itr.Value().GetName();
						printf("=========pValName=%s\n", pValName);
						if (strcmp(pValName, "Font"))
						{
							continue;
						}

						//printf("==========1\n");
						Font fontold = Font(obj0);
						const char *pKeyName =  itr.Key().GetName();
						printf("==========2,pKeyName=%s,fontname=%s,isEmbedded=%d,type=%d\n", pKeyName,fontold.GetName(), fontold.IsEmbedded(), fontold.GetType());

						Obj fd = fontold.GetDescriptor();
						printf("======fd=%x\n", fd);

						if (fd.FindObj("EU-BZ") != NULL)
						{
							printf("=====OOOOOOOOOOOOOOOO\n");
							//fd.Erase("FontFile2");
						}


						if (!fontold.IsEmbedded())
						{
							
							if (strcmp(fontold.GetName(), "方正黑体_GBK") == 0 && fontold.GetType() == Font::e_Type0)
							{
						
#if 0
								Common::Iterator<UInt32> itrTmp = fontold.GetCharCodeIterator();
								for (itrTmp;itrTmp.HasNext();itrTmp.Next())
								{
									int nCharCodeOld = itrTmp.Current();
									printf("=============nCharCodeOld=%d\n", nCharCodeOld);
								}
								printf("============end,2\n");
								
								unsigned int max_char_code = fontold.IsSimple() ? 0xFF: 0XFFFF;

								for (int i = 0; i < max_char_code; i++)
								{
									UString usStr = fontold.MapToUnicode(i);
									//printf("=============usStr=%s\n", usStr.ConvertToAscii().c_str());
								}
								//fontold.GetGlyphPath();
#endif

							}
				
						}
					}
				}




				doc.Close();
				PDFNet::Terminate();
				return 0;

#endif


				//========================test=======================
				//SDF::SDFDoc sdfdoc = doc.GetSDFDoc();



				SDFDoc& cos_doc = doc.GetSDFDoc();
				int num_objs = cos_doc.XRefSize();
				for (int i = 1; i < num_objs; ++i)
				{
					Obj obj0 = cos_doc.GetObj(i);
					if (obj0 != NULL && !obj0.IsFree() && (obj0.IsDict() || obj0.IsStream()))
					{
						//ProcessDict(obj0);

						DictIterator itr = obj0.Find("Type");
						if (!itr.HasNext() ||
							!itr.Value().IsName() ||
							strcmp(itr.Value().GetName(), "Font")) continue;

						//printf("==========1\n");
						Font fontold = Font(obj0);
						printf("==========2,fontname=%s,isEmbedded=%d,type=%d\n", fontold.GetName(), fontold.IsEmbedded(), fontold.GetType());
						if (!fontold.IsEmbedded())
						{
					
							if (strcmp(fontold.GetName(),"方正黑体_GBK") == 0 && fontold.GetType() == Font::e_Type0)
							{

								//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
								//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "fangzheng_GBK.TTF").c_str(), true, false);
								//Font fontnew = Font::CreateType1Font(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true);
								Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true,false);


								//LOGFONTW logfont;
								//logfont.lfCharSet = GB2312_CHARSET;
								//lstrcpy(logfont.lfFaceName, _T("Arial"));
			
								//Font fontnew = Font::CreateCIDTrueTypeFont2Unicode(doc.GetSDFDoc(), &logfont,true,false);
		
								
								bool bNewSimple = fontnew.IsSimple();
								bool bOldSimple = fontold.IsSimple();
								printf("=============bNewSimple=%d,bOldSimple=%d\n", bNewSimple, bOldSimple);
								//Font fontnew = Font::CreateTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
								//Font fontnew = Font::Create(doc.GetSDFDoc(), "华文仿宋", UString(string("GBK"),UString::e_utf16be_enc));//UTF-8  错误
								//Font fontnew = Font::Create(doc.GetSDFDoc(),Font::e_helvetica_bold,true);
								//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false,Font::e_Indices);//生成不了文字
								//Font fontnew = Font::Create(,);
								Obj new_font_obj = fontnew.GetSDFObj();
								//new_font_obj.Put("Encoding", RemapFontEncoding(doc, fontold));
								//new_font_obj.PutName("Encoding", "GBK-EUC-H");//GBK-EUC-H
						
								
								//	Obj widths = obj0.FindObj("Widths");
								// 								if (widths != NULL) {
								// 									new_font_obj.Put("Widths", widths);
								// 								}
								
								cos_doc.Swap(new_font_obj.GetObjNum(), obj0.GetObjNum());
								printf("===========4\n");

							}
						}


					}
					



				}


				doc.Save(output_path + output_filename, SDFDoc::e_remove_unused,0);
			
				doc.Close();
				
			

			
				


				doc.Close();
				PDFNet::Terminate();

			}
			catch (Common::Exception& e)
			{
				cout << e << endl;
				nRetCode = 1;
			}
			catch (...)
			{
				cout << "Unknown Exception" << endl;
				nRetCode = 1;
			}
		

		

        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}

wstring ConvertToUnicodeStr(string sStrOri)
{
	transform(sStrOri.begin(), sStrOri.end(), sStrOri.begin(), ::tolower);
	unsigned char ucUnicode[2] = { 0 };	//可以保存一个Unicode字符和一个结束符
	int nCurrent = 0;
	int nUnicodeLen = sStrOri.length();
	wstring sRet;
	while (nCurrent < nUnicodeLen)
	{

		//在以上两种路径中，可能出现解析出问题的情况，json对【\】会转义成【\\】,所以跳过【\\】
		//if (szUnicode.GetAt(nCurrent) == '\\' && szUnicode.GetAt(nCurrent + 1) == '\\')
		if (sStrOri.at(nCurrent) == '\\' && (nCurrent + 1 < nUnicodeLen) && sStrOri.at(nCurrent + 1) == 'u')
		{
			ucUnicode[0] = strtol(sStrOri.substr(nCurrent + 4, 2).c_str(), NULL, 16);
			ucUnicode[1] = strtol(sStrOri.substr(nCurrent + 2, 2).c_str(), NULL, 16);

			nCurrent += 6;
			wchar_t tmp[2] = { 0 };
			memcpy(tmp, ucUnicode, sizeof(wchar_t));
			sRet.append(tmp);
		}
		else
		{
			char c = sStrOri.at(nCurrent);
			nCurrent += 1;
			wchar_t tmp[2] = { 0 };
			memcpy(tmp, &c, 1);
			sRet.append(tmp);

		}
	}
	return sRet;
}

wstring s2ws(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}




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

wstring ConvertToUnicodeStr(string sStrOri);
wstring s2ws(const string& s);

int main()
{
	setlocale(LC_ALL, "chs");
    int nRetCode = 0;

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

			try
			{
				PDFNet::Initialize();
				PDFDoc doc(input_path + input_filename);
				doc.InitSecurityHandler();

				Font font1 = Font::CreateCIDTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str());
				Font font2 = Font::CreateCIDTrueTypeFont(doc, (input_path + "fangzheng_GBK.TTF").c_str());
				const char*pFontName1 = font1.GetName();
				int nFontType1 = font1.GetType();

				const char*pFontName2 = font2.GetName();
				int nFontType2 = font2.GetType();

				printf("===========pFontName1=%s,nFontType1=%d\n", pFontName1, nFontType1);
				printf("===========pFontName2=%s,nFontType2=%d\n", pFontName2, nFontType2);

				if (nFontType1 !=Font::e_Type0)
				{
					const char** pEncoded = font1.GetEncoding();
				}

				Common::Iterator<UInt32> itr1 = font1.GetCharCodeIterator();

				for (; itr1.HasNext(); itr1.Next())
				{
					int nCharCode = itr1.Current();
					UString usUincode = font2.MapToUnicode(nCharCode);
					string sUnicode = usUincode.ConvertToAscii();
					wstring wsUnicode = ConvertToUnicodeStr(sUnicode);
					wprintf(L"=====font1,nCharCode=%d,sUnicode=%s,wsUnicode=%s\n",nCharCode, s2ws(sUnicode).c_str(),wsUnicode.c_str());
				}

				for (int i = 0; i < 256; i++)
				{
					UString usUincode = font2.MapToUnicode(i);
					string sUnicode = usUincode.ConvertToAscii();
					wstring wsUnicode = ConvertToUnicodeStr(sUnicode);
					wprintf(L"=====font1,i=%d,sUnicode=%s,wsUnicode=%s\n", i, s2ws(sUnicode).c_str(), wsUnicode.c_str());
				}
#if 0
				Common::Iterator<UInt32> itr2 = font2.GetCharCodeIterator();
				for (; itr2.HasNext(); itr2.Next())
				{
					int nCharCode = itr2.Current();

					UString usUincode = font2.MapToUnicode(nCharCode);
					string sUnicode = usUincode.ConvertToAscii();
					wstring wsUnicode = ConvertToUnicodeStr(sUnicode);
					wprintf(L"=====font2,nCharCode=%d,sUnicode=%s,wsUnicode=%s\n", nCharCode, s2ws(sUnicode).c_str(), wsUnicode.c_str());
				}
#endif


				//========================test=======================

				int nIdx = 0;
				for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
				{
					printf("============page[%d]\n",++nIdx);
					Page page = itr.Current();
					Obj res = page.GetResourceDict();
					if (res != NULL)
					{
						printf("============2\n");

						DictIterator itr = res.GetDictIterator();
						for (;itr.HasNext();itr.Next())
						{
							Obj oValue = itr.Value();
							Obj oKey = itr.Key();
							if (oKey.GetType() == Obj::e_string)
							{
								printf("============1,is string=%s\n",oKey.GetName());
							}
							else if (oKey.GetType() == Obj::e_name)
							{
								printf("============is e_name=%s\n", oKey.GetName());
							}
						}

						Obj fonts = res.FindObj("Font");

						if (fonts != NULL)
						{
							printf("============3\n");
// 							DictIterator itr = fonts.d;
// 							DictIterator end = fonts.DictEnd();
// 
// 							for (; itr != end; itr.Next())
// 							{
// 								Obj fnt_dict = itr.Value();
// 								pdftron.PDF.Font font = new pdftron.PDF.Font(fnt_dict);
// 								if (font.IsEmbedded()) continue;
// 							}
						}
					}

				}

				//doc.Save(output_path + output_filename, SDFDoc::e_remove_unused | SDFDoc::e_hex_strings, 0);
			
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

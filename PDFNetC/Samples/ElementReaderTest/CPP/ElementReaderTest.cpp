//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1600)

# pragma execution_character_set("utf-8")

#endif

#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementReader.h>
#include <PDF/Element.h>
#include <iostream>
#include <algorithm>

using namespace pdftron;
using namespace std;
using namespace PDF;

//反斜杠Unicode转换成多字节,//【测试\u6d4b\u8bd5】=【测试测试】
string BslashUnicodeToMultiByte(string szUnicode)
{
	string szRet = "";
	unsigned char ucUnicode[4] = { 0 };	//可以保存一个Unicode字符和一个结束符
	int nCurrent = 0;
	int nUnicodeLen = szUnicode.length();
	while (nCurrent < nUnicodeLen)
	{
		//"file_path":"E:\\\\\u672c.doc"
		//"file_path":"E:\\usb.doc"
		//在以上两种路径中，可能出现解析出问题的情况，json对【\】会转义成【\\】,所以跳过【\\】
		//if (szUnicode.GetAt(nCurrent) == '\\' && szUnicode.GetAt(nCurrent + 1) == '\\')
		if (szUnicode.at(nCurrent) == '\\' && szUnicode.at(nCurrent + 1) == '\\')
		{
			//szRet.append(szUnicode. Mid(nCurrent, 2));
			szRet.append(szUnicode.substr(nCurrent, 2));
			nCurrent += 2;
			continue;
		}

		//if ((szUnicode.Mid(nCurrent, 2).Compare("\\u") == 0) && ((nCurrent + 6) <= nUnicodeLen))
		if ((szUnicode.substr(nCurrent, 2).compare("\\u") == 0) && ((nCurrent + 6) <= nUnicodeLen))
		{
			ucUnicode[1] = strtol(szUnicode.substr(nCurrent + 2, 2).c_str(), NULL, 16);	//小端在前
			ucUnicode[0] = strtol(szUnicode.substr(nCurrent + 4, 2).c_str(), NULL, 16);
			szRet.append((char*)ucUnicode);
			nCurrent += 6;
		}
		else
		{
			szRet.append(szUnicode.substr(nCurrent, 1));
			nCurrent += 1;
		}
	}
	return szRet;
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
		if (sStrOri.at(nCurrent) == '\\' && sStrOri.at(nCurrent + 1) == 'u')
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


void ProcessElements(ElementReader& reader) 
{
	for (Element element=reader.Next(); element; element = reader.Next()) 	// Read page contents
	{
		switch (element.GetType())
		{
			case Element::e_path:				 // Process path data...
			{
					PathData data = element.GetPathData();
					const std::vector<unsigned char>& operators = data.GetOperators();
					const std::vector<double>& points = data.GetPoints();
			}
			break; 
			
			case Element::e_text: 				// Process text strings...
			{
				const UString data = element.GetTextString();
				const UChar* pData =element.GetTextData();
				int nDataSize = element.GetImageDataSize();

				wprintf(L"=============nDataSize=%d\n",nDataSize);

// 				for (int i = 0;i < nDataSize;i++)
// 				{
// 					wprintf(L"====pData[%d]=0x%x\n", i,pData[i]);
// 				}

				wstring sRet = ConvertToUnicodeStr(data.ConvertToAscii());
				cout << data << endl;
				wprintf(L"====sRet=%s\n", sRet.c_str());
			}
			break;
			
			case Element::e_form:				// Process form XObjects
			{
					reader.FormBegin(); 
					ProcessElements(reader);
					reader.End(); 
			}
			break; 
		}
	}
}


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "chs");

	int ret = 0;
	PDFNet::Initialize();

	// Relative path to the folder containing test files.
	string input_path =  "./";

	try	// Extract text data from all pages in the document
	{
		cout << "-------------------------------------------------" << endl;
		cout << "Sample 1 - Extract text data from all pages in the document." << endl;
		cout << "Opening the input pdf..." << endl;

		PDFDoc doc((input_path + "ori.pdf").c_str());
		doc.InitSecurityHandler();

		int pgnum = doc.GetPageCount();
		
		PageIterator itr;
		ElementReader page_reader;

		for (itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())		//  Read every page
		{				
			page_reader.Begin(itr.Current());
			ProcessElements(page_reader);
			page_reader.End();
		}

		cout << "Done." << endl;
	}
	catch(Common::Exception& e)
	{
		cout << e << endl;
		ret = 1;
	}
	catch(...)
	{
		cout << "Unknown Exception" << endl;
		ret = 1;
	}

	PDFNet::Terminate();
	return ret;
}

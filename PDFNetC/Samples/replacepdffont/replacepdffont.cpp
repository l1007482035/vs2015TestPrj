// replacepdffont.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "replacepdffont.h"

#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementWriter.h>
#include <PDF/ElementReader.h>
#include <SDF/Obj.h>
#include <set>
#include <iostream>

using namespace pdftron;
using namespace std;
using namespace SDF;
using namespace PDF;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

#include <fstream>//ifstream���ļ���ofstreamд�ļ���fstream��д�ļ�
#include <map>

map<string, string> fontmap;

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

 void LoadGlyphlist(map<string, string>& fontmapTmp)
{
	ifstream in("glyphlist.txt");
	string line;

	if (in) // �и��ļ�
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�
		{
			//cout << line << endl;

			if (line.find("#") == string::npos)
			{
				//cout <<"========"<< line << endl;
				std::vector<std::string> sArry = split(line, ";");
				//printf("=========size=%d\n", sArry.size());
				if (sArry.size() == 2)
				{
					printf("=========ary[0]=%s,ary[1]=%s\n", sArry.at(0).c_str(), sArry.at(1).c_str());
					char* str;
					__int64 i = strtol(sArry.at(1).c_str(), &str, 16);
					printf("%x\r\n", i);
// 					string sWithU = "\\U" + sArry.at(1);
// 					fontmapTmp.insert(make_pair(sWithU, sArry.at(0)));
				}


			}

		}
	}
	
}

 string GetGlyphname(string sUniWithU)
 {
	 string sName = "";
	 map<string, string>::iterator itr = fontmap.find(sUniWithU);
	 if (itr != fontmap.end())
	 {
		 sName = itr->second;
	 }
	 return sName;
 }


int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���Ĵ�������Է���������Ҫ
            wprintf(L"����: MFC ��ʼ��ʧ��\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			map<string, string> fontmap;
			LoadGlyphlist(fontmap);

		
			

			

			return 0;

			UString sInputPath = "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/";
			UString sOutputPath = "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/";
			PDFNet::Initialize();
			bool bRet = PDFNet::SetResourcesPath(sInputPath);
			//PDFNet::AddFontSubst(PDFNet::e_GB1, input_path + "AdobeHeitiStd-Regular.otf");
			PDFNet::AddFontSubst(PDFNet::e_GB1, sInputPath + "AdobeHeitiStd-Regular.otf");
			PDFDoc doc(sInputPath + "ori.pdf");
			doc.InitSecurityHandler();
			for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
			{
	
				Page page = itr.Current();
				Obj res = page.GetResourceDict();

				DictIterator it1 = res.GetDictIterator();
				for (; it1.HasNext(); it1.Next())
				{
					Obj key1 = it1.Key();
					Obj val1 = it1.Value();
					//val1.
					printf("==========key1=%s\n", key1.GetName());

// 					DictIterator it2 = val1.GetDictIterator();
// 					for (; it2.HasNext(); it2.Next())
// 					{
// 						Obj key2 = it2.Key();
// 						Obj val2 = it2.Value();
// 						printf("==========key2=%s\n", key2.GetName());
// 					}
					
				}

				if (res != NULL)
				{
					printf("==========get dict suc\n");
					Obj fonts = res.FindObj("Font");
					if (fonts != NULL)
					{
						printf("==========FindObj suc\n");
						DictIterator it = fonts.GetDictIterator();
						for (;it.HasNext();it.Next())
						{
							Obj fnt_dict = it.Value();
							Font font = Font(fnt_dict);
							if (font.IsEmbedded())
							{
								printf("==========IsEmbedded\n");
								continue;
							}
						}
					}
				}
			}





			PDFNet::Terminate();


        }
    }
    else
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }

    return nRetCode;
}

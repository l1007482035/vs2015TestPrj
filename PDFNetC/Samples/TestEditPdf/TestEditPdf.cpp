// TestEditPdf.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestEditPdf.h"

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

int main()
{
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
			int ret = 0;
			PDFNet::Initialize();

			try
			{

				// Relative path to the folder containing test files.
				string input_path = "./";
				string output_path = "./";
				string input_filename = "ori.pdf";
				string output_filename = "ori_edit.pdf";
				ElementWriter writer;	// ElementWriter is used to write Elements to the page	
				ElementReader reader;

				Element element;
				GState gstate;
				Page page;

				PDFDoc doc(input_path + input_filename);
				doc.InitSecurityHandler();

				Font font2 = Font::CreateCIDTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str());
				for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
				{
					page = itr.Current();
					reader.Begin(page);
					//writer.Begin(page);	// begin writing to this page

					writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());

					while ((element = reader.Next()) == true) 	// Read page contents
					{
						if (element.GetType() == Element::e_text)
						{
							element.GetGState().SetFont(font2, 12);
						}

						writer.WriteElement(element);
					}

					writer.End();
					reader.End();
				}

				//doc.Save(output_path + output_filename, SDFDoc::e_remove_unused | SDFDoc::e_hex_strings, 0);
				doc.Save(output_path + output_filename, SDFDoc::e_remove_unused, 0);
				doc.Close();
				cout << "Done. Result saved in " << output_filename << "..." << endl;
			

			}
			catch (Common::Exception& e)
			{
				cout << e << endl;
				ret = 1;
			}
			catch (...)
			{
				cout << "Unknown Exception" << endl;
				ret = 1;
			}

			PDFNet::Terminate();

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

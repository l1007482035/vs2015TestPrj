// TestEditPdf.cpp : �������̨Ӧ�ó������ڵ㡣
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


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

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
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }

    return nRetCode;
}

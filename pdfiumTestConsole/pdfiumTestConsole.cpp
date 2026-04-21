// pdfiumTestConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pdfiumTestConsole.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;


#include <windows.h>
#include <winspool.h>
#include <fpdfview.h>
#include <fpdf_doc.h>
#include <fpdf_text.h>


using namespace std;


// Helper function to render a PDF page to a Windows device context (DC) for printing
void RenderPDFPageToPrinter(FPDF_PAGE page, HDC printerDC, int width, int height) {
	FPDF_RenderPage(printerDC, page, 0, 0, width, height, 0, FPDF_ANNOT | FPDF_PRINTING);
}

// Helper function to get default printer's device context (DC)
HDC GetDefaultPrinterDC() {
	// Get the name of the default printer

	CString sDefault;
	TCHAR printerName[1024] = { 0 };
	DWORD dwSize = 1024;
	GetDefaultPrinter(printerName, &dwSize);
	sDefault = printerName;

	if (!GetDefaultPrinter(printerName, &dwSize)) {
		std::cerr << "Failed to get default printer name." << std::endl;
		delete[] printerName;
		return nullptr;
	}

	// Open the printer's device context (DC)
	HDC printerDC = CreateDC(nullptr, printerName, nullptr, nullptr);
	
	if (!printerDC) {
		std::cerr << "Failed to create printer device context." << std::endl;
		return nullptr;
	}

	return printerDC;
}



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
			std::string pdfFilePath = "E:/MyProject/vs2015TestPrj/Release/1111.pdf";

			// Initialize the PDFium library
			FPDF_InitLibrary();

			// Open the PDF document
			FPDF_DOCUMENT pdfDoc = FPDF_LoadDocument(pdfFilePath.c_str(), nullptr);
			if (!pdfDoc) {
				printf("!!===pdfFilePath=%s\n", pdfFilePath.c_str());
				FPDF_DestroyLibrary();
				return 1;
			}

			// Get the number of pages in the PDF
			int pageCount = FPDF_GetPageCount(pdfDoc);
			std::cout << "PDF has " << pageCount << " pages." << std::endl;

			// Get default printer device context (DC)
			HDC printerDC = GetDefaultPrinterDC();
			if (!printerDC) {
				FPDF_CloseDocument(pdfDoc);
				FPDF_DestroyLibrary();
				return 1;
			}

			// Start printing document
			DOCINFO docInfo = { 0 };
			docInfo.cbSize = sizeof(DOCINFO);
			docInfo.lpszDocName = L"PDF Print Job";

			if (StartDoc(printerDC, &docInfo) <= 0) {
				std::cerr << "Failed to start print job." << std::endl;
				DeleteDC(printerDC);
				FPDF_CloseDocument(pdfDoc);
				FPDF_DestroyLibrary();
				return 1;
			}

			// Loop through each page and print
			for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex) {
				FPDF_PAGE page = FPDF_LoadPage(pdfDoc, pageIndex);
				if (!page) {
					std::cerr << "Failed to load page " << pageIndex << std::endl;
					continue;
				}

				// Get the page width and height in points
				double width = FPDF_GetPageWidth(page);
				double height = FPDF_GetPageHeight(page);

				// Start a new page for the print job
				if (StartPage(printerDC) <= 0) {
					std::cerr << "Failed to start new page in print job." << std::endl;
					FPDF_ClosePage(page);
					break;
				}

				// Convert page dimensions to printer units (pixels)
				int printWidth = GetDeviceCaps(printerDC, HORZRES);
				int printHeight = GetDeviceCaps(printerDC, VERTRES);

				// Render the page to the printer
				RenderPDFPageToPrinter(page, printerDC, printWidth, printHeight);

				// End the page
				if (EndPage(printerDC) <= 0) {
					std::cerr << "Failed to end page in print job." << std::endl;
					FPDF_ClosePage(page);
					break;
				}

				// Close the page
				FPDF_ClosePage(page);
			}

			// Finish the print job
			if (EndDoc(printerDC) <= 0) {
				std::cerr << "Failed to complete print job." << std::endl;
			}

			// Cleanup
			DeleteDC(printerDC);
			FPDF_CloseDocument(pdfDoc);
			FPDF_DestroyLibrary();
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

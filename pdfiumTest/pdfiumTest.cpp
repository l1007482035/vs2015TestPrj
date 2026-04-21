#include "stdafx.h"
#include "pdfiumTest.h"


#include <winspool.h>
#include <windows.h>


pdfiumTest::pdfiumTest(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	FPDF_InitLibraryWithConfig(nullptr);//FPDF_InitLibrary
}

pdfiumTest::~pdfiumTest()
{
	
	FPDF_DestroyLibrary();
}

void pdfiumTest::showEvent(QShowEvent *event)
{
	DWORD dwNeeded = 0,
		dwReturned = 0;
	EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, NULL, 0, &dwNeeded, &dwReturned);
	if (dwNeeded <= 0)
	{
		return;
	}

	LPBYTE lpBuffer = new BYTE[dwNeeded];
	EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, lpBuffer, dwNeeded, &dwNeeded, &dwReturned);

	PPRINTER_INFO_2 p2 = (PPRINTER_INFO_2)lpBuffer;

	for (DWORD x = 0; x < dwReturned; x++)
	{
		
		comboBox_printer->addItem(QString::fromStdWString(p2->pPrinterName));
		// 			if (p2->Attributes & PRINTER_ATTRIBUTE_DEFAULT)
		// 			{
		// 				nDefaultIndex = x;
		// 			}
		p2++;
	}

	delete[] lpBuffer;
}


void pdfiumTest::on_pushButton_print_clicked()
{
	if (!m_doc)
	{
		theLog.Write(_T("!!pdfiumTest::on_pushButton_print_clicked,m_doc is null"));
		return;
	}
	QString qsPrinterName = comboBox_printer->currentText();
	QString qsFilePath = lineEdit_path->text();
	if (qsPrinterName.isEmpty() || qsFilePath.isEmpty())
	{
		return;
	}
	//Query the size of the DEVMODE struct
	LONG lProp = DocumentProperties(NULL, NULL, (wchar_t *)qsPrinterName.toStdWString().c_str(), NULL, NULL, 0);
	if (lProp < 0)
	{
		theLog.Write(_T("!!pdfiumTest::on_pushButton_open_clicked,DocumentProperties,fail"));
	}

	DEVMODE *devmode = (DEVMODE*)new BYTE[lProp];
	memset(devmode, 0, lProp);
	devmode->dmSize = sizeof(DEVMODE);
	devmode->dmSpecVersion = DM_SPECVERSION;
	//Load the current default configuration for the printer into devmode
	if (DocumentProperties(NULL, NULL, (wchar_t *)qsPrinterName.toStdWString().c_str(), devmode, NULL, DM_OUT_BUFFER) < 0)
	{
		theLog.Write(_T("pdfiumTest::on_pushButton_open_clicked,2,fail"));
	}
	QFileInfo fileinfo(qsFilePath);

	CString szPrinterName = qsPrinterName.toStdWString().c_str();
	szPrinterName.Replace(_T("/"), _T("\\"));
	CString szFileName = fileinfo.fileName().toStdWString().c_str();
	szFileName.Replace(_T("/"), _T("\\"));

	DOCINFO docinfo;
	memset(&docinfo, 0, sizeof(docinfo));
	docinfo.cbSize = sizeof(docinfo);
	docinfo.lpszDatatype = _T("RAW");
	docinfo.lpszOutput = NULL;
	docinfo.lpszDocName = szFileName;
	int nErrRet = SP_NOTREPORTED;

	theLog.Write(_T("pdfiumTest::on_pushButton_open_clicked,2.1,szPrinterName=%s,szFileName=%s")
		, szPrinterName, szFileName);
	
	
	//创建hdc
	HDC hdc = CreateDC(NULL, szPrinterName, NULL, devmode);
	if (!hdc)
	{
		theLog.Write(_T("!!pdfiumTest::on_pushButton_open_clicked,3,fail"));
		return;
	}

	nErrRet = StartDoc(hdc, &docinfo);
	if (nErrRet <= 0)
	{
		theLog.Write(_T("!!pdfiumTest::on_pushButton_open_clicked,4,nErrRet=%d"), nErrRet);
		return;
	}

	int nPageCount = FPDF_GetPageCount(m_doc);
	for (int i = 0;i < nPageCount;i++)
	{
		if ( i == 0)
		{
			ResetDC(hdc,devmode);
			nErrRet = StartPage(hdc);
			theLog.Write(_T("!!pdfiumTest::on_pushButton_open_clicked,5,StartPage,fail,nErrRet=%d"), nErrRet);
		}
		FPDF_PAGE page = FPDF_LoadPage(m_doc, i);
		if (!page) 
		{
			theLog.Write(_T("pdfiumTest::on_pushButton_print_clicked,6,LoadPage fail,i=%d"),i);
			continue;
		}

		double width = FPDF_GetPageWidth(page);
		double height = FPDF_GetPageHeight(page);

		// Convert page dimensions to printer units (pixels)
		int printWidth = GetDeviceCaps(hdc, HORZRES);
		int printHeight = GetDeviceCaps(hdc, VERTRES);

		FPDF_RenderPage(hdc, page,0,0, printWidth, printHeight, 0, FPDF_ANNOT | FPDF_PRINTING);
		// 关闭当前页
		FPDF_ClosePage(page);
		if (i == nPageCount-1)
		{
			nErrRet = EndPage(hdc);
		}
	
	}

	EndDoc(hdc);
	// 释放PDF文档
	DeleteDC(hdc);
	FPDF_CloseDocument(m_doc);

	m_doc = NULL;

}

void pdfiumTest::on_pushButton_brower_clicked()
{
	QString currentPath = QDir::currentPath();
	QString qsFile =  QFileDialog::getOpenFileName(this, tr("Open Image"), currentPath, tr("PDF Files (*.pdf)"));
	lineEdit_path->setText(qsFile);

	if (m_doc)
	{
		FPDF_CloseDocument(m_doc);
		m_doc = NULL;
	}
	QString qsPath = lineEdit_path->text();

	FPDF_STRING fDocName = qsPath.toStdString().c_str();
	//FPDF_STRING fPrinterName = qsPrinterName.toStdString().c_str();
	//加载pdf
	m_doc = FPDF_LoadDocument(fDocName, NULL);
	if (!m_doc)
	{
		QMessageBox::information(this, "tip", "open fail");
		return;
	}
	int nPages = FPDF_GetPageCount(m_doc);
	label_4->setText(QString::number(nPages));

}

#include "stdafx.h"
#include "PdfTronHelper.h"
#include "PdfTronPrivate.h"


CPdfTronHelper::CPdfTronHelper():d_ptr(new CPdfTronPrivate(this))
{

}

CPdfTronHelper::~CPdfTronHelper()
{
	delete d_ptr;
	d_ptr = NULL;
}

BOOL CPdfTronHelper::InitLib()
{
	return CPdfTronPrivate::InitLib();
}

BOOL CPdfTronHelper::ReleaseLib()
{
	return CPdfTronPrivate::ReleaseLib();
}

BOOL CPdfTronHelper::Open(std::string sPdfPath)
{
	return d_ptr->Open(sPdfPath);
}

BOOL CPdfTronHelper::Close()
{
	return d_ptr->Close();
}

BOOL CPdfTronHelper::IsPdfA()
{
	return d_ptr->IsPdfA();
}

BOOL CPdfTronHelper::Pdf2EmbeddedFontPdf(const std::string sOutPdfPath)
{
	return d_ptr->Pdf2EmbeddedFontPdf(sOutPdfPath);
}



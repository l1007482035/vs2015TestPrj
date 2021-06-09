#pragma once
class CPdfTronPrivate;

class CPdfTronHelper
{
public:
	CPdfTronHelper();
	~CPdfTronHelper();

	static BOOL InitLib();
	static BOOL ReleaseLib();
	BOOL Open(std::string sPdfPath);
	BOOL Close();
	BOOL IsPdfA();
	BOOL Pdf2EmbeddedFontPdf(const std::string sOutPdfPath);
private:
	CPdfTronPrivate* d_ptr;
};


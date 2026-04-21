#include "StdAfx.h"
#include "QR_EncodeImage.h"

CQR_EncodeImage::CQR_EncodeImage(void)
{
	gdiplusToken = 0;
	//初始化gdi++
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CQR_EncodeImage::~CQR_EncodeImage(void)
{
	if(gdiplusToken)
	{
		GdiplusShutdown(gdiplusToken);
		gdiplusToken = 0;
	}
}

bool CQR_EncodeImage::EncodeData(int nLevel, int nVersion, bool bAutoExtent, int nMaskingNo, const char* lpsSource, int ncSource, const char* lpsOutImage, int nFactor)
{
	CQR_Encode Qr;
	if (Qr.EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo, lpsSource, ncSource))
	{
#if 0
		if (EncodeDataToImage(Qr, lpsOutImage, nFactor))
#else
		if (EncodeDataToImage(Qr.m_byModuleData, Qr.m_nSymbleSize, lpsOutImage, nFactor))
#endif
		{
			return true;
		}
	}
	return false;
}

int CQR_EncodeImage::GetEncoderClsidEx(const CStringA imagePath, CLSID* pClsid)
{
	WCHAR* format = NULL;
	CStringA csSuffix = imagePath.Right(3);
	if (0 == csSuffix.CompareNoCase("jpg"))
	{
		format = L"image/jpeg";
	}
	else if (0 == csSuffix.CompareNoCase("tif"))
	{
		format = L"image/tiff";
	}
	else if (0 == csSuffix.CompareNoCase("png"))
	{
		format = L"image/png";
	}
	else if (0 == csSuffix.CompareNoCase("bmp"))
	{
		format = L"image/bmp";
	}
	else if (0 == csSuffix.CompareNoCase("gif"))
	{
		format = L"image/gif";
	}

	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

bool CQR_EncodeImage::EncodeDataToImage(const CQR_Encode &Qr, const char* lpsOutImage, int nFactor)
{
	if (Qr.m_nSymbleSize>MAX_MODULESIZE)
	{
		return false;
	}

	//整个二维码最外围添加一圈宽度为1个nFactor像素的白边
	int nPictureWidth = (Qr.m_nSymbleSize + 2) * nFactor;
	int nPictureHeight = (Qr.m_nSymbleSize + 2) * nFactor;
	Bitmap *bmp = NULL;
	Graphics *graphics = NULL;
	bmp = new Bitmap(nPictureWidth, nPictureHeight);
	graphics = new Graphics(bmp);
	SolidBrush WhiteBrush(Color::White);
	SolidBrush BlackBrush(Color::Black);
	graphics->FillRectangle(&WhiteBrush, 0, 0, nPictureWidth, nPictureHeight);
	for (int r=0; r<Qr.m_nSymbleSize; r++)
	{
		for (int c=0; c<Qr.m_nSymbleSize; c++)
		{
			int nPostionX = (r + 1) * nFactor;
			int nPostionY = (c + 1) * nFactor;
			if (Qr.m_byModuleData[r][c] == 0)
			{
				//white
				graphics->FillRectangle(&WhiteBrush, nPostionX, nPostionY, nFactor, nFactor);
			}
			else
			{
				//black
				graphics->FillRectangle(&BlackBrush, nPostionX, nPostionY, nFactor, nFactor);
			}
		}
	}

	CLSID imageClsid;
	GetEncoderClsidEx(lpsOutImage, &imageClsid);
	CStringW wc(lpsOutImage);
	bmp->Save(wc, &imageClsid);
	delete bmp;
	delete graphics;
	graphics=NULL;
	bmp=NULL;
	return true;
}

bool CQR_EncodeImage::EncodeDataToImage(const BYTE byModuleData[MAX_MODULESIZE][MAX_MODULESIZE], int nSymbleSize,  const char* lpsOutImage, int nFactor)
{
	if (nSymbleSize>MAX_MODULESIZE)
	{
		return false;
	}

	//整个二维码最外围添加一圈宽度为1个nFactor像素的白边
	int nPictureWidth = (nSymbleSize + 2) * nFactor;
	int nPictureHeight = (nSymbleSize + 2) * nFactor;
	Bitmap *bmp = NULL;
	Graphics *graphics = NULL;
	bmp = new Bitmap(nPictureWidth, nPictureHeight);
	graphics = new Graphics(bmp);
	SolidBrush WhiteBrush(Color::White);
	SolidBrush BlackBrush(Color::Black);
	graphics->FillRectangle(&WhiteBrush, 0, 0, nPictureWidth, nPictureHeight);
	for (int r=0; r<nSymbleSize; r++)
	{
		for (int c=0; c<nSymbleSize; c++)
		{
			int nPostionX = (r + 1) * nFactor;
			int nPostionY = (c + 1) * nFactor;
			if (byModuleData[r][c] == 0)
			{
				//white
				graphics->FillRectangle(&WhiteBrush, nPostionX, nPostionY, nFactor, nFactor);
			}
			else
			{
				//black
				graphics->FillRectangle(&BlackBrush, nPostionX, nPostionY, nFactor, nFactor);
			}
		}
	}

	CLSID imageClsid;
	GetEncoderClsidEx(lpsOutImage, &imageClsid);
	CStringW wc(lpsOutImage);
	bmp->Save(wc, &imageClsid);
	delete bmp;
	delete graphics;
	graphics=NULL;
	bmp=NULL;
	return true;
}

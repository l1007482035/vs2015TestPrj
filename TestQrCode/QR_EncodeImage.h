#pragma once

#include "QR_Encode.h"

//GDI+»æÍ¼
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

class CQR_EncodeImage
{
public:
	CQR_EncodeImage(void);
	~CQR_EncodeImage(void);

public:
	bool EncodeData(int nLevel, int nVersion, bool bAutoExtent, int nMaskingNo, const char* lpsSource, int ncSource, const char* lpsOutImage, int nFactor);
	
private:
	int GetEncoderClsidEx(const CStringA imagePath, CLSID* pClsid);
	bool EncodeDataToImage(const CQR_Encode &Qr, const char* lpsOutImage, int nFactor);
	bool EncodeDataToImage(const BYTE byModuleData[MAX_MODULESIZE][MAX_MODULESIZE], int nSymbleSize, const char* lpsOutImage, int nFactor);

private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

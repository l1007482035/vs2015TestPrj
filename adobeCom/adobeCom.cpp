// adobeCom.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "acrobat.h"
#include <afxdisp.h>


int main()
{
	AfxOleInit();
	CAcroApp* m_pAcroApp = new CAcroApp;
	return 0;
}

#include "stdafx.h"
#include "FundTool.h"
#include <QtWidgets/QApplication>

CFileLog theLog;
CIniFile theIniFile;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	theLog.SetLogName(_T("FundTool"));
	theLog.EnableLog(TRUE);
	theIniFile.m_sPath.Format(_T("%sconfig\\config.ini"),CCommonFun::GetDefaultPath());
	FundTool w;
	w.show();
	return a.exec();
}

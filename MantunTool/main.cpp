#include "stdafx.h"
#include "MantunTool.h"
#include <QtWidgets/QApplication>

#define SYS_CONFIG_FILE			_T("config\\config.ini")

CFileLog theLog;
CIniFile theInifle;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	theLog.SetLogName(_T("MantunTool"));
	theLog.EnableLog(TRUE);
	theInifle.m_sPath.Format(_T("%s%s"), CCommonFun::GetDefaultPath().GetString(), SYS_CONFIG_FILE);

	MantunTool w;
	w.show();
	return a.exec();
}

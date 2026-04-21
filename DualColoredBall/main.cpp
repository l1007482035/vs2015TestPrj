#include "stdafx.h"
#include "DualColoredBall.h"
#include <QtWidgets/QApplication>
CIniFile theIniFile;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	theIniFile.m_sPath.Format(_T("%s%s"),CCommonFun::GetDefaultPath(),_T("dual.ini"));

	CSQliteDataSvc::GetInstance().SetsMutexName(_T("Sqlite_Dual"));
	CString sPath;
	sPath.Format(_T("%s%s"), CCommonFun::GetDefaultPath(), _T("dual.db"));
	CSQliteDataSvc::GetInstance().InitConnt((TCHAR*)sPath.GetString());

	DualColoredBall w;
	w.showMaximized();
	return a.exec();
}

#include "stdafx.h"
#include "DaLeTou.h"
#include <QtWidgets/QApplication>
CIniFile theIniFile;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	theIniFile.m_sPath.Format(_T("%s%s"),CCommonFun::GetDefaultPath(),_T("daletou.ini"));

	CSQliteDataSvc::GetInstance().SetsMutexName(_T("Sqlite_DaLeTou"));
	CString sPath;
	sPath.Format(_T("%s%s"), CCommonFun::GetDefaultPath(), _T("DaLeTou.db"));
	CSQliteDataSvc::GetInstance().InitConnt((TCHAR*)sPath.GetString());

	DaLeTou w;
	w.showMaximized();
	return a.exec();
}

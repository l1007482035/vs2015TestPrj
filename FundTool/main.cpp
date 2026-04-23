#include "stdafx.h"
#include "FundTool.h"
#include <QtWidgets/QApplication>

CFileLog theLog;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	theLog.SetLogName(_T("FundTool"));
	theLog.EnableLog(TRUE);
	FundTool w;
	w.show();
	return a.exec();
}

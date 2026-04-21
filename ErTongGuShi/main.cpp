#include "stdafx.h"
#include "ErTongGuShi.h"
#include <QtWidgets/QApplication>
CFileLog theLog;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	theLog.EnableLog(TRUE);
	theLog.SetLogName(_T("ErTongGuShi"));
	ErTongGuShi w;
	w.show();
	return a.exec();
}

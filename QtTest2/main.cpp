#include "stdafx.h"
#include "QtTest2.h"
#include <QtWidgets/QApplication>

CFileLog theLog;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	theLog.EnableLog(TRUE);
	//theLog.SetLogName("QtTest2");
	QtTest2 w;
	w.show();
	return a.exec();
}

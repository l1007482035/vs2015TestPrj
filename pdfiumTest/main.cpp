#include "stdafx.h"
#include "pdfiumTest.h"
#include <QtWidgets/QApplication>
CFileLog theLog;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	theLog.SetLogName(_T("pdfiumTest"));
	theLog.EnableLog(TRUE);
	pdfiumTest w;
	w.show();
	return a.exec();
}

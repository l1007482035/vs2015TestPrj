#include "stdafx.h"
#include "GenerateTool.h"
#include <QtWidgets/QApplication>

//CFileLog theLog;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//theLog.SetLogName("GenerateTool");
	//theLog.EnableLog(TRUE);

	GenerateTool w;
	w.show();
	return a.exec();
}

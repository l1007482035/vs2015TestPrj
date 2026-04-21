#include "stdafx.h"
#include "TestQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestQt w;
	w.show();
	return a.exec();
}

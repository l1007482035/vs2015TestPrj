#include "stdafx.h"
#include "ivoltTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ivoltTest w;
	//w.show();
	w.showFullScreen();
	return a.exec();
}

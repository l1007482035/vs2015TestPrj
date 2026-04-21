#include "stdafx.h"
#include "ggg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ggg w;
	w.show();
	return a.exec();
}

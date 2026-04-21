#include "stdafx.h"
#include "fff.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	fff w;
	w.show();
	return a.exec();
}

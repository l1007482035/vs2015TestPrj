#include "stdafx.h"
#include "QTest3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTest3 w;
	w.show();
	return a.exec();
}

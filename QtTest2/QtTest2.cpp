#include "stdafx.h"
#include "QtTest2.h"

QtTest2::QtTest2(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

void QtTest2::paintEvent(QPaintEvent *event)
{
	theLog.Write(_T("QtTest2::paintEvent"));
}

void QtTest2::on_pushButton_clicked()
{
// 	theLog.Write(_T("QtTest2::paintEvent"));
// 	QDialog dlg(this);
// 
// 	dlg.exec();
	tableWidget->setRowHidden(1,true);
	int nCount = tableWidget->rowCount();
	
}

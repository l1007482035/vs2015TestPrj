#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTest2.h"

class QtTest2 : public QWidget,public Ui::QtTest2Class
{
	Q_OBJECT

public:
	QtTest2(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *event);

	private slots:
	void on_pushButton_clicked();

};

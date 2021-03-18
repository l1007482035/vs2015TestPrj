#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTest.h"

class QtTest : public QWidget, Ui::QtTestClass
{
	Q_OBJECT

public:
	QtTest(QWidget *parent = Q_NULLPTR);

	void showEvent(QShowEvent *event);
private:

};

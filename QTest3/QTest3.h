#pragma once

#include <QtWidgets/QWidget>
#include "ui_QTest3.h"

class QTest3 : public QWidget
{
	Q_OBJECT

public:
	QTest3(QWidget *parent = Q_NULLPTR);

private:
	Ui::QTest3Class ui;
};

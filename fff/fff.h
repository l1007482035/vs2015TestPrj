#pragma once

#include <QtWidgets/QWidget>
#include "ui_fff.h"

class fff : public QWidget
{
	Q_OBJECT

public:
	fff(QWidget *parent = Q_NULLPTR);

private:
	Ui::fffClass ui;
};

#pragma once

#include <QtWidgets/QWidget>
#include "ui_ggg.h"

class ggg : public QWidget
{
	Q_OBJECT

public:
	ggg(QWidget *parent = Q_NULLPTR);

private:
	Ui::gggClass ui;
};

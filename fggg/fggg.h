#pragma once

#include <QtWidgets/QWidget>
#include "ui_fggg.h"

class fggg : public QWidget
{
	Q_OBJECT

public:
	fggg(QWidget *parent = Q_NULLPTR);

private:
	Ui::fgggClass ui;
};

#pragma once

#include <QWidget>
#include "ui_QuShiTu.h"

class QuShiTu : public QWidget,public Ui::QuShiTu
{
	Q_OBJECT

public:
	QuShiTu(QWidget *parent = Q_NULLPTR);
	~QuShiTu();

	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

	void LoadBlueQuShiTu();
	void LoadBlueQuShiTu2(ST_DaLeTouBlue& oBlue);

	void Show1();
	void Show2(ST_DaLeTouBlue& oBlue, ST_DaLeTouRed& oRed);

private:
};

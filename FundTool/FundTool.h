#pragma once

#include <QtWidgets/QWidget>
#include "ui_FundTool.h"

class FundTool : public QWidget,public Ui::FundToolClass
{
	Q_OBJECT

public:
	FundTool(QWidget *parent = Q_NULLPTR);

protected:
	bool QueryDiyJingzhi(int* pJingZhi);

private slots:
	void on_pushButton_query_clicked();
	void on_pushButton_add_clicked();
	void on_pushButton_diyquery_clicked();

};

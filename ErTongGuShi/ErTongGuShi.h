#pragma once

#include <QtWidgets/QWidget>
#include "ui_ErTongGuShi.h"

class ErTongGuShi : public QWidget,public Ui::ErTongGuShiClass
{
	Q_OBJECT

public:
	ErTongGuShi(QWidget *parent = Q_NULLPTR);

	CString GetHttpContentByUrl(CString szUrl);
	CString GetHttpsContentByUrl(CString szUrl);

private slots:
	void on_pushButton_clicked();

};

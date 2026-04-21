#pragma once

#include <QtWidgets/QWidget>
#include "ui_pdfiumTest.h"
#include "fpdfview.h"

class pdfiumTest : public QWidget,public Ui::pdfiumTestClass
{
	Q_OBJECT

public:
	pdfiumTest(QWidget *parent = Q_NULLPTR);
	~pdfiumTest();

	void showEvent(QShowEvent *event);

public:
	FPDF_DOCUMENT m_doc = NULL;

private slots:
	void on_pushButton_print_clicked();
	void on_pushButton_brower_clicked();
	
	
};

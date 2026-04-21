#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestQt.h"

class TestQt : public QWidget,public Ui::TestQtClass
{
	Q_OBJECT

public:
	TestQt(QWidget *parent = Q_NULLPTR);

	int longTimeFunc(int nVal,QString qsStr);

	void calculateSquareRoots();

	void longRunningTask();

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();

	void handleFinished();


signals:
	void progressValueChanged(int value);
private:
	QFutureWatcher<void> *futureWatcher;




};

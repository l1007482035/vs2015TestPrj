#pragma once

#include <QtWidgets/QWidget>
namespace QtCharts
{
	class QChartView;
	class QSplineSeries;
};
using namespace QtCharts;
#include "ui_QtTest.h"

class QtTest : public QWidget, Ui::QtTestClass
{
	Q_OBJECT

public:
	QtTest(QWidget *parent = Q_NULLPTR);

	void showEvent(QShowEvent *event);
private:

};

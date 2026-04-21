#include "stdafx.h"
#include "QtTest.h"

#pragma execution_character_set("utf-8")

#define SIZE_W     100
#define SIZE_H     30


#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtMath>
//QT_CHARTS_USE_NAMESPACE
QtTest::QtTest(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	//设置阴影
	//设置窗体透明
#if 0
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	//设置无边框
	//setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//实例阴影shadow
	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
	//设置阴影距离
	shadow->setOffset(0, 0);
	//设置阴影颜色
	shadow->setColor(QColor("#444444"));
	//设置阴影圆角
	shadow->setBlurRadius(20);
	//给嵌套QWidget设置阴影
	this->setGraphicsEffect(shadow);
#endif
	
	setWindowTitle("QChart简单绘图");

	//创建图表框架
	//QChartView* cview = new QChartView(this);
	QChart* chart = new QChart();
	chart->setTitle("简单函数曲线");

	widget->setChart(chart);


	//创建折现序列
	QLineSeries* seriesS = new QLineSeries;
	QLineSeries* seriesC = new QLineSeries;
	seriesS->setName("Sinθ");
	seriesC->setName("Cosθ");
	chart->addSeries(seriesS);
	chart->addSeries(seriesC);

	//添加数据绘制
	qreal y0, y1, t = 0, intv = 0.1;
	size_t count = 100;
	for (size_t i = 0; i < count; i++) {
		y0 = qSin(t);
		y1 = qCos(t);
		seriesS->append(t, y0);
		seriesC->append(t, y1);
		t += intv;
	}

	//创建坐标轴
	QValueAxis* axisX = new QValueAxis;
	axisX->setRange(0, 10);
	chart->setAxisX(axisX, seriesS);
	chart->setAxisX(axisX, seriesC);

	QValueAxis* axisY = new QValueAxis;
	axisY->setRange(-1, 1);
	chart->setAxisY(axisY, seriesS);
	chart->setAxisY(axisY, seriesC);



}

void QtTest::showEvent(QShowEvent *event)
{
	//label->setText("待到秋来九月八,我言花后愁花杀");

}

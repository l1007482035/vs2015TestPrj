#include "stdafx.h"
#include "QuShiTu.h"

#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

#pragma execution_character_set("utf-8")

QuShiTu::QuShiTu(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

QuShiTu::~QuShiTu()
{
}


void QuShiTu::showEvent(QShowEvent *event)
{
	//LoadBlueQuShiTu();
	//LoadRedQuShiTu();
	CString szCurNo = theIniFile.GetVal(_T("YiLou"), _T("CurNo"), _T(""));
	label_2->setText(QString::fromStdWString(szCurNo.GetString()));
}


void QuShiTu::LoadBlueQuShiTu()
{
	//大乐蓝球透折线图
	std::vector<ST_DaLeTouBlue> oDaLeTouBluVector;
	if (CSQliteDataSvc::GetInstance().GetDaLeTouBlueLimit20(oDaLeTouBluVector))
	{
		QtCharts::QChart* chart = new QtCharts::QChart();
		chart->setTitle("蓝球趋势图");
		widget_2->setChart(chart);
		widget_2->setRenderHint(QPainter::Antialiasing);
		//创建折线序列
		QtCharts::QLineSeries* series1 = new QtCharts::QLineSeries;
		QtCharts::QLineSeries* series2 = new QtCharts::QLineSeries;
		series1->setName("蓝球1");
		series2->setName("蓝球2");
		series1->setColor(QColor(Qt::blue));
		series2->setColor(QColor(Qt::darkBlue));
		chart->addSeries(series1);
		chart->addSeries(series2);

		
		//添加数据绘制
		for (auto it : oDaLeTouBluVector)
		{
			ST_DaLeTouBlue oInfo = it;
			series1->append(oInfo.nBlue1, oInfo.nSerial);
			series2->append(oInfo.nBlue2, oInfo.nSerial);
		}
		//创建坐标轴
		int beginVal = oDaLeTouBluVector.back().nSerial;
		int  endVal = oDaLeTouBluVector.front().nSerial;
		int nSize = oDaLeTouBluVector.size();
		QtCharts::QValueAxis* axisX = new QtCharts::QValueAxis;
		QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis;
		int xTicCount = 12 - 1 + 1;
		int yTicCount = endVal - beginVal + 1;

		axisX->setRange(1, 12);
		axisX->setTickCount(xTicCount);
		axisX->setLabelFormat("%d");
		//axisX->setReverse(true);
		chart->setAxisX(axisX, series1);
		chart->setAxisX(axisX, series2);

		axisY->setRange(beginVal, endVal);
		axisY->setTickCount(yTicCount);
		axisY->setLabelFormat("%d");
		axisY->setReverse(true);
		chart->setAxisY(axisY, series1);
		chart->setAxisY(axisY, series2);
		//chart->setRotation(M_PI/2);
	}
}

void QuShiTu::LoadBlueQuShiTu2(ST_DaLeTouBlue& oBlue)
{
	//大乐蓝球透折线图
	std::vector<ST_DaLeTouBlue> oDaLeTouBluVector;
	if (CSQliteDataSvc::GetInstance().GetDaLeTouBlueLimit20(oDaLeTouBluVector))
	{
		oDaLeTouBluVector.push_back(oBlue);
		std::sort(oDaLeTouBluVector.begin(),oDaLeTouBluVector.end());
		QtCharts::QChart* chart = new QtCharts::QChart();
		chart->setTitle("蓝球趋势图");
		widget_2->setChart(chart);
		widget_2->setRenderHint(QPainter::Antialiasing);
		//创建折线序列
		QtCharts::QLineSeries* series1 = new QtCharts::QLineSeries;
		QtCharts::QLineSeries* series2 = new QtCharts::QLineSeries;
		series1->setName("蓝球1");
		series2->setName("蓝球2");
		series1->setColor(QColor(Qt::blue));
		series2->setColor(QColor(Qt::darkBlue));
		chart->addSeries(series1);
		chart->addSeries(series2);
		//添加数据绘制
		for (auto it : oDaLeTouBluVector)
		{
			ST_DaLeTouBlue oInfo = it;
			series1->append(oInfo.nBlue1, oInfo.nSerial);
			series2->append(oInfo.nBlue2, oInfo.nSerial);
		}
		//创建坐标轴
		int beginVal = oDaLeTouBluVector.back().nSerial;
		int  endVal = oDaLeTouBluVector.front().nSerial;
		int nSize = oDaLeTouBluVector.size();
		QtCharts::QValueAxis* axisX = new QtCharts::QValueAxis;
		QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis;
		int xTicCount = 12 - 1 + 1;
		int yTicCount = endVal - beginVal + 1;

		axisX->setRange(1, 12);
		axisX->setTickCount(xTicCount);
		axisX->setLabelFormat("%d");
		//axisX->setReverse(true);
		chart->setAxisX(axisX, series1);
		chart->setAxisX(axisX, series2);

		axisY->setRange(beginVal, endVal);
		axisY->setTickCount(yTicCount);
		axisY->setLabelFormat("%d");
		axisY->setReverse(true);
		chart->setAxisY(axisY, series1);
		chart->setAxisY(axisY, series2);
		//chart->setRotation(M_PI/2);
	}
}

void QuShiTu::Show1()
{
	LoadBlueQuShiTu();
	showMaximized();
}

void QuShiTu::Show2(ST_DaLeTouBlue& oBlue, ST_DaLeTouRed& oRed)
{
	LoadBlueQuShiTu2(oBlue);
	showMaximized();
}

void QuShiTu::closeEvent(QCloseEvent *event)
{
	hide();
	event->ignore();
}


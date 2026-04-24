#pragma once

#include <QtWidgets/QWidget>
#include "ui_FundTool.h"

class FundTool : public QWidget,public Ui::FundToolClass
{
	Q_OBJECT

public:
	FundTool(QWidget *parent = Q_NULLPTR);
	void showEvent(QShowEvent *event);

protected:
	bool QueryDiyJingzhi(QString qsFundCode,QString qsBeginDate, QString qsEndDate, double* pfAvgJingZhi);
	//获取最近一天的净值
	bool GetRecentDayJingzhi(QString qsFundCode,double* pfCurrentJingzhi);
	//计算基金的相关值
	bool CalFundValue(QString qsFundCode, QString qsBeginDate,QString qsEndDate,int nPageIndex, double& fTotalJingzhi,int& nDataCount,int& nTotalCount);
	bool QueryFundName(QString qsFundCode, QString* pFundName);

	void AddAvgCol(int nRowIndex,int nColIndex,QString qsCurJingzhi,QString qsAvgValue);
	void SetAvgCol(int nRowIndex, int nColIndex, QString qsCurJingzhi, QString qsAvgValue);
	void AddOneRow(QString qsFundName, QString qsFundCode, QString qsCurJingZhi
		,QString qsAvg30, QString qsAvg60, QString qsAvg90, QString qsAvgyear);

private slots:
	void on_pushButton_query_clicked();
	void on_pushButton_add_clicked();
	void on_pushButton_diyquery_clicked();
	void on_cell_querypushbutton_clicked();
	void on_cell_deletepushbutton_clicked();
	void on_pushButton_queryall_clicked();
	void on_pushButton_lightquery_clicked();

};

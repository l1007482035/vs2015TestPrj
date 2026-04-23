#include "stdafx.h"
#include "FundTool.h"
#include <ctime>

FundTool::FundTool(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	// C++ 示例
	// 前3列根据内容调整
	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);

	// 最后一列拉伸填充剩余空间
	tableWidget->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

bool FundTool::QueryDiyJingzhi(int* pJingZhi)
{
	CHttpClient oClient;
	return true;
}

void FundTool::on_pushButton_query_clicked()
{
	QString qsFundCode = lineEdit_fundcode->text();
	QDate qCurDate = QDate::currentDate();
	qCurDate.toString(Qt::ISODate);
	

}

void FundTool::on_pushButton_add_clicked()
{

}

void FundTool::on_pushButton_diyquery_clicked()
{

}

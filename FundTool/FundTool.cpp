#include "stdafx.h"
#include "FundTool.h"
#include <ctime>
#include <QRegularExpressionValidator>
#include <QtConcurrent>
#include <QFuture>
FundTool::FundTool(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	QString pattern = "^([1-9]|[1-9][0-9]|[12][0-9]{2}|3[0-5][0-9]|36[0-5])$";
	QRegularExpression regEx(pattern);
	QRegularExpressionValidator *validator = new QRegularExpressionValidator(regEx, this);

	lineEdit_diydays->setValidator(validator);
	// C++ 示例
	// 前3列根据内容调整
	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(8, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(9, QHeaderView::ResizeToContents);
	tableWidget->horizontalHeader()->setSectionResizeMode(10, QHeaderView::ResizeToContents);

	// 最后一列拉伸填充剩余空间
	tableWidget->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Stretch);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//  	tableWidget->setStyleSheet(
//  		"QTableWidget::item:selected { background-color: rgb(0,120,215); color: white; }"
//  		"QTableWidget{font: 11pt \"微软雅黑\";}"
//  	);
 	//tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font: 16pt \"微软雅黑\";}");
	

	CString szValues = theIniFile.GetVal(_T("Fund"), _T("ZiXuan"), _T(""));
	CStringArray ary;
	CCommonFun::StringSplit(szValues, &ary, _T("|"));
	for (int i = 0; i < ary.GetCount(); i++)
	{
		CString szFund = ary.GetAt(i);
		CStringArray ary2;
		CCommonFun::StringSplit(szFund, &ary2, _T("-"));
		if (ary2.GetCount() == 2)
		{
			CString szFundCode = ary2.GetAt(0);
			CString szFundName = ary2.GetAt(1);
			AddOneRow(QString::fromStdWString(szFundName.GetString()), QString::fromStdWString(szFundCode.GetString())
				, "","", "", "", "", "","");
		}
	}
}

void FundTool::showEvent(QShowEvent *event)
{
}

bool FundTool::QueryFundQushi(QString qsFundCode, QString* pQushi)
{
	//先算第一页
	double fTotalJingZhi = 0.0;
	int nTotalCount = 0;
	QDate qEndDay = QDate::currentDate();
	QDate qBeginDay = qEndDay.addDays(-15);
	QString qsEndDay = qEndDay.toString(Qt::ISODate);
	QString qsBeginDay = qBeginDay.toString(Qt::ISODate);

	std::vector<double> oAry;
	if (!GetFundJingzhiAry(qsFundCode, qsBeginDay, qsEndDay, 1, oAry, nTotalCount))
	{
		theLog.Write(_T("!!FundTool::QueryFundQushi,1,GetFundJingzhiAry,fail"));
		return false;
	}
	int nPages = ceil((double)nTotalCount / 20.0);
	theLog.Write(_T("FundTool::QueryFundQushi,2,fTotalJingZhi=%f,nDataCount=%d,nPages=%d")
		, fTotalJingZhi, nTotalCount, nPages);
	if (nPages > 2)
	{
		for (int i = 0; i < nPages - 1; i++)//遍历剩余页数
		{
			int nTotalCountTmp = 0;
			if (!GetFundJingzhiAry(qsFundCode, qsBeginDay, qsEndDay, i + 2, oAry, nTotalCountTmp))//第二页开始
			{
				theLog.Write(_T("!!FundTool::QueryFundQushi,3,GetFundJingzhiAry,fail,nPageIndex=%d"), i + 2);
				return false;
			}
		}

	}
	int nKeepDays = 0;
	if (oAry.size() > 2)
	{
		if (oAry[1] > oAry[0])
		{
			*pQushi = "-";
		}
		else
		{
			*pQushi = "+";
		}
		for (int i = 0;i < oAry.size();i++)
		{
			//跌
			if (oAry[0] < oAry[1])
			{
				if (oAry[i] < oAry[i + 1])
				{
					nKeepDays++;
				}
				else
				{
					break;
				}	
			}
			//涨
			else
			{
				if (oAry[i] > oAry[i + 1])
				{
					nKeepDays++;
				}
				else
				{
					break;
				}
			}
		}
		theLog.Write(_T("FundTool::QueryFundQushi,50,nKeepDays=%d"), nKeepDays);
		*pQushi = *pQushi + QString::number(nKeepDays);
		theLog.Write(_T("FundTool::QueryFundQushi,51,pQushi=%s"), pQushi->toStdWString().c_str());

	}
	return true;
}

bool FundTool::QueryDiyJingzhi(QString qsFundCode,QString qsBeginDate, QString qsEndDate, double* pfAvgJingZhi)
{
	//先算第一页
	double fTotalJingZhi = 0.0;
	int nTotalCount = 0;

	std::vector<double> oAry;
	if (!GetFundJingzhiAry(qsFundCode, qsBeginDate, qsEndDate, 1, oAry, nTotalCount))
	{
		theLog.Write(_T("!!FundTool::QueryDiyJingzhi,1,GetFundJingzhiAry,fail"));
		return false;
	}
	int nPages = ceil((double)nTotalCount / 20.0);
	theLog.Write(_T("FundTool::QueryDiyJingzhi,2,fTotalJingZhi=%f,nDataCount=%d,nPages=%d")
		, fTotalJingZhi, nTotalCount, nPages);
	if (nPages > 2)
	{
		for (int i = 0;i < nPages-1;i++)//遍历剩余页数
		{
			int nTotalCountTmp = 0;
			if (!GetFundJingzhiAry(qsFundCode, qsBeginDate, qsEndDate, i+2, oAry, nTotalCountTmp))//第二页开始
			{
				theLog.Write(_T("!!FundTool::QueryDiyJingzhi,3,GetFundJingzhiAry,fail,nPageIndex=%d"),i + 2);
				return false;
			}
		}

	}
	for (auto it:oAry)
	{
		fTotalJingZhi += it;
	}
	*pfAvgJingZhi = fTotalJingZhi / oAry.size();
	*pfAvgJingZhi = std::round(*pfAvgJingZhi  * 10000.0) / 10000.0;
	theLog.Write(_T("FundTool::QueryDiyJingzhi,5,fAvgJingZhi=%f"), *pfAvgJingZhi);
	return true;
}

bool FundTool::GetRecentDayJingzhi(QString qsFundCode, double* pfCurrentJingzhi)
{
	QDate qEndDay = QDate::currentDate();
	QDate qBeginDay = qEndDay.addDays(-10);
	QString qsEndDay = qEndDay.toString(Qt::ISODate);
	QString qsBeginDay = qBeginDay.toString(Qt::ISODate);

	CHttpClient oClient;
	QString qsUrl = QString("http://api.fund.eastmoney.com/f10/lsjz?fundCode=%1&pageIndex=1&pageSize=20&startDate=%2&endDate=%3")
		.arg(qsFundCode).arg(qsBeginDay).arg(qsEndDay);
	std::string sResponse;
	std::list<std::string> oList;
	oList.push_back("Referer:http://fundf10.eastmoney.com/");
	oList.push_back("User-Agent:Mozilla/5.0");
	theLog.Write(_T("FundTool::GetRecentDayJingzhi,qsUrl=%s"), qsUrl.toStdWString().c_str());
	int nRet = oClient.Get(qsUrl.toStdString(), &oList, sResponse);
	theLog.Write(_T("FundTool::GetRecentDayJingzhi,0,nRet=%d,sResponse=%s"), nRet, CCommonFun::UTF8ToUnicode(sResponse.c_str()));
	if (nRet != 0)
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,1,nRet=%d"), nRet);
		return false;
	}
	Json::Value jsValue;
	Json::Reader jsReader;
	if (!jsReader.parse(sResponse, jsValue))
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,2,parse fail"));
		return false;
	}

	int nErrcode = jsValue["ErrCode"].asInt();
	if (nErrcode != 0)
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,3,nErrcode=%d"), nErrcode);
		return false;
	}
	int nTotalCount = jsValue["TotalCount"].asInt();
	Json::Value jsData = jsValue["Data"];
	if (jsData.type() != Json::objectValue)
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,4,jsData is not json object"));
		return false;
	}
	Json::Value jsLiShiJingZhi = jsData["LSJZList"];
	if (jsLiShiJingZhi.type() != Json::arrayValue)
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,5,jsLiShiJingZhi is not json arrary"));
		return false;
	}
	int nDataCount = jsLiShiJingZhi.size();
	if (nDataCount == 0)
	{
		theLog.Write(_T("!!FundTool::GetRecentDayJingzhi,6,nDataCount null"));
		return false;
	}
	*pfCurrentJingzhi = std::stod(jsLiShiJingZhi[0]["DWJZ"].asString());
	return true;

}

//获取基金单位净值数组
bool FundTool::GetFundJingzhiAry(QString qsFundCode, QString qsBeginDate, QString qsEndDate, int nPageIndex, std::vector<double>& oAry, int& nTotalCount)
{
	CHttpClient oClient;
	QString qsUrl = QString("http://api.fund.eastmoney.com/f10/lsjz?fundCode=%1&pageIndex=%2&pageSize=20&startDate=%3&endDate=%4")
		.arg(qsFundCode).arg(nPageIndex).arg(qsBeginDate).arg(qsEndDate);
	std::string sResponse;
	std::list<std::string> oList;
	oList.push_back("Referer:http://fundf10.eastmoney.com/");
	oList.push_back("User-Agent:Mozilla/5.0");
	theLog.Write(_T("FundTool::GetFundJingzhiAry,qsUrl=%s"), qsUrl.toStdWString().c_str());
	int nRet = oClient.Get(qsUrl.toStdString(), &oList, sResponse);
	theLog.Write(_T("FundTool::GetFundJingzhiAry,0,nRet=%d,sResponse=%s"), nRet, CCommonFun::UTF8ToUnicode(sResponse.c_str()));
	if (nRet != 0)
	{
		theLog.Write(_T("!!FundTool::GetFundJingzhiAry,1,nRet=%d"), nRet);
		return false;
	}
	Json::Value jsValue;
	Json::Reader jsReader;
	if (!jsReader.parse(sResponse, jsValue))
	{
		theLog.Write(_T("!!FundTool::GetFundJingzhiAry,2,parse fail"));
		return false;
	}

	int nErrcode = jsValue["ErrCode"].asInt();
	if (nErrcode != 0)
	{
		theLog.Write(_T("!!FundTool::GetFundJingzhiAry,3,nErrcode=%d"), nErrcode);
		return false;
	}
	nTotalCount = jsValue["TotalCount"].asInt();
	Json::Value jsData = jsValue["Data"];
	if (jsData.type() != Json::objectValue)
	{
		theLog.Write(_T("!!FundTool::GetFundJingzhiAry,4,jsData is not json object"));
		return false;
	}
	Json::Value jsLiShiJingZhi = jsData["LSJZList"];
	if (jsLiShiJingZhi.type() != Json::arrayValue)
	{
		theLog.Write(_T("!!FundTool::GetFundJingzhiAry,5,jsLiShiJingZhi is not json arrary"));
		return false;
	}
	for (int i = 0; i < jsLiShiJingZhi.size(); i++)
	{
		oAry.push_back(std::stod(jsLiShiJingZhi[i]["DWJZ"].asString()));
	}
	return true;
}

bool FundTool::QueryFundName(QString qsFundCode, QString* pFundName)
{
	CHttpClient oClient;
	//QString qsUrl = QString("http://fundgz.1234567.com.cn/js/%1.js").arg(qsFundCode);

	QString qsUrl = QString("http://fund.eastmoney.com/pingzhongdata/%1.js").arg(qsFundCode);

	std::string sResponse;
	int nRet = oClient.Get(qsUrl.toStdString(), nullptr, sResponse);
	if (nRet != 0)
	{
		theLog.Write(_T("!!FundTool::QueryFundName,get fail,qsUrl=%s"), qsUrl.toStdWString().c_str());
		return false;
	}
	theLog.Write(_T("FundTool::QueryFundName,0,nRet=%d,sResponse=%s"), nRet, CCommonFun::UTF8ToUnicode(sResponse.c_str()));
	QString qsResponse = QString::fromStdString(sResponse);
	QRegularExpression reg("var\\s+fS_name\\s*=\\s*\"([^\"]+)\"");
	QRegularExpressionMatch match = reg.match(qsResponse);
	if (match.hasMatch()) {
		*pFundName = match.captured(1);
		return true;
	}
	return false;	
}

void FundTool::AddAvgCol(int nRowIndex, int nColIndex, QString qsCurJingzhi, QString qsAvgValue)
{
	QTableWidgetItem *pItem = new QTableWidgetItem(qsAvgValue);
	pItem->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRowIndex, nColIndex, pItem);
	if (qsCurJingzhi.toDouble() > qsAvgValue.toDouble())
	{
		pItem->setTextColor(Qt::red);
	}
	else
	{
		pItem->setTextColor(Qt::green);
	}
}

void FundTool::SetAvgCol(int nRowIndex, int nColIndex, QString qsCurJingzhi, QString qsAvgValue)
{
	QTableWidgetItem *pItem = tableWidget->item(nRowIndex, nColIndex);
	pItem->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRowIndex, nColIndex, pItem);
	if (qsCurJingzhi.toDouble() > qsAvgValue.toDouble())
	{
		pItem->setTextColor(Qt::red);
	}
	else
	{
		pItem->setTextColor(Qt::green);
	}
	pItem->setText(qsAvgValue);
}

void FundTool::AddOneRow(QString qsFundName, QString qsFundCode, QString qsCurJingZhi, QString qsQushi
	, QString qsAvg7, QString qsAvg30, QString qsAvg60, QString qsAvg90, QString qsAvgyear)
{
	int nRowCount = tableWidget->rowCount();
	tableWidget->insertRow(nRowCount);

	QTableWidgetItem *pItem0 = new QTableWidgetItem(qsFundName);
	pItem0->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRowCount,0,pItem0);

	QTableWidgetItem *pItem1 = new QTableWidgetItem(qsFundCode);
	pItem1->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRowCount, 1, pItem1);

	QTableWidgetItem *pItem2 = new QTableWidgetItem(qsCurJingZhi);
	pItem2->setTextAlignment(Qt::AlignCenter);
	pItem2->setTextColor(Qt::blue);
	tableWidget->setItem(nRowCount, 2, pItem2);

	QTableWidgetItem *pItem3 = new QTableWidgetItem(qsQushi);
	pItem3->setTextAlignment(Qt::AlignCenter);
	if (qsQushi.contains("-"))
	{
		pItem3->setTextColor(Qt::green);
	}
	else
	{
		pItem3->setTextColor(Qt::red);
	}

	tableWidget->setItem(nRowCount, 3, pItem3);



	AddAvgCol(nRowCount, 4, qsCurJingZhi, qsAvg7);
	AddAvgCol(nRowCount, 5, qsCurJingZhi, qsAvg30);
	AddAvgCol(nRowCount, 6, qsCurJingZhi, qsAvg60);
	AddAvgCol(nRowCount, 7, qsCurJingZhi, qsAvg90);
	AddAvgCol(nRowCount, 8, qsCurJingZhi, qsAvgyear);

	//跌幅输入
	QWidget* widget0 = new QWidget();
	QLineEdit* pEdit = new QLineEdit;
	pEdit->setFixedWidth(60);
	QRegularExpression regExp("^([1-9]\\d*(\\.\\d+)?|0\\.\\d*[1-9]\\d*)$");
	QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, pEdit);
	pEdit->setValidator(validator);
	// 布局
	QHBoxLayout* layout0 = new QHBoxLayout();
	layout0->addWidget(pEdit);
	layout0->setContentsMargins(0, 0, 0, 0);
	widget0->setLayout(layout0);
	tableWidget->setCellWidget(nRowCount, 9, widget0);
	connect(pEdit, &QLineEdit::returnPressed, this, &FundTool::on_edit_returnPressed);

	//跌后净值
	QWidget* widget1 = new QWidget();
	QLineEdit* pEdit1 = new QLineEdit;
	pEdit1->setFixedWidth(60);
	pEdit1->setReadOnly(true);

	// 布局
	QHBoxLayout* layout1 = new QHBoxLayout();
	layout1->addWidget(pEdit1);
	layout1->setContentsMargins(0, 0, 0, 0);
	widget1->setLayout(layout1);
	tableWidget->setCellWidget(nRowCount, 10, widget1);


	// ===== 两个按钮 =====
	QWidget* widget = new QWidget();
	QPushButton* pQueryPushButton = new QPushButton(u8"查询");
	QPushButton* pDeletePushButton = new QPushButton(u8"删除");
	pQueryPushButton->setMinimumHeight(30);
	pDeletePushButton->setMinimumHeight(30);

	// 布局
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(pQueryPushButton);
	layout->addWidget(pDeletePushButton);
	layout->setContentsMargins(0, 0, 0, 0);

	widget->setLayout(layout);

	// 放入单元格
	tableWidget->setCellWidget(nRowCount, 11, widget);
	connect(pQueryPushButton, SIGNAL(clicked()), this, SLOT(on_cell_querypushbutton_clicked()));
	connect(pDeletePushButton, SIGNAL(clicked()), this, SLOT(on_cell_deletepushbutton_clicked()));
}

//查询一个基金详情
void FundTool::on_pushButton_query_clicked()
{

	QString qsFundCode = lineEdit_fundcode->text();
	if (qsFundCode.isEmpty())
	{
		QMessageBox::information(this, u8"提示", u8"请填写基金代码");
		return;
	}
	QDate qCurDate = QDate::currentDate();
	QString qsEndDate = qCurDate.toString(Qt::ISODate);
	QDate qBeginDate7 = qCurDate.addDays(7 * -1);
	QDate qBeginDate30 = qCurDate.addDays(30 * -1);
	QDate qBeginDate60 = qCurDate.addDays(60 * -1);
	QDate qBeginDate90 = qCurDate.addDays(90 * -1);
	QDate qBeginDateYear = QDate(qCurDate.year(),1,1);

	QString qsQushi;
	QString qsBeginDate7 = qBeginDate7.toString(Qt::ISODate);
	QString qsBeginDate30 = qBeginDate30.toString(Qt::ISODate);
	QString qsBeginDate60 = qBeginDate60.toString(Qt::ISODate);
	QString qsBeginDate90 = qBeginDate90.toString(Qt::ISODate);
	QString qsBeginDateYear = qBeginDateYear.toString(Qt::ISODate);

	double fAvgJingZhi7 = 0.0;
	double fAvgJingZhi30 = 0.0;
	double fAvgJingZhi60 = 0.0;
	double fAvgJingZhi90 = 0.0;
	double fAvgJingZhiYear = 0.0;
	QString qsFundName;
	double fCurJingzhi = 0.0;
	QApplication::setOverrideCursor(Qt::WaitCursor);
	BOOL bRet = false;
	do 
	{
		//先查询名称
		QFuture<bool> future = QtConcurrent::run(this, &FundTool::QueryFundName, qsFundCode, &qsFundName);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//查询最新净值
		future = QtConcurrent::run(this, &FundTool::GetRecentDayJingzhi, qsFundCode, &fCurJingzhi);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		//查询趋势
		//查询最新净值
		future = QtConcurrent::run(this, &FundTool::QueryFundQushi, qsFundCode, &qsQushi);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		//7天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate7, qsEndDate, &fAvgJingZhi7);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		
		//30天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate30, qsEndDate, &fAvgJingZhi30);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//60天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate60, qsEndDate, &fAvgJingZhi60);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//90天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate90, qsEndDate, &fAvgJingZhi90);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//今年以来
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDateYear, qsEndDate, &fAvgJingZhiYear);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		bRet = true;

	} while (0);
	QApplication::restoreOverrideCursor();
	if (!bRet)
	{
		theLog.Write(_T("FundTool::on_pushButton_query_clicked,QueryDiyJingzhi,fail"));
		QMessageBox::information(this, u8"提示", u8"查询失败");
		return;
	}
	lineEdit_fundname->setText(qsFundName);
	lineEdit_curjingzhi->setText(QString::number(fCurJingzhi));
	if (qsQushi.contains("-"))
	{
		lineEdit_qushi->setStyleSheet("color: green;");
	}
	else
	{
		lineEdit_qushi->setStyleSheet("color: red;");
	}
	lineEdit_qushi->setText(qsQushi);
	lineEdit_7avg->setText(QString::number(fAvgJingZhi7));
	lineEdit_30avg->setText(QString::number(fAvgJingZhi30));
	lineEdit_60avg->setText(QString::number(fAvgJingZhi60));
	lineEdit_90avg->setText(QString::number(fAvgJingZhi90));
	lineEdit_yearavg->setText(QString::number(fAvgJingZhiYear));
}

void FundTool::on_pushButton_add_clicked()
{
	QString qsFundName = lineEdit_fundname->text();
	QString qsFundCode = lineEdit_fundcode->text();
	QString qsCurJingZhi = lineEdit_curjingzhi->text();
	QString qsQushi = lineEdit_qushi->text();
	QString qsAvg7 = lineEdit_7avg->text();
	QString qsAvg30 = lineEdit_30avg->text();
	QString qsAvg60 = lineEdit_60avg->text();
	QString qsAvg90 = lineEdit_90avg->text();
	QString qsAvgYear = lineEdit_yearavg->text();
	if (qsFundName.isEmpty() || qsFundCode.isEmpty() || qsCurJingZhi.isEmpty() || qsAvg30.isEmpty() ||
		qsAvg60.isEmpty() || qsAvg90.isEmpty() || qsAvgYear.isEmpty())
	{
		QMessageBox::information(this, u8"提示", u8"有数据为空");
		return;
	}
	bool bFindExsit = false;
	for (int i = 0;i < tableWidget->rowCount();i++)
	{
		QString qsFunCodeTmp = tableWidget->item(i, 1)->text();
		if (qsFunCodeTmp == qsFundCode)
		{
			bFindExsit = true;
			break;
		}
	}
	if (bFindExsit)
	{
		QMessageBox::information(this, u8"提示", u8"已经添加过了");
		return;
	}

	AddOneRow(qsFundName,qsFundCode,qsCurJingZhi, qsQushi, qsAvg7,qsAvg30, qsAvg60, qsAvg90, qsAvgYear);
	CString szValues = theIniFile.GetVal(_T("Fund"), _T("ZiXuan"), _T(""));
	CString szValue = CString(qsFundCode.toStdWString().c_str()) + _T("-") + CString(qsFundName.toStdWString().c_str());
	if (szValues.IsEmpty())
	{
		szValues = szValue;
	}
	else
	{
		szValues.AppendFormat(_T("|%s"), szValue);
	}
	theIniFile.SetVal(_T("Fund"), _T("ZiXuan"), szValues);
}

void FundTool::on_pushButton_diyquery_clicked()
{
	QString qsFundCode = lineEdit_fundcode->text();
	if (qsFundCode.isEmpty())
	{
		QMessageBox::information(this, u8"提示", u8"请填写基金代码");
		return;
	}
	int nDiyDays = lineEdit_diydays->text().toInt();
	if (nDiyDays == 0)
	{
		QMessageBox::information(this, u8"提示", u8"自定义天数不能是零");
		return;
	}

	QDate qCurDate = QDate::currentDate();
	QString qsEndDate = qCurDate.toString(Qt::ISODate);
	QDate qBeginDate = qCurDate.addDays(nDiyDays*-1);
	QString qsBeginDate = qBeginDate.toString(Qt::ISODate);
	theLog.Write(_T("qsBeginDate=%s,qsEndDate=%s"), qsBeginDate.toStdWString().c_str(), qsEndDate.toStdWString().c_str());
	double fAvgJingZhi = 0.0;
	QString qsFundName;
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	BOOL bRet = false;
	do 
	{
		//先查询名称
		QFuture<bool> future = QtConcurrent::run(this, &FundTool::QueryFundName, qsFundCode, &qsFundName);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate, qsEndDate, &fAvgJingZhi);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		bRet = true;
	} while (0);
	QApplication::restoreOverrideCursor();

	if (!bRet)
	{
		theLog.Write(_T("FundTool::on_pushButton_diyquery_clicked,QueryDiyJingzhi,fail"));
		QMessageBox::information(this, u8"提示", u8"查询失败");
		return;
	}
	lineEdit_fundname->setText(qsFundName);
	lineEdit_diyjingzhi->setText(QString::number(fAvgJingZhi));

}

void FundTool::on_cell_querypushbutton_clicked()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	QModelIndex idx = tableWidget->indexAt(senderObj->parentWidget()->pos());
	int nRow = idx.row();
	QString qsFundCode = tableWidget->item(nRow, 1)->text();

	QDate qCurDate = QDate::currentDate();
	QString qsEndDate = qCurDate.toString(Qt::ISODate);
	QDate qBeginDate7 = qCurDate.addDays(7 * -1);
	QDate qBeginDate30 = qCurDate.addDays(30 * -1);
	QDate qBeginDate60 = qCurDate.addDays(60 * -1);
	QDate qBeginDate90 = qCurDate.addDays(90 * -1);
	QDate qBeginDateYear = QDate(qCurDate.year(), 1, 1);
	QString qsFundName;
	double fCurJingzhi = 0.0;
	QString qsQushi;
	QString qsBeginDate7 = qBeginDate7.toString(Qt::ISODate);
	QString qsBeginDate30 = qBeginDate30.toString(Qt::ISODate);
	QString qsBeginDate60 = qBeginDate60.toString(Qt::ISODate);
	QString qsBeginDate90 = qBeginDate90.toString(Qt::ISODate);
	QString qsBeginDateYear = qBeginDateYear.toString(Qt::ISODate);

	double fAvgJingZhi7 = 0.0;
	double fAvgJingZhi30 = 0.0;
	double fAvgJingZhi60 = 0.0;
	double fAvgJingZhi90 = 0.0;
	double fAvgJingZhiYear = 0.0;
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	BOOL bRet = false;
	do
	{
		//先查询名称
		QFuture<bool> future = QtConcurrent::run(this, &FundTool::QueryFundName, qsFundCode, &qsFundName);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//查询最新净值
		future = QtConcurrent::run(this, &FundTool::GetRecentDayJingzhi, qsFundCode, &fCurJingzhi);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		//查询趋势
		future = QtConcurrent::run(this, &FundTool::QueryFundQushi, qsFundCode, &qsQushi);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		//7天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate7, qsEndDate, &fAvgJingZhi7);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		//30天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate30, qsEndDate, &fAvgJingZhi30);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//60天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate60, qsEndDate, &fAvgJingZhi60);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//90天
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDate90, qsEndDate, &fAvgJingZhi90);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}
		//今年以来
		future = QtConcurrent::run(this, &FundTool::QueryDiyJingzhi, qsFundCode, qsBeginDateYear, qsEndDate, &fAvgJingZhiYear);
		while (!future.isFinished())
		{
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		if (!future.result())
		{
			break;
		}

		bRet = true;

	} while (0);

	QApplication::restoreOverrideCursor();

	if (!bRet)
	{
		theLog.Write(_T("FundTool::on_pushButton_query_clicked,QueryDiyJingzhi,fail"));
		QMessageBox::information(this, u8"提示", u8"查询失败");
		return;
	}
	tableWidget->item(nRow, 0)->setText(qsFundName);
	tableWidget->item(nRow, 2)->setText(QString::number(fCurJingzhi));

	//设置趋势
	QTableWidgetItem *pItem = tableWidget->item(nRow, 3);
	pItem->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRow, 3, pItem);
	if (qsQushi.contains("-"))
	{
		pItem->setTextColor(Qt::green);
	}
	else
	{
		pItem->setTextColor(Qt::red);
	}
	pItem->setText(qsQushi);
	
	SetAvgCol(nRow, 4, QString::number(fCurJingzhi), QString::number(fAvgJingZhi7));
	SetAvgCol(nRow, 5, QString::number(fCurJingzhi), QString::number(fAvgJingZhi30));
	SetAvgCol(nRow, 6, QString::number(fCurJingzhi), QString::number(fAvgJingZhi60));
	SetAvgCol(nRow, 7, QString::number(fCurJingzhi), QString::number(fAvgJingZhi90));
	SetAvgCol(nRow, 8, QString::number(fCurJingzhi), QString::number(fAvgJingZhiYear));
	

}

void FundTool::on_cell_deletepushbutton_clicked()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	QModelIndex idx = tableWidget->indexAt(senderObj->parentWidget()->pos());
	int nRow = idx.row();
	QString qsFundName = tableWidget->item(nRow, 0)->text();
	QString qsFundCode = tableWidget->item(nRow, 1)->text();
	tableWidget->removeRow(nRow);
	CString szValues = theIniFile.GetVal(_T("Fund"), _T("ZiXuan"), _T(""));
	CString szValue = CString(qsFundCode.toStdWString().c_str()) + _T("-") + CString(qsFundName.toStdWString().c_str());
	szValues.Replace(szValue,_T(""));
	szValues.Replace(_T("||"), _T("|"));
	szValues.Trim(_T("|"));
	theIniFile.SetVal(_T("Fund"), _T("ZiXuan"), szValues);
}

void FundTool::on_pushButton_queryall_clicked()
{
	for (int i = 0;i < tableWidget->rowCount();i++)
	{
		QWidget* pWidget = tableWidget->cellWidget(i,11);
		if (pWidget)
		{
			QHBoxLayout*pLayout =(QHBoxLayout*)pWidget->layout();
			if (pLayout)
			{
				QPushButton* pButton = (QPushButton*)pLayout->itemAt(0)->widget();
				if (pButton)
				{
					pButton->click();
				}
			}
		}
	}
}

void FundTool::on_pushButton_lightquery_clicked()
{

	QString qsKeyWord = lineEdit_keyword->text();
	if (qsKeyWord.isEmpty())
	{
		return;
	}

	QItemSelectionModel *sm = tableWidget->selectionModel();
	sm->clearSelection();  // 先清空之前的高亮

	for (int i = 0; i < tableWidget->rowCount(); i++)
	{
		QTableWidgetItem *pItem = tableWidget->item(i, 0);
		QString qsFundName = pItem->text();
		QString qsFundCode = tableWidget->item(i, 1)->text();

		if (qsFundName.contains(qsKeyWord, Qt::CaseInsensitive)
			|| qsFundCode.contains(qsKeyWord, Qt::CaseInsensitive))
		{
			QModelIndex index = tableWidget->model()->index(i, 0);
			sm->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
		}
	}

}

void FundTool::on_edit_returnPressed()
{
	QLineEdit *senderObj = qobject_cast<QLineEdit*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	double fDieFu = senderObj->text().toDouble();
	double fCurJingZhi = 0.0;
	double fRetValue = 0.0;
	QModelIndex idx = tableWidget->indexAt(senderObj->parentWidget()->pos());
	int nRow = idx.row();
	int nCol = idx.column();
	if (nCol == 8)
	{
		fCurJingZhi = tableWidget->item(nRow, 2)->text().toDouble();
		fRetValue = (100.0 - fDieFu) / 100.0*fCurJingZhi;
		fRetValue = std::round(fRetValue*10000.0) / 10000.0;
		QWidget* pWidget = tableWidget->cellWidget(nRow, 10);
		if (pWidget)
		{
			QHBoxLayout*pLayout = (QHBoxLayout*)pWidget->layout();
			QLayoutItem* pItem = pLayout->itemAt(0);
			QLineEdit* pEdit = (QLineEdit*)pItem->widget();
			pEdit->setText(QString::number(fRetValue));
		}
	}
}


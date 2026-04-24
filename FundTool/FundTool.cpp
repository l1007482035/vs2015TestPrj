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

	// 最后一列拉伸填充剩余空间
	tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget->setStyleSheet(
		"QTableWidget::item:selected { background-color: rgb(0,120,215); color: white; }"
	);

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
				, "", "", "", "", "");
		}
	}
}

void FundTool::showEvent(QShowEvent *event)
{
}

bool FundTool::QueryDiyJingzhi(QString qsFundCode,QString qsBeginDate, QString qsEndDate, double* pfAvgJingZhi)
{
	//先算第一页
	double fTotalJingZhi = 0.0;
	int nDataCount = 0;
	int nTotalCount = 0;
	if (!CalFundValue(qsFundCode, qsBeginDate, qsEndDate, 1, fTotalJingZhi, nDataCount, nTotalCount))
	{
		theLog.Write(_T("!!FundTool::QueryDiyJingzhi,1,CalFundValue,fail"));
		return false;
	}
	int nPages = ceil((double)nTotalCount / 20.0);
	theLog.Write(_T("FundTool::QueryDiyJingzhi,2,fTotalJingZhi=%f,nDataCount=%d,nTotalCount=%d,nPages=%d")
		, fTotalJingZhi, nDataCount, nTotalCount, nPages);
	if (nPages > 2)
	{
		for (int i = 0;i < nPages-1;i++)//遍历剩余页数
		{
			double fTotalJingZhiTmp = 0.0;
			int nDataCountTmp = 0;
			int nTotalCountTmp = 0;
			if (!CalFundValue(qsFundCode, qsBeginDate, qsEndDate, i+2, fTotalJingZhiTmp, nDataCountTmp, nTotalCountTmp))//第二页开始
			{
				theLog.Write(_T("!!FundTool::QueryDiyJingzhi,3,CalFundValue,fail,nPageIndex=%d"),i + 2);
				return false;
			}
			nDataCount += nDataCountTmp;
			fTotalJingZhi += fTotalJingZhiTmp;
			theLog.Write(_T("FundTool::QueryDiyJingzhi,4,nPageIndex=%d,nDataCountTmp=%d,fTotalJingZhiTmp=%f"), i + 2, nDataCountTmp, fTotalJingZhiTmp);
		}

	}
	*pfAvgJingZhi = fTotalJingZhi / nDataCount;
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

bool FundTool::CalFundValue(QString qsFundCode, QString qsBeginDate, QString qsEndDate, int nPageIndex, double& fTotalJingzhi, int& nDataCount, int& nTotalCount)
{
	CHttpClient oClient;
	QString qsUrl = QString("http://api.fund.eastmoney.com/f10/lsjz?fundCode=%1&pageIndex=%2&pageSize=20&startDate=%3&endDate=%4")
		.arg(qsFundCode).arg(nPageIndex).arg(qsBeginDate).arg(qsEndDate);
	std::string sResponse;
	std::list<std::string> oList;
	oList.push_back("Referer:http://fundf10.eastmoney.com/");
	oList.push_back("User-Agent:Mozilla/5.0");
	theLog.Write(_T("FundTool::CalFundValue,qsUrl=%s"), qsUrl.toStdWString().c_str());
	int nRet = oClient.Get(qsUrl.toStdString(), &oList, sResponse);
	theLog.Write(_T("FundTool::QueryDiyJingzhi,0,nRet=%d,sResponse=%s"), nRet, CCommonFun::UTF8ToUnicode(sResponse.c_str()));
	if (nRet!= 0)
	{
		theLog.Write(_T("!!FundTool::CalFundValue,1,nRet=%d"), nRet);
		return false;
	}
	Json::Value jsValue;
	Json::Reader jsReader;
	if (!jsReader.parse(sResponse, jsValue))
	{
		theLog.Write(_T("!!FundTool::CalFundValue,2,parse fail"));
		return false;
	}

	int nErrcode = jsValue["ErrCode"].asInt();
	if (nErrcode != 0)
	{
		theLog.Write(_T("!!FundTool::CalFundValue,3,nErrcode=%d"), nErrcode);
		return false;
	}
	nTotalCount = jsValue["TotalCount"].asInt();
	Json::Value jsData = jsValue["Data"];
	if (jsData.type() != Json::objectValue)
	{
		theLog.Write(_T("!!FundTool::CalFundValue,4,jsData is not json object"));
		return false;
	}
	Json::Value jsLiShiJingZhi = jsData["LSJZList"];
	if (jsLiShiJingZhi.type() != Json::arrayValue)
	{
		theLog.Write(_T("!!FundTool::CalFundValue,5,jsLiShiJingZhi is not json arrary"));
		return false;
	}
	nDataCount = jsLiShiJingZhi.size();
	for (int i = 0;i < nDataCount;i++)
	{
		fTotalJingzhi += std::stod(jsLiShiJingZhi[i]["DWJZ"].asString());
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
		pItem->setTextColor(Qt::green);
	}
	else
	{
		pItem->setTextColor(Qt::red);
	}
}

void FundTool::SetAvgCol(int nRowIndex, int nColIndex, QString qsCurJingzhi, QString qsAvgValue)
{
	QTableWidgetItem *pItem = tableWidget->item(nRowIndex, nColIndex);
	pItem->setTextAlignment(Qt::AlignCenter);
	tableWidget->setItem(nRowIndex, nColIndex, pItem);
	if (qsCurJingzhi.toDouble() > qsAvgValue.toDouble())
	{
		pItem->setTextColor(Qt::green);
	}
	else
	{
		pItem->setTextColor(Qt::red);
	}
	pItem->setText(qsAvgValue);
}

void FundTool::AddOneRow(QString qsFundName, QString qsFundCode, QString qsCurJingZhi
	, QString qsAvg30, QString qsAvg60, QString qsAvg90, QString qsAvgyear)
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




	AddAvgCol(nRowCount, 3,qsCurJingZhi,qsAvg30);
	AddAvgCol(nRowCount, 4, qsCurJingZhi, qsAvg60);
	AddAvgCol(nRowCount, 5, qsCurJingZhi, qsAvg90);
	AddAvgCol(nRowCount, 6, qsCurJingZhi, qsAvgyear);

	// ===== 第三列：两个按钮 =====
	QWidget* widget = new QWidget();
	QPushButton* pQueryPushButton = new QPushButton(u8"查询");
	QPushButton* pDeletePushButton = new QPushButton(u8"删除");
	pQueryPushButton->setMinimumHeight(30);
	pDeletePushButton->setMinimumHeight(30);

	// 布局
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->addWidget(pQueryPushButton);
	layout->addWidget(pDeletePushButton);
	layout->setContentsMargins(0, 0, 0, 0);

	widget->setLayout(layout);

	// 放入单元格
	tableWidget->setCellWidget(nRowCount, 7, widget);
	connect(pQueryPushButton, SIGNAL(clicked()), this, SLOT(on_cell_querypushbutton_clicked()));
	connect(pDeletePushButton, SIGNAL(clicked()), this, SLOT(on_cell_deletepushbutton_clicked()));
}


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
	QDate qBeginDate30 = qCurDate.addDays(30*-1);
	QDate qBeginDate60 = qCurDate.addDays(60 * -1);
	QDate qBeginDate90 = qCurDate.addDays(90 * -1);
	QDate qBeginDateYear = QDate(qCurDate.year(),1,1);

	QString qsBeginDate30 = qBeginDate30.toString(Qt::ISODate);
	QString qsBeginDate60 = qBeginDate60.toString(Qt::ISODate);
	QString qsBeginDate90 = qBeginDate90.toString(Qt::ISODate);
	QString qsBeginDateYear = qBeginDateYear.toString(Qt::ISODate);

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

	AddOneRow(qsFundName,qsFundCode,qsCurJingZhi,qsAvg30, qsAvg60, qsAvg90, qsAvgYear);
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
	QDate qBeginDate30 = qCurDate.addDays(30 * -1);
	QDate qBeginDate60 = qCurDate.addDays(60 * -1);
	QDate qBeginDate90 = qCurDate.addDays(90 * -1);
	QDate qBeginDateYear = QDate(qCurDate.year(), 1, 1);
	QString qsFundName;
	double fCurJingzhi = 0.0;

	QString qsBeginDate30 = qBeginDate30.toString(Qt::ISODate);
	QString qsBeginDate60 = qBeginDate60.toString(Qt::ISODate);
	QString qsBeginDate90 = qBeginDate90.toString(Qt::ISODate);
	QString qsBeginDateYear = qBeginDateYear.toString(Qt::ISODate);

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

	SetAvgCol(nRow, 3, QString::number(fCurJingzhi), QString::number(fAvgJingZhi30));
	SetAvgCol(nRow, 4, QString::number(fCurJingzhi), QString::number(fAvgJingZhi60));
	SetAvgCol(nRow, 5, QString::number(fCurJingzhi), QString::number(fAvgJingZhi90));
	SetAvgCol(nRow, 6, QString::number(fCurJingzhi), QString::number(fAvgJingZhiYear));
	

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
		QWidget* pWidget = tableWidget->cellWidget(i,7);
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


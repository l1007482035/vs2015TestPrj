#include "stdafx.h"
#include "DualColoredBall.h"
#include <QDialog>
#include <vector>
#include "QYiLouTongJi.h"
#pragma execution_character_set("utf-8")


DualColoredBall::DualColoredBall(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	//tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//pushButton_save_2->setHidden(true);
	m_oVRedBall.push_back(pushButton_1);m_oVRedBall.push_back(pushButton_2);m_oVRedBall.push_back(pushButton_3);m_oVRedBall.push_back(pushButton_4);
	m_oVRedBall.push_back(pushButton_5);m_oVRedBall.push_back(pushButton_6);m_oVRedBall.push_back(pushButton_7);m_oVRedBall.push_back(pushButton_8);
	m_oVRedBall.push_back(pushButton_9);m_oVRedBall.push_back(pushButton_10);m_oVRedBall.push_back(pushButton_11);m_oVRedBall.push_back(pushButton_12);
	m_oVRedBall.push_back(pushButton_13);m_oVRedBall.push_back(pushButton_14);m_oVRedBall.push_back(pushButton_15);m_oVRedBall.push_back(pushButton_16);
	m_oVRedBall.push_back(pushButton_17);m_oVRedBall.push_back(pushButton_18);m_oVRedBall.push_back(pushButton_19);m_oVRedBall.push_back(pushButton_20);
	m_oVRedBall.push_back(pushButton_21);m_oVRedBall.push_back(pushButton_22);m_oVRedBall.push_back(pushButton_23);m_oVRedBall.push_back(pushButton_24);
	m_oVRedBall.push_back(pushButton_25);m_oVRedBall.push_back(pushButton_26);m_oVRedBall.push_back(pushButton_27);m_oVRedBall.push_back(pushButton_28);
	m_oVRedBall.push_back(pushButton_29);m_oVRedBall.push_back(pushButton_30);m_oVRedBall.push_back(pushButton_31);m_oVRedBall.push_back(pushButton_32);
	m_oVRedBall.push_back(pushButton_33);
	m_oVBlueBall.push_back(pushButton_blue1); m_oVBlueBall.push_back(pushButton_blue2); m_oVBlueBall.push_back(pushButton_blue3); m_oVBlueBall.push_back(pushButton_blue4);
	m_oVBlueBall.push_back(pushButton_blue5); m_oVBlueBall.push_back(pushButton_blue6); m_oVBlueBall.push_back(pushButton_blue7); m_oVBlueBall.push_back(pushButton_blue8);
	m_oVBlueBall.push_back(pushButton_blue9); m_oVBlueBall.push_back(pushButton_blue10); m_oVBlueBall.push_back(pushButton_blue11); m_oVBlueBall.push_back(pushButton_blue12);
	m_oVBlueBall.push_back(pushButton_blue13); m_oVBlueBall.push_back(pushButton_blue14); m_oVBlueBall.push_back(pushButton_blue15); m_oVBlueBall.push_back(pushButton_blue16);
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//tableWidget->verticalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch)
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents)

	//tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应高度
	
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列

	tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	tableWidget_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//tableWidget_3->setColumnWidth(0, 30); tableWidget_3->setColumnWidth(1, 30);
	//tableWidget_3->setColumnWidth(2, 30); tableWidget_3->setColumnWidth(3, 30);
	//tableWidget_3->setColumnWidth(4, 30);
	m_pQYiLouTongJi = new QYiLouTongJi;

	LoadData();
}

void DualColoredBall::showEvent(QShowEvent *event)
{
}

void DualColoredBall::closeEvent(QCloseEvent *event)
{
	QMessageBox box(this);
	QPushButton* yesBtn = box.addButton("是(&Y)", QMessageBox::YesRole);
	box.setDefaultButton(yesBtn);
	QPushButton* noBtn = box.addButton("否(&N)", QMessageBox::NoRole);
	box.setText("是否保存数据？");
	box.setWindowTitle("关闭");
	box.setIcon(QMessageBox::Question);
	box.exec();

	if (box.clickedButton() == yesBtn)
	{
		SaveData();
	}
	else if (box.clickedButton() == noBtn)
	{ 
	}
}

void DualColoredBall::LoadData()
{
	//红球
	for (int i = 0;i < 33;i++)
	{
		CString szKey;
		szKey.Format(_T("red%d"), i + 1);
		int nState = theIniFile.GetVal(_T("Conf"), szKey,-1);
		if (nState == 0)//禁用
		{
			m_oVRedBall[i]->SetForbided();
		}
		else if (nState == 1)//选择
		{
			m_oVRedBall[i]->SetRedSelected(true);
		}
		else if (nState == 2)//未选
		{
			m_oVRedBall[i]->SetRedSelected(false);
		}
	}

	//蓝球
	for (int i = 0; i < 16; i++)
	{
		CString szKey;
		szKey.Format(_T("blue%d"), i + 1);
		int nState = theIniFile.GetVal(_T("Conf"), szKey, -1);
		if (nState == 0)//禁用
		{
			m_oVBlueBall[i]->SetForbided();
		}
		else if (nState == 1)//选择
		{
			m_oVBlueBall[i]->SetBlueSelected(true);
		}
		else if (nState == 2)//未选
		{
			m_oVBlueBall[i]->SetBlueSelected(false);
		}
	}


	for (int i = 0;i < 20;i++)
	{
		CString szKey;
		szKey.Format(_T("tableRow%d"), i);
		CString szBalls = theIniFile.GetVal(_T("Conf"), szKey, _T(""));
		if (szBalls.IsEmpty())
		{
			break;
		}
		CStringArray szAry;
		CCommonFun::StringSplit(szBalls, &szAry, _T(","));
		std::vector<int> oRed;
		int nBlue = 0;
		int nCount = szAry.GetCount();
		if (nCount == 7)
		{
			for (int i = 0; i < nCount; i++)
			{
				if (i == 6)
				{
					nBlue = _ttoi(szAry.GetAt(i).GetString());
				}
				else
				{
					oRed.push_back(_ttoi(szAry.GetAt(i).GetString()));
				}
			}
			AddRow(oRed,nBlue);
		}
		
	
	}
	lineEdit_dan->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("dan"), _T("")).GetString()));
	lineEdit_tuo->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("tuo"), _T("")).GetString()));
	lineEdit_blue->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("lan"), _T("")).GetString()));

	CString szCurNo = theIniFile.GetVal(_T("YiLou"),_T("CurNo"),_T(""));
	int nCurNo = _ttoi(szCurNo.GetString());
	lineEdit_curno->setText(QString::number(nCurNo));
	int nCol = tableWidget_2->columnCount();
	tableWidget_2->insertColumn(nCol++);
	tableWidget_2->insertColumn(nCol++);
	tableWidget_2->insertColumn(nCol++);
	tableWidget_2->insertColumn(nCol++);
	tableWidget_2->setColumnWidth(0, 80);
	tableWidget_2->setColumnWidth(1, 80);
	tableWidget_2->setColumnWidth(2, 80);
	tableWidget_2->setColumnWidth(3, 80);
	QStringList horList;
	horList << "红球";
	horList << QString::number(nCurNo);
	horList << QString::number(--nCurNo);
	horList << "出现总次数";
	tableWidget_2->setHorizontalHeaderLabels(horList);

	if (CSQliteDataSvc::GetInstance().GetShuangSeQiuRedYiLou(m_oYiLouVector))
	{
		AddYiLouToTable(m_oYiLouVector);
	}

	std::vector<ST_RedInfo> oRedInfoVect;//降序
	if (CSQliteDataSvc::GetInstance().GetShuangSeQiuRedInfo(oRedInfoVect))
	{
		for (auto it: oRedInfoVect)
		{
			AddOneRowRedInfo(it);
		}
// 		int nCount = tableWidget_3->rowCount();
// 		if (nCount > 20)
// 		{
// 			for (int i = 0; i < nCount - 20;i++)
// 			{
// 				tableWidget_3->setRowHidden(i,true);
// 			}
// 		}
	}

	CString szPre1 = theIniFile.GetVal(_T("Conf"), _T("pre1"), _T(""));
	CString szPre2 = theIniFile.GetVal(_T("Conf"), _T("pre2"), _T(""));
	CString szPre3 = theIniFile.GetVal(_T("Conf"), _T("pre3"), _T(""));
	CString szPre4 = theIniFile.GetVal(_T("Conf"), _T("pre4"), _T(""));
	CString szFixBall = theIniFile.GetVal(_T("Conf"), _T("fixball"), _T(""));
	int nCount1 = theIniFile.GetVal(_T("Conf"), _T("sel1"), 0);
	int nCount2 = theIniFile.GetVal(_T("Conf"), _T("sel2"), 0);
	int nCount3 = theIniFile.GetVal(_T("Conf"), _T("sel3"), 0);
	int nCount4 = theIniFile.GetVal(_T("Conf"), _T("sel4"), 0);
	lineEdit_pre1->setText(QString::fromStdWString(szPre1.GetString()));
	lineEdit_pre2->setText(QString::fromStdWString(szPre2.GetString()));
	lineEdit_pre3->setText(QString::fromStdWString(szPre3.GetString()));
	lineEdit_pre4->setText(QString::fromStdWString(szPre4.GetString()));
	lineEdit_fixball->setText(QString::fromStdWString(szFixBall.GetString()));
	lineEdit_selcount1->setText(QString::number(nCount1));
	lineEdit_selcount2->setText(QString::number(nCount2));
	lineEdit_selcount3->setText(QString::number(nCount3));
	lineEdit_selcount4->setText(QString::number(nCount4));
	CString szDate = theIniFile.GetVal(_T("Conf"), _T("lastsavetime"), _T(""));
	label_23->setText(QString::fromStdWString(szDate.GetString()));
}

void DualColoredBall::SaveData()
{
	//保存红球
	for (int i = 0;i < 33;i++)
	{
		CString szKey;
		szKey.Format(_T("red%d"),i+1);
		if (m_oVRedBall[i]->isForbided())
		{
			theIniFile.SetVal(_T("Conf"), szKey, 0);
		}
		else if (m_oVRedBall[i]->isSelected())
		{
			theIniFile.SetVal(_T("Conf"), szKey, 1);
		}
		else
		{
			theIniFile.SetVal(_T("Conf"), szKey, 2);
		}
	}
	//蓝球
	for (int i = 0;i < 16;i++)
	{
		CString szKey;
		szKey.Format(_T("blue%d"), i + 1);
		if (m_oVBlueBall[i]->isForbided())
		{
			theIniFile.SetVal(_T("Conf"), szKey, 0);
		}
		else if (m_oVBlueBall[i]->isSelected())
		{
			theIniFile.SetVal(_T("Conf"), szKey, 1);
		}
		else
		{
			theIniFile.SetVal(_T("Conf"), szKey, 2);
		}
	}
	
	int nRow = tableWidget->rowCount();
	//清空
	for (int i = 0;i < 20;i++)
	{
		CString szKey;
		szKey.Format(_T("tableRow%d"), i);
		theIniFile.SetVal(_T("Conf"), szKey, _T(""));
	}
	for (int i = 0;i < nRow;i++)
	{
		QString qsBalls;
		for (int j = 0;j < 7;j++)
		{
			QString	qsBall = tableWidget->item(i, j)->text();
			qsBalls += ",";
			qsBalls += qsBall;
		}
		qsBalls = qsBalls.right(qsBalls.length() - 1);
		CString szKey;
		szKey.Format(_T("tableRow%d"),i);
		theIniFile.SetVal(_T("Conf"), szKey, qsBalls.toStdWString().c_str());
	}
	CString szDan = lineEdit_dan->text().toStdWString().c_str();
	CString szTuo = lineEdit_tuo->text().toStdWString().c_str();
	CString szLan = lineEdit_blue->text().toStdWString().c_str();
	szDan.Trim(); szTuo.Trim(); szLan.Trim();
	szDan.Replace(_T("  "), _T(" "));
	szTuo.Replace(_T("  "), _T(" "));
	szLan.Replace(_T("  "), _T(" "));
	theIniFile.SetVal(_T("Conf"), _T("dan"), szDan);
	theIniFile.SetVal(_T("Conf"), _T("tuo"), szTuo);
	theIniFile.SetVal(_T("Conf"), _T("lan"), szLan);

	CString szPre1 = lineEdit_pre1->text().toStdWString().c_str();
	CString szPre2 = lineEdit_pre2->text().toStdWString().c_str();
	CString szPre3 = lineEdit_pre3->text().toStdWString().c_str();
	CString szPre4 = lineEdit_pre4->text().toStdWString().c_str();
	CString szFixBall = lineEdit_fixball->text().toStdWString().c_str();
	int nCount1 = lineEdit_selcount1->text().toInt();
	int nCount2 = lineEdit_selcount2->text().toInt();
	int nCount3 = lineEdit_selcount3->text().toInt();
	int nCount4 = lineEdit_selcount4->text().toInt();
	szPre1.Trim(); szPre2.Trim(); szPre3.Trim(); szPre4.Trim(); szFixBall.Trim();
	szPre1.Replace(_T("  "), _T(" "));
	szPre2.Replace(_T("  "), _T(" "));
	szPre3.Replace(_T("  "), _T(" "));
	szPre4.Replace(_T("  "), _T(" "));
	szFixBall.Replace(_T("  "), _T(" "));
	theIniFile.SetVal(_T("Conf"), _T("pre1"), szPre1);
	theIniFile.SetVal(_T("Conf"), _T("pre2"), szPre2);
	theIniFile.SetVal(_T("Conf"), _T("pre3"), szPre3);
	theIniFile.SetVal(_T("Conf"), _T("pre4"), szPre4);
	theIniFile.SetVal(_T("Conf"), _T("sel1"), nCount1);
	theIniFile.SetVal(_T("Conf"), _T("sel2"), nCount2);
	theIniFile.SetVal(_T("Conf"), _T("sel3"), nCount3);
	theIniFile.SetVal(_T("Conf"), _T("sel4"), nCount4);
	theIniFile.SetVal(_T("Conf"), _T("fixball"), szFixBall);
	//on_pushButton_save_2_clicked();
	QDateTime oDate = QDateTime::currentDateTime();
	QString qsDate = oDate.toString("yyyy-MM-dd hh:mm:ss");
	label_23->setText(qsDate);
	theIniFile.SetVal(_T("Conf"),_T("lastsavetime"),qsDate.toStdWString().c_str());

}

#include <random>
#include <chrono>

//从预选区选出几个球添加到选择区
void DualColoredBall::SelectFromPreSection(std::vector<int>& inVData, std::vector<int>& outVData, int nNumber)
{
	outVData.clear();
	if (inVData.size() < nNumber || inVData.size() == 0)
	{
		return;
	}

	int nCount = 0;
	std::vector<int> oVIndex;//从预选号数组中选出的号码索引
	//std::random_device rd;
	std::default_random_engine eng/*(rd())*/;
	std::uniform_int_distribution<unsigned> distribution(0, inVData.size()-1);
	
	bool bNeed = true;
	while (1)
	{
		eng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		int nIndex = distribution(eng);//从待选区随机产生一个索引
		bool bNeed = true;
		for (int j = 0; j < nCount; j++)//遍历已经选择的索引数组
		{
			if (oVIndex[j] == nIndex)//如果索引数组存在此索引则退出循环
			{
				bNeed = false;
				break;
			}
		}
		if (bNeed)
		{
			oVIndex.push_back(nIndex);
			nCount++;
		}

		if (nCount == nNumber)
		{
			break;
		}
	}

	for (auto it : oVIndex)
	{
		outVData.push_back(inVData[it]);
	}
	std::sort(outVData.begin(), outVData.end());
}

//从预选区选出1个球添加到选择区
int DualColoredBall::SelectOneFromPreSection(std::vector<int>& inVData)
{
	if (inVData.size() == 0)
	{
		return 0;
	}
	int nCount = 0;
	//std::random_device rd;
	std::default_random_engine eng/*(rd())*/;
	std::uniform_int_distribution<unsigned> u(0, inVData.size() - 1);

	bool bNeed = true;
	eng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	int nIndex = u(eng);//从待选区随机产生一个索引
	return inVData[nIndex];
}


CString DualColoredBall::GetRedBallQu(int nBall)
{
	CString szQu;
	if (nBall >= 1 && nBall <= 6)
	{
		szQu = _T("1");
	}
	else if (nBall >= 7 && nBall <= 13)
	{
		szQu = _T("2");
	}
	else if (nBall >= 14 && nBall <= 20)
	{
		szQu = _T("3");
	}
	else if (nBall >= 21 && nBall <= 27)
	{
		szQu = _T("4");
	}
	else if (nBall >= 28 && nBall <= 33)
	{
		szQu = _T("5");
	}
	return szQu;
}


void DualColoredBall::AddRow(std::vector<int>& vRedBall, int nBlueBall)
{
	if (vRedBall.size() != 6)
	{
		return;
	}
	int nRowCount = tableWidget->rowCount();
	tableWidget->insertRow(nRowCount);
	int nQuJian1 = 0;
	int nQuJian2 = 0;
	int nQuJian3 = 0;
	//0
	QTableWidgetItem *pItem0 = new QTableWidgetItem;
	pItem0->setText(QString::number(vRedBall[0]));
	pItem0->setTextAlignment(Qt::AlignCenter);
	pItem0->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 0, pItem0);

	//1
	QTableWidgetItem *pItem1 = new QTableWidgetItem;
	pItem1->setText(QString::number(vRedBall[1]));
	pItem1->setTextAlignment(Qt::AlignCenter);
	pItem1->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 1, pItem1);
	//2
	QTableWidgetItem *pItem2 = new QTableWidgetItem;
	pItem2->setText(QString::number(vRedBall[2]));
	pItem2->setTextAlignment(Qt::AlignCenter);
	pItem2->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 2, pItem2);
	//3
	QTableWidgetItem *pItem3 = new QTableWidgetItem;
	pItem3->setText(QString::number(vRedBall[3]));
	pItem3->setTextAlignment(Qt::AlignCenter);
	pItem3->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 3, pItem3);
	//4
	QTableWidgetItem *pItem4 = new QTableWidgetItem;
	pItem4->setText(QString::number(vRedBall[4]));
	pItem4->setTextAlignment(Qt::AlignCenter);
	pItem4->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 4, pItem4);
	//5
	QTableWidgetItem *pItem5 = new QTableWidgetItem;
	pItem5->setText(QString::number(vRedBall[5]));
	pItem5->setTextAlignment(Qt::AlignCenter);
	pItem5->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 5, pItem5);
	//6蓝球
	QTableWidgetItem *pItem6 = new QTableWidgetItem;
	pItem6->setText(QString::number(nBlueBall));
	pItem6->setTextAlignment(Qt::AlignCenter);
	pItem6->setForeground(Qt::blue);
	tableWidget->setItem(nRowCount, 6, pItem6);

	//7红遗区
	CString szYiLouQu = _T("1 2 3 4 5");
	for (int i = 0; i < vRedBall.size(); i++)
	{
		CString szQu = GetRedBallQu(vRedBall[i]);
		szYiLouQu.Replace(szQu, _T(""));
	}
	szYiLouQu.Replace(_T("  "), _T(" "));
	szYiLouQu.Trim();

	QTableWidgetItem *pItem7 = new QTableWidgetItem;
	pItem7->setText(QString::fromStdWString(szYiLouQu.GetString()));
	pItem7->setTextAlignment(Qt::AlignCenter);
	pItem7->setForeground(Qt::red);
	tableWidget->setItem(nRowCount, 7, pItem7);

	//8编辑计划任务
	QPushButton *pDel = new QPushButton(tr("删除"));
	pDel->setStyleSheet("max-height:15px;min-height:15px");
	tableWidget->setCellWidget(nRowCount, 8, pDel);
	connect(pDel, SIGNAL(clicked()), this, SLOT(on_del_pushbutton_clicked()));

	tableWidget->setRowHeight(nRowCount, 18);
}

void DualColoredBall::AddYiLouToTable(std::vector<ST_YiLou>& oYiLouVector)
{
	for (auto it : oYiLouVector)
	{
		int nRowCount = tableWidget_2->rowCount();
		ST_YiLou oYiLou = it;
		int nRedIdex = oYiLou.nBallIndex;
		int nCurYiLou = oYiLou.nCurYiLou;
		int nLastYiLou = oYiLou.nLastYiLou;
		int nTotalAppear = oYiLou.nTotalAppear;
		QTableWidgetItem *pItem0 = new QTableWidgetItem;
		QTableWidgetItem *pItem1 = new QTableWidgetItem;
		QTableWidgetItem *pItem2 = new QTableWidgetItem;
		QTableWidgetItem *pItem3 = new QTableWidgetItem;
		pItem0->setText(QString::number(nRedIdex));
		pItem1->setText(QString::number(nCurYiLou));
		pItem2->setText(QString::number(nLastYiLou));
		pItem3->setText(QString::number(nTotalAppear));
		tableWidget_2->insertRow(nRowCount);
		tableWidget_2->setItem(nRowCount, 0, pItem0);
		tableWidget_2->setItem(nRowCount, 1, pItem1);
		tableWidget_2->setItem(nRowCount, 2, pItem2);
		tableWidget_2->setItem(nRowCount, 3, pItem3);
	}

	for (int i = 0;i < tableWidget_2->rowCount();i++)
	{
		tableWidget_2->setRowHeight(i, 18);
	}
}

void DualColoredBall::AddOneRowRedInfo(ST_RedInfo& oInfo)
{
	int nRow = tableWidget_3->rowCount();
	tableWidget_3->insertRow(nRow);

	QTableWidgetItem* pItem0 = new QTableWidgetItem;
	QTableWidgetItem* pItem1 = new QTableWidgetItem;
	QTableWidgetItem* pItem2 = new QTableWidgetItem;
	QTableWidgetItem* pItem3 = new QTableWidgetItem;
	QTableWidgetItem* pItem4 = new QTableWidgetItem;
	pItem0->setTextAlignment(Qt::AlignCenter);
	pItem1->setTextAlignment(Qt::AlignCenter);
	pItem2->setTextAlignment(Qt::AlignCenter);
	pItem3->setTextAlignment(Qt::AlignCenter);
	pItem4->setTextAlignment(Qt::AlignCenter);

	pItem0->setText(QString::fromStdWString(oInfo.cSerial));
	pItem1->setText(QString::fromStdWString(oInfo.cKaiHao));
	pItem2->setText(QString::fromStdWString(oInfo.cChuXianQu));
	pItem3->setText(QString::fromStdWString(oInfo.cShangQiYiLou));
	pItem4->setText(QString::fromStdWString(oInfo.cYiLouQu));

	tableWidget_3->setItem(nRow, 0, pItem0);
	tableWidget_3->setItem(nRow, 1, pItem1);
	tableWidget_3->setItem(nRow, 2, pItem2);
	tableWidget_3->setItem(nRow, 3, pItem3);
	tableWidget_3->setItem(nRow, 4, pItem4);
	tableWidget_3->setRowHeight(nRow, 20);	
}

//四区预选区随机一注
void DualColoredBall::on_pushButton_prechoice1_clicked()
{
	std::vector<int> vRedBall;
	std::vector<int> vBlueBall;
	std::vector<int> vRedSelectBall;
	for (int i = 0; i < 33; i++)
	{
		if (m_oVRedBall[i]->isSelected())
		{
			vRedBall.push_back(i + 1);
		}
	}
	for (int i = 0; i < 16; i++)
	{
		if (m_oVBlueBall[i]->isSelected())
		{
			vBlueBall.push_back(i + 1);
		}
	}

	SelectFromPreSection(vRedBall, vRedSelectBall, 6);
	int nBlue = SelectOneFromPreSection(vBlueBall);
	AddRow(vRedSelectBall, nBlue);
}

//四区预选区随机五注
void DualColoredBall::on_pushButton_prechoice5_clicked()
{
	on_pushButton_clear_clicked();
	for (int i = 0; i < 5; i++)
	{
		on_pushButton_prechoice1_clicked();
	}
}

//随机一注
void DualColoredBall::on_pushButton_rand1_clicked()
{
#if 1
	//std::random_device rd;
	std::default_random_engine engine/*(rd())*/;
	std::uniform_int_distribution<unsigned> distribution1(1, 33);
	std::uniform_int_distribution<unsigned> distribution2(1, 16);

	std::vector<int> red(6);
	int cnt = 0, i = 0;
	while (6 > cnt)
	{
		//engine.seed(rd());
		engine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		int num = distribution1(engine);
		for (i = 0; i < cnt; i++)
		{
			if (num == red[i])
			{
				break;
			}
		}
		if (i == cnt)
		{
			red[cnt++] = num;
		}
	}
	int nBlue = distribution2(engine);
	std::sort(red.begin(), red.end());
	AddRow(red, nBlue);
#else
	srand((unsigned)time(NULL) + (unsigned)rand());
	std::vector<int> red(6);
	int cnt = 0, i = 0;
	while (6 > cnt)
	{
		int num = rand() % 33 + 1;
		for (i = 0; i < cnt; i++)
		{
			if (num == red[i])
			{
				break;
			}
		}
		if (i == cnt)
		{
			red[cnt++] = num;
		}
	}
	int nBlue = rand() % 16 + 1;
	std::sort(red.begin(), red.end());
	AddRow(red, nBlue);
#endif
}

//随机五注
void DualColoredBall::on_pushButton_rand5_clicked()
{
	on_pushButton_clear_clicked();
	for (int i = 0;i< 5;i++)
	{
		on_pushButton_rand1_clicked();
	}

}

//清空列已选
void DualColoredBall::on_pushButton_clear_clicked()
{
	while (tableWidget->rowCount())
	{
		tableWidget->removeRow(0);
	}
}

//删除一注
void DualColoredBall::on_del_pushbutton_clicked()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	QModelIndex idx = tableWidget->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	int nRow = idx.row();
	int nCol = idx.column();
	if (nCol == 8)
	{
		tableWidget->removeRow(nRow);
	}
} 

void DualColoredBall::on_pushButton_save_clicked()
{
	SaveData();
}

int64_t Factorial(int64_t n)
{
	int64_t res = n;
	if (n > 1)
		res = res*Factorial(n - 1);
	return res;

}

int64_t Combination(int nNum1, int nNum2)
{
	int64_t nVa1 = Factorial(nNum1);
	int64_t nVa2 = Factorial(nNum1 - nNum2)*Factorial(nNum2);
	int64_t nRet = nVa1 / nVa2;
	return nRet;
}

void DualColoredBall::on_pushButton_calc_clicked()
{
	CStringArray szAry1;
	CStringArray szAry2;
	CStringArray szAry3;
	CString szDan = lineEdit_dan->text().toStdWString().c_str();
	CString szTuo = lineEdit_tuo->text().toStdWString().c_str();
	CString szLan = lineEdit_blue->text().toStdWString().c_str();
	szDan.Trim(); szTuo.Trim(); szLan.Trim();
	szDan.Replace(_T("  "),_T(" "));
	szDan.Replace(_T("  "), _T(" "));
	szTuo.Replace(_T("  "), _T(" "));
	szTuo.Replace(_T("  "), _T(" "));
	szLan.Replace(_T("  "), _T(" "));
	szLan.Replace(_T("  "), _T(" "));
	CCommonFun::StringSplit(szDan,&szAry1,_T(" "));
	CCommonFun::StringSplit(szTuo, &szAry2, _T(" "));
	CCommonFun::StringSplit(szLan, &szAry3, _T(" "));
	int nDanCount = szAry1.GetCount();
	int nTuoCount = szAry2.GetCount();
	int nLanCount = szAry3.GetCount();

	if (nDanCount < 1)
	{
		QMessageBox::information(this,"提示","胆码个数不能小于1");
		return;
	}
	if (nDanCount > 5)
	{
		QMessageBox::information(this, "提示", "胆码个数不能大于5");
		return;
	}
	if (nTuoCount < 1)
	{
		QMessageBox::information(this, "提示", "拖码个数不能小于1");
		return;
	}
	if (nDanCount > 20)
	{
		QMessageBox::information(this, "提示", "拖码个数不能大于20");
		return;
	}
	if (nLanCount < 1)
	{
		QMessageBox::information(this, "提示", "蓝球个数不能小于1");
		return;
	}

	for (int i = 0;i < nTuoCount;i++)
	{
		for (int j = 0;j < nDanCount;j++)
		{
			if (szAry1.GetAt(j) == szAry2.GetAt(i))
			{
				QMessageBox::information(this, "提示", "拖码号不能与胆码号相同");
				return;
			}
		}
	}

	if (nDanCount + nTuoCount < 6)
	{
		QMessageBox::information(this, "提示", "胆拖号总数必须大于5");
		return;
	}

	int nLeft = 6 - nDanCount;
	int nRedComs = Combination(nTuoCount,nLeft);
	int nBlueComs = Combination(nLanCount, 1);
	int nComs = nRedComs*nBlueComs;
	int nMoney = nComs * 2;
	QString qsRet = QString("共%1注\n共%2元").arg(nComs).arg(nMoney);
	label_calcret->setText(qsRet);

}

void DualColoredBall::on_pushButton_cleardantuo_clicked()
{
	lineEdit_blue->clear();
	lineEdit_dan->clear();
	lineEdit_tuo->clear();
}

//计算组合数
void DualColoredBall::on_pushButton_calczuhe_clicked()
{
	int nTotal = lineEdit_total->text().toInt();
	int nSelect = lineEdit_select->text().toInt();
	if (nTotal < nSelect)
	{
		QMessageBox::information(this,"提示","总数不能小于选择数");
		return;
	}
	int nRet = Combination(nTotal, nSelect);
	lineEdit_comtotal->setText(QString::number(nRet));
}


//遗漏统计页确定
void DualColoredBall::on_pushButton_sure_clicked()
{
	CString szNewNo = lineEdit_newno->text().toStdWString().c_str();
	szNewNo.Trim();
	szNewNo.Replace(_T("   "),_T(" "));
	szNewNo.Replace(_T("  "), _T(" "));
	lineEdit_newno->setText(QString::fromStdWString(szNewNo.GetString()));
	int nSize = m_oYiLouVector.size();

	CStringArray ary1;
	CCommonFun::StringSplit(lineEdit_newno->text().toStdWString().c_str(), &ary1, _T(" "));
	if (ary1.GetCount() == 6)
	{
		//重新给m_oYiLouVector赋值
		for (auto& it : m_oYiLouVector)
		{
			ST_YiLou oYiLou = it;
			int nRedIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			int nTotalAppear = oYiLou.nTotalAppear;
			bool bFind = false;
			do
			{
				for (int i = 0; i < ary1.GetCount(); i++)
				{
					if (it.nBallIndex == _ttoi(ary1.GetAt(i)))
					{
						bFind = true;
						break;
					}
				}
			} while (0);
			it.nLastYiLou = it.nCurYiLou;
			if (bFind)
			{
				it.nCurYiLou = 0;
				it.nTotalAppear += 1;
			}
			else
			{
				it.nCurYiLou += 1;
			}
		}

		std::sort(m_oYiLouVector.begin(),m_oYiLouVector.end());

		while (tableWidget_2->rowCount())
		{
			tableWidget_2->removeRow(0);
		}
		AddYiLouToTable(m_oYiLouVector);
		int nCurNo = lineEdit_curno->text().toInt();
		lineEdit_curno->setText(QString::number(++nCurNo));

		QStringList horList;
		horList << "红球";
		horList << QString::number(nCurNo);
		horList << QString::number(--nCurNo);
		horList << "出现总次数";
		tableWidget_2->setHorizontalHeaderLabels(horList);

	}


	CString szYiLouQu = _T("1 2 3 4 5");
	CString szKaiHaoQu;
	for (int i = 0; i < ary1.GetCount(); i++)
	{
		CString szQu = GetRedBallQu(_ttoi(ary1.GetAt(i)));
		szKaiHaoQu.AppendFormat(_T("%s "),szQu);
		szYiLouQu.Replace(szQu, _T(""));
	}
	szYiLouQu.Trim();
	szYiLouQu.Replace(_T("   "), _T(" "));
	szYiLouQu.Replace(_T("  "), _T(" "));

	szKaiHaoQu.Trim();
	szKaiHaoQu.Replace(_T("   "), _T(" "));
	szKaiHaoQu.Replace(_T("  "), _T(" "));
	CString szCurNo = lineEdit_curno->text().toStdWString().c_str();

	int nRowCount1 = tableWidget_2->rowCount();
	CString szSQYiLou;
	for (int i = 0; i < nRowCount1; i++)
	{
		QTableWidgetItem *pItem1 = tableWidget_2->item(i, 1);
		QTableWidgetItem *pItem2 = tableWidget_2->item(i, 2);
		if (pItem1->text().toInt() == 0)
		{
			szSQYiLou.Append(pItem2->text().toStdWString().c_str());
			szSQYiLou.Append(_T(" "));
		}
	}
	szSQYiLou.TrimRight();
 	ST_RedInfo oInfo;
	wcscpy(oInfo.cSerial, szCurNo.GetString());
	wcscpy(oInfo.cKaiHao, szNewNo.GetString());
	wcscpy(oInfo.cChuXianQu, szKaiHaoQu.GetString());
	wcscpy(oInfo.cShangQiYiLou, szSQYiLou.GetString());
	wcscpy(oInfo.cYiLouQu, szYiLouQu.GetString());
	AddOneRowRedInfo(oInfo);
}
//遗漏统计页保存
void DualColoredBall::on_pushButton_save_2_clicked()
{
	//备份文件
	CopyFile(_T("dual.ini"), _T("dual.ini.bak"), FALSE);
	CopyFile(_T("dual.db"), _T("dual.db.bak"), FALSE);

	int nRowCount = tableWidget_2->rowCount();
	std::vector<ST_YiLou> oVector;
	if (!lineEdit_newno->text().isEmpty())
	{
		int nCurNo = lineEdit_curno->text().toInt();
		theIniFile.SetVal(_T("YiLou"), _T("CurNo"), nCurNo);
	}
	
	for (int i = 0;i < nRowCount;i++)
	{
		ST_YiLou oYiLou;
		QTableWidgetItem* pItem0 = tableWidget_2->item(i,0);
		QTableWidgetItem* pItem1 = tableWidget_2->item(i, 1);
		QTableWidgetItem* pItem2 = tableWidget_2->item(i, 2);
		QTableWidgetItem* pItem3 = tableWidget_2->item(i, 3);
		oYiLou.nBallIndex = pItem0->text().toInt();
		oYiLou.nCurYiLou = pItem1->text().toInt();
		oYiLou.nLastYiLou = pItem2->text().toInt();
		oYiLou.nTotalAppear = pItem3->text().toInt();
		oVector.push_back(oYiLou);
	}
	CSQliteDataSvc::GetInstance().InsertShuangSeQiuRedYiLou(oVector);

	int nRowCount2 = tableWidget_3->rowCount();
	std::vector<ST_RedInfo> oRedInfoVect;

	for (int i = 0; i < nRowCount2; i++)
	{
		ST_RedInfo oInfo;
		QTableWidgetItem* pItem0 = tableWidget_3->item(i, 0);
		QTableWidgetItem* pItem1 = tableWidget_3->item(i, 1);
		QTableWidgetItem* pItem2 = tableWidget_3->item(i, 2);
		QTableWidgetItem* pItem3 = tableWidget_3->item(i, 3);
		QTableWidgetItem* pItem4 = tableWidget_3->item(i, 4);
		wcscpy(oInfo.cSerial, pItem0->text().toStdWString().c_str());
		wcscpy(oInfo.cKaiHao, pItem1->text().toStdWString().c_str());
		wcscpy(oInfo.cChuXianQu, pItem2->text().toStdWString().c_str());
		wcscpy(oInfo.cShangQiYiLou, pItem3->text().toStdWString().c_str());
		wcscpy(oInfo.cYiLouQu, pItem4->text().toStdWString().c_str());
		oRedInfoVect.push_back(oInfo);
	}
	CSQliteDataSvc::GetInstance().InsertShuangSeQiuRedInfo(oRedInfoVect);
	QMessageBox::information(this,"提示","保存成功");
}

//胆拖区一注
void DualColoredBall::on_pushButton_dantuo1_clicked()
{
	CString szDan = lineEdit_dan->text().toStdWString().c_str();
	CString szTuo = lineEdit_tuo->text().toStdWString().c_str();
	CString szLan = lineEdit_blue->text().toStdWString().c_str();

	szDan.Trim(); szTuo.Trim(); szLan.Trim();
	szDan.Replace(_T("  "), _T(" "));
	szDan.Replace(_T("  "), _T(" "));
	szTuo.Replace(_T("  "), _T(" "));
	szTuo.Replace(_T("  "), _T(" "));
	szLan.Replace(_T("  "), _T(" "));
	szLan.Replace(_T("  "), _T(" "));

	std::vector<int> oRedBall;
	std::vector<int> oTuoBall;
	std::vector<int> oTuoBallSelected;
	std::vector<int> oLanBall;

	CStringArray ary1; CStringArray ary2; CStringArray ary3;
	CCommonFun::StringSplit(szDan, &ary1, _T(" "));
	CCommonFun::StringSplit(szTuo, &ary2, _T(" "));
	CCommonFun::StringSplit(szLan, &ary3, _T(" "));
	int nCount1 = ary1.GetCount();
	int nCount2 = ary2.GetCount();
	int nCount3 = ary3.GetCount();
	int nLeft = 6 - nCount1;
	if (nLeft > nCount2 || nCount3 < 1)
	{
		//QMessageBox::information(this,"提示","胆拖数量不对");
		return;
	}

	for (int i = 0;i < nCount2;i++)
	{
		oTuoBall.push_back(_ttoi(ary2.GetAt(i).GetString()));
	}
	SelectFromPreSection(oTuoBall, oTuoBallSelected, nLeft);
	
	for (int i = 0;i < nCount1;i++)
	{
		oRedBall.push_back(_ttoi(ary1.GetAt(i).GetString()));
	}
	oRedBall.insert(oRedBall.end(), oTuoBallSelected.begin(), oTuoBallSelected.end());
	for (int i = 0; i < nCount3; i++)
	{
		oLanBall.push_back(_ttoi(ary3.GetAt(i).GetString()));
	}

	//蓝球
	int nBlue = SelectOneFromPreSection(oLanBall);
	std::sort(oRedBall.begin(), oRedBall.end());
	AddRow(oRedBall, nBlue);

}

//胆拖区五注
void DualColoredBall::on_pushButton_dantuo5_clicked()
{
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_dantuo1_clicked();
	}
}

//执行选号
void DualColoredBall::on_pushButton_zhixing_clicked()
{
	CString szStr = lineEdit_1->text().toStdWString().c_str();
	int nNeed = lineEdit_2->text().toInt();
	if (nNeed <= 0)
	{
		return;
	}
	szStr.Trim();
	szStr.Replace(_T("  "), _T(" "));
	szStr.Replace(_T("  "), _T(" "));
	CStringArray ary1;
	CCommonFun::StringSplit(szStr, &ary1, _T(" "));
	int nCount = ary1.GetCount();
	if (nNeed > nCount)
	{
		return;
	}
	std::vector<int> oInTmp;
	std::vector<int> oOutTmp;
	for (int i = 0;i < nCount;i++)
	{
		oInTmp.push_back(_ttoi(ary1.GetAt(i).GetString()));
	}
	SelectFromPreSection(oInTmp, oOutTmp, nNeed);
	CString szTmp;
	for (auto it:oOutTmp)
	{
		szTmp += QString::number(it).toStdWString().c_str();
		szTmp += _T(" ");
	}
	szTmp.TrimRight();
	lineEdit_3->setText(QString::fromStdWString(szTmp.GetString()));

}

//执行五次
void DualColoredBall::on_pushButton_zhixing5_clicked()
{
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_zhixing2_clicked();
	}
}

//清除选择
void DualColoredBall::on_pushButton_clearsel_clicked()
{
	for (int i = 0; i < 33; i++)
	{
		m_oVRedBall[i]->SetRedSelected(false);
	}
	for (int i = 0; i < 16; i++)
	{
		m_oVBlueBall[i]->SetBlueSelected(false);
	}
}

void DualColoredBall::on_pushButton_zhixing2_clicked()
{
	CString szPr1 = lineEdit_pre1->text().toStdWString().c_str();
	CString szPr2 = lineEdit_pre2->text().toStdWString().c_str();
	CString szPr3 = lineEdit_pre3->text().toStdWString().c_str();
	CString szPr4 = lineEdit_pre4->text().toStdWString().c_str();
	CString szFixBall = lineEdit_fixball->text().toStdWString().c_str();
	szPr1.Replace(_T("  "), _T(" "));szPr2.Replace(_T("  "), _T(" "));
	szPr3.Replace(_T("  "), _T(" "));szPr4.Replace(_T("  "), _T(" "));
	szFixBall.Replace(_T("  "), _T(" "));
	szPr1.Trim(); szPr2.Trim(); szPr3.Trim(); szPr4.Trim(); szFixBall.Trim();
	int nCount1 = lineEdit_selcount1->text().toInt();
	int nCount2 = lineEdit_selcount2->text().toInt();
	int nCount3 = lineEdit_selcount3->text().toInt();
	int nCount4 = lineEdit_selcount4->text().toInt();

	CStringArray szAry5;
	CCommonFun::StringSplit(szFixBall, &szAry5, _T(" "));
	int nCount5 = szAry5.GetCount();
// 	if (szPr1.IsEmpty() && szPr2.IsEmpty() && szPr3.IsEmpty() && szPr4.IsEmpty())
// 	{
// 		return;
// 	}
// 	if (nCount5 == 0 && nCount1 == 0 && nCount2 == 0 && nCount3 == 0 && nCount4 == 0)
// 	{
// 		return;
// 	}
	if (nCount1 + nCount2 + nCount3 + nCount4 + nCount5> 6)
	{
		return;
	}
	CStringArray szAry1; CStringArray szAry2; CStringArray szAry3; CStringArray szAry4;
	CCommonFun::StringSplit(szPr1, &szAry1, _T(" "));
	CCommonFun::StringSplit(szPr2, &szAry2, _T(" "));
	CCommonFun::StringSplit(szPr3, &szAry3, _T(" "));
	CCommonFun::StringSplit(szPr4, &szAry4, _T(" "));
	int nSize1 = szAry1.GetCount();
	int nSize2 = szAry2.GetCount();
	int nSize3 = szAry3.GetCount();
	int nSize4 = szAry4.GetCount();
	
	std::vector<int> oRedSelOri;//原始红球
	std::vector<int> oRedSelPre1;//待选红球
	std::vector<int> oRedSelPre2;//待选红球
	std::vector<int> oRedSelPre3;//待选红球
	std::vector<int> oRedSelPre4;//待选红球
	std::vector<int> oRedRet;//最终选出的红球
	std::vector<int> oRedOutTmp;
	std::vector<int> oVBlue;
	
	for (int i = 0;i < m_oVRedBall.size();i++)
	{
		if (m_oVRedBall[i]->isSelected())
		{
			oRedSelOri.push_back(i + 1);
		}
	}

	for (int i = 0;i < nSize1;i++)
	{
		int nBall = _ttoi(szAry1.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedSelPre1.push_back(nBall);
	}
	for (int i = 0; i < nSize2; i++)
	{
		int nBall = _ttoi(szAry2.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedSelPre2.push_back(nBall);
	}	
	for (int i = 0; i < nSize3; i++)
	{
		int nBall = _ttoi(szAry3.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedSelPre3.push_back(nBall);
	}	
	for (int i = 0; i < nSize4; i++)
	{
		int nBall = _ttoi(szAry4.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedSelPre4.push_back(nBall);
	}

	for (int i = 0;i < nCount5;i++)
	{
		int nBall = _ttoi(szAry5.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedRet.push_back(_ttoi(szAry5.GetAt(i).GetString()));
	}
	int nLeft = 6;
	SelectFromPreSection(oRedSelPre1,oRedOutTmp,nCount1);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(),oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre2, oRedOutTmp, nCount2);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(),oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre3, oRedOutTmp, nCount3);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(),oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre4, oRedOutTmp, nCount4);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(),oRedOutTmp.end());
	nLeft = nLeft - nCount5;
	if (nLeft > 0)
	{
		SelectFromPreSection(oRedSelOri, oRedOutTmp, nLeft);
		oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	}
	
	for (int i = 0; i < m_oVBlueBall.size(); i++)
	{
		if (m_oVBlueBall[i]->isSelected())
		{
			oVBlue.push_back(i + 1);
		}
	}
	int nBlue = SelectOneFromPreSection(oVBlue);
	if (oRedRet.size() == 6)
	{
		std::sort(oRedRet.begin(),oRedRet.end());
		AddRow(oRedRet, nBlue);
	}

}

//红球全选
void DualColoredBall::on_pushButton_selredall_clicked()
{
	for (auto it:m_oVRedBall)
	{
		it->SetRedSelected(true);
	}
}

void DualColoredBall::on_pushButton_yilou_clicked()
{
	m_pQYiLouTongJi->showMaximized();
}

void DualColoredBall::on_pushButton_sort_clicked()
{
	while (tableWidget_2->rowCount())
	{
		tableWidget_2->removeRow(0);
	}
	std::vector<ST_YiLou_BallIdx> oTmp(33);

	memcpy(&oTmp[0],&m_oYiLouVector[0], sizeof(ST_YiLou) * 33);
	std::sort(oTmp.begin(), oTmp.end());

	std::vector<ST_YiLou> oTmp1(33);
	memcpy(&oTmp1[0], &oTmp[0], sizeof(ST_YiLou) * 33);
	AddYiLouToTable(oTmp1);

}

#include "stdafx.h"
#include "DaLeTou.h"
#include <QDialog>
#include <vector>
#pragma execution_character_set("utf-8")


#include <algorithm>
#include <QuShiTu.h>
#include "QYiLouTongJi.h"


DaLeTou::DaLeTou(QWidget *parent)
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
	m_oVRedBall.push_back(pushButton_33); m_oVRedBall.push_back(pushButton_34); m_oVRedBall.push_back(pushButton_35);
	m_oVBlueBall.push_back(pushButton_blue1); m_oVBlueBall.push_back(pushButton_blue2); m_oVBlueBall.push_back(pushButton_blue3); m_oVBlueBall.push_back(pushButton_blue4);
	m_oVBlueBall.push_back(pushButton_blue5); m_oVBlueBall.push_back(pushButton_blue6); m_oVBlueBall.push_back(pushButton_blue7); m_oVBlueBall.push_back(pushButton_blue8);
	m_oVBlueBall.push_back(pushButton_blue9); m_oVBlueBall.push_back(pushButton_blue10); m_oVBlueBall.push_back(pushButton_blue11); m_oVBlueBall.push_back(pushButton_blue12);	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//tableWidget->verticalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	
	//tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch)
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents)

	//tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置自适应高度
	
	//tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);    //x先自适应宽度
// 	tableWidget_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	m_pQuShiTu = new QuShiTu;
	m_pYiLouTongJi = new QYiLouTongJi;

	tableWidget_5->setHidden(true);
	tableWidget_blue->setHidden(true);

	LoadData();
}

void DaLeTou::showEvent(QShowEvent *event)
{
}

void DaLeTou::closeEvent(QCloseEvent *event)
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

void DaLeTou::LoadData()
{
	//红球
	for (int i = 0;i < 35;i++)
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
	for (int i = 0; i < 12; i++)
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
		std::vector<int> oBlue;
		int nCount = szAry.GetCount();
		if (nCount == 7)
		{
			for (int i = 0; i < nCount; i++)
			{
				if (i > 4)
				{
					oBlue.push_back(_ttoi(szAry.GetAt(i).GetString()));
				}
				else
				{
					oRed.push_back(_ttoi(szAry.GetAt(i).GetString()));
				}
			}
			AddRow(oRed, oBlue);
		}
		
	
	}
	lineEdit_hongdan->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("hongdan"), _T("")).GetString()));
	lineEdit_hongtuo->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("hongtuo"), _T("")).GetString()));
	lineEdit_landan->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("landan"), _T("")).GetString()));
	lineEdit_lantuo->setText(QString::fromStdWString(theIniFile.GetVal(_T("Conf"), _T("lantuo"), _T("")).GetString()));


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
	horList << QString::number(nCurNo-1);
	horList << "出现总次数";
	tableWidget_2->setHorizontalHeaderLabels(horList);

	nCol = tableWidget_5->columnCount();
	tableWidget_5->insertColumn(nCol++);
	tableWidget_5->insertColumn(nCol++);
	tableWidget_5->insertColumn(nCol++);
	tableWidget_5->setColumnWidth(0, 80);
	tableWidget_5->setColumnWidth(1, 80);
	tableWidget_5->setColumnWidth(2, 80);
	QStringList horList2;
	horList2 << "蓝球";
	horList2 << QString::number(nCurNo);
	horList2 << QString::number(nCurNo-1);
	tableWidget_5->setHorizontalHeaderLabels(horList2);

	if (CSQliteDataSvc::GetInstance().GetDaLeTouRedYiLou(m_oYiLouRedVector))
	{
		AddRedYiLouToTable<ST_YiLou>(m_oYiLouRedVector);
	}

	if (CSQliteDataSvc::GetInstance().GetDaLeTouBlueYiLou(m_oYiLouBlueVector))
	{
		AddBlueYiLouToTable(m_oYiLouBlueVector);
	}

	std::list<ST_RedInfo> oRedTongLianYiLouList;//同号连号 降序
	if (CSQliteDataSvc::GetInstance().GetDaLeTouRedInfo(oRedTongLianYiLouList))
	{
		while (oRedTongLianYiLouList.size() > 0)
		{
			ST_RedInfo oInfo = oRedTongLianYiLouList.back();
			oRedTongLianYiLouList.pop_back();
			AddRedTongLianYiLouToTable(oInfo.cSerial, oInfo.cKaiHao, oInfo.cChuXianQu, oInfo.cYiLouQu, oInfo.cShangQiYiLou);

		}
	}
	
	int nBlue1 = 0;
	int nBlue2 = 0;
	if (CSQliteDataSvc::GetInstance().GetBlueBallBySerial(nBlue1, nBlue2,nCurNo))
	{
		label_blue1->setText(QString::number(nBlue1));
		label_blue2->setText(QString::number(nBlue2));
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

	int nQuShi1 = theIniFile.GetVal(_T("Conf"), _T("qushi1"), 0);
	int nQuShi2 = theIniFile.GetVal(_T("Conf"), _T("qushi2"), 0);
	comboBox->setCurrentIndex(nQuShi1);
	comboBox_2->setCurrentIndex(nQuShi2);

	CString szDate = theIniFile.GetVal(_T("Conf"), _T("lastsavetime"), _T(""));
	label_43->setText(QString::fromStdWString(szDate.GetString()));

	//m_oYiLouRedVector

	std::vector<int> oTotalAppearVect;

	int nTotal = 0;
	for (auto&it: m_oYiLouRedVector)
	{
		oTotalAppearVect.push_back(it.nTotalAppear);
		nTotal += it.nTotalAppear;
	}
	std::sort(oTotalAppearVect.begin(),oTotalAppearVect.end());
	label_min->setText(QString::number(oTotalAppearVect.front()));
	label_max->setText(QString::number(oTotalAppearVect.back()));
	double fVal = nTotal / oTotalAppearVect.size();
	QString valueStr = QString::number(fVal, 'f', 2);
	label_av->setText(valueStr);
	//两个蓝球列表
	if (CSQliteDataSvc::GetInstance().GetDaLeTouBlue(m_oBlueVector))
	{
		AddBlueBallToTable(m_oBlueVector);
	}
}

void DaLeTou::SaveData()
{
	//保存红球
	for (int i = 0;i < 35;i++)
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
	//蓝球1
	for (int i = 0;i < 12;i++)
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
	CString szHongDan = lineEdit_hongdan->text().toStdWString().c_str();
	CString szHongTuo = lineEdit_hongtuo->text().toStdWString().c_str();
	CString szLanDan = lineEdit_landan->text().toStdWString().c_str();
	CString szLanTuo = lineEdit_lantuo->text().toStdWString().c_str();

	szHongDan.Trim(); szHongTuo.Trim(); szLanDan.Trim(); szLanTuo.Trim();
	szHongDan.Replace(_T("  "), _T(" ")); szHongDan.Replace(_T("  "), _T(" "));
	szHongTuo.Replace(_T("  "), _T(" ")); szHongTuo.Replace(_T("  "), _T(" "));
	szLanDan.Replace(_T("  "), _T(" ")); szLanDan.Replace(_T("  "), _T(" "));
	szLanTuo.Replace(_T("  "), _T(" ")); szLanTuo.Replace(_T("  "), _T(" "));
	theIniFile.SetVal(_T("Conf"), _T("hongdan"), szHongDan);
	theIniFile.SetVal(_T("Conf"), _T("hongtuo"), szHongTuo);
	theIniFile.SetVal(_T("Conf"), _T("landan"), szLanDan);
	theIniFile.SetVal(_T("Conf"), _T("landan"), szLanTuo);

	//on_pushButton_save_2_clicked();
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
	theIniFile.SetVal(_T("Conf"), _T("qushi1"),comboBox->currentIndex());
	theIniFile.SetVal(_T("Conf"), _T("qushi2"), comboBox_2->currentIndex());
	QDateTime oDate = QDateTime::currentDateTime();
	QString qsDate = oDate.toString("yyyy-MM-dd hh:mm:ss");
	label_43->setText(qsDate);
	theIniFile.SetVal(_T("Conf"), _T("lastsavetime"), qsDate.toStdWString().c_str());
}

#include <random>
#include <chrono>

//从预选区选出几个球添加到选择区
void DaLeTou::SelectFromPreSection(std::vector<int>& inVData, std::vector<int>& outVData, int nNumber)
{
	outVData.clear();
	if (inVData.size() < nNumber || inVData.size() == 0)
	{
		return;
	}
	int nCount = 0;
	std::vector<int> oVIndex;//从预选号数组中选出的号码索引
	//std::random_device rd;
	std::default_random_engine eng;
	std::uniform_int_distribution<unsigned> u(0, inVData.size()-1);
	bool bNeed = true;
	while (1)
	{
		Sleep(5);
		eng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		int nIndex = u(eng);//从待选区随机产生一个索引
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
int DaLeTou::SelectOneFromPreSection(std::vector<int>& inVData)
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
	Sleep(5);
	eng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	int nIndex = u(eng);//从待选区随机产生一个索引
	return inVData[nIndex];
}

void DaLeTou::UpdateRedTableAfterSure()
{
	int nSize = m_oYiLouRedVector.size();
	CStringArray ary1;
	CCommonFun::StringSplit(lineEdit_newno->text().toStdWString().c_str(), &ary1, _T(" "));
	if (ary1.GetCount() == 7)
	{
		//重新设置红球遗漏列表
		for (auto& it : m_oYiLouRedVector)
		{
			ST_YiLou oYiLou = it;
			int nRedIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			bool bFind = false;
			do
			{
				for (int i = 0; i < ary1.GetCount()-2; i++)
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

		std::sort(m_oYiLouRedVector.begin(), m_oYiLouRedVector.end());

		while (tableWidget_2->rowCount())
		{
			tableWidget_2->removeRow(0);
		}

		AddRedYiLouToTable<ST_YiLou>(m_oYiLouRedVector);
		int nCurNo = lineEdit_curno->text().toInt();
		QStringList horList;
		horList << "红球";
		horList << QString::number(nCurNo);
		horList << QString::number(nCurNo-1);
		horList << "出现总次数";
		tableWidget_2->setHorizontalHeaderLabels(horList);

		std::vector<int> oTotalAppearVect;

		int nTotal = 0;
		for (auto&it : m_oYiLouRedVector)
		{
			oTotalAppearVect.push_back(it.nTotalAppear);
			nTotal += it.nTotalAppear;
		}
		std::sort(oTotalAppearVect.begin(), oTotalAppearVect.end());
		label_min->setText(QString::number(oTotalAppearVect.front()));
		label_max->setText(QString::number(oTotalAppearVect.back()));
		double fVal = nTotal / oTotalAppearVect.size();
		QString valueStr = QString::number(fVal, 'f', 2);
		label_av->setText(valueStr);


	}

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
	CString szChuXianQu;
	CString szKaiHao;
	CString szYiLouQu = _T("1 2 3 4 5");
	for (int i = 0; i < ary1.GetCount()-2; i++)
	{
		CString szQu = GetRedBallQu(_ttoi(ary1.GetAt(i)));
		szChuXianQu.AppendFormat(_T("%s "),szQu);
		szKaiHao.AppendFormat(_T("%s "), ary1.GetAt(i));
		szYiLouQu.Replace(szQu,_T(""));
	}
	szSQYiLou.Trim();
	szChuXianQu.Trim();
	szKaiHao.Trim();
	szYiLouQu.Replace(_T("  "),_T(" "));
	szYiLouQu.Trim();
	
	AddRedTongLianYiLouToTable(szCurNo,szKaiHao, szChuXianQu, szYiLouQu, szSQYiLou);
}

void DaLeTou::UpdateBlueTableAfterSure()
{
	int nSize = m_oYiLouBlueVector.size();
	CStringArray ary1;
	CCommonFun::StringSplit(lineEdit_newno->text().toStdWString().c_str(), &ary1, _T(" "));
	int nBlue1 = 0;
	int nBlue2 = 0;
	if (ary1.GetCount() == 7)
	{
		nBlue1 = std::min(_ttoi(ary1.GetAt(5)), _ttoi(ary1.GetAt(6)));
		nBlue2 = std::max(_ttoi(ary1.GetAt(5)), _ttoi(ary1.GetAt(6)));
		label_blue1->setText(QString::number(nBlue1));
		label_blue2->setText(QString::number(nBlue2));
		ST_DaLeTouBlue oBlue;
		oBlue.nSerial = lineEdit_curno->text().toInt();
		oBlue.nBlue1 = nBlue1;
		oBlue.nBlue2 = nBlue2;
		m_oBlueVector.push_back(oBlue);

		//重新设置蓝球遗漏列表
		for (auto& it : m_oYiLouBlueVector)
		{
			ST_YiLou oYiLou = it;
			int nRedIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			bool bFind = false;
			do
			{
				for (int i = 5; i < ary1.GetCount(); i++)
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
			}
			else
			{
				it.nCurYiLou += 1;
			}
		}

		std::sort(m_oYiLouBlueVector.begin(), m_oYiLouBlueVector.end());

		while (tableWidget_5->rowCount())
		{
			tableWidget_5->removeRow(0);
		}
		AddBlueYiLouToTable(m_oYiLouBlueVector);
		int nCurNo = lineEdit_curno->text().toInt();
		QStringList horList;
		horList << "蓝球";
		horList << QString::number(nCurNo);
		horList << QString::number(--nCurNo);
		tableWidget_5->setHorizontalHeaderLabels(horList);

	}
	
	CString szCurNo = lineEdit_curno->text().toStdWString().c_str();

	int nRowCount1 = tableWidget_5->rowCount();
	CString szSQYiLou;
	for (int i = 0; i < nRowCount1; i++)
	{
		QTableWidgetItem *pItem1 = tableWidget_5->item(i, 1);
		QTableWidgetItem *pItem2 = tableWidget_5->item(i, 2);
		if (pItem1->text().toInt() == 0)
		{
			szSQYiLou.Append(pItem2->text().toStdWString().c_str());
			szSQYiLou.Append(_T(" "));
		}
	}

	while (tableWidget_blue->rowCount())
	{
		tableWidget_blue->removeRow(0);
	}
	AddBlueBallToTable(m_oBlueVector);
}


CString DaLeTou::GetRedBallQu(int nBall)
{
	CString szQu;
	if (nBall >=1 && nBall <= 7)
	{
		szQu = _T("1");
	}
	else if (nBall >= 8 && nBall <= 14)
	{
		szQu = _T("2");
	}
	else if (nBall >= 15 && nBall <= 21)
	{
		szQu = _T("3");
	}
	else if (nBall >= 22 && nBall <= 28)
	{
		szQu = _T("4");
	}
	else if (nBall >= 29 && nBall <= 35)
	{
		szQu = _T("5");
	}
	return szQu;
}

void DaLeTou::AddRow(std::vector<int>& vRedBall, std::vector<int>& vBlueBall)
{
	if (vRedBall.size() != 5 || vBlueBall.size() != 2)
	{
		return;
	}
	int nRowCount = tableWidget->rowCount();
	tableWidget->insertRow(nRowCount);
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
	//5蓝球1
	QTableWidgetItem *pItem5 = new QTableWidgetItem;
	pItem5->setText(QString::number(vBlueBall[0]));
	pItem5->setTextAlignment(Qt::AlignCenter);
	pItem5->setForeground(Qt::blue);
	tableWidget->setItem(nRowCount, 5, pItem5);
	//6蓝球2
	QTableWidgetItem *pItem6 = new QTableWidgetItem;
	pItem6->setText(QString::number(vBlueBall[1]));
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
	//6编辑计划任务
	QPushButton *pDel = new QPushButton(tr("删除"));
	pDel->setStyleSheet("max-height:28px;min-height:28px");
	tableWidget->setCellWidget(nRowCount, 8, pDel);
	connect(pDel, SIGNAL(clicked()), this, SLOT(on_del_pushbutton_clicked()));

	//7编辑计划任务
	QPushButton *pQuShi = new QPushButton(tr("趋势"));
	pQuShi->setStyleSheet("max-height:28px;min-height:28px");
	tableWidget->setCellWidget(nRowCount, 9, pQuShi);
	connect(pQuShi, SIGNAL(clicked()), this, SLOT(on_onequshi_pushbutton_clicked()));
}


template<typename T>
void DaLeTou::AddRedYiLouToTable(std::vector<T>& oYiLouVector)
{
	for (auto it : oYiLouVector)
	{
		int nRowCount = tableWidget_2->rowCount();
		T oYiLou = it;
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

	for (int i = 0; i < tableWidget_2->rowCount(); i++)
	{
		tableWidget_2->setRowHeight(i, 18);
	}
}

void DaLeTou::AddBlueYiLouToTable(std::vector<ST_YiLou>& oYiLouVector)
{
	for (auto it : oYiLouVector)
	{
		int nRowCount = tableWidget_5->rowCount();
		ST_YiLou oYiLou = it;
		int nBallIdex = oYiLou.nBallIndex;
		int nCurYiLou = oYiLou.nCurYiLou;
		int nLastYiLou = oYiLou.nLastYiLou;
		QTableWidgetItem *pItem0 = new QTableWidgetItem;
		QTableWidgetItem *pItem1 = new QTableWidgetItem;
		QTableWidgetItem *pItem2 = new QTableWidgetItem;
		pItem0->setText(QString::number(nBallIdex));
		pItem1->setText(QString::number(nCurYiLou));
		pItem2->setText(QString::number(nLastYiLou));
		tableWidget_5->insertRow(nRowCount);
		tableWidget_5->setItem(nRowCount, 0, pItem0);
		tableWidget_5->setItem(nRowCount, 1, pItem1);
		tableWidget_5->setItem(nRowCount, 2, pItem2);
	}

	for (int i = 0; i < tableWidget_5->rowCount(); i++)
	{
		tableWidget_5->setRowHeight(i, 18);
	}
}


void DaLeTou::AddRedTongLianYiLouToTable(CString szQiHao, CString szKaiHao, CString szChuXianQu, CString szYiLouQu, CString szSQYiLou)
{
	int nRow = tableWidget_3->rowCount();
	QTableWidgetItem* pItem0 = new QTableWidgetItem;
	QTableWidgetItem* pItem1 = new QTableWidgetItem;
	QTableWidgetItem* pItem2 = new QTableWidgetItem;
	QTableWidgetItem* pItem3 = new QTableWidgetItem;
	QTableWidgetItem* pItem4 = new QTableWidgetItem;

	pItem0->setText(QString::fromStdWString(szQiHao.GetString()));
	pItem0->setTextAlignment(Qt::AlignCenter);
	pItem1->setText(QString::fromStdWString(szKaiHao.GetString()));
	pItem1->setTextAlignment(Qt::AlignCenter);
	pItem2->setText(QString::fromStdWString(szChuXianQu.GetString()));
	pItem2->setTextAlignment(Qt::AlignCenter);
	pItem3->setText(QString::fromStdWString(szYiLouQu.GetString()));
	pItem3->setTextAlignment(Qt::AlignCenter);
	pItem4->setText(QString::fromStdWString(szSQYiLou.GetString()));
	pItem4->setTextAlignment(Qt::AlignCenter);
	tableWidget_3->insertRow(nRow);
	tableWidget_3->setItem(nRow, 0, pItem0);
	tableWidget_3->setItem(nRow, 1, pItem1);
	tableWidget_3->setItem(nRow, 2, pItem2);
	tableWidget_3->setItem(nRow, 3, pItem3);
	tableWidget_3->setItem(nRow, 4, pItem4);
	tableWidget_3->setRowHeight(nRow, 20);
}


//根据蓝球趋势选出蓝球
BOOL DaLeTou::GetBlueBallByQuShi(int& nBlue1, int& nBlue2)
{//0:左 1:右 2：不变
	int nBlue1QuShi = comboBox->currentIndex();
	int nBlue2QuShi = comboBox_2->currentIndex();
	int nCurBlue1 = label_blue1->text().toInt();
	int nCurBlue2 = label_blue2->text().toInt();
	std::vector<int> oBlueVector;
	if (nBlue1QuShi == 0 && nBlue2QuShi == 0)//blue1小于等于nCurBlue1 blue2小于等于nCurBlue2
	{
		for (int i = 1;i <= nCurBlue1;i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue1 = SelectOneFromPreSection(oBlueVector);
		oBlueVector.clear();
		for (int i = nBlue1 + 1;i <= nCurBlue2;i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue2 = SelectOneFromPreSection(oBlueVector);
	}
	else if (nBlue1QuShi == 0 && nBlue2QuShi == 1)//blue1小于等于nCurBlue1 blue2大于等于nCurBlue2
	{
		for (int i = 1; i <= nCurBlue1; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue1 = SelectOneFromPreSection(oBlueVector);
		oBlueVector.clear();
		for (int i = nCurBlue2; i <= 12; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue2 = SelectOneFromPreSection(oBlueVector);
	}
	else if (nBlue1QuShi == 1 && nBlue2QuShi == 0)//blue1大于等于nCurBlue1 blue2小于等于nCurBlue2
	{
		if (nCurBlue2 - nCurBlue1 - 1 < 2)
		{
			QMessageBox::information(this,"提示","趋势选择不合理");
			return FALSE;
		}
		for (int i = nCurBlue1; i < 12; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue1 = SelectOneFromPreSection(oBlueVector);
		oBlueVector.clear();
		for (int i = nBlue1 + 1; i < nCurBlue2; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue2 = SelectOneFromPreSection(oBlueVector);
	}
	else if (nBlue1QuShi == 1 && nBlue2QuShi == 1)//blue1大于等于nCurBlue1 blue2大于等于nCurBlue2
	{
		for (int i = nCurBlue1; i < 12; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue1 = SelectOneFromPreSection(oBlueVector);
		oBlueVector.clear();
		int nTmp = nBlue1 == nCurBlue2 ? (nCurBlue2 + 1) : (std::max(nBlue1, nCurBlue2) + 1);
		for (int i = nTmp; i <= 12; i++)
		{
			oBlueVector.push_back(i);
		}
		nBlue2 = SelectOneFromPreSection(oBlueVector);
	}
	
	return TRUE;
}

void DaLeTou::AddBlueBallToTable(std::vector<ST_DaLeTouBlue>& oBlueVector)
{
	for (auto it: oBlueVector)
	{
		int nRowCount = tableWidget_blue->rowCount();
		ST_DaLeTouBlue oBlue = it;
		int nSerial = oBlue.nSerial;
		int nBlue1 = oBlue.nBlue1;
		int nBlue2 = oBlue.nBlue2;
	
		QTableWidgetItem *pItem0 = new QTableWidgetItem;
		QTableWidgetItem *pItem1 = new QTableWidgetItem;
		QTableWidgetItem *pItem2 = new QTableWidgetItem;
		pItem0->setText(QString::number(nSerial));
		pItem1->setText(QString::number(nBlue1));
		pItem2->setText(QString::number(nBlue2));
		tableWidget_blue->insertRow(nRowCount);
		tableWidget_blue->setItem(nRowCount, 0, pItem0);
		tableWidget_blue->setItem(nRowCount, 1, pItem1);
		tableWidget_blue->setItem(nRowCount, 2, pItem2);
	}
}

//四区预选区随机一注
void DaLeTou::on_pushButton_prechoice1_clicked()
{
	std::vector<int> vInRedBall;
	std::vector<int> vOutRedBall;
	std::vector<int> vOutBlueBall;
	
	for (int i = 0;i < 35;i++)
	{
		if (m_oVRedBall[i]->isSelected())
		{
			vInRedBall.push_back(i+1);
		}
	}
	SelectFromPreSection(vInRedBall, vOutRedBall,5);
	int nBlue1 = 0, nBlue2 = 0;
	BOOL bRet =	GetBlueBallByQuShi(nBlue1, nBlue2);
	if (nBlue1 > 0 && nBlue1 < nBlue2)
	{
		vOutBlueBall.push_back(nBlue1);
		vOutBlueBall.push_back(nBlue2);
		AddRow(vOutRedBall, vOutBlueBall);
	}
	else
	{
		if (bRet)
		{
			on_pushButton_prechoice1_clicked();
		}
		
	}
	
}

//四区预选区随机五注
void DaLeTou::on_pushButton_prechoice5_clicked()
{
	on_pushButton_clear_clicked();
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_prechoice1_clicked();
	}
}

//四区预选区随机一注
void DaLeTou::on_pushButton_one_clicked()
{
	std::vector<int> vInRedBall;
	std::vector<int> vOutRedBall;

	std::vector<int> vInBlueBall;
	std::vector<int> vOutBlueBall;

	for (int i = 0; i < 35; i++)
	{
		if (m_oVRedBall[i]->isSelected())
		{
			vInRedBall.push_back(i + 1);
		}
	}
	SelectFromPreSection(vInRedBall, vOutRedBall, 5);
	
	for (int i = 0; i < 12; i++)
	{
		if (m_oVBlueBall[i]->isSelected())
		{
			vInBlueBall.push_back(i + 1);
		}
	}
	SelectFromPreSection(vInBlueBall, vOutBlueBall, 2);

	AddRow(vOutRedBall, vOutBlueBall);

}
//四区预选区随机五注
void DaLeTou::on_pushButton_five_clicked()
{
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_one_clicked();
	}
}

//随机一注
void DaLeTou::on_pushButton_rand1_clicked()
{
	//std::random_device rd;
	std::default_random_engine engine/*(rd())*/;
	std::uniform_int_distribution<unsigned> distribution1(1, 35);
	std::uniform_int_distribution<unsigned> distribution2(1, 12);

	std::vector<int> red(5);
	std::vector<int> blue(2);
	int cnt = 0, i = 0;
	while (5 > cnt)
	{
		Sleep(5);
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
	cnt = 0, i = 0;
	while (2 > cnt)
	{
		Sleep(5);
		engine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
		int num = distribution2(engine);
		for (i = 0; i < cnt; i++)
		{
			if (num == blue[i])
			{
				break;
			}
		}
		if (i == cnt)
		{
			blue[cnt++] = num;
		}
	}
	std::sort(red.begin(), red.end());
	std::sort(blue.begin(), blue.end());
	AddRow(red, blue);
}

//随机五注
void DaLeTou::on_pushButton_rand5_clicked()
{
	on_pushButton_clear_clicked();
	for (int j = 0; j < 5; j++)
	{
		on_pushButton_rand1_clicked();
	}
}

//清空列已选
void DaLeTou::on_pushButton_clear_clicked()
{
	while (tableWidget->rowCount())
	{
		tableWidget->removeRow(0);
	}
}

//删除一注
void DaLeTou::on_del_pushbutton_clicked()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	QModelIndex idx = tableWidget->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	int nRow = idx.row();
	int nCol = idx.column();
	tableWidget->removeRow(nRow);
}

//一注后趋势
void DaLeTou::on_onequshi_pushbutton_clicked()
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
		ST_DaLeTouBlue oBlue;
		ST_DaLeTouRed oRed;
		QTableWidgetItem* pItem0 = tableWidget->item(nRow, 0);
		QTableWidgetItem* pItem1 = tableWidget->item(nRow, 1);
		QTableWidgetItem* pItem2 = tableWidget->item(nRow, 2);
		QTableWidgetItem* pItem3 = tableWidget->item(nRow, 3);
		QTableWidgetItem* pItem4 = tableWidget->item(nRow, 4);
		QTableWidgetItem* pItem5 = tableWidget->item(nRow, 5);
		QTableWidgetItem* pItem6 = tableWidget->item(nRow, 6);
		oBlue.nBlue1 = pItem5->text().toInt();
		oBlue.nBlue2 = pItem6->text().toInt();
		oBlue.nSerial = lineEdit_curno->text().toInt() + 1;
		oRed.nRed1 = pItem0->text().toInt();
		oRed.nRed2 = pItem1->text().toInt();
		oRed.nRed3 = pItem2->text().toInt();
		oRed.nRed4 = pItem3->text().toInt();
		oRed.nRed5 = pItem4->text().toInt();
		oRed.nSerial = lineEdit_curno->text().toInt() + 1;
		m_pQuShiTu->Show2(oBlue,oRed);
	}


}

void DaLeTou::on_pushButton_save_clicked()
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

void DaLeTou::on_pushButton_calc_clicked()
{
	CStringArray szAry1;CStringArray szAry2;CStringArray szAry3;CStringArray szAry4;
	CString szHongDan = lineEdit_hongdan->text().toStdWString().c_str();
	CString szHongTuo = lineEdit_hongtuo->text().toStdWString().c_str();
	CString szLanDan = lineEdit_landan->text().toStdWString().c_str();
	CString szLanTuo = lineEdit_lantuo->text().toStdWString().c_str();
	szHongDan.Trim(); szHongTuo.Trim(); szLanDan.Trim(); szLanTuo.Trim();
	szHongDan.Replace(_T("  "),_T(" ")); szHongDan.Replace(_T("  "), _T(" "));
	szHongTuo.Replace(_T("  "), _T(" ")); szHongTuo.Replace(_T("  "), _T(" "));
	szLanDan.Replace(_T("  "), _T(" ")); szLanDan.Replace(_T("  "), _T(" "));
	szLanTuo.Replace(_T("  "), _T(" ")); szLanTuo.Replace(_T("  "), _T(" "));
	CCommonFun::StringSplit(szHongDan,&szAry1,_T(" "));
	CCommonFun::StringSplit(szHongTuo, &szAry2, _T(" "));
	CCommonFun::StringSplit(szLanDan, &szAry3, _T(" "));
	CCommonFun::StringSplit(szLanTuo, &szAry4, _T(" "));
	int nHongDanCount = szAry1.GetCount();
	int nHongTuoCount = szAry2.GetCount();
	int nLanDanCount = szAry3.GetCount();
	int nLanTuoCount = szAry4.GetCount();

	if (nHongDanCount < 1 || nHongDanCount > 4)
	{
		QMessageBox::information(this,"提示","红胆码个数不对");
		return;
	}
	if (nHongTuoCount < 1 || nHongTuoCount > 20)
	{
		QMessageBox::information(this, "提示", "红托码个数不对");
		return;
	}
	if (nLanDanCount < 1 || nLanDanCount > 1)
	{
		QMessageBox::information(this, "提示", "蓝胆码个数不对");
		return;
	}
	if (nLanTuoCount < 1 || nLanTuoCount > 10)
	{
		QMessageBox::information(this, "提示", "蓝托码个数不对");
		return;
	}
	
	for (int i = 0;i < nHongTuoCount;i++)
	{
		for (int j = 0;j < nHongDanCount;j++)
		{
			if (szAry1.GetAt(j) == szAry2.GetAt(i))
			{
				QMessageBox::information(this, "提示", "红拖码号不能与胆码号相同");
				return;
			}
		}
	}

	for (int i = 0; i < nLanTuoCount; i++)
	{
		for (int j = 0; j < nLanDanCount; j++)
		{
			if (szAry3.GetAt(j) == szAry4.GetAt(i))
			{
				QMessageBox::information(this, "提示", "蓝拖码号不能与胆码号相同");
				return;
			}
		}
	}

	if (nHongDanCount + nHongTuoCount < 5)
	{
		QMessageBox::information(this, "提示", "红胆拖号总数必须大于5");
		return;
	}
	if (nLanDanCount + nLanTuoCount < 2)
	{
		QMessageBox::information(this, "提示", "蓝胆拖号总数必须大于2");
		return;
	}

	int nLeftHong = 5 - nHongDanCount;
	int nLeftLan = 2 - nLanDanCount;
	int nRedComs = Combination(nHongTuoCount, nLeftHong);
	int nBlueComs = Combination(nLanTuoCount, nLeftLan);
	int nComs = nRedComs*nBlueComs;
	int nMoney = nComs * 2;
	QString qsRet = QString("共%1注\n共%2元").arg(nComs).arg(nMoney);
	label_calcret->setText(qsRet);
}

void DaLeTou::on_pushButton_cleardantuo_clicked()
{
	lineEdit_hongdan->clear();
	lineEdit_hongtuo->clear();
	lineEdit_landan->clear();
	lineEdit_lantuo->clear();

}

//计算组合数
void DaLeTou::on_pushButton_calczuhe_clicked()
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
void DaLeTou::on_pushButton_sure_clicked()
{
	CString szNewNo = lineEdit_newno->text().toStdWString().c_str();
	szNewNo.Trim();
	szNewNo.Replace(_T("  "), _T(" "));
	szNewNo.Replace(_T("  "), _T(" "));
	lineEdit_newno->setText(QString::fromStdWString(szNewNo.GetString()));
	int nCurNo = lineEdit_curno->text().toInt();
	lineEdit_curno->setText(QString::number(++nCurNo));
	UpdateRedTableAfterSure();
	UpdateBlueTableAfterSure();
}
//遗漏统计页保存
void DaLeTou::on_pushButton_save_2_clicked()
{
	//备份文件
	CopyFile(_T("daletou.ini"),_T("daletou.ini.bak"),FALSE);
	CopyFile(_T("daletou.db"), _T("daletou.db.bak"), FALSE);

	int nRowCount1 = tableWidget_2->rowCount();
	int nRowCount2 = tableWidget_5->rowCount();
	int nRowCount3 = tableWidget_3->rowCount();
	std::list<ST_RedInfo> oList2;
	std::list<ST_RedInfo> oList3;

	std::vector<ST_YiLou> oRedVector;
	std::vector<ST_YiLou> oBlueYiLouVector;
	int nCurNo = lineEdit_curno->text().toInt();
	theIniFile.SetVal(_T("YiLou"), _T("CurNo"), nCurNo);
	for (int i = 0; i < nRowCount1; i++)
	{
		ST_YiLou oYiLou;
		QTableWidgetItem* pItem0 = tableWidget_2->item(i, 0);
		QTableWidgetItem* pItem1 = tableWidget_2->item(i, 1);
		QTableWidgetItem* pItem2 = tableWidget_2->item(i, 2);
		QTableWidgetItem* pItem3 = tableWidget_2->item(i, 3);
		oYiLou.nBallIndex = pItem0->text().toInt();
		oYiLou.nCurYiLou = pItem1->text().toInt();
		oYiLou.nLastYiLou = pItem2->text().toInt();
		oYiLou.nTotalAppear = pItem3->text().toInt();
		oRedVector.push_back(oYiLou);
	}
	CSQliteDataSvc::GetInstance().InsertDaLeTouRedYiLou(oRedVector);

	for (int i = 0; i < nRowCount2; i++)
	{
		ST_YiLou oYiLou;
		QTableWidgetItem* pItem0 = tableWidget_5->item(i, 0);
		QTableWidgetItem* pItem1 = tableWidget_5->item(i, 1);
		QTableWidgetItem* pItem2 = tableWidget_5->item(i, 2);
		oYiLou.nBallIndex = pItem0->text().toInt();
		oYiLou.nCurYiLou = pItem1->text().toInt();
		oYiLou.nLastYiLou = pItem2->text().toInt();
		oBlueYiLouVector.push_back(oYiLou);
	}
	CSQliteDataSvc::GetInstance().InsertDaLeTouBlueYiLou(oBlueYiLouVector);

	for (int i = 0; i < nRowCount3; i++)
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
		wcscpy(oInfo.cYiLouQu, pItem3->text().toStdWString().c_str());
		wcscpy(oInfo.cShangQiYiLou, pItem4->text().toStdWString().c_str());
		oList2.push_back(oInfo);
	}
	CSQliteDataSvc::GetInstance().InsertDaLeTouRedInfo(oList2);
	
	ST_DaLeTouBlue oBlue;
	oBlue.nSerial = nCurNo;
	CStringArray ary;
	CCommonFun::StringSplit(lineEdit_newno->text().toStdWString().c_str(),&ary,_T(" "));
// 	if (ary.GetCount() == 7)
// 	{
// 		oBlue.nBlue1 = std::min(_ttoi(ary.GetAt(5).GetString()), _ttoi(ary.GetAt(6).GetString()));
// 		oBlue.nBlue2 = std::max(_ttoi(ary.GetAt(5).GetString()), _ttoi(ary.GetAt(6).GetString()));
// 		CSQliteDataSvc::GetInstance().InsertDaLeTouBlue(oBlue);
// 	}

	//保存蓝球列表
	std::vector<ST_DaLeTouBlue> oBlueVector;
	int nCount5 = tableWidget_blue->rowCount();
	for (int i = 0;i < nCount5;i++)
	{
		ST_DaLeTouBlue oBlue;
		QTableWidgetItem* pItem0 = tableWidget_blue->item(i, 0);
		QTableWidgetItem* pItem1 = tableWidget_blue->item(i, 1);
		QTableWidgetItem* pItem2 = tableWidget_blue->item(i, 2);
		oBlue.nSerial = pItem0->text().toInt();
		oBlue.nBlue1 = pItem1->text().toInt();
		oBlue.nBlue2 = pItem2->text().toInt();
		oBlueVector.push_back(oBlue);
	}
	CSQliteDataSvc::GetInstance().InsertDaLeTouBlue(oBlueVector);
	QMessageBox::information(this, "提示", "保存成功");

}

//胆拖区一注
void DaLeTou::on_pushButton_dantuo1_clicked()
{
	CString szHongDan = lineEdit_hongdan->text().toStdWString().c_str();
	CString szHongTuo = lineEdit_hongtuo->text().toStdWString().c_str();
	CString szLanDan = lineEdit_landan->text().toStdWString().c_str();
	CString szLanTuo = lineEdit_lantuo->text().toStdWString().c_str();
	szHongDan.Trim(); szHongTuo.Trim(); szLanDan.Trim(); szLanTuo.Trim();
	szHongDan.Replace(_T("  "), _T(" "));szHongDan.Replace(_T("  "), _T(" "));
	szHongTuo.Replace(_T("  "), _T(" "));szHongTuo.Replace(_T("  "), _T(" "));
	szLanDan.Replace(_T("  "), _T(" "));szLanDan.Replace(_T("  "), _T(" "));
	szLanTuo.Replace(_T("  "), _T(" "));szLanTuo.Replace(_T("  "), _T(" "));
	std::vector<int> oRedBall;
	std::vector<int> oHongTuoBall;
	std::vector<int> oHongTuoBallSelected;

	std::vector<int> oLanBall;
	std::vector<int> oLanTuoBall;
	std::vector<int> oLanTuoBallSelected;

	CStringArray ary1; CStringArray ary2; CStringArray ary3; CStringArray ary4;
	CCommonFun::StringSplit(szHongDan, &ary1, _T(" "));
	CCommonFun::StringSplit(szHongTuo, &ary2, _T(" "));
	CCommonFun::StringSplit(szLanDan, &ary3, _T(" "));
	CCommonFun::StringSplit(szLanTuo, &ary4, _T(" "));
	int nCount1 = ary1.GetCount();
	int nCount2 = ary2.GetCount();
	int nCount3 = ary3.GetCount();
	int nCount4 = ary4.GetCount();
	int nHongLeft = 5 - nCount1;
	int nLanLeft = 2 - nCount3;
	if (nHongLeft > nCount2 || nLanLeft > nCount4)
	{
		//QMessageBox::information(this,"提示","胆拖数量不对");
		return;
	}

	//红球
	for (int i = 0;i < nCount2;i++)
	{
		oHongTuoBall.push_back(_ttoi(ary2.GetAt(i).GetString()));
	}
	SelectFromPreSection(oHongTuoBall, oHongTuoBallSelected, nHongLeft);

	for (int i = 0;i < nCount1;i++)
	{
		oRedBall.push_back(_ttoi(ary1.GetAt(i).GetString()));
	}
	oRedBall.insert(oRedBall.end(), oHongTuoBallSelected.begin(), oHongTuoBallSelected.end());
	//蓝球
	for (int i = 0; i < nCount4; i++)
	{
		oLanTuoBall.push_back(_ttoi(ary4.GetAt(i).GetString()));
	}
	SelectFromPreSection(oLanTuoBall, oLanTuoBallSelected, nLanLeft);

	for (int i = 0; i < nCount3; i++)
	{
		oLanBall.push_back(_ttoi(ary3.GetAt(i).GetString()));
	}
	oLanBall.insert(oLanBall.end(), oLanTuoBallSelected.begin(), oLanTuoBallSelected.end());
	std::sort(oRedBall.begin(), oRedBall.end());
	std::sort(oLanBall.begin(), oLanBall.end());
	AddRow(oRedBall, oLanBall);
}

//胆拖区五注
void DaLeTou::on_pushButton_dantuo5_clicked()
{
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_dantuo1_clicked();
	}
}

//执行选号
void DaLeTou::on_pushButton_zhixing_clicked()
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

//执行五次选号
void DaLeTou::on_pushButton_zhixing5_clicked()
{
	for (int i = 0;i < 5;i++)
	{
		on_pushButton_zhixing2_clicked();
	}
}

//清除按钮选择
void DaLeTou::on_pushButton_clearsel_clicked()
{
	for (int i = 0;i < 35;i++)
	{
		m_oVRedBall[i]->SetRedSelected(false);
	}
	for (int i = 0; i < 12; i++)
	{
		m_oVBlueBall[i]->SetBlueSelected(false);
	}
}

void DaLeTou::on_pushButton_zhixing2_clicked()
{
	CString szPr1 = lineEdit_pre1->text().toStdWString().c_str();
	CString szPr2 = lineEdit_pre2->text().toStdWString().c_str();
	CString szPr3 = lineEdit_pre3->text().toStdWString().c_str();
	CString szPr4 = lineEdit_pre4->text().toStdWString().c_str();
	CString szFixBall = lineEdit_fixball->text().toStdWString().c_str();
	szPr1.Replace(_T("  "), _T(" ")); szPr2.Replace(_T("  "), _T(" "));
	szPr3.Replace(_T("  "), _T(" ")); szPr4.Replace(_T("  "), _T(" "));
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
	if (nCount1 + nCount2 + nCount3 + nCount4 + nCount5 > 5)
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

	for (int i = 0; i < m_oVRedBall.size(); i++)
	{
		if (m_oVRedBall[i]->isSelected())
		{
			oRedSelOri.push_back(i + 1);
		}
	}

	for (int i = 0; i < nSize1; i++)
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

	for (int i = 0; i < nCount5; i++)
	{
		int nBall = _ttoi(szAry5.GetAt(i).GetString());
		oRedSelOri.erase(std::remove(std::begin(oRedSelOri), std::end(oRedSelOri), nBall), std::end(oRedSelOri));
		oRedRet.push_back(_ttoi(szAry5.GetAt(i).GetString()));
	}
	int nLeft = 5;
	SelectFromPreSection(oRedSelPre1, oRedOutTmp, nCount1);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre2, oRedOutTmp, nCount2);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre3, oRedOutTmp, nCount3);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	SelectFromPreSection(oRedSelPre4, oRedOutTmp, nCount4);
	nLeft = nLeft - oRedOutTmp.size();
	oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	nLeft = nLeft - nCount5;
	if (nLeft > 0)
	{
		SelectFromPreSection(oRedSelOri, oRedOutTmp, nLeft);
		oRedRet.insert(oRedRet.end(), oRedOutTmp.begin(), oRedOutTmp.end());
	}
	BOOL bRet = FALSE;
	do 
	{
		int nBlue1 = 0, nBlue2 = 0;
		oVBlue.clear();
		bRet = GetBlueBallByQuShi(nBlue1, nBlue2);
		if (nBlue1 > 0 && nBlue1 < nBlue2)
		{
			oVBlue.push_back(nBlue1);
			oVBlue.push_back(nBlue2);
			std::sort(oRedRet.begin(), oRedRet.end());
			break;
		
		}
	} while (0);

	if (oRedRet.size() == 5 && bRet)
	{
		AddRow(oRedRet, oVBlue);
	}
}

//红球全选
void DaLeTou::on_pushButton_selredall_clicked()
{
	for (auto it : m_oVRedBall)
	{
		it->SetRedSelected(true);
	}
}

//蓝球趋势
void DaLeTou::on_pushButton_qushi_clicked()
{
	m_pQuShiTu->Show1();
}

//红遗漏区统计
void DaLeTou::on_pushButton_redyillou_clicked()
{
	m_pYiLouTongJi->show();
}

void DaLeTou::on_pushButton_redsort_clicked()
{
	while (tableWidget_2->rowCount())
	{
		tableWidget_2->removeRow(0);
	}
	std::vector<ST_YiLou_BallIdx> oTmp(35);
	memcpy(&oTmp[0], &m_oYiLouRedVector[0], sizeof(ST_YiLou) * 35);
	std::sort(oTmp.begin(), oTmp.end());
	AddRedYiLouToTable<ST_YiLou_BallIdx>(oTmp);
}

void DaLeTou::on_pushButton_totalsort_clicked()
{
	while (tableWidget_2->rowCount())
	{
		tableWidget_2->removeRow(0);
	}
	std::vector<ST_YiLou_BallTotalIdx> oTmp(35);
	memcpy(&oTmp[0], &m_oYiLouRedVector[0], sizeof(ST_YiLou) * 35);
	std::sort(oTmp.begin(), oTmp.end());
	AddRedYiLouToTable<ST_YiLou_BallTotalIdx>(oTmp);
}

void DaLeTou::on_pushButton_reset_clicked()
{
	while (tableWidget_2->rowCount())
	{
		tableWidget_2->removeRow(0);
	}
	AddRedYiLouToTable<ST_YiLou>(m_oYiLouRedVector);

}

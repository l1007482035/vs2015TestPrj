#include "stdafx.h"
#include "QYiLouTongJi.h"
#pragma execution_character_set("utf-8")

QYiLouTongJi::QYiLouTongJi(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
	m_oTongJi.resize(25,0);
}

QYiLouTongJi::~QYiLouTongJi()
{
}

void QYiLouTongJi::showEvent(QShowEvent *event)
{
	LoadData();
	showMaximized();
}

void QYiLouTongJi::LoadData()
{
	std::vector<int> x(25, 0);
	m_oTongJi.swap(x);
	while (tableWidget->rowCount())
	{
		tableWidget->removeRow(0);
	}
	std::vector<ST_DaLeTouRedYiLou> sRedYiLouVect;
	if (CSQliteDataSvc::GetInstance().GetDaLeTouRedYiLouQu(sRedYiLouVect))
	{
		for (auto& it: sRedYiLouVect)
		{
			AddRow(it);
		}
		int nRowCount = tableWidget->rowCount();
		//加上统计
		tableWidget->insertRow(nRowCount);
		for (int i = 0; i < 26; i++)
		{
			QTableWidgetItem *pItem = new QTableWidgetItem;
			pItem->setTextAlignment(Qt::AlignHCenter);
	
			if (i == 0)
			{
				pItem->setText("所有期统计");
			}
			else
			{
				pItem->setText(QString::number(m_oTongJi[i]));
			}
			
			tableWidget->setItem(nRowCount, i, pItem);
		}

	}
	//隐藏多余的行
	int nRowCount2 = tableWidget->rowCount();
	if (nRowCount2 > 21)//最后一行是统计
	{
		for (int i = 0;i < nRowCount2-21;i++)
		{
			tableWidget->setRowHidden(i,true);
		}
	}
}

void QYiLouTongJi::AddRow(ST_DaLeTouRedYiLou& oInfo)
{
	int nRowCount = tableWidget->rowCount();
	tableWidget->insertRow(nRowCount);
	std::vector<QTableWidgetItem *> oItemVect;
	for (int i = 0;i < 26;i++)
	{
		QTableWidgetItem *pItem = new QTableWidgetItem;
		pItem->setTextAlignment(Qt::AlignCenter);
		oItemVect.push_back(pItem);
		tableWidget->setItem(nRowCount,i,pItem);
	}
	oItemVect[0]->setText(QString::fromStdWString(oInfo.cSerial));

	QString qsQu = QString::fromStdWString(oInfo.cYiLouQu);

	for (int i = 1;i <= 25;i++)
	{
		QString qsHeaderText = tableWidget->horizontalHeaderItem(i)->text();
		if (qsQu.compare(qsHeaderText) == 0)
		{
			oItemVect[i]->setText("√");
			m_oTongJi[i]++;
			break;
		}
	}
}

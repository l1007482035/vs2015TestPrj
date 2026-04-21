#include "stdafx.h"
#include "QBaseDlqWidget.h"
#include "MantunTool.h"
#include "QDanXiang.h"
#include "QSanXiang.h"

QBaseDlqWidget::QBaseDlqWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pCall = (MantunTool*)parent;
}

QBaseDlqWidget::~QBaseDlqWidget()
{
}

void QBaseDlqWidget::SetDevInfo(int64_t nDevId, EN_DevType eType)
{
	m_nDevId = nDevId;
	m_nDevType = eType;
}

void QBaseDlqWidget::SetCfg(ST_DlqCfg& oDlqCfg)
{
	m_oDlqCfg.nAlarmEnVal = oDlqCfg.nAlarmEnVal;
	m_oDlqCfg.nAlarmSWEnVal = oDlqCfg.nAlarmSWEnVal;
	m_oDlqCfg.volAH = oDlqCfg.volAH;
	m_oDlqCfg.volAHEn = oDlqCfg.volAHEn;
	m_oDlqCfg.volAHSwEn = oDlqCfg.volAHSwEn;
	m_oDlqCfg.volWH = oDlqCfg.volWH;

	m_oDlqCfg.volAL = oDlqCfg.volAL;
	m_oDlqCfg.volALEn = oDlqCfg.volALEn;
	m_oDlqCfg.volALSwEn = oDlqCfg.volALSwEn;
	m_oDlqCfg.volWL = oDlqCfg.volWL;

	m_oDlqCfg.curAH = oDlqCfg.curAH;
	m_oDlqCfg.curAHEn = oDlqCfg.curAHEn;
	m_oDlqCfg.curAHSwEn = oDlqCfg.curAHSwEn;
	m_oDlqCfg.curWH = oDlqCfg.curWH;

	m_oDlqCfg.leakAH = oDlqCfg.leakAH;
	m_oDlqCfg.leakAHEn = oDlqCfg.leakAHEn;
	m_oDlqCfg.leakAHSwEn = oDlqCfg.leakAHSwEn;
	m_oDlqCfg.leakWH = oDlqCfg.leakWH;

	m_oDlqCfg.tmpAH = oDlqCfg.tmpAH;
	m_oDlqCfg.tmpAHEn = oDlqCfg.tmpAHEn;
	m_oDlqCfg.tmpAHSwEn = oDlqCfg.tmpAHSwEn;
	m_oDlqCfg.tmpWH = oDlqCfg.tmpWH;

	m_oDlqCfg.pwrpAH = oDlqCfg.pwrpAH;
	m_oDlqCfg.pwrpAHEn = oDlqCfg.pwrpAHEn;
	m_oDlqCfg.pwrpAHSwEn = oDlqCfg.pwrpAHSwEn;
	m_oDlqCfg.pwrpWH = oDlqCfg.pwrpWH;
}

int64_t QBaseDlqWidget::GetDevId()
{
	return m_nDevId;
}

void QBaseDlqWidget::on_pushButton_swon_clicked()
{
	if (m_pCall)
	{
		m_pCall->SwitchOn(m_nDevId);
	}
}

void QBaseDlqWidget::on_pushButton_swoff_clicked()
{
	if (m_pCall)
	{
		m_pCall->SwitchOff(m_nDevId);
	}
}

void QBaseDlqWidget::on_pushButton_savebaojing_clicked()
{
	if (m_pCall)
	{
		ST_DlqCfg oCfg;
		QWidget *pWidget = nullptr;
		QDanXiang* pWidgetDan = nullptr;
		QSanXiang* pWidgetSan = nullptr;
		if (m_nDevType == enDevType_DanXiang)
		{
			pWidgetDan = (QDanXiang*)this;
			oCfg.volAH = pWidgetDan->lineEdit_volAH->text().toDouble();
			oCfg.volAL = pWidgetDan->lineEdit_volAL->text().toDouble();
			oCfg.curAH = pWidgetDan->lineEdit_curAH->text().toDouble();
			oCfg.leakAH = pWidgetDan->lineEdit_leakAH->text().toDouble();
			oCfg.tmpAH = pWidgetDan->lineEdit_tmpAH->text().toDouble();
			oCfg.pwrpAH = pWidgetDan->lineEdit_pwrpAH->text().toDouble();
		}
		else if (m_nDevType == enDevType_SanXiang)
		{
			pWidgetSan = (QSanXiang*)this;
			oCfg.volAH = pWidgetDan->lineEdit_volAH->text().toDouble();
			oCfg.volAL = pWidgetDan->lineEdit_volAL->text().toDouble();
			oCfg.curAH = pWidgetDan->lineEdit_curAH->text().toDouble();
			oCfg.leakAH = pWidgetDan->lineEdit_leakAH->text().toDouble();
			oCfg.tmpAH = pWidgetDan->lineEdit_tmpAH->text().toDouble();
			oCfg.pwrpAH = pWidgetDan->lineEdit_pwrpAH->text().toDouble();
		}
			
		m_pCall->ModifyAlarmValue(m_nDevId, oCfg);
	}
}

void QBaseDlqWidget::on_pushButton_saveyujing_clicked()
{
	if (m_pCall)
	{
		ST_DlqCfg oCfg;
		QWidget *pWidget = nullptr;
		QDanXiang* pWidgetDan = nullptr;
		QSanXiang* pWidgetSan = nullptr;
		if (m_nDevType == enDevType_DanXiang)
		{
			pWidgetDan = (QDanXiang*)this;
			oCfg.volWH = pWidgetDan->lineEdit_volWH->text().toDouble();
			oCfg.volWL = pWidgetDan->lineEdit_volWL->text().toDouble();
			oCfg.curWH = pWidgetDan->lineEdit_curWH->text().toDouble();
			oCfg.leakWH = pWidgetDan->lineEdit_leakWH->text().toDouble();
			oCfg.tmpWH = pWidgetDan->lineEdit_tmpWH->text().toDouble();
			oCfg.pwrpWH = pWidgetDan->lineEdit_pwrpWH->text().toDouble();
		}
		else if (m_nDevType == enDevType_SanXiang)
		{
			pWidgetSan = (QSanXiang*)this;
			oCfg.volWH = pWidgetSan->lineEdit_volWH->text().toDouble();
			oCfg.volWL = pWidgetSan->lineEdit_volWL->text().toDouble();
			oCfg.curWH = pWidgetSan->lineEdit_curWH->text().toDouble();
			oCfg.leakWH = pWidgetSan->lineEdit_leakWH->text().toDouble();
			oCfg.tmpWH = pWidgetSan->lineEdit_tmpWH->text().toDouble();
			oCfg.pwrpWH = pWidgetSan->lineEdit_pwrpWH->text().toDouble();
		}

		m_pCall->ModifyYuJingValue(m_nDevId, oCfg);
	}
}

void QBaseDlqWidget::on_pushButton_alarmen_clicked()
{
	if (m_pCall)
	{
		ST_DlqCfg oCfg;
		QWidget *pWidget = nullptr;
		QDanXiang* pWidgetDan = nullptr;
		QSanXiang* pWidgetSan = nullptr;
		if (m_nDevType == enDevType_DanXiang)
		{
			pWidgetDan = (QDanXiang*)this;
			oCfg.volAHEn = pWidgetDan->checkBox_volAHEn->isChecked();
			oCfg.volALEn = pWidgetDan->checkBox_volALEn->isChecked();
			oCfg.curAHEn = pWidgetDan->checkBox_curAHEn->isChecked();
			oCfg.leakAHEn = pWidgetDan->checkBox_leakAHEn->isChecked();
			oCfg.tmpAHEn = pWidgetDan->checkBox_tmpAHEn->isChecked();
			oCfg.pwrpAHEn = pWidgetDan->checkBox_pwrpAHEn->isChecked();
		}
		else if (m_nDevType == enDevType_SanXiang)
		{
			pWidgetSan = (QSanXiang*)this;
			oCfg.volAHEn = pWidgetSan->checkBox_volAHEn->isChecked();
			oCfg.volALEn = pWidgetSan->checkBox_volALEn->isChecked();
			oCfg.curAHEn = pWidgetSan->checkBox_curAHEn->isChecked();
			oCfg.leakAHEn = pWidgetSan->checkBox_leakAHEn->isChecked();
			oCfg.tmpAHEn = pWidgetSan->checkBox_tmpAHEn->isChecked();
			oCfg.pwrpAHEn = pWidgetSan->checkBox_pwrpAHEn->isChecked();
		}

		m_pCall->ModifyAlarmEn(m_nDevId, m_oDlqCfg.nAlarmEnVal,oCfg);
	}
}

void QBaseDlqWidget::on_pushButton_alarmswen_clicked()
{
	if (m_pCall)
	{
		ST_DlqCfg oCfg;
		QWidget *pWidget = nullptr;
		QDanXiang* pWidgetDan = nullptr;
		QSanXiang* pWidgetSan = nullptr;
		if (m_nDevType == enDevType_DanXiang)
		{
			pWidgetDan = (QDanXiang*)this;
			oCfg.volAHSwEn = pWidgetDan->checkBox_volAHSwEn->isChecked();
			oCfg.volALSwEn = pWidgetDan->checkBox_volALSwEn->isChecked();
			oCfg.curAHSwEn = pWidgetDan->checkBox_curAHSwEn->isChecked();
			oCfg.leakAHSwEn = pWidgetDan->checkBox_leakAHSwEn->isChecked();
			oCfg.tmpAHSwEn = pWidgetDan->checkBox_tmpAHSwEn->isChecked();
			oCfg.pwrpAHSwEn = pWidgetDan->checkBox_pwrpAHSwEn->isChecked();
		}
		else if (m_nDevType == enDevType_SanXiang)
		{
			pWidgetSan = (QSanXiang*)this;
			oCfg.volAHSwEn = pWidgetSan->checkBox_volAHSwEn->isChecked();
			oCfg.volALSwEn = pWidgetSan->checkBox_volALSwEn->isChecked();
			oCfg.curAHSwEn = pWidgetSan->checkBox_curAHSwEn->isChecked();
			oCfg.leakAHSwEn = pWidgetSan->checkBox_leakAHSwEn->isChecked();
			oCfg.tmpAHSwEn = pWidgetSan->checkBox_tmpAHSwEn->isChecked();
			oCfg.pwrpAHSwEn = pWidgetSan->checkBox_pwrpAHSwEn->isChecked();
		}

		m_pCall->ModifyAlarmEnSW(m_nDevId, m_oDlqCfg.nAlarmEnVal, oCfg);
	}
}

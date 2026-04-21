#include "stdafx.h"
#include "QDanXiang.h"


QDanXiang::QDanXiang(QWidget *parent)
	: QBaseDlqWidget(parent)
{
	setupUi(this);
}

QDanXiang::~QDanXiang()
{
}

void QDanXiang::SetDlqCfg(ST_DlqCfg& oDlqCfg)
{
	SetCfg(oDlqCfg);
	lineEdit_devid->setText(QString::number(oDlqCfg.nDevId));
	lineEdit_name->setText(QString::fromStdString(oDlqCfg.sDevName));
	//报警阈值
	lineEdit_volAH->setText(QString::number(oDlqCfg.volAH));
	lineEdit_volAL->setText(QString::number(oDlqCfg.volAL));
	lineEdit_curAH->setText(QString::number(oDlqCfg.curAH));
	lineEdit_leakAH->setText(QString::number(oDlqCfg.leakAH));
	lineEdit_tmpAH->setText(QString::number(oDlqCfg.tmpAH));
	lineEdit_pwrpAH->setText(QString::number(oDlqCfg.pwrpAH));
	//预警阈值
	lineEdit_volWH->setText(QString::number(oDlqCfg.volWH));
	lineEdit_volWL->setText(QString::number(oDlqCfg.volWL));
	lineEdit_curWH->setText(QString::number(oDlqCfg.curWH));
	lineEdit_leakWH->setText(QString::number(oDlqCfg.leakWH));
	lineEdit_tmpWH->setText(QString::number(oDlqCfg.tmpWH));
	lineEdit_pwrpWH->setText(QString::number(oDlqCfg.pwrpWH));

	//报警使能
	checkBox_volAHEn->setChecked(oDlqCfg.volAHEn);
	checkBox_volALEn->setChecked(oDlqCfg.volALEn);
	checkBox_curAHEn->setChecked(oDlqCfg.curAHEn);
	checkBox_leakAHEn->setChecked(oDlqCfg.leakAHEn);
	checkBox_tmpAHEn->setChecked(oDlqCfg.tmpAHEn);
	checkBox_pwrpAHEn->setChecked(oDlqCfg.pwrpAHEn);

	//报警分闸使能

	checkBox_volAHSwEn->setChecked(oDlqCfg.volAHSwEn);
	checkBox_volALSwEn->setChecked(oDlqCfg.volALSwEn);
	checkBox_curAHSwEn->setChecked(oDlqCfg.curAHSwEn);
	checkBox_leakAHSwEn->setChecked(oDlqCfg.leakAHSwEn);
	checkBox_tmpAHSwEn->setChecked(oDlqCfg.tmpAHSwEn);
	checkBox_pwrpAHSwEn->setChecked(oDlqCfg.pwrpAHSwEn);

	update();
	
}

void QDanXiang::SetUpdateData(ST_UpdateData& oUpdateData)
{
	QString qsState = oUpdateData.on ? u8"合 " : u8"分";
	label_state->setText(qsState);
	lineEdit_vol->setText(QString::number(oUpdateData.vol));
	lineEdit_curl->setText(QString::number(oUpdateData.cur));
	lineEdit_leak->setText(QString::number(oUpdateData.leak));
	lineEdit_pwrP->setText(QString::number(oUpdateData.pwrP));
	lineEdit_pf->setText(QString::number(oUpdateData.pf));
	lineEdit_tmp->setText(QString::number(oUpdateData.tmp));
	lineEdit_freq->setText(QString::number(oUpdateData.freq));
	update();
}

void QDanXiang::ClearText()
{
	lineEdit_devid->clear();
	lineEdit_name->clear();
	label_state->setText(u8"未知");

	lineEdit_vol->clear();
	lineEdit_curl->clear();
	lineEdit_leak->clear();
	lineEdit_pwrP->clear();
	lineEdit_pf->clear();
	lineEdit_tmp->clear();
	lineEdit_freq->clear();

	lineEdit_volAH->clear();
	lineEdit_volAL->clear();
	lineEdit_curAH->clear();
	lineEdit_leakAH->clear();
	lineEdit_tmpAH->clear();
	lineEdit_pwrpAH->clear();


	lineEdit_volWH->clear();
	lineEdit_volWL->clear();
	lineEdit_curWH->clear();
	lineEdit_leakWH->clear();
	lineEdit_tmpWH->clear();
	lineEdit_pwrpWH->clear();

	checkBox_volAHSwEn->setChecked(false);
	checkBox_volALSwEn->setChecked(false);
	checkBox_curAHSwEn->setChecked(false);
	checkBox_leakAHSwEn->setChecked(false);
	checkBox_tmpAHSwEn->setChecked(false);
	checkBox_pwrpAHSwEn->setChecked(false);

	checkBox_volAHEn->setChecked(false);
	checkBox_volALEn->setChecked(false);
	checkBox_curAHEn->setChecked(false);
	checkBox_leakAHEn->setChecked(false);
	checkBox_tmpAHEn->setChecked(false);
	checkBox_pwrpAHEn->setChecked(false);
}



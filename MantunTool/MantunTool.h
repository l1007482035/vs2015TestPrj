#pragma once

#include <QtWidgets/QWidget>
#include "ui_MantunTool.h"
class CMqttThread;
class QDanXiang;
class QSanXiang;

class MantunTool : public QWidget,public Ui::MantunToolClass
{
	Q_OBJECT

public:
	MantunTool(QWidget *parent = Q_NULLPTR);
	~MantunTool();

	void showEvent(QShowEvent *event);
	void addOneButton(QPushButton* pButton);
	BOOL IsDlqExsit(int64_t nDevId);
	void Enable(BOOL bEnable);
	BOOL IsExpired(QString qsSecret);

	void InitMqttTh();
	void ReleaseMqttTh();
	std::string GetClientID(int len);

	void ParseDlqCfg(Json::Value& jsDev, ST_DlqCfg& oDlqCfg);
	void ParseDanXiangUpdateData(Json::Value& jsDev, ST_UpdateData& oUpdateData);
	void ParseSanXiangUpdateData(Json::Value& jsDev, ST_UpdateData& oUpdateData);

	void SwitchOn(int64_t nDevId);
	void SwitchOff(int64_t nDevId);
	//报警阈值
	void ModifyAlarmValue(int64_t nDevId,ST_DlqCfg& oCfg);
	//预警阈值
	void ModifyYuJingValue(int64_t nDevId, ST_DlqCfg& oCfg);
	//报警使能
	void ModifyAlarmEn(int64_t nDevId,int nOldEnableVal, ST_DlqCfg& oCfg);
	//报警分闸使能
	void ModifyAlarmEnSW(int64_t nDevId, int nOldEnableVal, ST_DlqCfg& oCfg);

protected:

	CMqttThread *m_pMqttTh = nullptr;
	QDanXiang *m_pDanXiang = nullptr;
	QSanXiang *m_pSanXiang = nullptr;
	int64_t m_nGwId = 0;

private slots:
	void on_pushButton_connect_clicked();
	void on_pushButton_get_clicked();
	void on_pushButton_gen_clicked();
	void on_pushButton_checksec_clicked();
	void slot_mqttmsg(char* pMsg);
	void on_pushButton_dlq_clicked();
	void on_pushButton_back_clicked();
	
	

};

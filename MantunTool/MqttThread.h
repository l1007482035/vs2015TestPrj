#pragma once
#include "MQTTClient.h"


// CMqttThread

#include <QObject>
class CMqttThread : public QObject,public CWinThread
{
	Q_OBJECT
	DECLARE_DYNCREATE(CMqttThread)
protected:
	CMqttThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CMqttThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void SetHandle(HANDLE han)
	{
		m_handle = han;
	}
	
	void SetDevInfo(std::string sMac,int64_t nGwDevId);
	

	BOOL IsConnected();
	BOOL ConnectSvr(std::string sIP, int nPort, std::string sUser, std::string sPwd, std::string sClientId);
	void Disconnect();
	//曼顿相关
	//获取属性
	void GetAttribute(int64_t nDevId, EN_Tag eTag);
	//控制命令
	void ControlCmd(int64_t nGwDevId, int64_t nDlqDevId, EN_Tag eTag,std::string sCmd);

	//修改报警阈值
	void ModifyAlarmValue(int64_t nDlqDevId, ST_DlqCfg &oDlqCfg);
	//修改预警阈值
	void ModifyYuJingValue(int64_t nDlqDevId, ST_DlqCfg &oDlqCfg);
	//修改报警使能
	void ModifyAlarmEnable(int64_t nDlqDevId, int nOldEnalbeVal,ST_DlqCfg &oDlqCfg);
	//修改报警分闸使能
	void ModifyAlarmSWEnable(int64_t nDlqDevId, int nOldEnalbeVal, ST_DlqCfg &oDlqCfg);
protected:
	void InitTopic();
	void SubscribeUtl(std::string sTopic,int nQos);
	void UnSubscribeUtl(std::string sTopic);
	void Subscribe();
	void UnSubscribe();

	BOOL Publish(const char* topic, const char* payload, int len,int nQos);


	static void OnMQTTClientConnlost_OtherThInvoke(void *pContext, char *pCause);
	static void OnMQTTClientDelivered_OtherThInvoke(void *pContext, MQTTClient_token dt);
	static int OnMQTTClientMsgArrvd_OtherThInvoke(void *pContext, char *topicName, int topicLen, MQTTClient_message *message);

	void DealMqttMsg(char* pMsg);




protected:
	DECLARE_MESSAGE_MAP()
	HANDLE m_handle;

	CString m_szClientId;
	MQTTClient_connectOptions m_oConnOpt = MQTTClient_connectOptions_initializer;
	MQTTClient	m_hMqtt = nullptr;	//MQTT客户端的句柄

	int64_t m_nGwDevId;
	std::string m_sMac;
	//上行消息
	std::string m_sAttrTopic = "";
	std::string m_sStatusTopic = "";
	std::string m_sEventTopic = "";
	std::string m_sRespTopic = "";

	//下行消息
	std::string m_sCmd = "";


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

signals:
	void sig_mqttmsg(char* pMsg);

};



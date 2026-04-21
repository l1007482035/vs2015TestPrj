// MqttThread.cpp : 实现文件
//

#include "stdafx.h"
#include "MantunTool.h"
#include "MqttThread.h"


// CMqttThread

IMPLEMENT_DYNCREATE(CMqttThread, CWinThread)

CMqttThread::CMqttThread()
{
}

CMqttThread::~CMqttThread()
{
}

BOOL CMqttThread::InitInstance()
{
	// TODO:    在此执行任意逐线程初始化
	PostThreadMessage(WM_MSG_OK, 0, 0);
	return TRUE;
}

BOOL CMqttThread::IsConnected()
{
	if (!m_hMqtt)
	{
		return FALSE;
	}
	return MQTTClient_isConnected(m_hMqtt);
}

BOOL CMqttThread::ConnectSvr(std::string sIP, int nPort, std::string sUser, std::string sPwd, std::string sClientId)
{
	theLog.Write(_T("CMqttThread::ConnectSvr,0,sIP=%s,nPort=%d,sUser=%s,sClientId=%s")
		,CCommonFun::UTF8ToUnicode(sIP.c_str()), nPort, CCommonFun::UTF8ToUnicode(sUser.c_str()), CCommonFun::UTF8ToUnicode(sClientId.c_str()));
	Disconnect();
	int nRet = MQTTCLIENT_SUCCESS;
	MQTTClient_nameValue *pNameValue = ::MQTTClient_getVersionInfo();

	theLog.Write(_T("CMqttThread::ConnectSvr,1,name=%s,value=%s"), CCommonFun::UTF8ToUnicode(pNameValue->name)
		, CCommonFun::UTF8ToUnicode(pNameValue->value));

	
	std::string sMqttUri = sIP + ":" + std::to_string(nPort);

	//MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
	m_oConnOpt.keepAliveInterval = 20;
	m_oConnOpt.cleansession = 1;
	//        connOpt.username = username;
	m_oConnOpt.username = sUser.c_str();
	//        connOpt.password = password;
	m_oConnOpt.password = sPwd.c_str();
	//ssl_opts.enableServerCertAuth = 0;

	//m_oConnOpt.ssl = &ssl_opts;


	if ((nRet = ::MQTTClient_create(&m_hMqtt
		,sMqttUri.c_str()
		,sClientId.c_str()
		, MQTTCLIENT_PERSISTENCE_NONE, NULL))
		!= MQTTCLIENT_SUCCESS)
	{
		theLog.Write(_T("!!CMqttThread::ConnectSvr,1,MQTTClient_create fail"));
		return FALSE;
	}
	else
	{
		theLog.Write(_T("CMqttThread::ConnectSvr,2,MQTTClient_create,suc,new Mqtt client client_id:%s,access:%s,m_hMqtt=%x")
			, CCommonFun::UTF8ToUnicode(sClientId.c_str()), CCommonFun::UTF8ToUnicode(sMqttUri.c_str()), m_hMqtt);

	}

	if (!m_hMqtt)
	{
		theLog.Write(_T("!!CLinkMQTTClient::Connect,3"));
		return FALSE;
	}
	if ((nRet = ::MQTTClient_setCallbacks(m_hMqtt, this, OnMQTTClientConnlost_OtherThInvoke
		, OnMQTTClientMsgArrvd_OtherThInvoke, OnMQTTClientDelivered_OtherThInvoke))
		!= MQTTCLIENT_SUCCESS)
	{
		theLog.Write(_T("!!CLinkMQTTClient::Connect,4,MQTTClient_setCallbacks Failed, ret=%d,m_hMqtt=%x"), nRet, m_hMqtt);
		return FALSE;
	}
	DWORD dwTick1 = ::GetTickCount();

	 theLog.Write(_T("CLinkMQTTClient::Connect,preConnect"));

	if ((!::MQTTClient_isConnected(m_hMqtt))
		&& ((nRet = ::MQTTClient_connect(m_hMqtt, &m_oConnOpt)) != MQTTCLIENT_SUCCESS))
		//MQTTClient_SUCCESS 异步立即返回，不能表明已经连上服务器,只能表明连接是否被请求
	{
		theLog.Write(_T("!!CLinkMQTTClient::Connect,5,MQTTClient_connect Failed, ret=%d,Cost %d MS,this=%x")
			, nRet, ::GetTickCount() - dwTick1, this);
		return FALSE;
	}
	else
	{
		theLog.Write(_T("CLinkMQTTClient::Connect,6,MQTTClient_connect,Sucess"));
		nRet = MQTTCLIENT_SUCCESS;
	}

	return TRUE;
}

void CMqttThread::Disconnect()
{
	if (!m_hMqtt)
	{
		return;
	}

	BOOL bIsConnected = MQTTClient_isConnected(m_hMqtt);
	if (!bIsConnected)
	{
		return;
	}
	//UnSubscribe();
	int nRet = MQTTCLIENT_SUCCESS;

	if ((nRet = ::MQTTClient_disconnect(m_hMqtt, 10000)) != MQTTCLIENT_SUCCESS)
	{
		theLog.Write(_T("!!CMqttThread::Disconnect,3,MQTTClient_disconnect Failed, ret=%d"), nRet);
	}
	else
	{
		theLog.Write(_T("CMqttThread::Disconnect,3,MQTTClient_disconnect suc, ret=%d"), nRet);
	}
	MQTTClient_destroy(&m_hMqtt);
	m_hMqtt = NULL;

}


void CMqttThread::GetAttribute(int64_t nDevId, EN_Tag eTag)
{
	if (enTag_Unkown == eTag)
	{
		return;
	}
	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	jsRequest["method"] = enMethod_Get;
	jsRequest["dstID"] = nDevId;
	jsRequest["msgCode"] = enMsgCode_Attributes;
	jsDev["tag"] = eTag;
	jsData.append(jsDev);
	jsRequest["data"] = jsData;
	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);
	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);
}

void CMqttThread::ControlCmd(int64_t nGwDevId, int64_t nDlqDevId, EN_Tag eTag, std::string sCmd)
{
	theLog.Write(_T("CMqttThread::ControlCmd"));
	if (enTag_Unkown == eTag)
	{
		return;
	}

	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	Json::Value jsDlqDevId;


	jsRequest["method"] = enMethod_Put;
	jsRequest["dstID"] = nGwDevId;
	jsRequest["msgCode"] = enMsgCode_UdpCommand;
	jsDlqDevId.append(nDlqDevId);

	jsDev["tag"] = eTag;
	jsDev["cmd"] = sCmd;
	jsDev["devID"] = jsDlqDevId;
	jsDev["count"] = 1;
	jsData.append(jsDev);
	jsRequest["data"] = jsData;

	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);

	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);

}

void CMqttThread::ModifyAlarmValue(int64_t nDlqDevId, ST_DlqCfg &oDlqCfg)
{
	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	jsRequest["method"] = enMethod_Put;
	jsRequest["dstID"] = nDlqDevId;
	jsRequest["msgCode"] = enMsgCode_Attributes;
	jsDev["tag"] = enTag_Threshold;
	jsDev["volAH"] = oDlqCfg.volAH;
	jsDev["volAL"] = oDlqCfg.volAL;
	jsDev["curAH"] = oDlqCfg.curAH;
	jsDev["leakAH"] = oDlqCfg.leakAH;
	jsDev["tmpAH"] = oDlqCfg.tmpAH;
	jsDev["pwrpAH"] = 1000*oDlqCfg.pwrpAH;//曼顿文档功率单位是乱的，修改时候单位是w,因此乘以1000
	jsData.append(jsDev);
	jsRequest["data"] = jsData;
	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);
	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);
}

//修改预警阈值
void CMqttThread::ModifyYuJingValue(int64_t nDlqDevId, ST_DlqCfg &oDlqCfg)
{
	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	jsRequest["method"] = enMethod_Put;
	jsRequest["dstID"] = nDlqDevId;
	jsRequest["msgCode"] = enMsgCode_Attributes;
	jsDev["tag"] = enTag_Threshold;
	jsDev["volWH"] = oDlqCfg.volWH;
	jsDev["volWL"] = oDlqCfg.volWL;
	jsDev["curWH"] = oDlqCfg.curWH;
	jsDev["leakWH"] = oDlqCfg.leakWH;
	jsDev["tmpWH"] = oDlqCfg.tmpWH;
	jsDev["pwrpWH"] = 1000 * oDlqCfg.pwrpWH;
	jsData.append(jsDev);
	jsRequest["data"] = jsData;
	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);
	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);
}

//修改报警使能
void CMqttThread::ModifyAlarmEnable(int64_t nDlqDevId, int nOldEnalbeVal,ST_DlqCfg &oDlqCfg)
{
	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	jsRequest["method"] = enMethod_Put;
	jsRequest["dstID"] = nDlqDevId;
	jsRequest["msgCode"] = enMsgCode_Attributes;
	jsDev["tag"] = enTag_CommSet;
	nOldEnalbeVal = oDlqCfg.volAHEn ? (nOldEnalbeVal | (1 << 6)) : (nOldEnalbeVal & ~(1 << 6));//过压报警使能
	nOldEnalbeVal = oDlqCfg.volALEn ? (nOldEnalbeVal | (1 << 11)) : (nOldEnalbeVal & ~(1 << 11)); //欠压报警使能
	nOldEnalbeVal = oDlqCfg.curAHEn ? (nOldEnalbeVal | (1 << 5)) : (nOldEnalbeVal & ~(1 << 5));//过流报警使能
	nOldEnalbeVal = oDlqCfg.leakAHEn ? (nOldEnalbeVal | (1 << 4)) : (nOldEnalbeVal & ~(1 << 4));//漏电报警使能
	nOldEnalbeVal = oDlqCfg.tmpAHEn ? (nOldEnalbeVal | (1 << 21)) : (nOldEnalbeVal & ~(1 << 21));//过温报警使能
	nOldEnalbeVal = oDlqCfg.pwrpAHEn ? (nOldEnalbeVal | (1 << 2)) : (nOldEnalbeVal & ~(1 << 2));//过载报警使能
	jsDev["imcbFuncEn"] = nOldEnalbeVal;
	jsData.append(jsDev);
	jsRequest["data"] = jsData;
	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);
	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);
}

//修改报警分闸使能
void CMqttThread::ModifyAlarmSWEnable(int64_t nDlqDevId, int nOldEnalbeVal, ST_DlqCfg &oDlqCfg)
{
	Json::Value jsRequest;
	Json::Value jsData;
	Json::Value jsDev;
	jsRequest["method"] = enMethod_Put;
	jsRequest["dstID"] = nDlqDevId;
	jsRequest["msgCode"] = enMsgCode_Attributes;
	jsDev["tag"] = enTag_CommSet;
	nOldEnalbeVal = oDlqCfg.volAHSwEn ? (nOldEnalbeVal | (1 << 6)) : (nOldEnalbeVal & ~(1 << 6));//过压报警分闸使能
	nOldEnalbeVal = oDlqCfg.volALSwEn ? (nOldEnalbeVal | (1 << 11)) : (nOldEnalbeVal & ~(1 << 11)); //欠压报警分闸使能
	nOldEnalbeVal = oDlqCfg.curAHSwEn ? (nOldEnalbeVal | (1 << 5)) : (nOldEnalbeVal & ~(1 << 5));//过流报警分闸使能
	nOldEnalbeVal = oDlqCfg.leakAHSwEn ? (nOldEnalbeVal | (1 << 4)) : (nOldEnalbeVal & ~(1 << 4));//漏电报警分闸使能
	nOldEnalbeVal = oDlqCfg.tmpAHSwEn ? (nOldEnalbeVal | (1 << 21)) : (nOldEnalbeVal & ~(1 << 21));//过温报警分闸使能
	nOldEnalbeVal = oDlqCfg.pwrpAHSwEn ? (nOldEnalbeVal | (1 << 2)) : (nOldEnalbeVal & ~(1 << 2));//过载报警分闸使能
	jsDev["imcbCutEn"] = nOldEnalbeVal;
	jsData.append(jsDev);
	jsRequest["data"] = jsData;
	Json::FastWriter fast;
	std::string sRequest = fast.write(jsRequest);
	Publish(m_sCmd.c_str(), sRequest.c_str(), sRequest.size(), 0);
}
void CMqttThread::InitTopic()
{

	m_sAttrTopic = "/dev/MTS/" + m_sMac + "/attr/json";
	m_sStatusTopic = "/dev/MTS/" + m_sMac + "/status/json";
	m_sEventTopic = "/dev/MTS/" + m_sMac + "/event/json";
	m_sRespTopic = "/dev/MTS/" + m_sMac + "/resp/json";

	m_sCmd = "/dev/MTS/" + m_sMac + "/cmd/json";

}

void CMqttThread::SubscribeUtl(std::string sTopic, int nQos)
{
	if (sTopic.empty())
	{
		return;
	}
	int nRet = MQTTCLIENT_SUCCESS;

	if (!::MQTTClient_isConnected(m_hMqtt))
	{
		theLog.Write(_T("!!CMqttThread::Subscribe,1,NOT Cnnt"));
		return;
	}
	if ((nRet = ::MQTTClient_subscribe(m_hMqtt, sTopic.c_str(), nQos)) != MQTTCLIENT_SUCCESS)
	{
		theLog.Write(_T("!!CMqttThread::Subscribe,2,MQTTClient_subscribe fail,Ret=%d,lpszTopic=%s,err=%d,%s")
			, nRet, sTopic.c_str(), errno, strerror(errno));
		return;
	}

	theLog.Write(_T("CMqttThread::Subscribe,3,Subscribe OK,Topic=%s"), CCommonFun::UTF8ToUnicode(sTopic.c_str()));

	return;
}

void CMqttThread::UnSubscribeUtl(std::string sTopic)
{
	int ret = MQTTCLIENT_SUCCESS;
	if (!MQTTClient_isConnected(m_hMqtt))
	{
		theLog.Write(_T("!!CMqttThread::UnSubscribe,failed,m_hMqtt=%x"), m_hMqtt);
		return;
	}

	if ((ret = MQTTClient_unsubscribe(m_hMqtt, sTopic.c_str())) != MQTTCLIENT_SUCCESS) {
		theLog.Write(_T("CMqttThread::UnSubscribe,MQTTClient_unsubscribe Failed, ret=%d,lpszTopic=%s"), ret, sTopic.c_str());
	}
	else
	{
		theLog.Write(_T("CMqttThread::UnSubscribe,topic:%s"), CCommonFun::UTF8ToUnicode(sTopic.c_str()));
	}
}

void CMqttThread::Subscribe()
{
	SubscribeUtl(m_sAttrTopic,0);
	SubscribeUtl(m_sStatusTopic, 0);
	SubscribeUtl(m_sEventTopic, 0);
	SubscribeUtl(m_sRespTopic, 0);
}

void CMqttThread::UnSubscribe()
{
	UnSubscribeUtl(m_sAttrTopic);
	UnSubscribeUtl(m_sStatusTopic);
	UnSubscribeUtl(m_sEventTopic);
	UnSubscribeUtl(m_sRespTopic);
}

BOOL CMqttThread::Publish(const char* topic, const char* payload, int len, int nQos)
{
	theLog.Write(_T("CMqttThread::Publish,topic=%s,payload=%s")
		,CCommonFun::UTF8ToUnicode(topic),CCommonFun::UTF8ToUnicode(payload));
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	srand((int)time(0));
	MQTTClient_deliveryToken token = rand();
	int ret = MQTTCLIENT_SUCCESS;
	pubmsg.payload = (void*)payload;
	pubmsg.payloadlen = len;
	pubmsg.qos = nQos;
	pubmsg.retained = 0;

	if (!MQTTClient_isConnected(m_hMqtt))
	{
		theLog.Write(_T("!!CLinkMQTTClient::Publish,failed"));
		return FALSE;
	}

	int nRet = MQTTClient_publishMessage(m_hMqtt, topic, &pubmsg,&token);
	theLog.Write(_T("CMqttThread::Publish,nRet=%d"), nRet);
	if (nRet != MQTTCLIENT_SUCCESS)  //只能代表发送请求成功
	{
		theLog.Write(_T("!!CMqttThread::Publish,MQTTClient_publishMessage Failed"));
		return FALSE;
	}
	else {
		//m_pLog->Write("CLinkMQTTClient::Publish,send topic:%s, token:%d, payload_size:%d, payload:%s\n", topic, token, len, (char*)payload);
	}
	return TRUE;
}


void CMqttThread::CMqttThread::OnMQTTClientConnlost_OtherThInvoke(void *pContext, char *pCause)
{
	CMqttThread* pTh = (CMqttThread*)pContext;
}

void CMqttThread::OnMQTTClientDelivered_OtherThInvoke(void *pContext, MQTTClient_token dt)
{
	CMqttThread* pTh = (CMqttThread*)pContext;
}

int CMqttThread::OnMQTTClientMsgArrvd_OtherThInvoke(void *pContext, char *topicName, int topicLen, MQTTClient_message *message)
{
	

	CMqttThread* pTh = (CMqttThread*)pContext;
	int nMsgLen = message->payloadlen;

	BYTE* pBuf = new BYTE[nMsgLen + 1];
	ZeroMemory(pBuf, nMsgLen + 1);
	memcpy(pBuf, message->payload, nMsgLen);
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	theLog.Write(_T("CMqttThread::OnMQTTClientMsgArrvd_OtherThInvoke,nMsgLen=%d,payload=%s"), nMsgLen,CCommonFun::UTF8ToUnicode((char*)pBuf));
	CThreadMgr::PostThreadMsg(pTh->m_nThreadID, WM_MSG_MQTT, (WPARAM)pBuf, (LPARAM)nMsgLen + 1);

	return 1;
}

void CMqttThread::DealMqttMsg(char* pMsg)
{
	emit sig_mqttmsg(pMsg);
}


int CMqttThread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	AfxEndThread(0);
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMqttThread, CWinThread)
END_MESSAGE_MAP() 


// CMqttThread 消息处理程序


void CMqttThread::SetDevInfo(std::string sMac, int64_t nDevId)
{
	m_nGwDevId = nDevId;
	m_sMac = sMac;
	if (IsConnected())
	{
		InitTopic();
		Subscribe();
	}
	
}


BOOL CMqttThread::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MSG_OK)
	{
		SetEvent(m_handle);
	}
	else if (pMsg->message == WM_THREAD_EXIT)
	{
		ExitInstance();
	}
	else if (pMsg->message == WM_MSG_MQTT)
	{
		BYTE *pBuf = (BYTE *)pMsg->wParam;
		int nLen = (int)pMsg->lParam;
		DealMqttMsg((char*)pBuf);
	
 	}

	return CWinThread::PreTranslateMessage(pMsg);
}

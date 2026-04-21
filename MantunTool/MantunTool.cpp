#include "stdafx.h"
#include "MantunTool.h"
#include "MqttThread.h"
#include <chrono>
#include "QDanXiang.h"
#include "QSanXiang.h"

#pragma execution_character_set("utf-8")


MantunTool::MantunTool(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	m_pDanXiang = new QDanXiang(this);
	m_pSanXiang = new QSanXiang(this);
	stackedWidget->addWidget(m_pDanXiang);
	stackedWidget->addWidget(m_pSanXiang);
	InitMqttTh();

	connect(m_pMqttTh,&CMqttThread::sig_mqttmsg,this, &MantunTool::slot_mqttmsg);
}

MantunTool::~MantunTool()
{
	ReleaseMqttTh();
}


void MantunTool::showEvent(QShowEvent *event)
{
	CString szMqttUrl = theInifle.GetVal(_T("Mqtt"), _T("Ip"), _T(""));
	CString szUserName = theInifle.GetVal(_T("Mqtt"), _T("User"), _T(""));
	CString szPwd = theInifle.GetVal(_T("Mqtt"), _T("Pwd"), _T(""));
	int nMqttPort = theInifle.GetVal(_T("Mqtt"), _T("Port"), 1883);
	CString szMac = theInifle.GetVal(_T("Mqtt"), _T("Mac"), _T(""));
	CString szSecret = theInifle.GetVal(_T("Mqtt"), _T("Secret"), _T(""));

	lineEdit_ip->setText(QString::fromStdWString(szMqttUrl.GetString()));
    lineEdit_Port->setText(QString::number(nMqttPort));
	lineEdit_user->setText(QString::fromStdWString(szUserName.GetString()));
	lineEdit_pwd->setText(QString::fromStdWString(szPwd.GetString()));
	lineEdit_mac->setText(QString::fromStdWString(szMac.GetString()));
	lineEdit_secret->setText(QString::fromStdWString(szSecret.GetString()));
	pushButton_gen->setHidden(true);
	//pushButton_back->setHidden(true);


	if (IsExpired(lineEdit_secret->text()))
	{
		Enable(FALSE);
	}
	else
	{
		Enable(TRUE);
	}

	
}

void MantunTool::addOneButton(QPushButton* pButton)
{
	int nPerCount = 3;//每行3个
	const int nTotal = 20;//最多20个按钮
	int nButtonsCout = gridLayout_devs->count();
	pButton->setText("断路器"+QString::number(nButtonsCout));
	if (nButtonsCout > nTotal)
	{
		return;
	}

	int nRow = nButtonsCout/nPerCount;
	int nCol = nButtonsCout%nPerCount;
	gridLayout_devs->addWidget(pButton, nRow, nCol);
}

BOOL MantunTool::IsDlqExsit(int64_t nDevId)
{
	int nCount = gridLayout_devs->count();
	for (int i = 0;i < nCount;i++)
	{

		QPushButton* pButton = (QPushButton*)gridLayout_devs->itemAt(i)->widget();
		int64_t nId = pButton->property("devId").toLongLong();
		if (nDevId == nId)
		{
			return TRUE;
		}
		
	}
	return FALSE;
}

void MantunTool::Enable(BOOL bEnable)
{
	pushButton_gen->setEnabled(bEnable);
	pushButton_connect->setEnabled(bEnable);
	pushButton_gen->setEnabled(bEnable);
}

BOOL MantunTool::IsExpired(QString qsSecret)
{
	if (qsSecret.isEmpty())
	{
		return TRUE;
	}
	CPWDCryEx cry;
	string sStr = cry.UnCryptPWD(qsSecret.toStdString());
	int nPos = sStr.find("_");
	if (nPos > 0)
	{
	}
	string sTime = sStr.substr(nPos + 1, sStr.length() - nPos);
	int64_t num = std::stoll(sTime);

	// 获取当前时间点
	auto now = std::chrono::system_clock::now();
	int64_t now_s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

	if (now_s < num)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void MantunTool::InitMqttTh()
{
	theLog.Write(_T("MantunTool::InitMqttTh,0"));
	if (!m_pMqttTh)
	{
		m_pMqttTh = (CMqttThread*)AfxBeginThread(RUNTIME_CLASS(CMqttThread), THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
		HANDLE pHandle = CreateEvent(0,0,0,0);
		m_pMqttTh->SetHandle(pHandle);
		m_pMqttTh->ResumeThread();
		WaitForSingleObject(pHandle,INFINITE);
		CloseHandle(pHandle);
	}
	theLog.Write(_T("MantunTool::InitMqttTh,1"));
}

void MantunTool::ReleaseMqttTh()
{
	theLog.Write(_T("MantunTool::ReleaseMqttTh,0"));
	if (m_pMqttTh)
	{
		CThreadMgr::DestroyThread(m_pMqttTh,INFINITE);
		m_pMqttTh = nullptr;
	}
	theLog.Write(_T("MantunTool::ReleaseMqttTh,1"));
}

std::string MantunTool::GetClientID(int len)
{
	int ret = 0;
	char *id = new char[len + 1];
	memset(id, 0, len + 1);
	srand((int)time(NULL));
	for (int i = 0; i < len; i++) {
		if (rand() % 2 == 1) {
			id[i] = rand() % 26 + 'a';
		}
		else {
			id[i] = rand() % 10 + '0';
		}
	}
	std::string sRet = "MantunTool_" + std::string(id);
	delete[]id;
	id = NULL;
	return sRet;
}

void MantunTool::ParseDlqCfg(Json::Value& jsDev, ST_DlqCfg& oDlqCfg)
{
	Json::Value jsMcbThd = jsDev["mcbThd"];//断路器阈值设定
	Json::Value jsMcbComCfg = jsDev["mcbComCfg"];//断路器通用设定,包含报警使能,报警分闸使能,包含设备类型
	Json::Value jsComCfg = jsDev["comCfg"];//表示设备通用属性

	int nAlarmEnable = jsMcbComCfg["imcbFuncEn"].asInt();//报警使能
	int nAlarmSwitchEnble = jsMcbComCfg["imcbCutEn"].asInt();//报警分闸使能
	int64_t nDevId = jsDev["devID"].asInt64();

	//报警使能
	int nGuoYaEnble = nAlarmEnable >> 6 & 0x1;//过压报警使能
	int nQianYaEnble = nAlarmEnable >> 11 & 0x1;//欠压报警使能
	int nGuoLiuEnable = nAlarmEnable >> 5 & 0x1;//过流报警使能
	int nLouDianEnable = nAlarmEnable >> 4 & 0x1;//漏电报警使能
	int nGuoWenEnable = nAlarmEnable >> 21 & 0x1;//过温报警使能
	int nGuoZaiEnable = nAlarmEnable >> 2 & 0x1;//过载报警使能

	//报警分闸使能
	int nGuoYaSwitchEnble = nAlarmSwitchEnble >> 6 & 0x1;//过压报警闸使能
	int nQianYaSwitchEnble = nAlarmSwitchEnble >> 11 & 0x1;//欠压报警闸使能
	int nGuoLiuSwitchEnable = nAlarmSwitchEnble >> 5 & 0x1;//过流报警闸使能
	int nLouDianSwitchEnable = nAlarmSwitchEnble >> 4 & 0x1;//漏电报警闸使能
	int nGuoWenSwitchEnable = nAlarmSwitchEnble >> 21 & 0x1;//过温报警闸使能
	int nGuoZaiSwitchEnable = nAlarmSwitchEnble >> 2 & 0x1;//过载报警闸使能

	oDlqCfg.nDevId = nDevId;
	oDlqCfg.sDevName = jsComCfg["devName"].asString();
	oDlqCfg.nAlarmEnVal = nAlarmEnable;
	oDlqCfg.nAlarmSWEnVal = nAlarmSwitchEnble;
	oDlqCfg.volAH = jsMcbThd["volAH"].asDouble(); //过压报警值V
	oDlqCfg.volAHEn = nGuoYaEnble;//过压报警使能0/1
	oDlqCfg.volAHSwEn = nGuoYaSwitchEnble;//过压报警分闸使能0/1
	oDlqCfg.volWH = jsMcbThd["volWH"].asDouble();//过压预警值V

	oDlqCfg.volAL = jsMcbThd["volAL"].asDouble();//欠压报警值V
	oDlqCfg.volALEn = nQianYaEnble;//欠压报警使能0/1
	oDlqCfg.volALSwEn = nQianYaSwitchEnble;//欠压报警分闸使能0/1
	oDlqCfg.volWL = jsMcbThd["volWL"].asDouble();//欠压预警值V

	oDlqCfg.curAH = jsMcbThd["curAH"].asDouble();//过流报警值A
	oDlqCfg.curAHEn = nGuoLiuEnable;//过流报警使能0/1
	oDlqCfg.curAHSwEn = nGuoLiuSwitchEnable;//过流报警分闸使能0/1
	oDlqCfg.curWH = jsMcbThd["curWH"].asDouble();//过流预警值A

	oDlqCfg.leakAH = jsMcbThd["leakAH"].asDouble();//漏电报警值ma
	oDlqCfg.leakAHEn = nLouDianEnable;//漏电报警使能0/1
	oDlqCfg.leakAHSwEn = nLouDianSwitchEnable;//漏电报警分闸使能0/1
	oDlqCfg.leakWH = jsMcbThd["leakWH"].asDouble();//漏电预警值ma

	oDlqCfg.tmpAH = jsMcbThd["tmpAH"].asDouble();//过温报警值℃
	oDlqCfg.tmpAHEn = nGuoWenEnable;//过温报警使能0/1
	oDlqCfg.tmpAHSwEn = nGuoWenSwitchEnable;//过温报警分闸使能0/1
	oDlqCfg.tmpWH = jsMcbThd["tmpWH"].asDouble();//过温预警值℃

	oDlqCfg.pwrpAH = jsMcbThd["pwrpAH"].asDouble();//过载报警值KW
	oDlqCfg.pwrpAHEn = nGuoZaiEnable;//过载报警使能0/1
	oDlqCfg.pwrpAHSwEn = nGuoZaiSwitchEnable;//过载报警分闸使能0/1
	oDlqCfg.pwrpWH = jsMcbThd["pwrpWH"].asDouble();//过载预警值KW
}

void MantunTool::ParseDanXiangUpdateData(Json::Value& jsDev, ST_UpdateData& oUpdateData)
{
	Json::Value jsMcbSta = jsDev["mcbSta"];//综合线路状态
	Json::Value jsMcbComSta = jsDev["mcbComSta"];//断路器设备状态，包含分合闸状态和设备类型
	oUpdateData.on = jsMcbComSta["on"].asInt(); 	//分合闸状态 0:分闸，1合闸
	oUpdateData.vol = jsMcbSta["vol"].asDouble();  //电压值，单位V
	oUpdateData.cur = jsMcbSta["cur"].asDouble();  //电流值，单位A
	oUpdateData.leak = jsMcbSta["leak"].asDouble(); //漏电流值，单位mA
	oUpdateData.pwrP = jsMcbSta["pwrP"].asDouble();// 有功功率值，单位kW
	oUpdateData.pf = jsMcbSta["pf"].asDouble();//功率因数, 百分比
	oUpdateData.tmp = jsMcbSta["tmp"].asDouble();// 内部温度值, 单位℃
	oUpdateData.freq = jsMcbSta["freq"].asDouble();//频率, 单位Hz
}

void MantunTool::ParseSanXiangUpdateData(Json::Value& jsDev, ST_UpdateData& oUpdateData)
{
	Json::Value jsMcbSta = jsDev["mcbSta"];//综合线路状态
	Json::Value jsMcbStaA = jsDev["mcbStaA"];//A线路状态
	Json::Value jsMcbStaB = jsDev["mcbStaB"];//A线路状态
	Json::Value jsMcbStaC = jsDev["mcbStaC"];//A线路状态

	Json::Value jsMcbComSta = jsDev["mcbComSta"];//断路器设备状态

	oUpdateData.on = jsMcbComSta["on"].asInt(); 	//分合闸状态 0:分闸，1合闸

	oUpdateData.vol = jsMcbSta["vol"].asDouble();  //合相电压值，单位V
	oUpdateData.vola = jsMcbStaA["vol"].asDouble(); //a相电压值，单位V
	oUpdateData.volb = jsMcbStaB["vol"].asDouble();  //b相电压值，单位V
	oUpdateData.volc = jsMcbStaC["vol"].asDouble();  //c相电压值，单位V

	oUpdateData.cur = jsMcbSta["cur"].asDouble(); //合相电流值，单位A
	oUpdateData.cura = jsMcbStaA["cur"].asDouble();//a相电流值，单位A
	oUpdateData.curb = jsMcbStaB["cur"].asDouble();//b相电流值，单位A
	oUpdateData.curc = jsMcbStaC["cur"].asDouble(); //c相电流值，单位A

	oUpdateData.leak = jsMcbSta["leak"].asDouble();  //漏电流值，单位mA

	oUpdateData.pwrP = jsMcbSta["pwrP"].asDouble();  //合相有功功率值，单位kW
	oUpdateData.pwrPa = jsMcbStaA["pwrP"].asDouble(); //a相有功功率值，单位kW
	oUpdateData.pwrPb = jsMcbStaB["pwrP"].asDouble(); //b相有功功率值，单位kW
	oUpdateData.pwrPc = jsMcbStaC["pwrP"].asDouble(); //c相有功功率值，单位kW

	oUpdateData.pf = jsMcbSta["pf"].asDouble();//合相功率因数, 百分比
	oUpdateData.pfa = jsMcbStaA["pf"].asDouble();//a相功率因数, 百分比
	oUpdateData.pfb = jsMcbStaB["pf"].asDouble();//b相功率因数, 百分比
	oUpdateData.pfc = jsMcbStaC["pf"].asDouble();//c相功率因数, 百分比

	oUpdateData.tmp = jsMcbSta["tmp"].asDouble(); //合相内部温度值, 单位℃
	oUpdateData.tmpa = jsMcbStaA["tmpD"].asDouble(); //a相内部温度值, 单位℃
	oUpdateData.tmpb = jsMcbStaB["tmpD"].asDouble(); //b相内部温度值, 单位℃
	oUpdateData.tmpc = jsMcbStaC["tmpD"].asDouble(); //c相内部温度值, 单位℃

	oUpdateData.freq = jsMcbSta["freq"].asDouble();//合相频率, 单位Hz 
}

void MantunTool::SwitchOn(int64_t nDevId)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ControlCmd(m_nGwId,nDevId, enTag_Cmd,CTRL_CMD_SWON);
	}
}

void MantunTool::SwitchOff(int64_t nDevId)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ControlCmd(m_nGwId, nDevId, enTag_Cmd, CTRL_CMD_SWOFF);
	}
}

void MantunTool::ModifyAlarmValue(int64_t nDevId, ST_DlqCfg& oCfg)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ModifyAlarmValue(nDevId, oCfg);
	}
}

void MantunTool::ModifyYuJingValue(int64_t nDevId, ST_DlqCfg& oCfg)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ModifyYuJingValue(nDevId, oCfg);
	}
}

//报警使能
void MantunTool::ModifyAlarmEn(int64_t nDevId, int nOldEnableVal, ST_DlqCfg& oCfg)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ModifyAlarmEnable(nDevId, nOldEnableVal,oCfg);
	}
}

//报警分闸使能
void MantunTool::ModifyAlarmEnSW(int64_t nDevId, int nOldEnableVal, ST_DlqCfg& oCfg)
{
	if (m_pMqttTh)
	{
		m_pMqttTh->ModifyAlarmSWEnable(nDevId, nOldEnableVal, oCfg);
	}
}

void MantunTool::on_pushButton_connect_clicked()
{
	on_pushButton_gen_clicked();
	QString qsIp = lineEdit_ip->text();
	QString qsPort = lineEdit_Port->text();
	QString qsUser = lineEdit_user->text();
	QString qsPwd = lineEdit_pwd->text();
	QString qsClientId = lineEdit_clientid->text();
	qsIp.trimmed(); qsPort.trimmed(); qsUser.trimmed(); qsPwd.trimmed(), qsClientId.trimmed();
	if (qsIp.isEmpty() || qsPort.isEmpty() || qsUser.isEmpty() || qsPwd.isEmpty() || qsClientId.isEmpty())
	{
		QMessageBox::information(this, "提示", "信息有误");
		return;
	}

	if (m_pMqttTh)
	{
		
		if (m_pMqttTh->ConnectSvr(qsIp.toStdString(), qsPort.toInt()
			, qsUser.toStdString(), qsPwd.toStdString(), qsClientId.toStdString()))
		{
			label_5->setText("已连接");
			theInifle.SetVal(_T("Mqtt"), _T("Ip"), qsIp.toStdWString().c_str());
			theInifle.SetVal(_T("Mqtt"), _T("User"), qsUser.toStdWString().c_str());
			theInifle.SetVal(_T("Mqtt"), _T("Pwd"), qsPwd.toStdWString().c_str());
			theInifle.SetVal(_T("Mqtt"), _T("Port"), 1883);

			QMessageBox::information(this, "提示", "连接成功");
			
		}
		else
		{
			QMessageBox::information(this, "提示", "连接失败");
		}

	}
}

void MantunTool::on_pushButton_get_clicked()
{
	QString qsMac = lineEdit_mac->text();
	if (qsMac.isEmpty())
	{
		QMessageBox::information(this, "提示", "Mac有误");
		return;
	}
	QString qsTmp = qsMac + "00";
	bool ok;
	int64_t nDevId = qsTmp.toLongLong(&ok,16);
	if (!ok)
	{
		QMessageBox::information(this, "提示", "Mac有误");
		return;
	}
	QString qsDevId = QString::number(nDevId);
	lineEdit_devid->setText(qsDevId);
	theInifle.SetVal(_T("Mqtt"), _T("Mac"), qsMac.toStdWString().c_str());


	if (m_pMqttTh)
	{
		m_pMqttTh->SetDevInfo(qsMac.toStdString(),nDevId);
		if (!m_pMqttTh->IsConnected())
		{
			QMessageBox::information(this, "提示", "当前未连接");
		}
		m_pMqttTh->GetAttribute(nDevId, enTag_TongXunPeiZhi);//获取网关信息
	}
	

// 	QApplication::setOverrideCursor(Qt::WaitCursor);
// 	QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
// 	Sleep(2000);
// 	QApplication::restoreOverrideCursor();

}

void MantunTool::on_pushButton_gen_clicked()
{
	std::string sClientId = GetClientID(15);
	lineEdit_clientid->setText(QString::fromStdString(sClientId));
}

void MantunTool::on_pushButton_checksec_clicked()
{
	QString qsSecret = lineEdit_secret->text();
	qsSecret.trimmed();
	if (IsExpired(qsSecret))
	{
		Enable(FALSE);
		QMessageBox::information(this, "提示", "授权异常");
	}
	else 
	{
		Enable(TRUE);
		theInifle.SetVal(_T("Mqtt"), _T("Secret"), qsSecret.toStdWString().c_str());
		QMessageBox::information(this, "提示", "授权正常");
		
	}
}

void MantunTool::slot_mqttmsg(char* pMsg)
{
	Json::Reader jsReader;
	Json::Value jsValue;
	std::string sMsg(pMsg);
	delete[] pMsg;
	try
	{

		if (!jsReader.parse(sMsg, jsValue))
		{
			return;
		}
	}
	catch (const std::exception&)
	{
		return;
	}

	Json::Value jsData = jsValue["data"];
	
	if (jsData.type() != Json::arrayValue)
	{
		theLog.Write(_T("!!MantunTool::slot_mqttmsg,1,data is not arry"));
		return;
	}
	int nCount = jsData.size();
	theLog.Write(_T("MantunTool::slot_mqttmsg,2,nCount=%d"), nCount);
	for (int i = 0; i < nCount; i++)
	{
		Json::Value jsDev = jsData[i];
		int nTag = jsDev["tag"].asInt();
		theLog.Write(_T("MantunTool::slot_mqttmsg,1,nTag=%d"), nTag);
		if (nTag == enTag_DanXiangDlqCfg) //单相路器配置
		{
			int64_t nDevId = jsDev["devID"].asInt64();
			if (nDevId == m_pDanXiang->GetDevId())
			{
				ST_DlqCfg oDlqCfg;
				ParseDlqCfg(jsDev, oDlqCfg);
				m_pDanXiang->SetDlqCfg(oDlqCfg);
			}
		}
		else if (nTag == enTag_SanDlqCfg)//三相路器配置
		{
			int64_t nDevId = jsDev["devID"].asInt64();
			if (nDevId == m_pSanXiang->GetDevId())
			{
				ST_DlqCfg oDlqCfg;
				ParseDlqCfg(jsDev, oDlqCfg);
				m_pSanXiang->SetDlqCfg(oDlqCfg);
			}
		}
		else if (nTag == enTag_DanXiangDlqUpdateData)//单相路器实时数据
		{
			int64_t nDevId = jsDev["devID"].asInt64();
			if (nDevId == m_pDanXiang->GetDevId())
			{
				ST_UpdateData oUpdateData;
				ParseDanXiangUpdateData(jsDev,oUpdateData);
 				m_pDanXiang->SetUpdateData(oUpdateData);
			}
		}
		else if (nTag == enTag_SanXiangDlqUpdateData)//三相路器实时数据
		{
			int64_t nDevId = jsDev["devID"].asInt64();
			if (nDevId == m_pSanXiang->GetDevId())
			{
				ST_UpdateData oUpdateData;
				ParseSanXiangUpdateData(jsDev, oUpdateData);
				m_pSanXiang->SetUpdateData(oUpdateData);
			}
		}
		else if (nTag == enTag_TongXunPeiZhi)
		{//网关信息
			m_nGwId = jsDev["devID"].asInt64();
			Json::Value jsCellarCfg = jsDev["cellarCfg"];
			Json::Value jsSons = jsDev["sons"];
			string sImei = jsCellarCfg["imei"].asString();
			string sIccId = jsCellarCfg["iccid"].asString();
			lineEdit_imei->setText(QString::fromStdString(sImei));
			lineEdit_iccid->setText(QString::fromStdString(sIccId));
			list<QPushButton*> pButtonList;
			for (int i = 0;i < jsSons.size();i++)
			{
				int64_t nDlqId = jsSons[i].asInt64();
				if (!nDlqId)
				{
					break;
				}
				if (m_pMqttTh)
				{
					m_pMqttTh->GetAttribute(nDlqId, enTag_CommSet);//查询设备类型
				}
			}
		}
		else if (nTag == enTag_CommSet)
		{
			int nDevType = jsDev["devType"].asInt();
			int64_t nDevId = jsValue["dstID"].asInt64();
			if (!IsDlqExsit(nDevId))
			{
				QPushButton* pButton = new QPushButton();
				pButton->setProperty("devId", QVariant(nDevId));
				pButton->setProperty("devType", QVariant(nDevType));
				pButton->setStyleSheet(
					"font: 9pt \"微软雅黑\";"
					"max-width: 150;"
					"min-height: 70;"
				);
				connect(pButton, &QPushButton::clicked, this, &MantunTool::on_pushButton_dlq_clicked);
				addOneButton(pButton);
			}
		}
		else
		{

		}
	}
}

void MantunTool::on_pushButton_dlq_clicked()
{
	m_pDanXiang->ClearText();
	m_pSanXiang->ClearText();
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());
	int64_t nDevId = pButton->property("devId").toLongLong();
	int nDevType = pButton->property("devType").toInt();

	if (m_pMqttTh)
	{
		if (nDevType == enDevType_DanXiang)
		{
			m_pDanXiang->SetDevInfo(nDevId,enDevType_DanXiang);
			m_pMqttTh->GetAttribute(nDevId, enTag_DanXiangDlqCfg);
			m_pMqttTh->GetAttribute(nDevId, enTag_DanXiangDlqUpdateData);
			pushButton_back->setHidden(false);
			stackedWidget->setCurrentWidget(m_pDanXiang);
		}
		else if (enDevType_SanXiang)
		{
			m_pSanXiang->SetDevInfo(nDevId, enDevType_SanXiang);
			m_pMqttTh->GetAttribute(nDevId, enTag_SanDlqCfg);
			m_pMqttTh->GetAttribute(nDevId, enTag_SanXiangDlqUpdateData);
			pushButton_back->setHidden(false);
			stackedWidget->setCurrentWidget(m_pSanXiang);
		}
	
	}
	
}

void MantunTool::on_pushButton_back_clicked()
{
	pushButton_back->setHidden(true);
	stackedWidget->setCurrentIndex(0);
}
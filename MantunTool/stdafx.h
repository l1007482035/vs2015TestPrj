#pragma once

#define NOMINMAX

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

// 如果必须将位于下面指定平台之前的平台作为目标，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以指定将 Windows Me 或更高版本作为目标。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <QtWidgets>
#include "../Public/Global.h"
#include "../Public/CmmLibPortEx.h"
#include "../aCmmLib/ThreadMgr.h"

#include "../Public/JsonPort.h"
#include "../Public/EncryptPort.h"

#define  WM_MSG_OK		WM_USER + 2000
#define  WM_MSG_MQTT	WM_USER + 2001
using namespace std;


typedef enum tdf_EN_METHOD
{
	enMethod_Put = 3,
	enMethod_Get = 4,
	enMethod_Post = 5,
	enMethod_Delete = 6,
}EN_METHOD;

typedef enum tdf_EN_MsgCode
{
	enMsgCode_Devices = 110,//在线设备信息
	enMsgCode_Attributes = 111,//设备属性数据，用于在特定时刻（上电、配置变化）推送设备属性、配置、设定等，也支持主动获取
	enMsgCode_Status = 112,//设备状态数据，用于定期推送设备的状态、测量值等，也支持主动获取
	enMsgCode_Event = 113,//设备事件数据，用于事件发生时刻推送设备的事件、记录等，也支持主动查询
	enMsgCode_Meter = 114,//设备统计数据
	enMsgCode_Timer = 115,//设备定时数据
	enMsgCode_UdpCommand = 120,//UDP设备提供的特别命令或者服务, 分合闸
}EN_MsgCode;

//曼顿tag字段枚举
typedef enum tdf_EN_Tag
{
	enTag_Unkown = 0,
	enTag_Cmd = 305,//控制命令
	enTag_TongXunPeiZhi = 602,//通讯模块配置
	enTag_TongXunShiShi = 603,//通讯模块实时
	enTag_SanDlqCfg = 604,//三相断路器配置
	enTag_SanXiangDlqUpdateData = 605,//三相断路器实时数据
	enTag_DanXiangDlqCfg = 606,//单相断路器配置
	enTag_DanXiangDlqUpdateData = 607,//单相断路器实时数据
	enTag_CommSet = 720,//表示通用设定mcbComCfg,里面包含devTypey以及使能
	enTag_Threshold = 722,//表示阈值设定mcbThd

}EN_Tag;

//曼顿设备类型枚举
typedef enum tdf_EN_DevType
{
	enDevType_Unkown = 0,
	enDevType_DanXiang = 128,
	enDevType_SanXiang = 132,

}EN_DevType;

#define CTRL_CMD_SWOFF				"do_turn_off" //分闸
#define CTRL_CMD_SWON				"do_turn_on" //合闸
#define CTRL_CMD_REBOOT				"do_reboot" //远程重启
#define CTRL_CMD_RESET				"do_set_factory" //恢复出厂设置
#define CTRL_CMD_AUTO_ADDRESS		"do_auto_address" //自动分配地址



typedef struct tdf_ST_DlqCfg
{
	int64_t nDevId;
	string sDevName;
	int nAlarmEnVal;
	int nAlarmSWEnVal;
	///过压
	double volAH;//过压报警值V
	int volAHEn;////过压报警使能0/1
	int volAHSwEn;//过压报警分闸使能0/1
	double volWH;//过压预警值V

	//欠压
	double volAL;
	int volALEn;
	int volALSwEn;
	double volWL;

	//过流
	double curAH;
	int curAHEn;
	int curAHSwEn;
	double curWH;

	//漏电
	double leakAH;
	int leakAHEn;
	int leakAHSwEn;
	double leakWH;

	//过温
	double tmpAH;
	int tmpAHEn;
	int tmpAHSwEn;
	double tmpWH;

	//过载
	double pwrpAH;
	int pwrpAHEn;
	int pwrpAHSwEn;
	double pwrpWH;

}ST_DlqCfg;

typedef struct tdf_ST_UpdateData
{
	int on;
	double vol;
	double vola;
	double volb;
	double volc;

	double cur;
	double cura;
	double curb;
	double curc;

	double leak;

	double pwrP;
	double pwrPa;
	double pwrPb;
	double pwrPc;

	double pf;
	double pfa;
	double pfb;
	double pfc;

	double tmp;
	double tmpa;
	double tmpb;
	double tmpc;

	double freq;

}ST_UpdateData;


extern CFileLog theLog;
extern CIniFile theInifle;
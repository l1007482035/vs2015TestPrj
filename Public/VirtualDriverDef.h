#ifndef _VIRTUALDRIVERDEF_3C168011_98BB_4EE1_AB4C_38DE384721CD_H_ 
#define _VIRTUALDRIVERDEF_3C168011_98BB_4EE1_AB4C_38DE384721CD_H_

//其中%s是最终要替换的打印机驱动名[IST_PRINTER_NAME]

#define XAB_PRINTER_KEY_PATH	_T("SYSTEM\\CurrentControlSet\\Control\\Print\\Printers\\%s")
//#define XAB_PORT_KEY_PATH		_T("SYSTEM\\CurrentControlSet\\Control\\Print\\Monitors\\Xab Print Port Monitor\\Ports\\XabVPrinterPort")
#define XAB_PORT_KEY_PATH		_T("SYSTEM\\CurrentControlSet\\Control\\Print\\Monitors\\Xab Print Port Monitor\\Ports\\%s")

#define XAB_JOB_DIR				_T("JobDir")
#define XAB_JOB_EXE				_T("JobExe")

#define XAB_PORTMON_NAME		_T("Xab Print Port Monitor")
#define XAB_PORTMON_DLL			_T("XabVMonitor.dll")
#define XAB_PORTMONUI_DLL		_T("XabVMonitorUI.dll")
#define XAB_PRINTER_DRIVER		_T("XabVPrinterDriver")
#define XAB_PRINTER_PORT		_T("XabVPrinterPort")
#define XAB_PRINTER_SHARE_PORT	_T("XabVPrinterSharePort")

#define IST_PRINTER_NAME		_T("XabVPrinter")			//默认的打印机驱动名
#define IST_PRINTER_DRIVER		_T("%sDriver")
#define IST_PRINTER_PORT		_T("%sPort")
#define IST_PRINTER_DATATYPE	_T("RAW")
#define _PrintEnvironment		NULL

#ifdef _AMD64_
#define PTINTER_BIN_DIR _T("x64\\printer")
#else
#define PTINTER_BIN_DIR _T("x86\\printer")
#endif

#define PRODUCT_CUSTOM_REGISTY_KEY	_T("SOFTWARE\\iSecStar") 

#ifdef _AMD64_
#define XAB_MONITORENVNT		_T("Windows x64")
#else
#define XAB_MONITORENVNT		_T("Windows NT x86")
#endif

#define WINDOWS_SPOOL_SVR_NAME	_T("Spooler")

//导入注册表的打印机名占位符，最终在导入注册表之前，要求替换成【IST_PRINTER_NAME】
#define REGISTRY_PRINTER_NAME_PLACEHOLDE	_T("{D880C28A-B15A-4B9E-A038-18A8893BD1F7}")


#endif	//_VIRTUALDRIVERDEF_3C168011_98BB_4EE1_AB4C_38DE384721CD_H_


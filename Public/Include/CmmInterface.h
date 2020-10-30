
#ifndef _ICLTLOGCALLBACK_HEADER
#define _ICLTLOGCALLBACK_HEADER
//----------------------------
//�ʲ���Ϣ
struct _AA_DLL_EXPORT_ ICltLogCallback
{
public:
	//�ʲ�����
	virtual void OnAssetsUpdated(int nType,void* pHard){ASSERT(0);}
	//�ļ�������־
	virtual void OnFileSystemLog(void* pLogList, int nCount){ASSERT(0);}
	//��ַ
	virtual void OnUrlAccessed(int nLocal,int nRemote,CString sWebstation,CString sUrl){ASSERT(0);}
	//���򴴽�
	virtual void OnProcessCreated(DWORD dwPid,CString sPath,BOOL bAllowed){ASSERT(0);}
	//����ر�
	virtual void OnProcessShutdown(DWORD dwPid){ASSERT(0);}
	//��Ļ��־
	virtual void OnScreenCaptrued(void*){ASSERT(0);}
	//��ӡ��־
	virtual void OnPrinted(void*){ASSERT(0);}
	//��ӡ��ҵ��Ϣ
	virtual void OnJobInfo(DWORD dwType, void*){ASSERT(0);}
	//��ӡ�¼���־
	virtual void OnPrintedEvent(void*,BOOL bAllowed){ASSERT(0);}
	//�豸������־
	virtual void OnDeviceAttached(void*){ASSERT(0);}
	//�豸������־
	virtual void OnDeviceDettached(void*){ASSERT(0);}
	//����������־
	virtual void OnNetStreamLog(void* ,int){ASSERT(0);}
	// web�ʼ�������־
	virtual void OnSendWebMailLog(void* ){ASSERT(0);}
	
	//������ʾ
	virtual void OnTipMsg(int,CString,DWORD,DWORD){ASSERT(0);}

	//Ԥ������
	//���ʷǷ���ַ
	virtual void OnUrlAlarmed(CString sUrl){ASSERT(0);}
	//ʹ�÷Ƿ�����
	virtual void OnProcessAlarmed(){ASSERT(0);}
	//Ӳ���ʲ��仯
	virtual	void OnHardwareChanged(){ASSERT(0);}
	//����ʲ��仯
	virtual void OnSoftwareChanged(){ASSERT(0);}
	//ip��ַ�޸�
	virtual void OnIpChanged(){ASSERT(0);}
	//�������޸�
	virtual void OnHostNameChaned(){ASSERT(0);}
	//�ϴ���־
	virtual int OnLogUpload(int,int,const void*,int,void*){ASSERT(0);return 0;}
	//���ز�ѯ
	virtual int OnLogCallback(int,int,const void* ,int){ASSERT(0);return 0;}
};


//ģ���������ܵĽӿ�
struct _AA_DLL_EXPORT_ IModuleCallback
{
public:
	//֪ͨ�����
	virtual int NotifyMainFrm(DWORD dwCmd,WPARAM w,LPARAM l){ASSERT(0);return 0;}
	//֪ͨ�����߳�
	virtual int NotifyNetTh(DWORD dwCmd,WPARAM w,LPARAM l){ASSERT(0);return 0;}
	//ͨ���������̷߳�������
	virtual int SendByNetTh(int nCmd,int nSub,BYTE* pData,int nSize,int nCompress = -1 ){ASSERT(0);return 0;}
	//��ѯ��ǰ�û���Ϣ
	virtual void QueryUserInfo(int& nUserId,int& nAccountId,CString& sName){ASSERT(0);}
	//���е�ǰsession�Ľ������
	virtual BOOL RunUiProcess(){ASSERT(0);return 0;}
	//�����ύ��ӡ����
	virtual BOOL OnRequestSubmitPrintJob(int nId){ASSERT(0);return 0;}
	//�ϴ���־��Ϣ����
	virtual void OnUploadLogResult(int type,BOOL bSuc,void* other = 0){ASSERT(0);}
	//��־�ϴ�
	virtual void OnUploadLog(int type,void* log){ASSERT(0);}
	//������ʾ
	virtual void OnTipMsg(int,CString,DWORD,DWORD){ASSERT(0);}
	//���糬ʱ
	virtual void OnSocketTimeOut(){ASSERT(0);}
	//����ر�
	virtual void OnSocketClosed(){ASSERT(0);}
};
//�ܵ��ӿ�
struct _AA_DLL_EXPORT_ IPipeCallback
{
public:
	virtual void OnPipeRcv(void*,BYTE* pData,int nSize){ASSERT(0);}
	virtual int OnNewPipe(void* ){ASSERT(0);return 0;}
	virtual void OnPipeClose(void*){ASSERT(0);}
};
//Ӧ�ó���ӿ�
struct _AA_DLL_EXPORT_ IAppMgrCallback
{
public:
	//����ö��
	virtual void OnPopProcess(void*){ASSERT(0);}
	//����ö��
	virtual void OnPopSvc(void*){ASSERT(0);}
	//����ö��
	virtual void OnPopShare(void*){ASSERT(0);}
	//����Ϣö��
	virtual void OnPopGroup(void*){ASSERT(0);}
	//�û���Ϣö��
	virtual void OnPopUser(void*){ASSERT(0);}
	//������ö��
	virtual void OnPopStartItem(void*){ASSERT(0);}
	//����ö��
	virtual void OnPopDiskDriver(void*){ASSERT(0);}
	//�豸ö��
	virtual void OnPopDevice(void*){ASSERT(0);}
	//�豸ö��
	virtual void onPopFirewall(void*){ASSERT(0);}
	//�豸ö��
	virtual void onPopAntiSofeware(void*){ASSERT(0);}
};

//��Ļ�ӿ�
struct _AA_DLL_EXPORT_ IScreenCallback
{
public:
	//��Ļ��Ϣ;
	virtual void OnScreenInit(){ASSERT(0);}
	virtual void OnPopScreen(){ASSERT(0);}
	virtual void OnScreenExit(){ASSERT(0);}
};
//�ļ�����
struct _AA_DLL_EXPORT_ ITransmitFileCallback
{
public:
	virtual void OnBegin(int ,TCHAR* ){ASSERT(0);}
	virtual void OnTransmit(int , TCHAR*,int){ASSERT(0);}
	virtual void OnFinished(int , TCHAR*){ASSERT(0);}
	virtual void OnCompleted(int){ASSERT(0);}
	virtual void OnError(int,int){ASSERT(0);}
};

//-----------------------------------------------
//qt����ص��ӿ�
struct _AA_DLL_EXPORT_ IQtAppMgrUiCallback
{
public:
	virtual void OnPopData(void*){ASSERT(0);}
};

//qt�������������߳̽ӿ�
struct _AA_DLL_EXPORT_ IQtNetThreadCallback
{
public:
	//��������
	virtual int SendToSvr(int nCmd,int nSub,BYTE* pData,int nSize,int nCompress = -1 ){ASSERT(0);return 0;}
	
};

//��ӡ����ϵͳ��ӡ�Ʒ�
struct _AA_DLL_EXPORT_ IPrtStationPrintCallback
{
	virtual int OnPrinted(int){ASSERT(0);return 0;}
	virtual int OnNewPagePrinted(int){ASSERT(0);return 0;}
	virtual int OnPrintedCmplt(int){ASSERT(0);return 0;}
	virtual int OnPrintedErr(int ,int){ASSERT(0);return 0;}
};

//�����������ģ��֮��Ľӿ�
struct _AA_DLL_EXPORT_ ISvcCallback
{
	//������ǰsession�Ľ������
	virtual int OnRunCurrentSessionUiProcess(TCHAR* ){ASSERT(0);return 0;}
	
	// [12/27/2011 Songqx] clienthelper֪ͨ������̲�����ʱ�Ƿ���Ҫ��������
	virtual void SetShowUIFlag(BOOL bShowUI){ASSERT(0);}
	
	//�û���½�¼�
	virtual void OnSessionChange(DWORD dwEventType,LPVOID lpEventData){ASSERT(0);}
	//
	virtual void SetCallback(ISvcCallback* ){ASSERT(0);}
	//�豸������־
	virtual void OnDeviceAttached(void*){ASSERT(0);}
	//�豸������־
	virtual void OnDeviceDettached(void*){ASSERT(0);}
	
};
struct _AA_DLL_EXPORT_ IServiceCtlCallback
{
public:
	virtual void OnWebReqAck(int nCmd,int nSub,BYTE* pData,int nSize){return;}
};
//----------------------------------------------
#endif
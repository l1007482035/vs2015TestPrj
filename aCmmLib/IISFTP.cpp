// IISFTP.cpp: implementation of the CIISFTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IISFTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIISFTP::CIISFTP()
{

}

CIISFTP::~CIISFTP()
{

}
//////////////////////////////////////////
//�õ�Ftpվ����б�
//
//////////////////////////////////////////
void CIISFTP::GetFtpSiteList(CPtrList *pList)
{
	RemoveAllList(*pList);
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	
	// ���ȴ���һ������ʵ��
	if( ADsGetObject(L"IIS://localhost/MSFTPSVC",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		IEnumVARIANT *pEnum;
		LPUNKNOWN     pUnk;
		VARIANT       var;
		IDispatch    *pDisp;
		BSTR          bstrName;
		BSTR          bstrPath;
		unsigned long    lFetch;
		IADs         *pADs; 
		
		
		iContainer->get__NewEnum(&pUnk);
		
		pUnk->QueryInterface(IID_IEnumVARIANT, (void**) &pEnum);
		pUnk->Release();
		
		// Now Enumerate 
		HRESULT hr = pEnum->Next(1, &var, &lFetch);
		while(hr == S_OK)
		{
			if (lFetch == 1)
			{
				pDisp = V_DISPATCH(&var);
				pDisp->QueryInterface(IID_IADs, (void**)&pADs); 
				pDisp->Release();
				pADs->get_Name(&bstrName);
				CString sName(bstrName);		
				pADs->get_ADsPath(&bstrPath);
				CString sPath(bstrPath);
				
				_variant_t varComment;
				pADs->Get(_bstr_t("ServerComment"),&varComment);	
				CString sComment = m_fun.GetVariantStr(varComment);
				sComment.TrimLeft(_T(" "));
				sComment.TrimRight(_T(" "));
				if( !sComment.IsEmpty()!=0)
				{
					CString sVirPath;
					GetFtpSitePath(sPath,sVirPath);
					VARIANT varBindings;
					pADs->Get(_bstr_t("ServerBindings"),&varBindings);
					CString sBindings = GetServerBinding( &varBindings );
					int nPos = sBindings.Find(_T(":"));
					int nPos2 = sBindings.ReverseFind( _T(':' ));
					CString sServerIP = sBindings.Left( nPos );
					CString sServerPort = sBindings.Mid(nPos+1, nPos2 - nPos -1 );
					
					//------------------------------------------
					// Save comment
					P_S_SITEINFO pInfo = new S_SITEINFO;
					ZeroMemory( pInfo, sizeof(S_SITEINFO));
					
					pInfo->nNumber = m_fun.SToN(sName);
					_tcscpy(pInfo->szPort,sServerPort);
					_tcscpy(pInfo->szIP,sServerIP);
					_tcscpy(pInfo->szComment, sComment);
					_tcscpy(pInfo->szVPath,sVirPath);
					
					pList->AddTail( pInfo );
				}
				
				pADs->Release();
			}
			hr = pEnum->Next(1, &var, &lFetch);
		}			
		
		pEnum->Release();			
	}
	if( iContainer )
	{			
		iContainer->Release();
		iContainer = NULL;
	}
}
///////////////////////////////////////////////////////////
//�õ�Ftpվ���path
//nNumΪftpվ���
///////////////////////////////////////////////////////////
void CIISFTP::GetFtpSitePath(int nNum,CString &sVPath)
{
	CString sFtp;
	sFtp.Format(_T("IIS://LocalHost/MSFTPSVC/%d"),nNum);	
	GetFtpSitePath(sFtp,sVPath);
}

///////////////////////////////////////////////////////////
//�õ�Ftpվ���path
//sIISPathΪFtpվ���IIS·����:IIS://LocalHost/FtpSvc/1
////////////////////////////////////////////////////////////
void CIISFTP::GetFtpSitePath(CString sIISPath, CString &sVPath)
{
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;

	HRESULT     hr;
	BSTR bsTmp = sIISPath.AllocSysString();
	hr = ADsGetObject(bsTmp,IID_IADsContainer,(void**)&iContainer);
	::SysFreeString(bsTmp);
 	// ���ȴ���һ������ʵ��
	if( hr == S_OK ) 
	{
		_bstr_t bsRoot("Root");
		hr = iContainer->GetObject(_bstr_t("IIsFtpVirtualDir"), bsRoot,(IDispatch**)&iAds);
		if( hr == S_OK )
		{
			_variant_t varComment;
			iAds->Get(_bstr_t("Path"),&varComment);
			
			sVPath = varComment.bstrVal;
			
			iAds->Release();
		}

		iContainer->Release();
	}
}

///////////////////////////////////////////////////////////
//����Ftpվ��
//LPCTSTR sComment ��������
//LPCTSTR sPath  ·��
//int nPort  �˿�
////////////////////////////////////////////////////////////
BOOL CIISFTP::CreateFtpSite(LPCTSTR sComment, LPCTSTR sPath,int nPort,BOOL bStart)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/MSFTPSVC"));
 	/* ���FtpSever */ 
	if(ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer) != S_OK)
		return FALSE;

	//��������Ŀ¼ 
	int nIndex = GetUnusedFtpNum();	
	if( nIndex == 0 )
		nIndex = 10;
	if(HRESULT hr =iContainer->Create(_bstr_t("IIsFtpServer"), _bstr_t(m_fun.NToS(nIndex)),(IDispatch**)&iAds)!=S_OK)
	{
		iContainer->Release();
		return FALSE;
	}
	CString sBinding;
	sBinding.Format(_T(":%d:"),nPort);
	iAds->Put(_bstr_t("ServerSize"),_variant_t((long)1));
	iAds->Put(_bstr_t("ServerComment"),_variant_t(sComment));
	iAds->Put(_bstr_t("ServerBindings"),_variant_t(sBinding));
	iAds->Put(_bstr_t("ServerAutoStart"),_variant_t((long)1));
	//iContainer->Start();
	//iAds->Put(_bstr_t("ServerState"),_variant_t((long)1));

	iAds->SetInfo();
	BSTR bsIISPath;
	iAds->get_ADsPath(&bsIISPath);


	sIISPath = CString(bsIISPath);
	if( !CreateVirtualFtpDir(sIISPath,sPath,_T("ROOT")) )
	{
		return FALSE;
	}


	if( bStart )
	{
	//	AfxMessageBox("��ʼ����");
		IADsServiceOperations *pSrvOp = NULL;
		long status = 0;
		
		HRESULT hr = iAds->QueryInterface(IID_IADsServiceOperations,(void**)&pSrvOp);
		
		
		if(pSrvOp)
		{
		//	AfxMessageBox("���������ӿ�");
			HRESULT hr = pSrvOp->Start();
			CString szMsg;
			szMsg.Format(_T("%u    Error:%d"),hr,GetLastError());
		//	AfxMessageBox(szMsg);
		}
		if(pSrvOp)
			pSrvOp->Release();	
	}
	iAds->Release();
	iContainer->Release();
	return TRUE;
}
///////////////////////////////////////////////////////////
//����Ftpվ������Ŀ¼
// LPCTSTR sDiskPath Ӳ��·��
//LPCTSTR sVirName ����Ŀ¼����
//nSvIndex Ftpվ���
////////////////////////////////////////////////////////////
BOOL CIISFTP::CreateVirtualFtpDir(int nSvIndex,LPCTSTR sDiskPath,LPCTSTR sVirName)
{
	CString sPath;
	sPath.Format(_T("IIS://localhost/MSFTPSVC/%d/Root"),nSvIndex);
	return CreateVirtualFtpDir(sPath,sDiskPath,sVirName);
}

///////////////////////////////////////////////////////////
//����Ftpվ������Ŀ¼
//LPCTSTR sIISPath Ftpվ���IIS·����:IIS://LocalHost/w3svc/1
// LPCTSTR sDiskPath Ӳ��·��
//LPCTSTR sVirName ����Ŀ¼����
////////////////////////////////////////////////////////////
BOOL CIISFTP::CreateVirtualFtpDir(LPCTSTR sIISPath,LPCTSTR sDiskPath,LPCTSTR sVirName)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString lpszDiskPath = sDiskPath;
	CString lpszVirtualDirName = sVirName;

 	/* ���FtpSever */ 
	HRESULT hr= ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer);
	if( hr != S_OK)
		return FALSE;

	//�ȼ��������Ŀ¼ �Ƿ����
	if( this->IsVirtualDirExist(sIISPath,sVirName) )
	{
		TRACE(" The same virtual directory is already exist!\n");
		if(iContainer->GetObject(_bstr_t("IIsFtpVirtualDir"), _bstr_t(lpszVirtualDirName),(IDispatch**)&iAds) != S_OK)
		{
			iContainer->Release();
			return FALSE;
		}
		iContainer->Release();
	}
	else
	{
		//��������Ŀ¼ 
		if(iContainer->Create(_bstr_t("IIsFtpVirtualDir"), _bstr_t(lpszVirtualDirName),(IDispatch**)&iAds)!=S_OK)
		{
			iContainer->Release();
			return FALSE;
		}
		iContainer->Release();
	}

	//��������Ŀ¼������ 
	iAds->Put(_bstr_t("AccessRead"),_variant_t("True"));//ע���VB�е��������ԱȽ�
	iAds->Put(_bstr_t("AccessWrite"),_variant_t("true"));
	iAds->Put(_bstr_t("DontLog"),_variant_t("TRUE"));
	iAds->Put(_bstr_t("Path"),_variant_t(lpszDiskPath));
	iAds->SetInfo();
	iAds->Release();

	return TRUE;
}

///////////////////////////////////////////////////////////
//���վ�������Ŀ¼�Ƿ����
//nSvIndexΪFTPվ���
//////////////////////////////////////////////////////////
BOOL CIISFTP::IsVirtualDirExist(LPCTSTR sVirDir,int nSvIndex)
{
	IADsContainer* iContainer;

	CString sW3Path;
	sW3Path.Format(_T("IIS://localhost/MSFTPSVC/%d/Root/%s"),nSvIndex,sVirDir);
 	/* ���FTPSever */ 
	HRESULT hr1 = ADsGetObject(_bstr_t(sW3Path),IID_IADsContainer,(void**)&iContainer);
	if( hr1 == S_OK)
	{	
		iContainer->Release();
		return TRUE;
	}

	return FALSE;
}
///////////////////////////////////////////////////////////
//���վ�������Ŀ¼�Ƿ����
//nSvIndexΪFTPվ���
//////////////////////////////////////////////////////////
BOOL CIISFTP::IsVirtualDirExist(LPCTSTR sIISPath,LPCTSTR sVirDir)
{
	IADsContainer* iContainer;

	CString sW3Path;
	sW3Path.Format(_T("%s/%s"),sIISPath,sVirDir);
 	/* ���FTPSever */ 
	HRESULT hr1 = ADsGetObject(_bstr_t(sW3Path),IID_IADsContainer,(void**)&iContainer);
	if( hr1 == S_OK)
	{	
		iContainer->Release();
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////
//ɾ��վ��
//nIndexΪFtpվ���
//////////////////////////////////////////////////////////
BOOL CIISFTP::DeleteFtpSite(int nIndex)
{	
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	CString sPath;
	sPath.Format(_T("IIS://localhost/MSFTPSVC"));
	// ���ȴ���һ������ʵ��
	HRESULT hr =  ADsGetObject(_bstr_t(sPath),IID_IADsContainer,(void**)&iContainer);
	if(hr == S_OK ) 
	{
#ifndef UNICODE
		hr = iContainer->Delete(_bstr_t("IIsFtpServer"),m_fun.SToB(m_fun.NToS(nIndex)));
#else
		CString sIndex = _T("");
		sIndex.Format(_T("%d"), nIndex);
		hr = iContainer->Delete(_bstr_t("IIsFtpServer"), sIndex.GetBuffer());
		sIndex.ReleaseBuffer();
#endif
		iContainer->Release();
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//�õ���С��һ��δ�õ�վ���
//////////////////////////////////////////////////////////
int CIISFTP::GetUnusedFtpNum()
{
	int nIndex = 0;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	
	// ���ȴ���һ������ʵ��
	if( ADsGetObject(L"IIS://localhost/MSFTPSVC",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		for(int i=1; i<100; i++)
		{
			CString sNumber;
			sNumber.Format(_T("%d"), i);
			
			if( iContainer->GetObject(_bstr_t("IIsFtpServer"), _bstr_t( sNumber.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
			{				
				iAds->Release();
			}
			else
			{
				nIndex = i;
				break;
			}
			
		}
		
		iContainer->Release();
	}
	return nIndex;
}
///////////////////////////////////////////////////////////
//�õ�WebBinding
//nWebNumΪwebվ���
//////////////////////////////////////////////////////////
CString CIISFTP::GetFtpBinding(int nFtpNum)
{
	CString sBindings;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
 	
	CString sFtp;
	sFtp.Format(_T("%d"),nFtpNum);
	if( ADsGetObject(L"IIS://localhost/MSFTPSVC",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		if( iContainer->GetObject(_bstr_t("IIsFtpServer"), _bstr_t( sFtp.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
		{
			VARIANT varBindings;
			int nRet;
			nRet = iAds->Get(_bstr_t("ServerBindings"),&varBindings);
			sBindings = GetServerBinding( &varBindings );			
			iAds->Release();
		}

		iContainer->Release();
	}

	return sBindings;
}

BOOL CIISFTP::SetFtpSitePath(int nIndex, CString sPath)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/MSFTPSVC/%d"),nIndex);
 	/* ���FtpSever */ 
	if(ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer) != S_OK)
		return FALSE;

	if( !iContainer->GetObject(_bstr_t("IIsFtpVirtualDir"), _bstr_t("ROOT"),(IDispatch**)&iAds) == S_OK )
	{
		return FALSE;
	}

	

	//��������Ŀ¼������ 	
	_variant_t var;
	var.vt = VT_BOOL;
	var.boolVal = true;
	iAds->Put(_bstr_t("AccessRead"),var);
	iAds->Put(_bstr_t("AccessWrite"),var);
	var.boolVal = false;
	iAds->Put(_bstr_t("DontLog"),var);
	iAds->Put(_bstr_t("Path"),_variant_t(sPath));
	iAds->SetInfo();

	iAds->Release();
	iContainer->Release();

	return TRUE;
}

BOOL CIISFTP::SetFTPProperty(int nIndex, CString szName,BOOL bValue)
{
	CString sBindings;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
 	
	CString sFtp;
	sFtp.Format(_T("%d"),nIndex);
	if( ADsGetObject(L"IIS://localhost/MSFTPSVC",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		if( iContainer->GetObject(_bstr_t("IIsFtpServer"), _bstr_t( sFtp.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
		{
			VARIANT varBindings;
			int nRet;
			_variant_t var;
			var.vt = VT_BOOL;
			var.boolVal = bValue;
			nRet = iAds->Put(_bstr_t(szName),var);
			iAds->SetInfo();
			iAds->Release();
		}

		iContainer->Release();
	}
	return true;
}

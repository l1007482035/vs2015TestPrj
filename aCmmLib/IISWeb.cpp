// IISWeb.cpp: implementation of the CIISWeb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IISWeb.h"
#include <iiisext.h>
#include <iisext_i.c>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIISWeb::CIISWeb()
{

}

CIISWeb::~CIISWeb()
{

}
//////////////////////////////////////////
//�õ�WEBվ����б�
//
//////////////////////////////////////////
void CIISWeb::GetWebSiteList(CPtrList *pList)
{
	RemoveAllList(*pList);
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	
	// ���ȴ���һ������ʵ��
	if( ADsGetObject(L"IIS://localhost/w3svc",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
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
				if( !sComment.IsEmpty()  
					&& sComment.CompareNoCase(_T("���� Web վ��")) !=0
					&& sComment.CompareNoCase(_T("Microsoft SharePoint ����")) !=0
					&& sComment.CompareNoCase(_T("Windows Media ����վ��")) !=0
					&& sComment.CompareNoCase(_T("Administration")) !=0
					)
					
				{
					CString sVirPath;
					GetWebSitePath(sPath,sVirPath);
					VARIANT varBindings;
					pADs->Get(_bstr_t("ServerBindings"),&varBindings);
					CString sBindings = GetServerBinding( &varBindings );
					int nPos = sBindings.Find(_T(":"));
					int nPos2 = sBindings.ReverseFind( ':' );
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
//�õ�WEBվ���path
//nWebNumΪwebվ���
///////////////////////////////////////////////////////////
void CIISWeb::GetWebSitePath(int nWebNum,CString &sVPath)
{
	CString sWeb;
	sWeb.Format(_T("IIS://LocalHost/w3svc/%d"),nWebNum);	
	GetWebSitePath(sWeb,sVPath);
}

///////////////////////////////////////////////////////////
//�õ�WEBվ���path
//sIISPathΪwebվ���IIS·����:IIS://LocalHost/w3svc/1
////////////////////////////////////////////////////////////
void CIISWeb::GetWebSitePath(CString sIISPath,CString &sVPath)
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
		hr = iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), bsRoot,(IDispatch**)&iAds);
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
void  CIISWeb::GetVirtualWebDirPath(int nWebNum,CString sVDir,CString &sVPath)
{
	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/w3svc/%d/ROOT"),nWebNum);	

	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;

	HRESULT     hr;
	BSTR bsTmp = sIISPath.AllocSysString();
	hr = ADsGetObject(bsTmp,IID_IADsContainer,(void**)&iContainer);
	::SysFreeString(bsTmp);
 	// ���ȴ���һ������ʵ��
	if( hr == S_OK ) 
	{
		_bstr_t bsRoot(sVDir);
		hr = iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), bsRoot,(IDispatch**)&iAds);
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
//����webվ��
//LPCTSTR sComment ��������
//LPCTSTR sPath  ·��
//int nPort  �˿�
////////////////////////////////////////////////////////////
BOOL CIISWeb::CreateWebSite(LPCTSTR sComment, LPCTSTR sPath,int nPort,BOOL bStart)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/w3svc"));
 	/* ���WebSever */ 
	if(ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer) != S_OK)
		return FALSE;

	//��������Ŀ¼ 
	int nIndex = GetUnusedWebNum();	
	if( nIndex == 0 )
		nIndex = 10;
	if(HRESULT hr =iContainer->Create(_bstr_t("IIsWebServer"), _bstr_t(m_fun.NToS(nIndex)),(IDispatch**)&iAds)!=S_OK)
	{
		iContainer->Release();
		return FALSE;
	}
	CString sBinding;
	sBinding.Format(_T(":%d:"),nPort);
	iAds->Put(_bstr_t("ServerSize"),_variant_t("1"));
	iAds->Put(_bstr_t("ServerComment"),_variant_t(sComment));
	iAds->Put(_bstr_t("ServerBindings"),_variant_t(sBinding));
	iAds->Put(_bstr_t("ServerAutoStart"),_variant_t("1"));
	if( bStart )
	{
		IADsServiceOperations *pSrvOp = NULL;
		long status = 0;
		
		HRESULT hr = iAds->QueryInterface(IID_IADsServiceOperations,(void**)&pSrvOp);
		
		
		if(pSrvOp) pSrvOp->Start();
		if(pSrvOp) pSrvOp->Release();		
	}
	iAds->SetInfo();
	BSTR bsIISPath;
	iAds->get_ADsPath(&bsIISPath);
	iAds->Release();
	iContainer->Release();

	sIISPath = CString(bsIISPath);
	if( !CreateVirtualWebDir(sIISPath,sPath,_T("ROOT")) )
	{
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////
//����webվ������Ŀ¼
// LPCTSTR sDiskPath Ӳ��·��
//LPCTSTR sVirName ����Ŀ¼����
//nSvIndex WEBվ���
////////////////////////////////////////////////////////////
BOOL CIISWeb::CreateVirtualWebDir(int nSvIndex,LPCTSTR sDiskPath,LPCTSTR sVirName,LPCTSTR sUserName,LPCTSTR sPwd)
{
	CString sPath;
	sPath.Format(_T("IIS://localhost/w3svc/%d/Root"),nSvIndex);
	return CreateVirtualWebDir(sPath,sDiskPath,sVirName,sUserName,sPwd);
}

///////////////////////////////////////////////////////////
//����webվ������Ŀ¼
//LPCTSTR sIISPath WEBվ���IIS·����:IIS://LocalHost/w3svc/1
// LPCTSTR sDiskPath Ӳ��·��
//LPCTSTR sVirName ����Ŀ¼����
////////////////////////////////////////////////////////////
BOOL CIISWeb::CreateVirtualWebDir(LPCTSTR sIISPath,LPCTSTR sDiskPath,LPCTSTR sVirName,LPCTSTR sUserName,LPCTSTR sPwd)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString lpszDiskPath = sDiskPath;
	CString lpszVirtualDirName = sVirName;

 	/* ���WebSever */ 
	HRESULT hr=ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer);
	if( hr != S_OK)
	{
		m_fun.WriteFileLog(_T("ADsGetObject(%s) Error=%d hr=0x%x"),sIISPath,GetLastError(),hr);
		return FALSE;
	}

	//�ȼ��������Ŀ¼ �Ƿ����
	if( this->IsVirtualDirExist(sIISPath,sVirName) )
	{
		m_fun.WriteFileLog(_T(" %s,%s already exist!"),sIISPath,sVirName);
		hr=iContainer->Delete(_bstr_t("IIsWebVirtualDir"), _bstr_t(lpszVirtualDirName));
		if( hr != S_OK)
		{
			m_fun.WriteFileLog(_T("Delete(IIsWebVirtualDir %s) Error=%d hr=0x%x"),lpszVirtualDirName,GetLastError(),hr);
		}

		/*hr=iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), _bstr_t(lpszVirtualDirName),(IDispatch**)&iAds);
		if( hr != S_OK)
		{
			m_fun.WriteFileLog(_T("GetObject(IIsWebVirtualDir) Error=%d hr=0x%x"),GetLastError(),hr);
			iContainer->Release();
			return FALSE;
		}
		iContainer->Release();*/
	}
	//else
//	{		
		//��������Ŀ¼ 
		if(hr=iContainer->Create(_bstr_t("IIsWebVirtualDir"), _bstr_t(lpszVirtualDirName),(IDispatch**)&iAds)!=S_OK)
		{
			m_fun.WriteFileLog(_T("Create(%s) Error=%d hr=0x%x"),lpszVirtualDirName,GetLastError(),hr);
			iContainer->Release();
			return FALSE;
		}
		iContainer->Release();
//	}

	//��������Ŀ¼������ 
	iAds->Put(_bstr_t("AccessRead"),_variant_t("True"));//ע���VB�е��������ԱȽ�
	iAds->Put(_bstr_t("AccessWrite"),_variant_t("False"));
	iAds->Put(_bstr_t("AccessNoRemoteWrite"),_variant_t("False"));
	iAds->Put(_bstr_t("EnableDirBrowsing"),_variant_t("FALSE"));
	iAds->Put(_bstr_t("EnableDefaultDoc"),_variant_t("true"));
	iAds->Put(_bstr_t("AccessFlags"),_variant_t(long(513)));

	iAds->Put(_bstr_t("DontLog"),_variant_t("TRUE"));
	iAds->Put(_bstr_t("Path"),_variant_t(lpszDiskPath));
	iAds->Put(_bstr_t("AspEnableParentPaths"),_variant_t(true));
	
	if( sUserName != NULL && !CString(sUserName).IsEmpty() )
	{
		iAds->Put(_bstr_t("UNCUserName"),_variant_t(sUserName));
		iAds->Put(_bstr_t("UNCPassword"),_variant_t(sPwd));
	}

	//------------------------------------------------
	IISApp *pApp = NULL;
	IISApp2 *pApp2 = NULL;
	IISApp3 *pApp3 = NULL;	

	hr = iAds->QueryInterface( IID_IISApp, (void **)&pApp );
	if ( FAILED( hr ) )
	{
		hr = iAds->QueryInterface( IID_IISApp2, (void **)&pApp2 );
		if ( FAILED( hr ) )
		{
			hr = iAds->QueryInterface( IID_IISApp3, (void **)&pApp3 );
			if ( FAILED( hr ) )
			{
				TRACE( "QI for IIsApp3 failed. Error 0x%0x\n", hr );
				goto error;
			}
		}
	}
	VARIANT varPool;
	VariantInit( &varPool );
	
	varPool.vt = VT_BSTR;
	varPool.bstrVal = SysAllocString( L"DefaultAppPool" );
	
	VARIANT varCreatePool;
	VariantInit( &varCreatePool );	
	varCreatePool.vt = VT_BOOL;
	varCreatePool.boolVal = VARIANT_TRUE;
	
	if(pApp)
		hr = pApp->AppCreate(FALSE);
	else if(pApp2)
		hr = pApp2->AppCreate2(1);
	else if(pApp3)
		hr = pApp3->AppCreate3( 2, varPool, varCreatePool );
	if ( FAILED( hr ) )
	{
		TRACE( "AppCreateX() call failed. Error 0x%0x\n", hr );
		goto error;
	}
	
	TRACE( "Call to AppCreate3() succeeded!\n" );

	iAds->Put(_bstr_t("AppFriendlyName"),_variant_t(sVirName));

error:
	if ( pApp)
		pApp->Release();
	if ( pApp3 )
		pApp3->Release();
	
	if ( pApp2 )
		pApp2->Release();

	//-------------------------------------------------

	iAds->SetInfo();
	iAds->Release();

	return TRUE;
}
///////////////////////////////////////////////////////////
//�õ�WebBinding
//nWebNumΪwebվ���
//////////////////////////////////////////////////////////
CString CIISWeb::GetWebBinding(int nWebNum)
{
	CString sBindings;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
 	
	CString sWebNum;
	sWebNum.Format(_T("%d"),nWebNum);
	if( ADsGetObject(L"IIS://localhost/w3svc",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		if( iContainer->GetObject(_bstr_t("IIsWebServer"), _bstr_t( sWebNum.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
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
///////////////////////////////////////////////////////////
//ɾ��վ��
//nIndexΪwebվ���
//////////////////////////////////////////////////////////
BOOL CIISWeb::DeleteWebSite(int nIndex)
{	
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	CString sPath;
	sPath.Format(_T("IIS://localhost/w3svc"));	
	// ���ȴ���һ������ʵ��
	HRESULT hr =  ADsGetObject(_bstr_t(sPath),IID_IADsContainer,(void**)&iContainer);
	if(hr == S_OK ) 
	{
#ifndef UNICODE
		hr = iContainer->Delete(_bstr_t("IIsWebServer"), m_fun.SToB(m_fun.NToS(nIndex)));
#else
		CString sIndex = _T("");
		sIndex.Format(_T("%d"), nIndex);
		hr = iContainer->Delete(_bstr_t("IIsWebServer"), sIndex.GetBuffer());
		sIndex.ReleaseBuffer();
#endif
		iContainer->Release();
	}

	return TRUE;
}
///////////////////////////////////////////////////////////
//�õ���С��һ��δ�õ�վ���
//////////////////////////////////////////////////////////
int CIISWeb::GetUnusedWebNum()
{
	int nIndex = 0;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
	
	// ���ȴ���һ������ʵ��
	if( ADsGetObject(L"IIS://localhost/w3svc",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		for(int i=1; i<100; i++)
		{
			CString sNumber;
			sNumber.Format(_T("%d"), i);
			
			if( iContainer->GetObject(_bstr_t("IIsWebServer"), _bstr_t( sNumber.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
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
//���վ�������Ŀ¼�Ƿ����
//nSvIndexΪwebվ���
//////////////////////////////////////////////////////////
BOOL CIISWeb::IsVirtualDirExist(LPCTSTR sVirDir,int nSvIndex)
{
	IADsContainer* iContainer;

	CString sW3Path;
	sW3Path.Format(_T("IIS://localhost/w3svc/%d/Root/%s"),nSvIndex,sVirDir);
 	/* ���WebSever */ 
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
//nSvIndexΪwebվ���
//////////////////////////////////////////////////////////
BOOL CIISWeb::IsVirtualDirExist(LPCTSTR sIISPath,LPCTSTR sVirDir)
{
	IADsContainer* iContainer;

	CString sW3Path;
	sW3Path.Format(_T("%s/%s"),sIISPath,sVirDir);
 	/* ���WebSever */ 
	HRESULT hr1 = ADsGetObject(_bstr_t(sW3Path),IID_IADsContainer,(void**)&iContainer);
	if( hr1 == S_OK)
	{	
		iContainer->Release();
		return TRUE;
	}

	return FALSE;
}

BOOL CIISWeb::SetWebSitePath(int nIndex, CString sPath)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/w3svc/%d"),nIndex);
 	/* ���FtpSever */ 
	HRESULT hr;
	if(hr=ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer) != S_OK)
	{
		m_fun.WriteFileLog(_T("Path=%s hr=0x%x"),sIISPath,hr);
		return FALSE;
	}

	if( hr=iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), _bstr_t("ROOT"),(IDispatch**)&iAds) != S_OK )
	{
		m_fun.WriteFileLog(_T("Path=%s hr=0x%x"),sIISPath,hr);
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
BOOL CIISWeb::SetWebSiteDefaultDoc(int nIndex, CString sDoc)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	sIISPath.Format(_T("IIS://localhost/w3svc/%d"),nIndex);
 	/* ���FtpSever */ 
	if(ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer) != S_OK)
		return FALSE;

	if( !iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), _bstr_t("ROOT"),(IDispatch**)&iAds) == S_OK )
	{
		return FALSE;
	}

	

	//��������Ŀ¼������ 	

	iAds->Put(_bstr_t("DefaultDoc"),_variant_t(sDoc));
	iAds->Put(_bstr_t("AspEnableParentPaths"),_variant_t(true));

	iAds->SetInfo();

	iAds->Release();
	iContainer->Release();

	return TRUE;
}

BOOL CIISWeb::SetWebDirWriteAccess(int nIndex, CString sVName, CString sDir)
{
	IADsContainer* iContainer;
	IADs* iAds;

	CString sIISPath;
	HRESULT hr;
	sIISPath.Format(_T("IIS://localhost/w3svc/%d/ROOT/%s"),nIndex,sVName);
 	/* ���FtpSever */ 
	hr = ADsGetObject(_bstr_t(sIISPath),IID_IADsContainer,(void**)&iContainer);
	if( hr != S_OK)
		return FALSE;

	hr = iContainer->GetObject(_bstr_t("IIsWebVirtualDir"), _bstr_t(sDir),(IDispatch**)&iAds);

	if( FAILED(hr) )
	{
		m_fun.WriteFileLog(_T("GetObject(IIsWebDirectory) Error %d,hr=0x%x "),GetLastError(),hr);
		return FALSE;
	}

	
	//��������Ŀ¼������ 	
	_variant_t var;
	var.vt = VT_BOOL;
	var.boolVal = true;
	iAds->Put(_bstr_t("AccessRead"),var);
	iAds->Put(_bstr_t("AccessWrite"),var);
	iAds->SetInfo();

	iAds->Release();
	iContainer->Release();

	return TRUE;
}

BOOL CIISWeb::DeleteVirtualDir(LPCTSTR sVirDir, int nSvIndex)
{
	IADsContainer* iContainer;

	CString sW3Path;
	sW3Path.Format(_T("IIS://localhost/w3svc/%d/Root"),nSvIndex);
 	/* ���WebSever */ 
	HRESULT hr1 = ADsGetObject(_bstr_t(sW3Path),IID_IADsContainer,(void**)&iContainer);
	if( hr1 == S_OK)
	{	
		HRESULT hr=iContainer->Delete(_bstr_t("IIsWebVirtualDir"), _bstr_t(sVirDir));
		iContainer->Release();
		if( hr == S_OK )
		{
			return TRUE;
		}
		else
		{
			m_fun.WriteFileLog(_T("Delete(IIsWebVirtualDir %s) Error=%d hr=0x%x"),sVirDir,GetLastError(),hr);

		}
	}

	return FALSE;
}

void CIISWeb::StartWebSite(int nIndex)
{
	/*
	CString sBindings;
	IADsContainer* iContainer = NULL;
	IADs* iAds = NULL;
 	
	CString sWebNum;
	sWebNum.Format(_T("%d"),nIndex);
	if( ADsGetObject(L"IIS://localhost/w3svc",IID_IADsContainer,(void**)&iContainer) == S_OK ) 
	{
		if( iContainer->GetObject(_bstr_t("IIsWebServer"), _bstr_t( sWebNum.operator LPCTSTR() ),(IDispatch**)&iAds) == S_OK )
		{
			iAds->Start();	
			iAds->Release();
		}

		iContainer->Release();
	}
	*/
}

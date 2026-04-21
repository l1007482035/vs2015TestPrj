#include "stdafx.h"
#include "ErTongGuShi.h"
#include <afxinet.h>

ErTongGuShi::ErTongGuShi(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

void ErTongGuShi::on_pushButton_clicked()
{

}

CString ErTongGuShi::GetHttpContentByUrl(CString szUrl)
{
	CString szinfo = _T("");
	CInternetSession *pInetSession = NULL;
	try
	{
		pInetSession = new CInternetSession;
		CHttpFile *pHttpFile = NULL;
		pHttpFile = (CHttpFile*)pInetSession->OpenURL(szUrl);   //打开一个URL
		if (!pHttpFile)
		{
			theLog.Write(_T("!!CSnmpPrinterMeterMonitorHP::HtmlToList,1,fail"));
			return szinfo;
		}

		//theLog.Write("CSnmpPrinterMeterMonitorHP::HtmlToList,2,pHttpFile=0x%x", pHttpFile);
		//pHttpFile 确实是否要删除
		CString str;

		while (pHttpFile->ReadString(str))
		{
			szinfo += str;
		}
		delete pHttpFile;
		pHttpFile = NULL;
		delete pInetSession;
		pInetSession = NULL;
	}
	catch (...)
	{
		theLog.Write(_T("!!GetMeterByUrl catch exception.ERROR=%d"), GetLastError());
		delete pInetSession;
		pInetSession = NULL;
	}
	return szinfo;
}

CString ErTongGuShi::GetHttpsContentByUrl(CString szUrl)
{
	DWORD dwFlags;
	DWORD dwStatus = 0;
	DWORD dwStatusLen = sizeof(dwStatus);
	CString strLine;
	DWORD m_dwServiceType;
	CString m_strServer;
	CString m_strObject_URI;
	INTERNET_PORT  m_nServerPort = 0;
	CString m_strHttpVersion;
	CString m_strHtml;

	AfxParseURL(szUrl, m_dwServiceType, m_strServer, m_strObject_URI, m_nServerPort);
	CInternetSession *m_pSess = new CInternetSession;
	CHttpFile *m_pHttpFile = NULL;
	CHttpConnection *m_pHttpConn = NULL;

	try {
		m_pHttpConn = m_pSess->GetHttpConnection(m_strServer, INTERNET_FLAG_SECURE, m_nServerPort,
			NULL, NULL);
		if (m_pHttpConn)
		{
			m_pHttpFile = (CHttpFile*)m_pHttpConn->OpenRequest(CHttpConnection::HTTP_VERB_GET, m_strObject_URI, NULL, 1,  //HTTP_VERB_POST
				NULL, m_strHttpVersion,
				INTERNET_FLAG_SECURE |
				INTERNET_FLAG_EXISTING_CONNECT |
				INTERNET_FLAG_RELOAD |
				INTERNET_FLAG_NO_CACHE_WRITE |
				INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
				INTERNET_FLAG_IGNORE_CERT_CN_INVALID
			);
			//get web server option  
			BOOL BRet = m_pHttpFile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
			if (!BRet)
			{
				theLog.Write(_T("!!CSnmpPrinterMeterMonitorHP::GetHttpsMeterByUrl,11,QueryOption fail,err=%d"), GetLastError());
			}
			//dwFlags |= SECURITY_FLAG_IGNORE_WRONG_USAGE;//SECURITY_FLAG_IGNORE_UNKNOWN_CA;  
			//			dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;//SECURITY_FLAG_IGNORE_UNKNOWN_CA;  
			dwFlags |= SECURITY_IGNORE_ERROR_MASK;	//SECURITY_FLAG_IGNORE_UNKNOWN_CA;
													//set web server option  
			BRet = m_pHttpFile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
			if (!BRet)
			{
				theLog.Write(_T("!!CSnmpPrinterMeterMonitorHP::SetOption,11,QueryOption fail,err=%d"), GetLastError());
			}
			m_pHttpFile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded"));
			m_pHttpFile->AddRequestHeaders(_T("Accept: */*"));
			if (m_pHttpFile->SendRequest())
			{
				//get response status if success, return 200  
				int nRet = m_pHttpFile->QueryInfo(HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_STATUS_CODE,
					&dwStatus, &dwStatusLen, 0);
				//theLog.Write("CSnmpPrinterMeterMonitorHP::SetOption,13,QueryOption nRet=%d",nRet);
				while (m_pHttpFile->ReadString(strLine))
				{
					m_strHtml += strLine + char(13) + char(10);
				}
			}
			else
			{
				theLog.Write(_T("!!CSnmpPrinterMeterMonitorHP::SetOption,13,send request failed"));

			}
		}
		else
		{
			theLog.Write(_T("CSnmpPrinterMeterMonitorHP::SetOption,13,send request failed"));
		}
	}
	catch (CInternetException *e)
	{
		e->ReportError();
	}
	m_pSess->Close();
	delete m_pSess;
	m_pSess = NULL;
	m_pHttpFile->Close();
	delete m_pHttpFile;
	m_pHttpFile = NULL;
	return m_strHtml;
}
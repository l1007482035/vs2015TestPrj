// adobeCom2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "adobeCom2.h"
#include "acrobat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			wprintf(L"错误: MFC 初始化失败\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
			//AfxOleInit();
			CoInitialize(NULL);
			CAcroApp* m_pAcroApp = new CAcroApp;

			if (!m_pAcroApp->CreateDispatch(TEXT("AcroExch.App")))
			{
				//DisplayMsg(_T("Failed to create m_pAcroApp"));
				//break;;
				printf("create app fail\n");
			}
			CAcroAVDoc* m_pAcroAVDoc = new CAcroAVDoc;
			if (!m_pAcroAVDoc->CreateDispatch(TEXT("AcroExch.AVDoc")))
			{
				//DisplayMsg(_T("Failed to create AVDoc"));
				//break;
				printf("create doc fail\n");
			}
			m_pAcroAVDoc->Open("D:\\ddd.pdf", _T(""));
			CAcroPDDoc tempDoc;
			tempDoc.AttachDispatch(m_pAcroAVDoc->GetPDDoc(), TRUE);



			LPDISPATCH jso = tempDoc.GetJSObject();
			if (jso == NULL)
			{
				//AfxMessageBox(_T("jso == null"));
			}
			DISPID dispId;
			OLECHAR FAR* szMember = L"SaveAs";
			HRESULT hr = jso->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispId);
			if (FAILED(hr))throw (hr);
			DISPPARAMS dispParams;
			memset(&dispParams, 0, sizeof(dispParams));
			dispParams.cArgs = 2;
			CComVariant* pVars = new CComVariant[2];
			pVars[1] = L"d:\\pdfa.pdf";
			pVars[0] = L"com.callas.preflight.pdfa";//com.adobe.acrobat.tiff com.callas.preflight.pdfa
			pVars[1].ChangeType(VT_BSTR);
			pVars[0].ChangeType(VT_BSTR);
			dispParams.rgvarg = pVars;
			dispParams.cNamedArgs = 0;
			EXCEPINFO excepInfo;
			memset(&excepInfo, 0, sizeof(excepInfo));
			CComVariant vaResult;
			UINT nArgErr = (UINT)-1;
			hr = jso->Invoke(dispId, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispParams, &vaResult, &excepInfo, &nArgErr);
			delete[] pVars;


			// Print all pages of the document
			//itfAVDocument->PrintPagesSilent(0, nPages - 1, 0, true, true);


			// Close the document
			m_pAcroAVDoc->Close(true);


			// Close Adobe Acrobat Writer
			m_pAcroApp->Exit();
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		wprintf(L"错误: GetModuleHandle 失败\n");
		nRetCode = 1;
	}

	return nRetCode;
}

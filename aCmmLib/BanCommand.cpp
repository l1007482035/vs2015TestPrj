// BanSomeApplication.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "BanCommand.h"
#include "shlwapi.h"
#include "SecurityTool.h"
#pragma comment(lib, "shlwapi.lib")
BanCommand::BanCommand()
{

}

BanCommand::~BanCommand()
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ȡ�����/ɾ������
BOOL BanCommand::SetBanDIApplication(BOOL sign)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Uninstall");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Uninstall"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Uninstall failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("NoAddRemovePrograms"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Uninstall NoAddRemovePrograms failed!"));
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg;
	return bRet;
}

BOOL BanCommand::SetBanTaskManager(BOOL sign)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("DisableTaskmgr"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System DisableTaskmgr failed!"));
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg;
	return bRet;
}

BOOL BanCommand::SetBanLinkProperty(BOOL sign)
{
	ASSERT(0);
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Policies\\Microsoft\\Windows\\Network Connections");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Policies\\Microsoft\\Windows\\Network Connections"),sSID);
			theLog.Write(_T("ǰ�û���ϵͳsKeyPath = %s"),sKeyPath);
		}
		else
		{
			nID = 2;
			pReg = new CRegistry2(0,0);
		}
			
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Policies\\Microsoft\\Windows\\Network Connections failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		if (!pReg->Write(_T("NC_EnableAdminProhibits"),Num))
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Policies\\Microsoft\\Windows\\Network Connections NC_EnableAdminProhibits failed!"));
			bRet = 0;
			break;
		}
		if (!pReg->Write(_T("NC_LanProperties"),0))
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Policies\\Microsoft\\Windows\\Network Connections NC_LanProperties failed"));
			bRet = 0;
			break;
		}
		if (!pReg->Write(_T("NC_LanConnect"),0))
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Policies\\Microsoft\\Windows\\Network Connections NC_LanProperties failed"));
			bRet = 0;
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg; 
	return bRet;
}

BOOL BanCommand::SetBanComputername(BOOL sign)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoPropertiesMyComputer");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoPropertiesMyComputer"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoPropertiesMyComputer failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("NoPropertiesMyComputer"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoPropertiesMyComputer NoPropertiesMyComputer failed!"));
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg;
	SendMessage(HWND_BROADCAST,WM_SETTINGCHANGE,0,0);  
	return bRet;
}

BOOL BanCommand::SetBanMenu(BOOL sign)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("NoSetTaskBar"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer NoSetTaskBar failed!"));
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg;
	SendMessage(HWND_BROADCAST,WM_SETTINGCHANGE,0,0);  
	return bRet;
}

BOOL BanCommand::DelStartItem(CString path)
{
	ASSERT(0);
	BOOL bRet = TRUE;
	// �޸��ļ��ĵ�����
	CFileStatus status;
	if (CFile::GetStatus(path,status))
	{
		status.m_attribute = 0x00;
		CFile::SetStatus(path,status);
		// ɾ���ļ� 
		DeleteFile(path);
	}
	else
	{
		CRegistry2* pReg = NULL;
		CString sWinUser;
		CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
		CString sKeyAllPath =  path;
		int length = path.GetLength();
		int lastindex = path.ReverseFind('\\');
		if (-1 == lastindex)
			return FALSE;
		CString name = path.Right(length-lastindex-1);
		do 
		{
			// �����ɾ���Ĺ�������
			if (sKeyAllPath.Find(_T("HKEY_LOCAL_MACHINE")) != -1)
			{
				pReg = new CRegistry2(2,0);
				if (!pReg)
				{
					theLog.Write(_T("new CRegistry2 failed"));
					bRet = 0;
					break;
				}
			}
			else if (sKeyAllPath.Find(_T("HKEY_CURRENT_USER")) != -1)
			{
				// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
				CSecurityTool::GetCurrProcessUser(sWinUser);
				if(sWinUser.CompareNoCase(_T("system")) == 0)
				{
					CString sSID;
					CSecurityTool::GetCurUserSID(sSID);
					if (sSID.IsEmpty())
					{
						theLog.Write(_T("GetCurUserSID failed"));
						bRet = 0;
						break;
					}
					pReg = new CRegistry2(3,0);
					if (!pReg)
					{
						theLog.Write(_T("new CRegistry2 failed"));
						bRet = 0;
						break;
					}
					sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"),sSID);
				}
				else
				{
					pReg = new CRegistry2(0,0);
					// �������ʧ�ܣ�ֱ�ӷ���
					if (!pReg)
					{
						theLog.Write(_T("new CRegistry2 failed"));
						bRet = 0;
						break;
					}
				}
			}
			if (pReg)
			{
				bRet = pReg->Open(sKeyPath);
				if (!bRet)
				{
					sKeyAllPath.Format(_T("RegOpenKeyEx %s failed"),path);
					theLog.Write(sKeyAllPath);
					bRet = 0;
					break;
				}

				bRet = pReg->Delete(name);
				if (!bRet)
				{
					sKeyAllPath.Format(_T("RegDeleteValue %s failed"),path);
					theLog.Write(sKeyAllPath);
					bRet = 0;
					break;
				}
			}
		} while (0);

		// ����ͷ���Դ
		if (pReg)
			delete pReg;
	}
	return bRet;
}
//��ֹʹ��ע���
BOOL BanCommand::SetBanRegister(BOOL sign)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 1;
	if (!sign)
		Num = 0;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\System\\	 failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("DisableRegistryTools"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System DisableRegistryTools failed!"));
			break;
		}
	} while (0);
	// ����ͷ���Դ
	if (pReg)
		delete pReg; 
	return bRet;
}

// ��ʾ�ļ���׺��
BOOL BanCommand::SetFileExtShow(BOOL bShow)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	DWORD dwCret = 0;
	DWORD Num = 0;
	if (!bShow)
		Num = 1;
	CRegistry2* pReg = NULL;
	CString sKeyPath = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced");
	CString sWinUser;
	int nID = 0;
	do 
	{
		// �����ǰ�û���ϵͳ����Ա,����Щ������Ϣд����ǰ��¼���û���
		CSecurityTool::GetCurrProcessUser(sWinUser);
		if(sWinUser.CompareNoCase(_T("system")) == 0)
		{
			CString sSID;
			CSecurityTool::GetCurUserSID(sSID);
			if (sSID.IsEmpty())
			{
				bRet = 0;
				break;
			}
			pReg = new CRegistry2(3,0);
			nID = 3;
			sKeyPath.Format(_T("%s\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),sSID);
		}
		else
			pReg = new CRegistry2(0,0);
		// �������ʧ�ܣ�ֱ�ӷ���
		if (!pReg)
		{
			theLog.Write(_T("new CRegistry2 failed"));
			bRet = 0;
			break;
		}
		// ��ע������
		bRet = pReg->Open(sKeyPath);
		if (!bRet)
		{
			// �����ע�����ʧ�ܣ��򴴽�֮
			bRet = pReg->CreateKey(sKeyPath,nID);
			if (!bRet)
			{
				theLog.Write(_T("CreateKey HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced	 failed!"));
				break;
			}
		}
		// ������д�뵽ע���
		bRet = pReg->Write(_T("HideFileExt"),Num);
		if (!bRet)
		{
			theLog.Write(_T("Write HKEY_CURRENT_USER Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced DisableRegistryTools failed!"));
			break;
		}
	} while (0);

	// ����ͷ���Դ
	if (pReg)
		delete pReg; 
	return bRet;
}
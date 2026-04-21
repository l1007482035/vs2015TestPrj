#pragma once

// 密码加密与验证

#include "AES.h"
class  CPWDCry
{
public:
	CPWDCry(void);
	~CPWDCry(void);
public:
	char*		CryptPWD(char* strPwd);
	int		UnCryptPWD(char* strSec,char* szPwd,int& nSize);
	char*		CryptPWD(int nID, char* strPwd);

	int		CheckPWD(char* strPwd, char* strCry);
	int		CheckPWD(int nID, char* strPwd, char* strCry);
private:
	char*		Crypt(char* szData, int nLength, int nID = -1);

	int		PutData(char* szData, int nSize, unsigned char* pInfo, unsigned char* pPos, int nInfoLen);
	int		GetData(char* szData, int nSize, unsigned char* pInfo, unsigned char* pPos, int nInfoLen);
	void		Data2String(char* szData, int nLength, char* str);
	char*		String2Data(char* szData, int& nLength);
};

//以后采用这个加密算法
class  CPWDCryEx
{
public:
	CPWDCryEx(void);
	~CPWDCryEx(void);
public:
	std::string		CryptPWD(std::string strPwd);
	std::string		UnCryptPWD(std::string strPwd);
	bool			CheckPWD(std::string strPwd, std::string strCryPwd);
private:
	AES				*m_pAes = nullptr; //用堆变量，成员变量会奔溃
};

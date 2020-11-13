#pragma once
#include <iostream>
using namespace std;

class CHookApi
{
public:
	CHookApi(void);
	~CHookApi(void);

	void Hook(std::string sModule,std::string sFunc,void *pNewFuncAddr);
	void UnHook();

	void ReHook();

protected:
	char m_szOldAPI[12];
	char m_szNewAPI[12];

	void *m_pOldFuncAddr;
	void *m_pNewFuncAddr;
};

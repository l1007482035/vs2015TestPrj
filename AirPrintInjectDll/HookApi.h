#pragma once
#include <iostream>
using namespace std;

class CHookApi
{
public:
	CHookApi(void);
	~CHookApi(void);



	void Hook(std::string sModule, std::string sFunc, void *pMyFuncAddr);
	void UnHook();

	void ReHook();

protected:
	void* ReWriteFunc(void* pNewAddr);
protected:

	void *m_pMyFuncAddr;
	void *m_pOriFuncAddr;
	std::string m_sModuleName;
	std::string m_sFunName;
};

#pragma once
#include <iostream>
using namespace std;

class CHookApi
{
public:
	CHookApi(void);
	~CHookApi(void);



	void Hook(std::string sModule, std::string sFunc, void *pNewFuncAddr);
	void UnHook();

	void ReHook();

protected:

	void* ReWriteFunc(void* pNewAddr);
protected:

	void *m_pOldFuncAddr;
	void *m_pNewFuncAddr;
	std::string m_sModuleName;
	std::string m_sFunName;
};

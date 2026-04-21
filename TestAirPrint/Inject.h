#pragma once
#include <list>

class CInject
{
public:
	CInject(void);
	~CInject(void);


	void ImprovePermission();
	void GetPidByPrcoName(std::list<DWORD>& pidlist,char *pProcessName);

	bool InjectDll(DWORD dwTargetPid,std::string sDllPath);
	bool UnInjectDll(DWORD dwTargetPid,std::string sDllPath);
};

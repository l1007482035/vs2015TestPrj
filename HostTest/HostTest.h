#pragma once

#include "resource.h"
class CService;
class CSvcHost : public CService
{
public:
	CSvcHost(TCHAR* szName);
	~CSvcHost(void);
public:
	void OnStart();
	void OnStop();
	void OnShutdown();

	virtual BOOL OnServiceInstalled(SC_HANDLE svc);
	virtual BOOL OnServiceUninstalled(SC_HANDLE svc);
	void Initial();



protected:

};

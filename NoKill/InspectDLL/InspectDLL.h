#pragma once
#ifndef ASSERT
#include <crtdbg.h>
#define ASSERT(X) _ASSERT(X);
#endif
class Hook64
{
public:
	Hook64(void);
	~Hook64(void);
	PVOID pOldAPI;
	char  szOldAPI[12];
	char  szNewAPI[12];
	void UnHook();
	void ReHook();
	bool HookAPI(char const * ModuleName, char const * ApiName, PVOID NewAPI);
};


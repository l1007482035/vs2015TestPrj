#include "stdafx.h"
#include "Hello.h"
#include "../CmmLib/SpdLog.h"
#pragma comment(lib,"../Release/CmmLib.lib")
CSpdLog theLog;


CHello::CHello()
{
	printf("CHello::CHello,thelog addr=%x\n",&theLog);
}


CHello::~CHello()
{
}

void CHello::Func()
{
	CSpdLog one = CSpdLog::GetInstance();
	printf("CHello::Func,one=%x\n",&one);
}

#include "stdafx.h"
#include "SpdLog.h"


CSpdLog::CSpdLog()
{
}


CSpdLog::~CSpdLog()
{
}

CSpdLog& CSpdLog::GetInstance()
{
	static CSpdLog one;
	return one;
}

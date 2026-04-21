#pragma once

class __declspec(dllexport) CSpdLog
{
public:
	CSpdLog();
	~CSpdLog();
	static CSpdLog& GetInstance();
};

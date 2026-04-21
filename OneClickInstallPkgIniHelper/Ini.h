#pragma once
#include <string>
class CIni
{
public:
	CIni();
	~CIni();
protected:
	std::string trim(const std::string& str);
public:

	std::string GetVal(std::string sSection, std::string sKey, std::string sDefault);
	int GetVal(std::string sSection, std::string sKey, int nDefault);
	void SetVal(std::string sSection, std::string sKey, std::string sVal);
	void SetVal(std::string sSection, std::string sKey, int nVal);
public:
	std::string m_sPath;
};


#include "stdafx.h"
#include "Ini.h"

#include <fstream>
#include <string>
#include <map>
#include <sstream>


CIni::CIni(void)
	: m_sPath("")
{
}

CIni::~CIni(void)
{
}


std::string CIni::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t");
	if (first == std::string::npos) return "";
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, last - first + 1);
}



std::string CIni::GetVal(std::string sSection, std::string sKey, std::string sDefault)
{
	std::ifstream file(m_sPath);
	if (!file.is_open()) return sDefault;

	std::string line, current_section;
	while (std::getline(file, line)) 
	{
		line = trim(line);
		//printf("===line=%s\n", line.c_str());
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			current_section = line.substr(1, line.size() - 2);
			continue;
		}

		size_t pos = line.find('=');
		if (pos == std::string::npos) continue;

		std::string file_key = trim(line.substr(0, pos));
		std::string value = trim(line.substr(pos + 1));
		if (current_section == sSection && file_key == sKey) 
		{
			return value.c_str();
		}
	}
	return sDefault;
}

int CIni::GetVal(std::string sSection, std::string sKey, int nDefault)
{
	std::ifstream file(m_sPath);
	if (!file.is_open()) return nDefault;

	std::string line, current_section;
	while (std::getline(file, line)) 
	{
		line = trim(line);
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			current_section = line.substr(1, line.size() - 2);
			continue;
		}

		size_t pos = line.find('=');
		if (pos == std::string::npos) continue;

		std::string file_key = trim(line.substr(0, pos));
		std::string value = trim(line.substr(pos + 1));
		try
		{
			if (current_section == sSection && file_key == sKey) 
			{
				return std::stoi(value);
			}
		}
		catch (...)
		{
			return nDefault;
		}


	}
	return nDefault;
}

void CIni::SetVal(std::string sSection, std::string sKey, std::string sVal)
{
	std::map<std::string, std::map<std::string, std::string>> data;
	std::ifstream infile(m_sPath);
	std::string line, current_section;
	while (std::getline(infile, line)) {
		line = trim(line);
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			current_section = line.substr(1, line.size() - 2);
			data[current_section] = {};
		}
		else {
			size_t pos = line.find('=');
			if (pos != std::string::npos && !current_section.empty()) {
				std::string file_key = trim(line.substr(0, pos));
				std::string file_value = trim(line.substr(pos + 1));
				data[current_section][file_key] = file_value;
			}
		}
	}
	infile.close();
	data[sSection][sKey] = sVal;

	std::ofstream outfile(m_sPath);

	for (const auto& sec : data) {
		outfile << "[" << sec.first << "]\n";
		for (const auto& pair : sec.second) {
			outfile << pair.first << "=" << pair.second << "\n";
		}
		outfile << "\n";
	}
}

void CIni::SetVal(std::string sSection, std::string sKey, int nVal)
{
	std::map<std::string, std::map<std::string, std::string>> data;
	std::ifstream infile(m_sPath);

	std::string line, current_section;
	while (std::getline(infile, line)) {
		line = trim(line);
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			current_section = line.substr(1, line.size() - 2);
			data[current_section] = {};
		}
		else {
			size_t pos = line.find('=');
			if (pos != std::string::npos && !current_section.empty()) {
				std::string file_key = trim(line.substr(0, pos));
				std::string file_value = trim(line.substr(pos + 1));
				data[current_section][file_key] = file_value;
			}
		}
	}
	infile.close();

	data[sSection][sKey] = nVal;

	std::ofstream outfile(m_sPath);
	for (const auto& sec : data) {
		outfile << "[" << sec.first << "]\n";
		for (const auto& pair : sec.second) {
			outfile << pair.first << "=" << pair.second << "\n";
		}
		outfile << "\n";
	}
}

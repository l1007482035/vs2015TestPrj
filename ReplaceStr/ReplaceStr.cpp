// ReplaceStr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void replace_str(string& str, const string to_replaced, const string newchars)
{
	for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
}

void PrintUsage()
{
	printf("param[1]:{-s}slash/{-bs}backslash\n");
	printf("param[2]:dest file\n");
	printf("param[3]:replace str\n");
	printf("param[4]:dest str\n");
}

bool JudgeParam(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("JudgeParam,argv[%d]=%s\n", i, argv[i]);
	}
	if (argc != 5)
	{
		printf("!!JudgeParam,1,argc=%d\n", argc);
		return false;
	}
	if (strncmp(argv[1],"-s",strlen(argv[1])) != 0 && strncmp(argv[1], "-bs", strlen(argv[1])) != 0)
	{
		printf("!!JudgeParam,2,argv[1]=%s\n", argv[1]);
		return false;
	}
	return true;
}


int main(int argc, char* argv[])
{
	if (!JudgeParam(argc, argv))
	{
		PrintUsage();
		return 0;
	}
	// 	for (int i = 0; i < argc; i++)
	// 	{
	// 		printf("argv[%d]=%s\n", argc, argv[i]);
	// 	}
	char *pSeparator = argv[1];//要替换的文件
	char *pDstFile = argv[2];//要替换的文件
	char *pSrctField = argv[3];//被替换的字段
	char *pDstField = argv[4];//替换后的字段

	string sSeparator = pSeparator;
	string sDstField = pDstField;
	if (sSeparator.compare("-s") == 0)
	{
		std::replace(sDstField.begin(), sDstField.end(), '\\', '/');
	}
	else if (sSeparator.compare("-bs") == 0)
	{
		std::replace(sDstField.begin(), sDstField.end(), '/', '\\');
	}

	printf("pDstFile=%s,pSrctField=%s,sDstField=%s\n", pDstFile, pSrctField, sDstField.c_str());

	string sDestFile = pDstFile;
	std::replace(sDestFile.begin(), sDestFile.end(), '\\', '/');

	std::string sRead;
	std::ifstream infile(sDestFile);
	if (!infile)
	{
		printf("!!infile file");
		return 0;
	}
	string sFinal = "";
	while (getline(infile, sRead, '\n'))
	{
		sRead += "\n";
		replace_str(sRead, pSrctField, sDstField.c_str());
		printf("sRead=%s\n", sRead.c_str());
		sFinal += sRead;
	}

	infile.close();

	std::ofstream outfile(sDestFile, std::ios_base::out);
	outfile << sFinal;
	outfile.close();

	return 0;
}

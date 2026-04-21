// MantunAuthTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Public/EncryptPort.h"
#include <windows.h>
#include <chrono>
#include <iostream>

using namespace std;


int main(int argc,int** argv)
{
	int nDays = 0;
	if (argc != 2)
	{
		printf("请输入授权天数:");
		scanf("%d", &nDays);
	}

	// 获取当前时间点
	auto now = std::chrono::system_clock::now();
	int64_t now_s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
	now_s += nDays * 24 * 60 * 60;

	string sScret = "MantunAuth_" + to_string(now_s);
	CPWDCryEx cry;
	sScret = cry.CryptPWD(sScret);
	printf("密钥：\n%s\n",sScret.c_str());
    return 0;
}


// TestZuhe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestZuhe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/assign.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;

size_t test2(int n, int m, boost::function<void(std::vector<int>& vec)> fn)
{
	vector<int> p, set;
	p.insert(p.end(), m, 1);
	p.insert(p.end(), n - m, 0);
	for (int i = 0; i != p.size(); ++i)
		set.push_back(i + 1);
	vector<int> vec;
	size_t cnt = 0;
	do {
		for (int i = 0; i != p.size(); ++i)
			if (p[i])
				vec.push_back(set[i]);
		fn(vec);
		cnt++;
		vec.clear();
	} while (prev_permutation(p.begin(), p.end()));
	return cnt;
}


int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。
        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}

// CallPython.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CallPython.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
#include <Python.h>

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
			DWORD t1 = GetTickCount();
			Py_Initialize();
			if (!Py_IsInitialized())
			{
				printf("!Py_IsInitialized,fail\n");
				return 0;
			}

			PyObject * pModule = NULL;//声明变量
			PyObject * pFunc1 = NULL;// 声明变量
			PyObject * pFunc2 = NULL;// 声明变量
			PyObject* sysPath = NULL;//指定python脚本路径

            // TODO: 在此处为应用程序的行为编写代码。
			do 
			{
				
				//运行简单的pythpn语句
				//PyRun_SimpleString:执行字符串命令
				PyRun_SimpleString("print('I am Python!')");

				//执行python脚本
				const char *pName = "./forCPlus.py";
				FILE* fp = fopen(pName, "r");
				PyRun_AnyFile(fp, pName);

				//调用python函数
				sysPath = PySys_GetObject("path");
				if (!sysPath)
				{
					printf("!!PySys_GetObject\n");
					PyErr_Print();
					break;
				}
				//====当前路径则不需要
				PyList_Append(sysPath, PyUnicode_FromString("./"));
				//====
				pModule = PyImport_ImportModule("forCPlus");//这里是要调用的文件名
				if (!pModule)
				{
					printf("!!PyImport_ImportModule\n");
					PyErr_Print();
					break;
				}
				pFunc1 = PyObject_GetAttrString(pModule, "myadd");//这里是要调用的函数名
				if (!pFunc1)
				{
					printf("!!PyObject_GetAttrString\n");
					PyErr_Print();
					break;
				}

				pFunc2 = PyObject_GetAttrString(pModule, "testfunc");//这里是要调用的函数名
				if (!pFunc2)
				{
					printf("!!PyObject_GetAttrString\n");
					PyErr_Print();
					break;
				}
				// 创建参数：两个整数 5 和 10
				PyObject* pArgs = PyTuple_Pack(2, PyLong_FromLong(5), PyLong_FromLong(10));

				DWORD t2 = GetTickCount();
				printf("===========span1=%d\n",t2-t1);
				PyObject* pValue = PyObject_CallObject(pFunc1, pArgs);
				if (pValue != nullptr)
				{
					long result = PyLong_AsLong(pValue);
					std::cout << "Result of Python function: " << result << std::endl;
					Py_DECREF(pValue);  // 释放 pValue
				}
				DWORD t3 = GetTickCount();
				printf("===========span2=%d\n", t3 - t2);

				// 创建参数:字符串
				PyObject* pArgs2 = PyTuple_Pack(1, PyUnicode_FromString("hello world"));

// 				PyObject* pValue2 = PyObject_CallObject(pFunc2, pArgs2);
// 				
// 				if (pValue2 != nullptr)
// 				{
// 					const char* result = PyUnicode_AsUTF8(pValue2);
// 					std::cout << "Result of Python function: " << result << std::endl;
// 					Py_DECREF(pValue);  // 释放 pValue
// 				}
				
				
			} while (0);

			if (sysPath)
			{
				Py_DECREF(sysPath);
			}

			if (pModule)
			{
				Py_DECREF(pModule);
			}
			if (pFunc1)
			{
				Py_DECREF(pFunc1);
			}
			if (pFunc2)
			{
				Py_DECREF(pFunc2);
			}

			// 3. 清理Python解释器
			Py_Finalize();

		



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

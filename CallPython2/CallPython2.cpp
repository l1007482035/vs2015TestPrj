// CallPython2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CallPython2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#include <pybind11/embed.h>  // pybind11 嵌入头文件
//#include <pybind11/stl.h>    // 支持 STL 容器
namespace py = pybind11;
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
			py::scoped_interpreter guard{}; // 启动 Python 解释器
								
			py::exec(R"(print("hello world"))"); //// 执行简单的 Python 代码,R意味着后面跟的是原始字符串字面常量

			//执行脚本中的函数
			try
			{

				//====当前路径则不需要
				py::module sys = py::module::import("sys");
				sys.attr("path").attr("append")("./");  // 替换为你的脚本路径
				py::module example = pybind11::module::import("forCPlus");
		
			
				//bool bRet = example.attr("testfunc").is_none();
				py::object result = example.attr("testfunc")("hello pybind11");  // 调用 greet("World")	
				std::cout << result.cast<std::string>() << std::endl;  // 输出: Hello, World!													   // 调用 add 函数
				py::object sum_result = example.attr("myadd")(3, 5);  // 调用 add(3, 5)
				std::cout << "Sum: " << sum_result.cast<int>() << std::endl;  // 输出: Sum: 8

			}
			catch (const std::exception &e) {
				// 捕获所有标准异常
				std::cerr << "An error occurred: " << e.what() << std::endl;
				return 1;  // 返回非零值表示错误
			}
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

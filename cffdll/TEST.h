#pragma once
#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)  // 导出宏（DLL内部定义）
#else
#define MYDLL_API __declspec(dllimport)  // 导入宏（外部程序使用）
#endif

// 仅导出普通函数（使用 extern "C" 防止 C++ 名称修饰）
extern "C" {
	MYDLL_API int Add(int a, int b);
}

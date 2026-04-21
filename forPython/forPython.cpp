// forPython.cpp : 定义控制台应用程序的入口点。
//


#include <pybind11/pybind11.h>

namespace py = pybind11;

// 一个简单的 C++ 函数
int add(int a, int b) {
	return a + b;
}

// 定义 Python 模块
PYBIND11_MODULE(forpython, m) {
	m.def("add", &myadd, "A function that adds two numbers");//"add"是c++函数名，myadd是python中使用的函数名
}

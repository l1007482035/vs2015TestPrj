#include "stdafx.h"
#include "TEST.h"
#include <string>


// 实现导出函数
extern "C" {
	MYDLL_API int Add(int a, int b) {
		return a + b;
		theLog.Write(_T("Add called"));
	}
}

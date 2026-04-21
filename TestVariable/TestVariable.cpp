// TestVariable.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdarg.h>

void IntegerVarArgFunc(int i, ...) 
{
	va_list pArgs = NULL;
	va_start(pArgs, i);
	int j = va_arg(pArgs, int);
	va_end(pArgs);
	printf("i=%d, j=%d\n", i, j);
}

int main()
{
	//IntegerVarArgFunc(10);
	//IntegerVarArgFunc(10);
	char * pTest = "abcd";

	printf("a=%c,b=%c\n", *pTest, *(pTest + 1));

    return 0;
}


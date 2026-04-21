// TestUnicode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestUnicode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;



#include <afx.h> // 包含 MFC 类定义
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 将16进制字符串转换为整数
int hexToInt(const char* hex) {
	return (int)strtol(hex, NULL, 16);
}

// 解析 \u 开头的 Unicode 转义序列，并返回解析后的 CStringW
CStringW parseUnicodeEscape(const char* input) {
	CStringW output;
	const char* p = input;
	while (*p) {
		if (*p == '\\' && *(p + 1) == 'u') {
			// 提取四位的16进制数字
			char codePoint[5] = { 0 };
			// 使用 _TRUNCATE 确保不会溢出
			strncpy_s(codePoint, _countof(codePoint), p + 2, 4);
			// 将其转换为宽字符并添加到输出
			output += (wchar_t)hexToInt(codePoint);
			// 移动指针到下一个字符
			p += 6;
		}
		else {
			// 对于非转义字符，直接复制
			output += *p++;
		}
	}
	return output; // 按值返回 CStringW
}

int main() {
	// 设置本地化环境，确保正确处理多字节字符
	setlocale(LC_ALL, "");

	const char* unicodeString = "\\u7f51\\u5173SN\\u53f7\\u4e0d\\u80fd\\u4e3a\\u7a7a";

	// 解析字符串中的 Unicode 转义序列并接收返回的 CStringW
	CStringW wideString = parseUnicodeEscape(unicodeString);

	// 打印宽字符字符串
	wprintf(L"%ls\n", wideString.GetString());

	// 如果需要转换回多字节字符串，可以使用 CT2A 或 WideCharToMultiByte 函数
	CT2A multiByteString(wideString); // 自动进行宽字符到多字节字符的转换
	printf("%s\n", multiByteString.m_psz);

	return 0;
}
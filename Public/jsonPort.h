#pragma once

//json��ı������Ҫ����CloudPrintRouterDemo��һ�¡���/MD���͡��ڹ���DLL��ʹ��MFC��

#include "../Public/jsoncpp-1.8.4/include/json/json.h"

#ifdef _DEBUG
#pragma comment(lib,"../Public/jsoncpp-1.8.4/lib/debug/lib_json.lib")
#else
#pragma comment(lib,"../Public/jsoncpp-1.8.4/lib/release/lib_json.lib")
#endif

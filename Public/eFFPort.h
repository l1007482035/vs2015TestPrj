#pragma once

//eCC.dll���ӡ��Ʒ��������ļ��г�ͻ������һ��eFF.dll�ļ��ܿ��ļ���������eCC.dllһ�¡�

#include "../public/eFFHeader.h"
#ifdef _DEBUG
#pragma comment(lib,"../public/lib/debug/eFF.lib")
#else
#pragma comment(lib,"../public/lib/release/eFF.lib")
#endif

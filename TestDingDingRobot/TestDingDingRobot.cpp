// TestDingDingRobot.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../CurlWrapLib/MailSender.h"
#include "../CurlWrapLib/HttpClient.h"
#include "../CurlWrapLib/FtpClient.h"

#pragma comment(lib, "../CurlWrapLib/libcurl/lib/I386/LIBCURL.LIB")

#ifdef _DEBUG
#pragma comment(lib, "../CurlWrapLib/mimetic-0.9.8/win32/libmimetic_d.lib")
#pragma comment(lib,"../Debug/CurlWrapLib.lib")
#else
#pragma comment(lib, "../CurlWrapLib/mimetic-0.9.8/win32/libmimetic.lib")
#pragma comment(lib,"../Release/CurlWrapLib.lib")

#endif

/*
curl 'https://oapi.dingtalk.com/robot/send?access_token=xxxxxxxx' \
-H 'Content-Type: application/json' \
-d '{"msgtype": "text","text": {"content":"我就是我, 是不一样的烟火"}}'

*/

int main()
{
	CHttpClient http;
	string sUrl = "https://oapi.dingtalk.com/robot/send?access_token=https://oapi.dingtalk.com/robot/send?access_token=c58dab17144e3061d47432e1946b38dee49a02953bf4de8de28f17a05d4f4f6e";
	string sRequ = "{\"msgtype\": \"text\",\"text\": {\"content\":\"我就是我, 是不一样的烟火\"}}";
	string sResponse;

	http.Posts(sUrl,sRequ, sResponse);
	printf("===sResponse=%s\n", sResponse.c_str());
    return 0;
}


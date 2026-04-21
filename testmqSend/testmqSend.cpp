// testmqSend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "testmqSend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>
CStringA MultiByteToUTF8(const char* puszSource)
{
	CStringA szRetA = "";
	if (puszSource)
	{
		int len = MultiByteToWideChar(936, 0, (LPCSTR)puszSource, -1, NULL, 0);
		wchar_t* wszText = new wchar_t[len + 1];
		memset(wszText, 0, len * 2 + 2);
		MultiByteToWideChar(936, 0, (LPCSTR)puszSource, -1, wszText, len);

		len = WideCharToMultiByte(CP_UTF8, 0, wszText, -1, NULL, 0, NULL, NULL);
		char *szText = new char[len + 1];
		memset(szText, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wszText, -1, szText, len, NULL, NULL);

		szRetA = szText;
		delete[] wszText;
		delete[] szText;
	}
	return szRetA;
}
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

			try
			{
				// 连接到 RabbitMQ 服务器
				printf("============1\n");
				auto channel = AmqpClient::Channel::Create("111.229.72.140", 5672, "printer", "printer!@#", "/");
				//auto channel = AmqpClient::Channel::Create("192.168.5.130", 5672, "printer", "printer!@#", "/");


				// 定义交换机、队列和路由键
				std::string exchangeName = "direct.gateway";
				std::string routingKey = "routing.gateway.3";
				printf("============2\n");
				// 声明 direct 交换机
				channel->DeclareExchange(exchangeName, AmqpClient::Channel::EXCHANGE_TYPE_DIRECT);
				printf("============3\n");

				// 发送消息
				std::string message = "{\"cmd\": 1,\"time\": 1737440999360,\"data\": {\"gatewayId\": 3,\"gatewayCode\": \"A1B2C3\",\"orgId\": 2,\"orgName\": \"安思易\"}}";

				std::string sSend = MultiByteToUTF8(message.c_str()).GetString();

				channel->BasicPublish(exchangeName, routingKey, AmqpClient::BasicMessage::Create(sSend));

				std::cout << "Sent: " << message << std::endl;

		

			}

			// 			catch (const AmqpClient::AmqpException& e)
			// 			{
			// 				printf("===============1,what=%s\n", e.what());
			// 			}
			catch (std::exception& e)
			{
				printf("===============2,what=%s\n", e.what());
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
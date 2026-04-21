// testmq.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "testmq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>

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
				std::cout << "SimpleAmqpClient Version: "
					<< SIMPLEAMQPCLIENT_VERSION_MAJOR << "."
					<< SIMPLEAMQPCLIENT_VERSION_MINOR << "."
					<< SIMPLEAMQPCLIENT_VERSION_PATCH << std::endl;

				// 连接到 RabbitMQ 服务器
				printf("============1\n");
				auto channel = AmqpClient::Channel::Create("111.229.72.140", 5672, "printer", "printer!@#", "/");
				//auto channel = AmqpClient::Channel::Create("192.168.5.130", 5672, "printer", "printer!@#", "/");
				
				// 定义交换机、队列和路由键
				std::string exchangeName = "direct.gateway";
				std::string routingKey = "routing.gateway.123";
				printf("============2\n");
				// 声明 direct 交换机
				channel->DeclareExchange(exchangeName, AmqpClient::Channel::EXCHANGE_TYPE_DIRECT);
				printf("============3\n");

				std::string queueName = channel->DeclareQueue("queuenametest", false, true, false, false);
				printf("============4\n");

				// 将队列绑定到交换机，使用指定的路由键
				channel->BindQueue(queueName, exchangeName, routingKey);
				printf("============5\n");

				std::string sConsumer = channel->BasicConsume(queueName, "", true, false, false, true);

				printf("============6,exchangeName=%s,routingKey=%s,queueName=%s,sConsumer=%s\n"
					, exchangeName.c_str(), routingKey.c_str(),queueName.c_str(), sConsumer.c_str());
#if 1
				while (true)
				{
					// 消费消息
					AmqpClient::Envelope::ptr_t delivered;//接收的消息体
					while (channel->BasicConsumeMessage(sConsumer, delivered, 500)) //非阻塞
					{
						string strMsg = delivered->Message()->Body();
						channel->BasicAck(delivered);
						printf("message=%s\n", strMsg.c_str());
					}
				}
#else


				while (true)
				{
					AmqpClient::Envelope::ptr_t envelope = channel->BasicConsumeMessage(sConsumer);//阻塞
					channel->BasicAck(envelope);
					std::cout << "Received: " << envelope->Message()->Body() << std::endl;
				}
#endif
				
			}
			
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

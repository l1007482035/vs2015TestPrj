// webserver.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include "HttpServer.h"
#pragma comment(lib, "ws2_32.lib")

CHttpServer webServer;

void handleRequestBody(const char* pBodyData, int nBodyLen)
{
	printf("------handleRequestBody----\n");
	char buff[65535] = { 0 };
	memcpy(buff, pBodyData, min(nBodyLen, 65535));
	printf_s("%s\n", buff);
}

void send2client(SOCKET socketValue, const char* pResponseBuf, int nSendLen)
{
	printf("send\n【%s】\n", pResponseBuf);
	int nSendedLen = 0;
	while(nSendLen > 0)
	{
		nSendedLen = send(socketValue, pResponseBuf, nSendLen, 0);
		if(nSendedLen > 0)
		{
			pResponseBuf += nSendedLen;
			nSendLen -= nSendedLen;
		}
		else if(errno == EWOULDBLOCK)
		{
			continue;
		}
		else
		{
			closesocket(socketValue);
			break;
		}
	}
}

/* Using "Fiddler app" simulation tests */
unsigned int __stdcall handleData(void *pData)
{
	SOCKET socketValue = (SOCKET)pData;
	//the buff is just for test.
	char buff[1024 * 60] = { 0 };
	int nSumBytes = 0;
	int nNowBytes = 0;
	struct tagHttpResponseData httpResponseData;
	webServer.SetHttpRequestBodyCallBack(handleRequestBody);
	while (1)
	{
		nNowBytes = recv(socketValue, buff + nSumBytes, sizeof(buff) - nSumBytes, 0);
		if (nNowBytes > 0)
		{
			int nOldSumBytes = nSumBytes;
			nSumBytes += nNowBytes;
			if (nSumBytes > sizeof(buff) - 1)
			{
				printf("buff full.\n");
				closesocket(socketValue);
				break;
			}
			buff[nSumBytes] = 0;
			printf("-----recv\n【%s】\n", &buff[nOldSumBytes]);
			int nStatusCode = webServer.HttpParser(buff, nNowBytes);
			if (W_HTTP_PARSER_AGAIN == nStatusCode)
			{
				printf("-----again recv data\n");
				continue;
			}
			else 
			{
				nSumBytes = 0;
				bool bIsKeepAlive = false;
				int nResponseResult = webServer.HttpResponseHeader(nStatusCode, &httpResponseData);
				if (nResponseResult == W_HTTP_RESPONSE_OK)
				{
					//send header
					bIsKeepAlive = httpResponseData.u.bIsKeepAlive;
					printf("=====send head\n");
					send2client(socketValue, httpResponseData.pBuff, httpResponseData.nBuffLen);

					//send body
					nResponseResult = webServer.HttpResponseBody(&httpResponseData);
					if (W_HTTP_RESPONSE_OK == nResponseResult)
					{
						printf("=====send body\n");
						send2client(socketValue, httpResponseData.pBuff, httpResponseData.nBuffLen);
						webServer.HttpResponseBodyOver();
					}
				}

				if (!bIsKeepAlive || nStatusCode != W_HTTP_OK)
				{
					closesocket(socketValue);
					break;
				}
			}
		} 
		else if (SOCKET_ERROR == nNowBytes)
		{
			printf("recv error:%d,fd:%d,bytes=%d\n", WSAGetLastError(), socketValue, nNowBytes);
			Sleep(1000);
		}
		else
		{
			printf("close...");
			closesocket(socketValue);
			break;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
//char buff[20];
//#define ttest(buf, fmt, ...) _snprintf_s(buf, 20, fmt, __VA_ARGS__)
//ttest("x=%d\n",100);
//printf(buff);
//return 0;

//	char *test = "GET /?aldtype=85&keyfrom=alading HTTP/1.1\
//Host: 127.0.0.1:9999\
//Connection: keep-alive\
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/\*;q=0.8\
//Upgrade-Insecure-Requests: 1\
//User-Agent: Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko)Chrome/45.0.2454.101 Safari/537.36\
//Accept-Encoding: gzip, deflate, sdch\
//Accept-Language: zh-CN,zh;q=0.8\
//\
//";
//    int nLen = strlen(test);
//    webServer.HttpParser(test, nLen);
//	return 0;

	WSADATA wsaData;
	int error = 0;

	error = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (error == SOCKET_ERROR)
	{
		char errorBuffer[100];

		error = WSAGetLastError();
		if (error == WSAVERNOTSUPPORTED)
		{
			sprintf_s(errorBuffer, "Startup() - WSAStartup() error.\nRequested v2.0(highest v2.2), found only v%d.%d.",
				LOBYTE(wsaData.wVersion),
				HIBYTE(wsaData.wVersion));
			WSACleanup();
		}
		else
			sprintf_s(errorBuffer, "Startup() - WSAStartup() error %d", WSAGetLastError());

		printf(errorBuffer);
		return 0;
	}

	SOCKET socketValue = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (socketValue == INVALID_SOCKET)
	{
		printf("wsasocket error %d\n", errno);
		return 0;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9988);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	int nBind = ::bind(socketValue, (sockaddr*)&addr, sizeof(addr));
	if (nBind == INVALID_SOCKET)
	{
		::closesocket(socketValue);
		printf("bind error %s\n", errno);
		return 0;
	}

	int nListen = ::listen(socketValue, 200);
	if (SOCKET_ERROR == nListen)
	{
		::closesocket(socketValue);
		printf("listen error %s\n", errno);
		return 0;
	}

	sockaddr_in addrAccept;
	int addrLen = sizeof(addrAccept);

	printf("prepare accept...\n");
	while (1)
	{
		//使用google浏览器请求(输入"127.0.0.1:9999")发现accept调用了2次.因为可能:
		//server没有及时响应http请求，有些浏览器在pipeline被阻塞情况下会再次发起新连接
		SOCKET acceptRet = ::accept(socketValue, (sockaddr*)&addrAccept, &addrLen);

		if (acceptRet == INVALID_SOCKET)
		{
			printf("accept error %s\n", errno);
			continue;
		} 
		else
		{
			printf("connect from addr = %s, port = %d\n", inet_ntoa(addrAccept.sin_addr), addrAccept.sin_port);
			_beginthreadex(NULL, 0, handleData, (void*)acceptRet, 0, NULL);
		}
	}

	::closesocket(socketValue);
	WSACleanup();

	return 0;
}


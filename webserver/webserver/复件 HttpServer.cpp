#include "HttpServer.h"
#define ONEDATA_LEN  256
#define HEADER_LEN   64

//http = header + body
//header and body is cuted by "\r\n"
//each line of http header ending by "\r\n",
//so,header and body is cuted by "\r\n\r\n"


//GET /search?hl=zh-CN&source=hp&q=domety&aq=f&oq= HTTP/1.1 

//HTTP 请求消息头部实例(line:8-22):
//GET /a.html HTTP/1.1
//Host：rss.sina.com.cn
//User - Agent：Mozilla / 5、0(Windows; U; Windows NT 5、1; zh - CN; rv:1、8、1、14) Gecko / 20080404 Firefox / 2、0、0、14
//Accept：text / xml, application / xml, application / xhtml + xml, text / html; q = 0、9, text / plain; q = 0、8, image / png, */*;q=0、5
//Accept-Language：zh-cn,zh;q=0、5
//Accept-Encoding：gzip,deflate
//Accept-Charset：gb2312,utf-8;q=0、7,*;q=0、7
//Keep-Alive：300
//Connection：keep-alive
//Cookie：userId=C5bYpXrimdmsiQmsBPnE1Vn8ZQmdWSm3WRlEB3vRwTnRtW &lt;-- Cookie
//If-Modified-Since：Sun, 01 Jun 2008 12:05:30 GMT
//Cache-Control：max-age=0
//
//body
//


//HTTP 响应消息头部实例：
//Status：OK - 200 &lt;-- 响应状态码，表示 web 服务器处理的结果。
//Date：Sun, 01 Jun 2008 12:35:47 GMT
//Server：Apache/2、0、61 (Unix)
//Last-Modified：Sun, 01 Jun 2008 12:35:30 GMT
//Accept-Ranges：bytes
//Content-Length：18616
//Cache-Control：max-age=120
//Expires：Sun, 01 Jun 2008 12:37:47 GMT
//Content-Type：application/xml
//Age：2
//X-Cache：HIT from 236-41、D07071951、sina、com、cn &lt;-- 反向代理服务器使用的 HTTP 头部
//Via：1.0 236-41.D07071951.sina.com.cn:80 (squid/2.6.STABLE13)
//Connection：close


CHttpServer::CHttpServer()
{
	m_sHeaderStart = 0;
	m_sHeaderEnd = 0;

	m_szResponseBody = new char[HTTP_LIMIT_LENTH];
	InitErrorInfo();
}

CHttpServer::~CHttpServer()
{
	delete[]m_szResponseBody;
	m_mapErrorInfo.clear();
}

void CHttpServer::InitErrorInfo()
{
	m_mapErrorInfo.insert(std::pair<int, const char*>(WEB_UNKNOWN_ERROR, "未知错误"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(100, "100 Continue"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(101, "101 Switching Protocols"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(200, "200 OK"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(201, "201 Created"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(202, "202 Accepted"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(203, "203 Non-Authoritative Information"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(204, "204 No Content"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(205, "205 Reset Content"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(206, "206 Partial Content"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(300, "300 Multiple Choices"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(301, "301 Moved Permanently"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(302, "302 Found"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(303, "303 See Other"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(304, "304 Not Modified"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(305, "305 Use Proxy"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(307, "307 Temporary Redirect"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(400, "400 无法解析此请求"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(403, "403 访问被拒绝"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(404, "404 未找到"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(405, "405 用于访问该页的 HTTP 动作未被许可"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(406, "406 客户端浏览器不接受所请求页面的 MIME 类型"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(407, "407 Web 服务器需要初始的代理验证"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(410, "410 文件已删除"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(412, "412 客户端设置的前提条件在 Web 服务器上评估时失败"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(413, "413 Request Entity Too Large"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(414, "414 请求 URL 太大，因此在 Web 服务器上不接受该 URL"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(500, "500 服务器内部错误"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(501, "501 标题值指定的配置没有执行"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(502, "502 Web 服务器作为网关或代理服务器时收到无效的响应"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(503, "503 服务不可用"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(504, "504 网关超时"));
	m_mapErrorInfo.insert(std::pair<int, const char*>(505, "505 HTTP版本不受支持"));
}

int CHttpServer::GetHeader(const char* pSource, int nSourceLen, char *pDest, int nDestLen)
{

	return WEB_PARSER_SUCCESS;
}

int CHttpServer::GetOneData(const char* pSource, int nSourceLen, char *pDest, int nDestLen, char filter)
{
	char *pSourceOld = pSource;
	*pDest = 0;

	while (nSourceLen > 0 && nDestLen > 0)
	{
		char byteValue = *pSource;
		if (filter == byteValue || '\r' == byteValue || '\n' == byteValue)
		{
			while (nSourceLen > 0)
			{
				byteValue = *pSource;
				if (' ' == byteValue || '\t' == byteValue || '\r' == byteValue || '\n' == byteValue)
				{
					pSource++;
					nSourceLen--;
					continue;
				}
				else break;
			}

			*pDest = 0;
			break;
		}

		*pDest++ = *pSource++;
		nSourceLen--;
		nDestLen--;
	}

	return pSource - pSourceOld;
}

int CHttpServer::ParseHeader(const char* pSource, int nSourceLen, std::unordered_map<string, string/*, tagUnorderMapHash, tagMapCmp*/> &mapHeader)
{
	char header[HEADER_LEN];
	while (nSourceLen > 0 && *pSource != 0)
	{
		char bt = *pSource;
		if (' ' == bt || '\r' == bt || '\n' == bt || '\t' == bt)
		{
			pSource++;
			nSourceLen--;
			continue;
		}

		//get header
		int nHeaderLen = 0;
		header[0] = 0;
		while (*pSource != ':' && nSourceLen > 0 && *pSource != 0 && nHeaderLen < HEADER_LEN - 1)
		{
			header[nHeaderLen] = *pSource++;
			nSourceLen--;
			nHeaderLen++;
		}
		if (0 == header[0]) return 400;
		header[nHeaderLen] = 0;

		//get content
		int nContentLen = 0;
		m_szWebData[0] = 0;
		while ('\r' != *pSource && '\n' != *pSource && nSourceLen > 0 && nContentLen < HTTP_LIMIT_LENTH - 1)
		{
			m_szWebData[nContentLen] = *pSource++;
			nSourceLen--;
			nContentLen++;
		}
		if (0 == m_szWebData[0]) return 400;
		m_szWebData[nContentLen] = 0;
		mapHeader.insert(std::pair<string, string>(header, m_szWebData));
	}

	return WEB_PARSER_SUCCESS;
}

int CHttpServer::HttpGet(const char* pWebData, int nDataLen)
{
	//url
	int nLen = GetOneData(pWebData, nDataLen, m_szWebData, HTTP_LIMIT_LENTH, ' ');
	if (0 == m_szWebData[0]) return WEB_UNKNOWN_ERROR;
	nDataLen -= nLen;
	pWebData += nLen;

	//HTTP/1.1
	char szOneData[128];
	nLen = GetOneData(pWebData, nDataLen, szOneData, sizeof(szOneData), ' ');
	if (0 == szOneData[0]) return WEB_UNKNOWN_ERROR;
	nDataLen -= nLen;
	pWebData += nLen;

	//HTTP
	if (strstr(szOneData, "HTTP"))
	{
		char *pVersion = szOneData + strlen("HTTP") + 1;
		if (strcmp(pVersion, "1.0") != 0 && strcmp(pVersion, "1.1"))
			return 505;

		//std::unordered_map<char*, char*, tagUnorderMapHash, tagMapCmp> mapHeader;
		std::unordered_map<string, string> mapHeader;

		int nParse = ParseHeader(pWebData, nDataLen, mapHeader);
		if (nParse) return nParse;

		std::unordered_map<string, string>::iterator it = mapHeader.find("content-length");
		int nContentLen = 0;
		if (it != mapHeader.end())
			nContentLen = atoi(it->second.c_str());

		bool bIsChunked = false;
		it = mapHeader.find("transfer-encoding");
		if (it != mapHeader.end())
		{
			const char *pMode = it->second.c_str();
			if (strcmp(pMode, "chunked") == 0) bIsChunked = true;
			if (strcmp(pMode, "identity") != 0 && !bIsChunked)
				return 501;
		}

		if (bIsChunked)
		{
			char *pWebDataTmp = pWebData;
			int nDataLenTmp = nDataLen;
			m_szResponseBody[0] = 0;
			bool bIsOver = false;
			while (nDataLenTmp > 0)
			{
				char byteValue = *pWebDataTmp;
				if (0 == byteValue)
				{
					bIsOver = true;
					break;
				}
				if ('\r' != byteValue && '\n' != byteValue)
				{
					*m_szResponseBody++ = *pWebDataTmp++;
					nDataLenTmp--;
				}
			}
			if (!bIsOver) return WEB_RECV_AGAIN;
		}
		else
		{
			if (nContentLen > HTTP_LIMIT_LENTH) return 413;
		}
	}

	return WEB_PARSER_SUCCESS;
}

int CHttpServer::HttpPost(char* pWebData, int nDataLen)
{
	return WEB_PARSER_SUCCESS;
}

int CHttpServer::HttpParser(const char* pWebData, int* pDataLen)
{
	int nDataLenTmp = *pDataLen;
	int nLen = GetHeader(const char* pSource, int nSourceLen);

	//GET、POST...
	nLen = GetOneData(pWebData, nDataLenTmp, m_szWebData, HTTP_LIMIT_LENTH, ' ');
	nDataLenTmp -= nLen;

	if (0 == _stricmp(m_szWebData, "GET"))
	{
		return HttpGet(pWebData + nLen, nDataLenTmp);
	}
	else if (0 == _stricmp(m_szWebData, "POST"))
	{
		return HttpPost(pWebData + nLen, nDataLenTmp);
	}
	else
	{
		return W_HTTP_BAD_REQUEST;
	}

	return WEB_PARSER_SUCCESS;
}
#ifndef __WEBSERVER__H__
#define __WEBSERVER__H__
#include <unordered_map>
#include <string>
using namespace std;

#define WEB_PARSER_SUCCESS 0
#define WEB_UNKNOWN_ERROR  -1
#define WEB_RECV_AGAIN -2

struct tagUnorderMapHash
{
	size_t operator() (const char *str) const
	{
		std::hash<char*> hashStr;
		return hashStr((char*)str);
	}
};

struct tagMapCmp
{
	bool operator() (char const *a, char const *b) const
	{
		return std::strcmp(a, b) < 0;
	}
};

class CHttpServer
{
#define HTTP_HEADER_LIMIT  1024
#define HTTP_BODY_LIMIT    7168
#define HTTP_LIMIT_LENTH   8192

public:
	CHttpServer();
	~CHttpServer();
private:
	unsigned short m_sHeaderStart;
	unsigned short m_sHeaderEnd;

	char *m_szResponseBody;
	std::unordered_map<int, const char*> m_mapErrorInfo;
private:
	void  InitErrorInfo();
	int   GetHeader(const char* pSource, int nSourceLen);
	int   GetOneData(const char* pSource, int nSourceLen, char *pDest, int nDestLen, char filter);
	int   HttpGet(const char* pWebData, int nDataLen);
	int   HttpPost(const char* pWebData, int nDataLen);
	int   ParseHeader(const char* pSource, int nSourceLen, std::unordered_map<string, string/*, tagUnorderMapHash, tagMapCmp*/> &mapHeader);
public:
	int   HttpParser(const char* pWebData, int* pDataLen);
};

#endif
// mdnsTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <map>
using namespace std;

#include "dns_sd.h"
#include <time.h>
#include <sys/types.h>      // For u_char
#include <winsock2.h>

//*************************************************************************************************************
// Sample callback functions for each of the operation types

#define printtimestamp() printtimestamp_F(stdout)

static void printtimestamp_F(FILE *outstream)
{
	struct tm tm;
	int ms;
	static char date[16];
	static char new_date[16];
#ifdef _WIN32
	SYSTEMTIME sysTime;
	time_t uct = time(NULL);
	tm = *localtime(&uct);
	GetLocalTime(&sysTime);
	ms = sysTime.wMilliseconds;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	localtime_r((time_t*)&tv.tv_sec, &tm);
	ms = tv.tv_usec / 1000;
#endif
	strftime(new_date, sizeof(new_date), "%a %d %b %Y", &tm);
	if (strncmp(date, new_date, sizeof(new_date)))
	{
		fprintf(outstream, "DATE: ---%s---\n", new_date); //display date only if it has changed
		strncpy(date, new_date, sizeof(date));
	}
	fprintf(outstream, "%2d:%02d:%02d.%03d  ", tm.tm_hour, tm.tm_min, tm.tm_sec, ms);
}

// formating time to RFC 4034 format
static void FormatTime(unsigned long te, unsigned char *buf, int bufsize)
{
	struct tm tmTime;
#ifdef _WIN32
	__time32_t t = (__time32_t)te;
	_gmtime32_s(&tmTime, &t);
#else
	// Time since epoch : strftime takes "tm". Convert seconds to "tm" using
	// gmtime_r first and then use strftime
	time_t t = (time_t)te;
	gmtime_r(&t, &tmTime);
#endif
	strftime((char *)buf, bufsize, "%Y%m%d%H%M%S", &tmTime);
}



#if 0
typedef void (DNSSD_API *DNSServiceRegisterReply)
(
	DNSServiceRef sdRef,
	DNSServiceFlags flags,
	DNSServiceErrorType errorCode,
	const char                          *name,
	const char                          *regtype,
	const char                          *domain,
	void                                *context
	);
#endif


static void WINAPI reg_reply
(
	DNSServiceRef						sdRef,
	DNSServiceFlags						flags,
	DNSServiceErrorType					errorCode,
	const char                          *name,
	const char                          *regtype,
	const char                          *domain,
	void                                *context
)
{
	printf("===============进入回调函数Got a reply for service %s.%s%s: \n", name, regtype, domain);
	if (errorCode == kDNSServiceErr_NoError)
	{
		printf("Successfuly registered\n");
	}
	else
	{
		printf("Failed to register");
	}
}

#define LONG_TIME 100000000
static volatile int stopNow = 0;
static DNSServiceRef client = NULL;
static char bigNULL[8192];  // 8K is maximum rdata we support
static volatile int timeOut = LONG_TIME;

static void myTimerCallBack(void)
{
	printf("myTimerCallBack,1\n");
#if 0
	DNSServiceErrorType err = kDNSServiceErr_Unknown;

	printf("Adding big NULL record\n");
	err = DNSServiceAddRecord(client, &record, 0, kDNSServiceType_NULL, sizeof(bigNULL), &bigNULL[0], 0);
	if (err) printf("Failed: %d\n", err); else printf("Succeeded\n");
	timeOut = LONG_TIME;
	break;
	

	if (err != kDNSServiceErr_NoError)
	{
		fprintf(stderr, "DNSService add/update/remove failed %ld\n", (long int)err);
		stopNow = 1;
	}
#endif
}


static void HandleEvents(void)
{
	int dns_sd_fd = client ? DNSServiceRefSockFD(client) : -1;
	printf("HandleEvents,dns_sd_fd=%d\n", dns_sd_fd);
	int nfds = dns_sd_fd + 1;
	fd_set readfds;
	struct timeval tv;
	int result;


	while (!stopNow)
	{
		// 1. Set up the fd_set as usual here.
		// This example client has no file descriptors of its own,
		// but a real application would call FD_SET to add them to the set here
		FD_ZERO(&readfds);

		// 2. Add the fd for our client(s) to the fd_set
		if (client) FD_SET(dns_sd_fd, &readfds);
	
		// 3. Set up the timeout.
		tv.tv_sec = timeOut;
		tv.tv_usec = 0;

		result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
		if (result > 0)
		{
			DNSServiceErrorType err = kDNSServiceErr_NoError;
			if (client    && FD_ISSET(dns_sd_fd, &readfds)) err = DNSServiceProcessResult(client);
			if (err) { printtimestamp_F(stderr); fprintf(stderr, "DNSServiceProcessResult returned %d\n", err); stopNow = 1; }
		}
		else if (result == 0)
			myTimerCallBack();
		else
		{
			printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
			if (errno != EINTR) stopNow = 1;
		}
	}
}



int main()
{
	printf("mdnsTest main\n");
	typedef union { unsigned char b[2]; unsigned short NotAnInteger; } Opaque16;
	map<string, string> mapRecord;
	
	Opaque16 registerPort = { { 0x02, 0x77 } };
	DNSServiceErrorType err;
	
	uint16_t			txtLen = 0;
	void * DNSSD_API	pData = NULL;

	mapRecord.insert(make_pair("txtvers","1"));
	mapRecord.insert(make_pair("qtotal", "1"));
	mapRecord.insert(make_pair("rp", "printers/Pantum_M7100DW_Series_PCL6-12"));
	mapRecord.insert(make_pair("ty", "Pantum M7100DW Series PCL6"));
	mapRecord.insert(make_pair("adminurl", "http://WIN-5I4V32F5962:631/"));
	mapRecord.insert(make_pair("note", ""));
	mapRecord.insert(make_pair("priority", "0"));
	mapRecord.insert(make_pair("product", "Pantum M7100DW Series PCL6"));
	mapRecord.insert(make_pair("WINDOWS", "T"));
	mapRecord.insert(make_pair("Transparent", "T"));
	mapRecord.insert(make_pair("Binary", "T"));
	mapRecord.insert(make_pair("Color", "F"));
	mapRecord.insert(make_pair("Duplex", "T"));
	mapRecord.insert(make_pair("Staple", "F"));
	mapRecord.insert(make_pair("Copies", "T"));
	mapRecord.insert(make_pair("Collate", "F"));
	mapRecord.insert(make_pair("Punch", "F"));
	mapRecord.insert(make_pair("Bind", "F"));
	mapRecord.insert(make_pair("Sort", "F"));
	mapRecord.insert(make_pair("Scan", "F"));
	mapRecord.insert(make_pair("pdl", "application/pdf,image/jpeg,image/urf"));
	mapRecord.insert(make_pair("URF", "W8,DM1,CP255,RS600"));
	mapRecord.insert(make_pair("air", "username,password"));

	TXTRecordRef		txtRef;
	TXTRecordCreate(&txtRef, 0, NULL);
	map<string, string>::iterator it = mapRecord.begin();
	for (;it != mapRecord.end();it++)
	{
		string sKey = it->first;
		string sVal = it->second;
		TXTRecordSetValue(&txtRef, sKey.c_str(), sVal.length(), sVal.c_str());
		pData = (void *)TXTRecordGetBytesPtr(&txtRef);
		txtLen = TXTRecordGetLength(&txtRef);
	}
	pData = (void *)TXTRecordGetBytesPtr(&txtRef);
	txtLen = TXTRecordGetLength(&txtRef);
	printf("========注册前reg_reply=0x%x,client=0x%x\n", reg_reply, client);
#if 1
	err = DNSServiceCreateConnection(&client);
	if (err)
	{
		printf("!!DNSServiceCreateConnection returned %d\n", err);
	}
	printf("after DNSServiceCreateConnection,nSd=%d\n", DNSServiceRefSockFD(client));
	err = DNSServiceRegister(&client, kDNSServiceFlagsShareConnection, kDNSServiceInterfaceIndexAny, "Pantum M7100DW Series PCL6-12 @ WIN-5I4V32F5962",
	"_ipp._tcp,_universal", "local", NULL, registerPort.NotAnInteger,txtLen, pData, reg_reply, NULL);
#else
	err = DNSServiceRegister(&client, 0, kDNSServiceInterfaceIndexAny, "Pantum M7100DW Series PCL6-12 @ WIN-5I4V32F5962",
		"_ipp._tcp,_universal", "local", NULL, registerPort.NotAnInteger, txtLen, pData, reg_reply, NULL);
#endif


	int nSd = DNSServiceRefSockFD(client);
	printf("===========err=%d,nSd=%d\n", err,nSd);

	while (true)
	{

	}


	printf("...STARTING...\n");
	HandleEvents();

	// Be sure to deallocate the DNSServiceRef when you're finished
	if (client) DNSServiceRefDeallocate(client);
	TXTRecordDeallocate(&txtRef);
	while (true)
	{

	}
	printf("process end\n");

    return 0;
}


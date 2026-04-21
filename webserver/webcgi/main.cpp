#include <stdio.h>
#include <iostream>
using namespace std;
#define  MAXLINE  1024

int main()
{
	char *buf, *p;
	char name[MAXLINE], passwd[MAXLINE], content[MAXLINE];

	/* Extract the two arguments */
	if ((buf = getenv("QUERY_STRING")) != NULL) {
		p = strchr(buf, '&');
		if (p){
			*p = '\0';
			strcpy(passwd, p + 1);
		}
		else{
			strcpy(passwd, "null");
		}
		strcpy(name, buf);
	}
	else{
		printf("---------error arg!----------");
		fflush(stdout);
		exit(1);
		return 0;
	}


	/* Make the response body */
	_snprintf_s(content, MAXLINE, _TRUNCATE, "welcome to my web:%s and %s\r\n", name, passwd);
	_snprintf_s(content, MAXLINE, _TRUNCATE, "%sthis is a dynamic web!\r\n", content);

	_snprintf_s(content, MAXLINE, _TRUNCATE, "%sthanks for visiting!\r\n", content);

	printf("%s", content);
	fflush(stdout);
	exit(0);
	return 0;
}
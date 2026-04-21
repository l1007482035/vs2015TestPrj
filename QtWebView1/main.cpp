#include "stdafx.h"
#include "QtWebView1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtWebView1 w;
	//char* pBuf = argv[1];
	//char* pBuf = "http://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo=";
	//w.setUrl(argv[1], argv[2]);
	w.showMaximized();
	//w.show();
	return a.exec();
}

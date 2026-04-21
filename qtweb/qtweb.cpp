#include "stdafx.h"
#include "qtweb.h"



qtweb::qtweb(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//webView = new QWebEngineView(this);

	//ui.widget->load(QUrl("https://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo="));
	ui.widget->load(QUrl("https://www.baidu.com"));
	//webView->show();

}

qtweb::~qtweb()
{
	//delete webView;
	//webView = nullptr;
}


void qtweb::closeEvent(QCloseEvent *event)
{
	event->ignore();
#if 0
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(2000);
	animation->setStartValue(1);
	animation->setEndValue(0);
	animation->start();
	connect(animation, SIGNAL(finished()), this, SLOT(close()));
#endif

}

void qtweb::resizeEvent(QResizeEvent *event)
{
	//webView->resize(this->size());

}

void qtweb::on_widget_loadFinished(bool ok)
{
	int a = 4;
	//QPixmap 
}

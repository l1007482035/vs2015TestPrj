#include "stdafx.h"
#include "QtWebView1.h"

QtWebView1::QtWebView1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	//view = new QWebEngineView(this);
//	connect(view, SIGNAL(loadFinished(bool)), this, SLOT(on_view_loadFinish(bool)));
//	connect(view, &QWebEngineView::loadFinished,this, &QtWebView1::on_view_loadFinish);
	//view->load(QUrl("https://www.baidu.com/"));
	//widget->load(QUrl("http://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo="));
	//widget->show();
// 	widget->setFixedHeight(800);
// 	widget->setFixedWidth(1000);
	//widget->setGeometry(0,0,1000,800);
	m_bFinish = FALSE;
	m_pTimer = new QTimer(this);
//	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(Func()));
	qsSavePath = "";
	setMinimumSize(1122, 768);


	widget->load(QUrl("http://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo="));
	qsSavePath = QString("E:/1.png");

	
	//widget->
	//widget->setFixedWidth(1122);
	//widget->setFixedHeight(768);
}



void QtWebView1::resizeEvent(QResizeEvent *event)
{
	QSize oSize = widget->size();
	QString qsText = QString("%1x%2-%3x%4").arg(widget->width()).arg(widget->height()).arg(oSize.width()).arg(oSize.height());
	label->setText(qsText);
}

void QtWebView1::showEvent(QShowEvent *event)
{
	QSize oSize = widget->size();
	QString qsText = QString("%1x%2-%3x%4").arg(widget->width()).arg(widget->height()).arg(oSize.width()).arg(oSize.height());
	label->setText(qsText);

	widget->setZoomFactor(widget->width()/1000.0);
}

void QtWebView1::on_widget_loadFinished(bool bok)
{
	//widget->setZoomFactor(1.7);
	m_pTimer->start(10);
// 	if (bok)
// 	{
// 		m_bFinish = TRUE;
// 	}
// 	QPixmap pixmap(widget->size());
//  	widget->render(&pixmap);
// 	DWORD dwTime =  GetTickCount();
// 	while (1)
// 	{
// 		DWORD dwTime2 = GetTickCount();
// 		if(dwTime2 - dwTime > 10000)
// 		{ 
// 		//	m_bFinish
// 			pixmap.save("E:/1.png", Q_NULLPTR, 100);
// 			return;
// 		}
// 	}

}

void QtWebView1::on_pushButton_image_clicked()
{
	int dpm;

	// 		WebTemp.setZoomFactor(6.256);
	dpm = 1200 / 0.0254; // ~600 DPI

						 //widget->setZoomFactor(3.128);
						 //dpm = 300 / 0.0254; // ~300 DPI

	QSize size = widget->size();

	QImage image(size, QImage::Format_ARGB32);
	image.setDotsPerMeterX(dpm);
	image.setDotsPerMeterY(dpm);
	QPainter painter(&image);
	//painter.setRenderHint(QPainter::Antialiasing);
	//painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);


	widget->render(&painter);
	painter.end();
	if (image.save(qsSavePath))
	{

	}
}

void QtWebView1::on_pushButton_zoomin_clicked()
{
	qreal fReal = widget->zoomFactor();
	fReal += 0.1;
	widget->setZoomFactor(fReal);
}
void QtWebView1::on_pushButton_zoomout_clicked()
{
	qreal fReal = widget->zoomFactor();
	fReal -= 0.1;
	widget->setZoomFactor(fReal);
}

void QtWebView1::on_pushButton_bzoomin_clicked()
{
	QSize oSize = size();
	qreal fReal = 1.0;
	fReal += 0.1;
	oSize *= fReal;
	setFixedSize(oSize);
}

void QtWebView1::on_pushButton_bzoomout_clicked()
{

}

void QtWebView1::Func()
{

	int dpm;

	// 		WebTemp.setZoomFactor(6.256);
	 		dpm = 1200 / 0.0254; // ~600 DPI

	//widget->setZoomFactor(3.128);
	//dpm = 300 / 0.0254; // ~300 DPI

	QSize size = widget->size();

	QImage image(size, QImage::Format_ARGB32);
	image.setDotsPerMeterX(dpm);
	image.setDotsPerMeterY(dpm);
	QPainter painter(&image);
	//painter.setRenderHint(QPainter::Antialiasing);
	//painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);


	widget->render(&painter);
	painter.end();
	if (image.save(qsSavePath))
	{

	}
	m_pTimer->stop();


}
void QtWebView1::setUrl(char * pBuf ,char* pPath)
{
	widget->load(QUrl("http://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo="));
	qsSavePath = QString("E:/1.png");
}
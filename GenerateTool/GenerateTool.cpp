#include "stdafx.h"
#include "GenerateTool.h"

GenerateTool::GenerateTool(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	m_fBaseWidth = 1122.0;
	m_fBaseHeight = 762.0;
	double fScale = 3;

	m_fBaseWidth *= fScale;
	m_fBaseHeight *= fScale;

	
	

	m_pWebView = new QWebEngineView(this);
	m_pWebView->resize(m_fBaseWidth, m_fBaseHeight);
	m_pWebView->setZoomFactor((m_fBaseWidth - 200) / 1000.0);
	m_pTimer = new QTimer(this);
	connect(m_pWebView,SIGNAL(loadFinished(bool)),this,SLOT(onloadFinished(bool)));
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	m_pWebView->load(QUrl("http://ebpm.yzpc.edu.cn/default/work/yzpc/zdzm/zdzmPrint.jsp?token=ewogICAibm9uY2UiIDogImplTzBZZmVmbWhKQXIzU0kiLAogICAic2lnbmF0dXJlIiA6ICIzQTNFNjA1MjdFODgxRUNGNTQ1ODFBRjY3QTZGNEYxQiIsCiAgICJ0aW1lU3RhbXAiIDogIjE2NTQwNjc4NTg5NjgiLAogICAidHlwZSIgOiAiMSIsCiAgICJ4Z2giIDogIjEwMTY2OCIKfQo="));
	m_pWebView->show();
}

GenerateTool::~GenerateTool()
{
	if (m_pWebView)
	{
		delete m_pWebView;
		m_pWebView = nullptr;
	}

	if (m_pTimer)
	{
		delete m_pTimer;
		m_pTimer = nullptr;
	}
}

void GenerateTool::onloadFinished(bool ok)
{
	//theLog.Write("GenerateTool::on_m_pWebView_loadFinished");
	if (ok)
	{
		m_pTimer->start(500);
	}
}

void GenerateTool::on_timeout()
{
	int dpm;

	// 		WebTemp.setZoomFactor(6.256);
	dpm = 1200 / 0.0254; // ~600 DPI

						 //widget->setZoomFactor(3.128);
						 //dpm = 300 / 0.0254; // ~300 DPI

	QSize size = m_pWebView->size();

	QImage image(size, QImage::Format_ARGB32);
	image.setDotsPerMeterX(dpm);
	image.setDotsPerMeterY(dpm);
	QPainter painter(&image);
	//painter.setRenderHint(QPainter::Antialiasing);
	//painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);


	m_pWebView->render(&painter);
	painter.end();
	if (image.save("E:/1.png"))
	{
		
	}
	m_pTimer->stop();
	close();
}

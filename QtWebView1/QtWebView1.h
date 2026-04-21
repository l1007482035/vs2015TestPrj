#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWebView1.h"
#include <QWebEngineView>
#include <QTimer>




class QtWebView1 : public QWidget,public Ui::QtWebView1Class
{
	Q_OBJECT

public:
	QtWebView1(QWidget *parent = Q_NULLPTR);
	void resizeEvent(QResizeEvent *event);
	void showEvent(QShowEvent *event);

	QTimer* m_pTimer;
	BOOL m_bFinish;
	QString qsSavePath;
	void setUrl(char * pBuf, char* pPath);

	//QWebEngineView * view;
	public slots:
	void  Func();
	void  on_widget_loadFinished(bool bok);
	void on_pushButton_image_clicked();
	void on_pushButton_zoomin_clicked();
	void on_pushButton_zoomout_clicked();
	void on_pushButton_bzoomin_clicked();
	void on_pushButton_bzoomout_clicked();

protected:
private:
};

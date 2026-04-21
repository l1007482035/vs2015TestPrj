#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtweb.h"
#include <QWebEngineView>

class qtweb : public QWidget
{
	Q_OBJECT

public:
	qtweb(QWidget *parent = Q_NULLPTR);
	~qtweb();
	void closeEvent(QCloseEvent *event);

	void resizeEvent(QResizeEvent *event);

private:
	Ui::qtwebClass ui;

	QWebEngineView *webView;
private slots:
void on_widget_loadFinished(bool ok);
};

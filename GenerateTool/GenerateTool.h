#pragma once

#include <QWebEngineView>
#include <QtWidgets/QWidget>
#include "ui_GenerateTool.h"

class GenerateTool : public QWidget, Ui::GenerateToolClass
{
	Q_OBJECT

public:
	GenerateTool(QWidget *parent = Q_NULLPTR);
	~GenerateTool();

protected:
	QWebEngineView * m_pWebView;
	QTimer *m_pTimer;
	double m_fBaseWidth;
	double m_fBaseHeight;

private slots :
	void onloadFinished(bool ok);
	void on_timeout();
	

};

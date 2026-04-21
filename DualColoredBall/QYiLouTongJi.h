#pragma once

#include <QWidget>
#include "ui_QYiLouTongJi.h"

class QYiLouTongJi : public QWidget,public Ui::QYiLouTongJi
{
	Q_OBJECT

public:
	QYiLouTongJi(QWidget *parent = Q_NULLPTR);
	~QYiLouTongJi();

	void showEvent(QShowEvent *event);
	void LoadData();
	void AddRow(ST_DaLeTouRedYiLou& oInfo);

	std::vector<int> m_oTongJi;

private:

};

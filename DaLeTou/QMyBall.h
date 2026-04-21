#pragma once

#include <QPushButton>
#include "ui_QMyBall.h"
class QMyBall : public QPushButton, Ui::QMyBall
{
	Q_OBJECT

public:
	QMyBall(QWidget *parent = Q_NULLPTR);
	~QMyBall();
public:
	void mouseReleaseEvent(QMouseEvent *e);
	bool isForbided();
	bool isSelected();
public:
	void SetForbided();
	void SetRedSelected(bool bSelected);
	void SetBlueSelected(bool bSelected);
private:
	bool m_bBallForbid = false;//当前该球是否被禁用
	bool m_bBallSelected = false;//当前球是否被选中
};

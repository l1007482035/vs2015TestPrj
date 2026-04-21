#include "stdafx.h"
#include "QMyBall.h"

QMyBall::QMyBall(QWidget *parent)
	: QPushButton(parent)
{
	setupUi(this);
	setMinimumHeight(40);
}

QMyBall::~QMyBall()
{
}

void QMyBall::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
	{
		if (!m_bBallForbid)//设置成禁用界面
		{
			m_bBallForbid = true;
			setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");//黑色
			setCheckable(false);
			m_bBallSelected = false;
		
		}
		else
		{//设置成可用界面
			m_bBallForbid = false;
			setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");//白色
			setCheckable(true);
			setChecked(false);
		}
		
	}
	else if (e->button() == Qt::LeftButton)
	{
		if (!m_bBallForbid)//可用界面
		{
			if (!m_bBallSelected)//未选中->选中
			{
				m_bBallSelected = true;
				setCheckable(true);
				setChecked(true);
				QString qsObjName = objectName();
				if (qsObjName == "pushButton_blue1" || qsObjName == "pushButton_blue2" || qsObjName == "pushButton_blue3" || qsObjName == "pushButton_blue4"
					|| qsObjName == "pushButton_blue5" || qsObjName == "pushButton_blue6" || qsObjName == "pushButton_blue7" || qsObjName == "pushButton_blue8"
					|| qsObjName == "pushButton_blue9" || qsObjName == "pushButton_blue10" || qsObjName == "pushButton_blue11" || qsObjName == "pushButton_blue12"
					|| qsObjName == "pushButton_blue13" || qsObjName == "pushButton_blue14" || qsObjName == "pushButton_blue15" || qsObjName == "pushButton_blue16")
				{
					setStyleSheet("background-color: rgb(0, 0, 255);color: rgb(0, 0, 0);");//蓝色
				}
				else
				{
					setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(0, 0, 0);");//红色
				}
			}
			else
			{//选中->未选中
				m_bBallSelected = false;
				setCheckable(true);
				setChecked(false);
				setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");//白色
			}
			
		}
	}
}

bool QMyBall::isForbided()
{
	return m_bBallForbid;
}

bool QMyBall::isSelected()
{
	return m_bBallSelected;
}

void QMyBall::SetForbided()
{//黑色
	m_bBallForbid = true;
	setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
	setCheckable(false);
	m_bBallSelected = false;
}

void QMyBall::SetRedSelected(bool bSelected)
{
	if (bSelected)
	{
		m_bBallSelected = true;
		m_bBallForbid = false;
		setCheckable(true);
		setChecked(true);
		setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(0, 0, 0);");
	}
	else
	{
		m_bBallSelected = false;
		m_bBallForbid = false;
		setCheckable(true);
		setChecked(false);
		setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
	}
}

void QMyBall::SetBlueSelected(bool bSelected)
{
	if (bSelected)
	{
		m_bBallSelected = true;
		m_bBallForbid = false;
		setCheckable(true);
		setChecked(true);
		setStyleSheet("background-color: rgb(0, 0, 255);color: rgb(0, 0, 0);");
	}
	else
	{
		m_bBallSelected = false;
		m_bBallForbid = false;
		setCheckable(true);
		setChecked(false);
		setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
	}
}
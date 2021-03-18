#include "stdafx.h"
#include "QtTest.h"

#pragma execution_character_set("utf-8")

#define SIZE_W     100
#define SIZE_H     30


QtTest::QtTest(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	//设置阴影
	//设置窗体透明
#if 1
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	//设置无边框
	//setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//实例阴影shadow
	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
	//设置阴影距离
	shadow->setOffset(0, 0);
	//设置阴影颜色
	shadow->setColor(QColor("#444444"));
	//设置阴影圆角
	shadow->setBlurRadius(20);
	//给嵌套QWidget设置阴影
	this->setGraphicsEffect(shadow);
#endif
	


}

void QtTest::showEvent(QShowEvent *event)
{
	//label->setText("待到秋来九月八,我言花后愁花杀");

	int nWidth1 = frameGeometry().width();
	int nHeigth = frameGeometry().height();

	int nWidth2 = geometry().width();
	int nHeigt2 = geometry().height();

	int nWidth3 = width();
	int nHeigt3 = height();

	int nWidth4 = label_1->width();
	int nHeigt4 = label_1->height();

	int nWidth5 = label_1->geometry().width();
	int nHeigt5 = label_1->geometry().height();

	int nWidth6 = label_1->frameGeometry().width();
	int nHeigt6 = label_1->frameGeometry().height();





	QString text1("待到秋来九月八,我言花后愁花杀");
	QFont ft;
	QFontMetrics fm(ft);
	//QString text2 = fm.elidedText(text1, Qt::ElideRight, SIZE_W);
	QString text2 = fm.elidedText(text1, Qt::ElideMiddle, SIZE_W);

	QString text3 = fm.elidedText(text1, Qt::ElideRight, SIZE_W);//


	label_1->setFixedSize(SIZE_W, SIZE_H);
	//label_1->move(0, SIZE_H * 1);
	label_1->setText(text1);


	label_2->setFixedSize(SIZE_W, SIZE_H);
	//label_2->move(0, SIZE_H * 2);
	label_2->setText(text2);


	label_3->setFixedSize(SIZE_W, SIZE_H);
	label_3->setWordWrap(true);
	label_3->setAlignment(Qt::AlignTop);
	//label_2->move(0, SIZE_H * 3);
	label_3->setText(text3);

	QString qsStr = label_2->text();
}

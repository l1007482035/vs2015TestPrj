#pragma once

#include <QWidget>
#include "ui_QSanXiang.h"
#include "QBaseDlqWidget.h"

class QSanXiang : public QBaseDlqWidget,public Ui::QSanXiang
{
	Q_OBJECT

public:
	QSanXiang(QWidget *parent = Q_NULLPTR);
	~QSanXiang();

public:
	void SetDlqCfg(ST_DlqCfg& oDlqCfg);
	void SetUpdateData(ST_UpdateData& oUpdateData);
	void ClearText();
};

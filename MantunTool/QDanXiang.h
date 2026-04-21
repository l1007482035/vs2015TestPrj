#pragma once

#include <QWidget>
#include "ui_QDanXiang.h"
#include "QBaseDlqWidget.h"

class QDanXiang : public QBaseDlqWidget,public Ui::QDanXiang
{
	Q_OBJECT

public:
	QDanXiang(QWidget *parent = Q_NULLPTR);
	~QDanXiang();
public:
	void SetDlqCfg(ST_DlqCfg& oDlqCfg);
	void SetUpdateData(ST_UpdateData& oUpdateData);
	void ClearText();
};

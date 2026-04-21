#pragma once

#include <QWidget>
class MantunTool;

class QBaseDlqWidget : public QWidget
{
	Q_OBJECT

public:
	QBaseDlqWidget(QWidget *parent);
	~QBaseDlqWidget();
public:
	void SetDevInfo(int64_t nDevId,EN_DevType eType);
	int64_t GetDevId();
	void SetCfg(ST_DlqCfg& oDlqCfg);

protected:
	int64_t m_nDevId;
	EN_DevType m_nDevType = enDevType_Unkown;
	MantunTool *m_pCall = nullptr;
	ST_DlqCfg m_oDlqCfg;
private slots:
	void on_pushButton_swon_clicked();
	void on_pushButton_swoff_clicked();
	void on_pushButton_savebaojing_clicked();
	void on_pushButton_saveyujing_clicked();
	void on_pushButton_alarmen_clicked();
	void on_pushButton_alarmswen_clicked();
};

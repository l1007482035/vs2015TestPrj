#pragma once

#include <QtWidgets/QWidget>
#include "ui_DualColoredBall.h"
#include "../Public/CaiPiao.h"
class QYiLouTongJi;
class DualColoredBall : public QWidget,public Ui::DualColoredBallClass
{
	Q_OBJECT

public:
	DualColoredBall(QWidget *parent = Q_NULLPTR);
public:
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);
protected:
	void LoadData();
	void SaveData();

	//从预选区选出几个球添加到选择区
	void SelectFromPreSection(std::vector<int>& inVData, std::vector<int>& outVData, int nNumber);
	//从预选区选出1个球添加到选择区
	int SelectOneFromPreSection(std::vector<int>& inVData);
	CString GetRedBallQu(int nBall);
	/*添加一注
	/vRedBall 红球数组
	/nBlueBall 蓝球号
	*/
	void AddRow(std::vector<int>& vRedBall, int nBlueBall);
	void AddYiLouToTable(std::vector<ST_YiLou>& oYiLouVector);
	void AddOneRowRedInfo(ST_RedInfo& oInfo);
protected:
	std::vector<QMyBall*> m_oVRedBall;
	std::vector<QMyBall*> m_oVBlueBall;
	std::vector<ST_YiLou> m_oYiLouVector;//遗漏红球列表
	QYiLouTongJi	*m_pQYiLouTongJi;

private slots:
	//四区预选区随机一注
	void on_pushButton_prechoice1_clicked();
	//四区预选区随机五注
	void on_pushButton_prechoice5_clicked();
	//随机一注
	void on_pushButton_rand1_clicked();
	//随机五注
	void on_pushButton_rand5_clicked();
	//清空列已选
	void on_pushButton_clear_clicked();
	//删除一注
	void on_del_pushbutton_clicked();
	//保存
	void on_pushButton_save_clicked();
	//胆拖结算
	void on_pushButton_calc_clicked();
	//清除胆拖
	void on_pushButton_cleardantuo_clicked();
	//计算组合数
	void on_pushButton_calczuhe_clicked();
	//遗漏统计页确定
	void on_pushButton_sure_clicked();
	//遗漏统计页保存
	void on_pushButton_save_2_clicked();
	//胆拖区一注
	void on_pushButton_dantuo1_clicked();
	//胆拖区五注
	void on_pushButton_dantuo5_clicked();
	//执行选号
	void on_pushButton_zhixing_clicked();
	//执行五次
	void on_pushButton_zhixing5_clicked();
	//清除选择
	void on_pushButton_clearsel_clicked();
	void on_pushButton_zhixing2_clicked();
	//红球全选
	void on_pushButton_selredall_clicked();
	void on_pushButton_yilou_clicked();
	void on_pushButton_sort_clicked();


};

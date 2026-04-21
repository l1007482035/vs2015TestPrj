#pragma once

#include <QtWidgets/QWidget>

// namespace QtCharts
// {
// 	class QChartView;
// 	class QSplineSeries;
// };
//using namespace QtCharts;

#include "ui_DaLeTou.h"

class QuShiTu;
class QYiLouTongJi;
class DaLeTou : public QWidget,public Ui::DaLeTouClass
{
	Q_OBJECT

public:
	DaLeTou(QWidget *parent = Q_NULLPTR);
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

	//从范围随机一个数
	int SelectOneFromRange(int nBegin,int nEnd);
	/*添加一注
	/vRedBall 红球数组
	/nBlueBall 蓝球号
	*/
	void UpdateRedTableAfterSure();
	void UpdateBlueTableAfterSure();
	CString GetRedBallQu(int nBall);
	
	void AddRow(std::vector<int>& vRedBall, std::vector<int>& vBlueBall);
	template<typename T>
	//void AddRedYiLouToTable(std::vector<ST_YiLou>& oYiLouVector);
	void AddRedYiLouToTable(std::vector<T>& oYiLouVector);

	void AddBlueYiLouToTable(std::vector<ST_YiLou>& oYiLouVector);
	void AddRedTongLianYiLouToTable(CString szQiHao, CString szKaiHao, CString szChuXianQu,CString szYiLouQu, CString szSQYiLou);
	//根据蓝球趋势选出蓝球
	BOOL GetBlueBallByQuShi(int& nBlue1, int& nBlue2);
	void AddBlueBallToTable(std::vector<ST_DaLeTouBlue>& oBlueVector);
protected:
	std::vector<QMyBall*> m_oVRedBall;
	std::vector<QMyBall*> m_oVBlueBall;

	std::vector<ST_YiLou> m_oYiLouRedVector;//遗漏红球列表
	std::vector<ST_YiLou> m_oYiLouBlueVector;//遗漏蓝球列表

	QuShiTu* m_pQuShiTu;
	QYiLouTongJi* m_pYiLouTongJi;

	std::vector<ST_DaLeTouBlue> m_oBlueVector;//所有蓝球列表




private slots:
	//四区预选区随机一注
	void on_pushButton_prechoice1_clicked();
	//四区预选区随机五注
	void on_pushButton_prechoice5_clicked();

	//四区预选区随机一注
	void on_pushButton_one_clicked();
	//四区预选区随机五注
	void on_pushButton_five_clicked();

	//随机一注
	void on_pushButton_rand1_clicked();
	//随机五注
	void on_pushButton_rand5_clicked();
	//清空列已选
	void on_pushButton_clear_clicked();
	//删除一注
	void on_del_pushbutton_clicked();
	//一注后趋势
	void on_onequshi_pushbutton_clicked();
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
	//执行五次选号
	void on_pushButton_zhixing5_clicked();
	//清除按钮选择
	void on_pushButton_clearsel_clicked();
	//
	void on_pushButton_zhixing2_clicked();
	//红球全选
	void on_pushButton_selredall_clicked();

	void on_pushButton_qushi_clicked();
	//红遗漏区统计
	void on_pushButton_redyillou_clicked();

	void on_pushButton_redsort_clicked();
	void on_pushButton_totalsort_clicked();
	void on_pushButton_reset_clicked();


};

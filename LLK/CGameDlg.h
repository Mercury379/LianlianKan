#pragma once
#include "afxdialogex.h"
#include"global.h"
#include"CGameLogic.h"
#include"CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();
	void InitBackground();	//游戏背景初始化
	void InitElement();		//游戏元素初始化
	void UpdateWindow();	//窗口大小调整
	void UpdateGameMap();	//更新游戏地图
	void DrawTopFrame(int nRow, int nCol);//绘画点击框
	//bool IsLink();
	void DrawTipLine(Vertex v1, Vertex v2);//连线
	void SetBreak();	//休闲模式设置
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
protected:
	CDC m_dcMem;			//内存DC
	CDC m_dcBG;				//背景DC
	CDC m_dcElment;			//元素内存DC
	CDC m_dcMask;			//掩码内存DC
	CDC m_dcStop;			//游戏暂停图片显示
	CPoint m_ptGameTop;		//游戏区起始区
	CSize m_sizeElem;		//元素图片的大小
	CRect m_rtGameRect;		//游戏区域大小
	bool m_bFirstPoint;		//是否第一个点
	Vertex m_ptSelFirst;	//选中的第一个点
	Vertex m_ptSelSec;		//选中的第二个点
	//int m_anMap[10][14];
	//CGameLogic gamelogic;
	CGameControl gameControl;//游戏控制
	Vertex Path[140];			 //连接路径
	int nVertex;			 //路径点数目
	int count;				//计时
	bool pause;				//暂停游戏标志
	bool breakmodel;		//休闲模式标志
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();	//开始游戏按钮响应
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//鼠标点击相应
	afx_msg void OnBnClickedButton4();	//重排按钮响应
	afx_msg void OnBnClickedStop();	//停止游戏按钮响应
	afx_msg void OnBnClickedRemind();	//提示按钮响应
	afx_msg void OnBnClickedHelp();	//帮助按钮响应
	CProgressCtrl m_GameProgress;	//进度条变量
	afx_msg void OnTimer(UINT_PTR nIDEvent);	//时间响应
};

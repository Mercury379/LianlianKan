
// LLKDlg.h: 头文件
//

#pragma once


// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = nullptr);	// 标准构造函数
	void InitBackground();	//加载位图
	void UpdateWindow();	//调整对话框
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;	//位图内存
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();	//初始化对话框
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();	//绘图
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonBasic();	//基本模式按钮响应
	afx_msg void OnSize(UINT nType, int cx, int cy);	//调整窗口大小
	afx_msg void OnBnClickedHelp();	//帮助按钮响应
	afx_msg void OnBnClickedBreak();	//休闲模式按钮响应
};

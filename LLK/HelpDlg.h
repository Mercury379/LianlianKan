#pragma once
#include "afxdialogex.h"


// HelpDlg 对话框

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();	//问题一按钮响应
	afx_msg void OnBnClickedButton2();	//问题二按钮响应
	afx_msg void OnBnClickedButton3();	//问题三按钮响应
	afx_msg void OnPaint();	//绘图
};

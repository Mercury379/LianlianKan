// WinDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "WinDlg.h"


// WinDlg游戏胜利对话框

IMPLEMENT_DYNAMIC(WinDlg, CDialogEx)

WinDlg::WinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

WinDlg::~WinDlg()
{
}

void WinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WinDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// WinDlg 消息处理程序
void WinDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

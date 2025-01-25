// HelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "HelpDlg.h"


// HelpDlg 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &HelpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &HelpDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &HelpDlg::OnBnClickedButton3)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HelpDlg 消息处理程序

//问题一按钮响应
void HelpDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(55, _T("Courier New"));	//创建字体
	CFont* oldFont;
	oldFont = dc.SelectObject(&font);
	dc.SetTextColor(255);
	dc.SetBkColor(RGB(240, 240, 240));
	CRect rect;
	GetClientRect(&rect);
	CString strText = _T("只有空白连接路径上拐点不超过2个的两个相同水果之间才可以消子。在规定时间内消完游戏所有的水果后游戏胜利。");
	CSize size;
	size = dc.GetTextExtent(strText, strText.GetLength());
	dc.TextOutW(0, 230, strText);	//显示字体
}

//问题二按钮响应
void HelpDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(55, _T("Courier New"));	//创建字体
	CFont* oldFont;
	oldFont = dc.SelectObject(&font);
	dc.SetTextColor(255);
	dc.SetBkColor(RGB(240, 240, 240));
	CRect rect;
	GetClientRect(&rect);
	CString strText = _T("可以尝试退出游戏地图后重新进入该游戏模式。");
	CSize size;
	size = dc.GetTextExtent(strText, strText.GetLength());
	dc.TextOutW(260, 325, strText);	//显示字体
}

//问题三按钮响应
void HelpDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(55, _T("Courier New"));	//创建字体
	CFont* oldFont;
	oldFont = dc.SelectObject(&font);
	dc.SetTextColor(255);
	dc.SetBkColor(RGB(240, 240, 240));
	CRect rect;
	GetClientRect(&rect);
	CString strText = _T("可以点击游戏界面右下角的‘重排’按钮");
	CSize size;
	size = dc.GetTextExtent(strText, strText.GetLength());
	dc.TextOutW(280, 420, strText);	//显示字体
}

//问题四按钮响应
void HelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

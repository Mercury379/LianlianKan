
// LLKDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include"CGameDlg.h"
#include"HelpDlg.h"
#include<Windows.h>
#include <MMSystem.h>
#pragma comment (lib,"Winmm.lib");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLLKDlg::OnClickedButtonBasic)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON6, &CLLKDlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDC_BUTTON2, &CLLKDlg::OnBnClickedBreak)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	InitBackground();
	//播放音乐
	PlaySound(_T("D:\\数据结构与算法综合实验\\欢乐连连看游戏\\Eutopia.wav"), NULL, SND_FILENAME | SND_ASYNC);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		dc.BitBlt(0, 0, 800,600, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
		
	}
}

//初始化背景
void CLLKDlg::InitBackground() {
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);	//加载位图资源
	CClientDC dc(this);					//得到当前对话框内存
	m_dcMem.CreateCompatibleDC(&dc);	//创建当前对话框兼容的内存
	m_dcMem.SelectObject(bmpMain);		//选入位图加载到当前对话框中
	UpdateWindow();
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//基本模式按钮响应
void CLLKDlg::OnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);	//隐藏主界面窗口
	CGameDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);	//显示主界面窗口
	//CWnd::ShowWindow();	//控制主界面的隐藏与显示
	// TODO: 在此添加控件通知处理程序代码
}


void CLLKDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
}

//调整游戏窗口
void CLLKDlg::UpdateWindow() {
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);			//获得窗口大小
	this->GetClientRect(rtClient);		//获得客户区大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();//标题栏和外边框大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);//设置窗口大小
	CenterWindow();//在Windows窗口正中央
}


//帮助按钮响应
void CLLKDlg::OnBnClickedHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg dlg;
	dlg.DoModal();
}

//休闲模式按钮响应
void CLLKDlg::OnBnClickedBreak()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);	//隐藏主界面窗口
	CGameDlg dlg;
	dlg.SetBreak();	//设置游戏界面为休闲模式
	dlg.DoModal();	//调用游戏界面
	this->ShowWindow(SW_SHOW);	//显示主界面窗口
}

//绘图
void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include"WinDlg.h"
#include"LLKDlg.h"
#include"CHelpDialog.h"
#include<Windows.h>
#include <MMSystem.h>
#pragma comment (lib,"Winmm.lib");

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化游戏资源
	m_ptGameTop.x = 40;
	m_ptGameTop.y = 80;
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 14;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 10;
	m_bFirstPoint = true;
	count = 0;
	pause = false;
	breakmodel = false;
	//gamelogic.InitMap(m_anMap);
	gameControl.StartGame();
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedRemind)
	ON_BN_CLICKED(IDC_BUTTON6, &CGameDlg::OnBnClickedHelp)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序
void CGameDlg::InitBackground() {
	//CClientDC dc(this);	//获得当前对话框内存
	//HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//m_dcMem.CreateCompatibleDC(&dc);
	//m_dcMem.SelectObject(hBmpBG);
	//m_dcBG.CreateCompatibleDC(&dc);
	////将位图资源选进DC
	//m_dcBG.SelectObject(hBmpBG);
	//m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//UpdateWindow();
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//加载BMP图片资源
	CClientDC dc(this);//获得视频内存
	m_dcBG.CreateCompatibleDC(&dc);//创建于视频内容兼容的内存DC
	m_dcBG.SelectObject(bmp);		//将位图资源选进DC
	m_dcMem.CreateCompatibleDC(&dc);//创建内存DC
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);//将位图资源选进DC
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);//绘制背景图片
	if (breakmodel==true) {
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
		count = -100000;
	}
	UpdateWindow();
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//CDialogEx::OnPaint();
}

//游戏元素初始化
void CGameDlg::InitElement() {
	CClientDC dc(this);
	HANDLE hBmp = ::LoadImageW(NULL,_T("theme\\picture\\fruit_element.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_dcElment.CreateCompatibleDC(&dc);
	m_dcElment.SelectObject(hBmp);
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
	HANDLE hBmp1 = ::LoadImageW(NULL, _T("theme\\picture\\stop.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcStop.CreateCompatibleDC(&dc);
	m_dcStop.SelectObject(hBmp1);
}

//开始游戏按钮响应
void CGameDlg::OnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateGameMap();	//更新地图
	Invalidate(FALSE);
	//初始进度条
	m_GameProgress.SetRange(0, 60 * 5);		//初始范围
	m_GameProgress.SetStep(-1);				//初始步数值
	m_GameProgress.SetPos(60 * 5);			//设置初始值
	this->SetTimer(1, 1000, NULL);
	if (pause == true) {
		pause = false;
		m_GameProgress.SetPos(300 - count);	//设置暂停后再开始进度条初始值
	}
	//按钮禁用解除
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	//播放音乐
	//PlaySound(_T("D:\\数据结构与算法综合实验\\欢乐连连看游戏\\Eutopia.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

//调整窗口大小
void CGameDlg::UpdateWindow() {
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获取窗口大小
	this->GetClientRect(rtClient);//获取客户区大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();//标题栏和外边框大小
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);	//设置窗口大小
	CenterWindow();	//在Windows窗口正中央
}

//更新游戏地图
void CGameDlg::UpdateGameMap() {
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG,m_rtGameRect.left ,m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			/*m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElment, 0, m_anMap[i][j] * nElemH, SRCAND);*/
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, gameControl.GetElement(i,j) * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElment, 0, gameControl.GetElement(i, j) * nElemH, SRCAND);
		}
	}
}

//鼠标点击相应
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//设置点击范围
	if (point.y<m_rtGameRect.top || point.y>m_rtGameRect.bottom || point.x<m_rtGameRect.left || point.x>m_rtGameRect.right) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > 10 || nCol > 14) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//点击的第一个点
	if (m_bFirstPoint) {
		DrawTopFrame(nRow, nCol);	
		//m_ptSelFirst.col = nCol;
		//m_ptSelFirst.row = nRow;
		gameControl.SetFirstPoint(nRow, nCol);
	}
	//点击的第二个点
	else {
		DrawTopFrame(nRow, nCol);
		/*m_ptSelSec.col = nCol;
		m_ptSelSec.row = nRow;*/
		gameControl.SetSecPoint(nRow, nCol);
		//根据连线路径中点的个数连线
		if (gameControl.Link(Path,nVertex)/*gamelogic.IsLink(m_anMap, m_ptSelFirst, m_ptSelSec)*/) {
			for (int i = 0; i < nVertex-1; i++) {
				DrawTipLine(Path[i],Path[i+1]);
			}
			//if (nVertex == 2) {
			//	DrawTipLine(gameControl.GetFirstPoint(), gameControl.GetSecPoint());
			//}
			//else if (nVertex == 3) {
			//	DrawTipLine(gameControl.GetFirstPoint(), Path[1]);
			//    DrawTipLine(Path[1], gameControl.GetSecPoint());
			//}
			//else if(nVertex==4) {
			//	if (Path[2].row == gameControl.GetFirstPoint().row || Path[2].col == gameControl.GetFirstPoint().col) {
			//		DrawTipLine(gameControl.GetFirstPoint(), Path[2]);
			//		DrawTipLine(Path[2], Path[1]);
			//		DrawTipLine(Path[1], gameControl.GetSecPoint());
			//	}
			//	else {
			//		DrawTipLine(gameControl.GetFirstPoint(), Path[1]);
			//		DrawTipLine(Path[1], Path[2]);
			//		DrawTipLine(Path[2], gameControl.GetSecPoint());
			//	}
			//}
			//m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] = -1;
			//m_anMap[m_ptSelSec.row][m_ptSelSec.col] = -1;
			gameControl.Clear();
			UpdateGameMap();
			//判断胜负
			if (gameControl.Win()&&count<300) {
				//CPaintDC dc(this);	//创建CPaintDC对象
				//dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
				//CFont font;
				//font.CreatePointFont(200, _T("Courier New"));	//创建字体
				//CFont* oldFont;
				//oldFont = dc.SelectObject(&font);
				//dc.SetTextColor(255);
				//dc.SetBkColor(RGB(0, 0, 0));
				//CRect rect;
				//GetClientRect(&rect);
				//CString strText = _T("Welcome to LLK - Game");
				//CSize size;
				//size = dc.GetTextExtent(strText, strText.GetLength());
				//int x = (rect.Width() - size.cx) / 2;
				//int y = (rect.Height() - size.cy) / 2;
				//dc.TextOutW(x, y, strText);
				//CDialogEx::OnPaint();
				WinDlg dlg;
				dlg.DoModal();

			}
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	//重新点击
	m_bFirstPoint = !m_bFirstPoint;
	CDialogEx::OnLButtonUp(nFlags, point);
}

//绘画点击框
void CGameDlg::DrawTopFrame(int nRow,int nCol) {	//绘制点击框
	CClientDC dc(this);
	CBrush brush(RGB(255, 255, 0));
	CRect rtTipFrame;
	//计算画框大小
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}
//bool CGameDlg::IsLink() {
//	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col]) {
//		return true;
//	}
//	return false;
//}

//路径连线
void CGameDlg::DrawTipLine(Vertex v1,Vertex v2) {
	CClientDC dc(this);							//获取DC
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));	//设置画笔
	CPen* pOldpPen = dc.SelectObject(&penLine);	//将画笔选入dc
	//连线
	dc.MoveTo(m_ptGameTop.x + v1.col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + v1.row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.LineTo(m_ptGameTop.x + v2.col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + v2.row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.SelectObject(pOldpPen);
}

//重排按钮响应
void CGameDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	gameControl.Flush();
	UpdateGameMap();	//更新地图
	Invalidate(FALSE);
}

//暂停游戏按钮响应
void CGameDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	pause = true;
	CClientDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	dc.BitBlt(20, 60, 600, 450, &m_dcStop, 0, 0, SRCCOPY);
	//按钮禁用
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
}

//提示按钮响应
void CGameDlg::OnBnClickedRemind()
{
	// TODO: 在此添加控件通知处理程序代码
	gameControl.Help(Path, nVertex);	//获取连接路径
	DrawTopFrame(Path[0].row, Path[0].col);	//绘制点击框
	DrawTopFrame(Path[nVertex-1].row, Path[nVertex-1].col);
	for (int i = 0; i < nVertex - 1; i++) {	//绘制连接路径
		DrawTipLine(Path[i], Path[i + 1]);
	}
}

//帮助按钮响应
void CGameDlg::OnBnClickedHelp()
{
	CHelpDialog helpdialog;	
	helpdialog.DoModal();	//调用帮助对话框
	// TODO: 在此添加控件通知处理程序代码
}

//时间响应
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (count > 300) {	//当时间超过300s自动判负
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(100, _T("Courier New"));	//创建字体
		CFont* oldFont;
		oldFont = dc.SelectObject(&font);
		dc.SetTextColor(255);
		dc.SetBkColor(RGB(240, 240, 240));
		CRect rect;
		GetClientRect(&rect);
		CString strText = _T("游戏时间已到！游戏失败！");	
		CSize size;
		size = dc.GetTextExtent(strText, strText.GetLength());
		dc.TextOutW(150, 235, strText);	//显示游戏失败
		pause = true;
		CDialog::OnOK();	//退出游戏界面，返回主界面
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	if (pause == false) {
		count++;	//计时
		m_GameProgress.StepIt();	//进度条
	}
	str.Format(_T("%-3d秒"), 300 - count);	//显示还剩多少秒
	SetDlgItemText(IDC_EDIT1, str);//在文本框中显示str结果
	m_GameProgress.SetBarColor(RED_SHIFT);
	CDialogEx::OnTimer(nIDEvent);
}

//休闲模式设置
void CGameDlg::SetBreak() {
	breakmodel = true;
}


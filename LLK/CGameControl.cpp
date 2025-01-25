#include "pch.h"
#include "CGameControl.h"
//开始游戏
void CGameControl::StartGame() {
	gamelogic.InitMap(m_graph);
	m_graph.TestGraph();
}

//获取地图中的元素
int CGameControl::GetElement(int nRow,int nCol) {
	//return m_anMap[nRow][nCol];
	return m_graph.GetVertex(nRow*14+nCol);
}

//设置选中的第一个点
void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//设置选中的第二个点
void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//连接判断
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM],int &nVertex) {
	//判断点重合
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}
	//消子判断
	// CGameLogic gamelogic;
	//if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col]&&m_anMap[m_ptSelFirst.row][m_ptSelFirst.col]!=BLANK) {
	//	if (gamelogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
	//		nVertex = gamelogic.GetVertexPath(avPath);	//获取路径上点数
	//		return true;
	//	}
	//}
	CGameLogic gamelogic1;
	if (gamelogic1.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
		nVertex = gamelogic1.GetVertexPath(avPath);	//获取路径上点数
		return true;
	}
	CGameLogic gamelogic2;
	if (gamelogic2.IsLink(m_graph, m_ptSelSec, m_ptSelFirst)) {
		nVertex = gamelogic2.GetVertexPath(avPath);	//获取路径上点数
		return true;
	}
	return false;
}

//消除两个点

void CGameControl::Clear() {
	gamelogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
}

//获取选中的第一个点
Vertex CGameControl::GetFirstPoint() {
	return m_ptSelFirst;
}

//获取选中的第二个点
Vertex CGameControl::GetSecPoint() {
	return m_ptSelSec;
}

//胜负判断
bool CGameControl::Win() {
	return gamelogic.IsWin(m_graph);;
}

//重排
void CGameControl:: Flush() {
	srand(time(nullptr));//设置随机数种子
	//int anMap[10][14];
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		anMap[i][j] = rand() % 6;//产生一个随机数
	//	}
	//}
	////更新游戏地图
	//m_graph.InitGraph();
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		m_graph.AddVertex(anMap[i][j]);
	//		gamelogic.UpdateArc(m_graph, i, j);
	//	}
	//}
	for (int i = 0; i < 300; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;	//随机选取交换两点
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		if (nIndex1 % 14 != 0 && nIndex2 % 14 != 0 
			&& nIndex1 % 14 != 13 && nIndex2 % 14 != 13 
			&& nIndex1 > 14 && nIndex1 < MAX_VERTEX_NUM - 14 
			&& nIndex2>14 && nIndex2 < MAX_VERTEX_NUM - 14) {	//判断随机选取点是否在地图外框
			int t = m_graph.GetVertex(nIndex1);		//交换两点
			m_graph.UpdateVertex(nIndex1, m_graph.GetVertex(nIndex2));
			m_graph.UpdateVertex(nIndex2, t);
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			gamelogic.UpdateArc(m_graph, i, j);
		}
	}
}

//提示
bool CGameControl::Help(Vertex avPath[], int& nVexnum) {	
	CGameLogic gamelogic;
	if (gamelogic.SearchValiPath(m_graph)) {	//寻找是否存在有效路径
		nVexnum = gamelogic.GetVertexPath(avPath);	//获取连接路径
		return true;
	}
	return false;
}


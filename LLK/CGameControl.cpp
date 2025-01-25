#include "pch.h"
#include "CGameControl.h"
//��ʼ��Ϸ
void CGameControl::StartGame() {
	gamelogic.InitMap(m_graph);
	m_graph.TestGraph();
}

//��ȡ��ͼ�е�Ԫ��
int CGameControl::GetElement(int nRow,int nCol) {
	//return m_anMap[nRow][nCol];
	return m_graph.GetVertex(nRow*14+nCol);
}

//����ѡ�еĵ�һ����
void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//����ѡ�еĵڶ�����
void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

//�����ж�
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM],int &nVertex) {
	//�жϵ��غ�
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}
	//�����ж�
	// CGameLogic gamelogic;
	//if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col]&&m_anMap[m_ptSelFirst.row][m_ptSelFirst.col]!=BLANK) {
	//	if (gamelogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
	//		nVertex = gamelogic.GetVertexPath(avPath);	//��ȡ·���ϵ���
	//		return true;
	//	}
	//}
	CGameLogic gamelogic1;
	if (gamelogic1.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)) {
		nVertex = gamelogic1.GetVertexPath(avPath);	//��ȡ·���ϵ���
		return true;
	}
	CGameLogic gamelogic2;
	if (gamelogic2.IsLink(m_graph, m_ptSelSec, m_ptSelFirst)) {
		nVertex = gamelogic2.GetVertexPath(avPath);	//��ȡ·���ϵ���
		return true;
	}
	return false;
}

//����������

void CGameControl::Clear() {
	gamelogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
}

//��ȡѡ�еĵ�һ����
Vertex CGameControl::GetFirstPoint() {
	return m_ptSelFirst;
}

//��ȡѡ�еĵڶ�����
Vertex CGameControl::GetSecPoint() {
	return m_ptSelSec;
}

//ʤ���ж�
bool CGameControl::Win() {
	return gamelogic.IsWin(m_graph);;
}

//����
void CGameControl:: Flush() {
	srand(time(nullptr));//�������������
	//int anMap[10][14];
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		anMap[i][j] = rand() % 6;//����һ�������
	//	}
	//}
	////������Ϸ��ͼ
	//m_graph.InitGraph();
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		m_graph.AddVertex(anMap[i][j]);
	//		gamelogic.UpdateArc(m_graph, i, j);
	//	}
	//}
	for (int i = 0; i < 300; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;	//���ѡȡ��������
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		if (nIndex1 % 14 != 0 && nIndex2 % 14 != 0 
			&& nIndex1 % 14 != 13 && nIndex2 % 14 != 13 
			&& nIndex1 > 14 && nIndex1 < MAX_VERTEX_NUM - 14 
			&& nIndex2>14 && nIndex2 < MAX_VERTEX_NUM - 14) {	//�ж����ѡȡ���Ƿ��ڵ�ͼ���
			int t = m_graph.GetVertex(nIndex1);		//��������
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

//��ʾ
bool CGameControl::Help(Vertex avPath[], int& nVexnum) {	
	CGameLogic gamelogic;
	if (gamelogic.SearchValiPath(m_graph)) {	//Ѱ���Ƿ������Ч·��
		nVexnum = gamelogic.GetVertexPath(avPath);	//��ȡ����·��
		return true;
	}
	return false;
}


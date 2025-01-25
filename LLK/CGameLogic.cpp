#include "pch.h"
#include "CGameLogic.h"
#include<stdlib.h>
#include<time.h>
#include"CGraph.h"

CGameLogic::CGameLogic() {
	m_nVertexNum = 0;
	m_nCornerNum = 0;
}

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(CGraph &graph) {
	srand(time(nullptr));//�������������
	int anMap[10][14];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			anMap[i][j] = rand() % 6;//-1;	//����һ�������
		}
	}
	for (int i = 0; i < 10; i++) {	//���������
		anMap[i][0] = -1;
		anMap[i][13] = -1;
	}
	for (int j = 0; j < 14; j++) {
		anMap[0][j] = -1;
		anMap[9][j] = -1;
	}
	//int anMap[10][14] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	//				  -1,4,2,2,1,3,2,1,0,0,1,4,0,-1,
	//				  -1,3,2,2,0,1,2,1,0,5,1,3,0,-1,
	//				  -1,3,4,0,1,3,2,1,4,0,1,3,0,-1,
	//				  -1,3,2,2,5,4,4,1,0,0,1,3,1,-1,
	//				  -1,5,2,2,0,3,2,1,4,5,1,4,0,-1,
	//				  -1,3,4,0,1,3,2,4,0,0,5,3,1,-1,
	//				  -1,3,2,2,4,3,5,1,0,0,1,3,5,-1,
	//				  -1,3,2,5,1,1,2,1,5,2,1,4,5,-1,
	//				  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	//};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			graph.AddVertex(anMap[i][j]);
			//graph.AddVertex(-1);
			UpdateArc(graph, i, j);
		}
	}
	////���������Ϸ��ͼ
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		m_anMap[i][j] = rand() % 6;//����һ�������
	//	}
	//}
}

//�����ж�
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2) {
	////һ��ֱ����ͨ
	//AddVertex(v1);	//���������ͼ·��
	//if (v1.row == v2.row) {
	//	if(LinkInRow(graph, v1, v2)){
	//		AddVertex(v2);	//���������ͼ·��
	//		return true;
	//	}
	//}
	//if (v1.col == v2.col) {
	//	if (LinkInCol(graph, v1, v2)) {
	//		AddVertex(v2);	//���������ͼ·��
	//		return true;
	//	}
	//}
	////����ֱ����ͨ
	//if (OneCornerLink(graph, v1, v2)) {
	//	AddVertex(v2);	//���������ͼ·��
	//	return true;
	//}
	////����ֱ��
	//if (TwoCornerLink(graph, v1, v2)) {
	//	AddVertex(v2);	//���������ͼ·��
	//	return true;
	//}
	AddVertex(v1);
	//��ȡ�ڶ��������е�������
	int nIndex1 = v1.row * 14 + v1.col;
	int nIndex2 = v2.row * 14 + v2.col;
	//if (graph.GetArc(nIndex1, nIndex2)) {
	//	AddVertex(v2);
	//	return true;
	//}
	
	if (graph.GetVertex(nIndex1)==graph.GetVertex(nIndex2)&&graph.GetVertex(nIndex1)!=BLANK&&SearchPath(graph, nIndex1, nIndex2) == true) {
		return true;
	}
	DeleteVertex();
	return false;
}

//����
bool CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2) {
	//m_anMap[v1.row][v1.col] = BLANK;
	//m_anMap[v2.row][v2.col] = BLANK;
	
	//��ȡ������
	int nIndex1 = v1.row * 14 + v1.col;
	int nIndex2 = v2.row * 14 + v2.col;

	//���¶���
	graph.UpdateVertex(nIndex1,BLANK);
	graph.UpdateVertex(nIndex2, BLANK);

	//���±���Ϣ
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			UpdateArc(graph, i, j);
		}
	}
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
	return true;
}

//һ��������
bool CGameLogic::LinkInRow(CGraph& graph, Vertex v1, Vertex v2) {
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	//������С˳��
	if (nCol1>nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	//�����ж�
	for (int i = nCol1 + 1; i <= nCol2; i++) {
		if (i == nCol2) {
			return true;
		}
		//if (anMap[nRow][i]!=BLANK) {
		//	break;
		//}
	}
	return false;
}

//һ��������
bool CGameLogic::LinkInCol(CGraph& graph, Vertex v1, Vertex v2) {
	int nCol = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	//������С˳��
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	///�����ж�
	for (int i = nRow1 + 1; i <= nRow2; i++) {
		if (i == nRow2) {
			return true;
		}
		//if (anMap[i][nCol] != BLANK) {
		//	break;
		//}
	}
	return false;
}

//�����������ж�
bool CGameLogic::LineX(CGraph& graph, int nRow,int nCol1,int nCol2) {
	//������С˳��
	if (nCol1 > nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	//�����ж�
	for (int i = nCol1 + 1; i < nCol2; i++) {
		if (i == nCol2) {
			return true;
		}
		//if (anMap[nRow][i] != BLANK) {
		//	return false;
		//}
	}
	return true;
}

//�����������ж�
bool CGameLogic::LineY(CGraph& graph, int nCol, int nRow1, int nRow2) {
	//������С˳��
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	//�����ж�
	for (int i = nRow1 + 1; i < nRow2; i++) {
		if (i == nRow2) {
			return true;
		}
		//if (anMap[i][nCol] != BLANK) {
		//	return false;
		//}
	}
	return true;
}

//����������
bool CGameLogic::OneCornerLink(CGraph& graph, Vertex v1, Vertex v2) {
	//Ѱ���йյ�
	//if (anMap[v1.row][v2.col] == BLANK) {
	//	if (LineY(anMap, v2.col,v1.row, v2.row) && LineX(anMap, v1.row, v1.col, v2.col)) {
	//		Vertex v = { v1.row,v2.col,BLANK };
	//		AddVertex(v);
	//		return true;
	//	}
	//}
	// Ѱ���йյ�
	//if (anMap[v2.row][v1.col] == BLANK) {
	//	if (LineY(anMap, v1.col, v1.row, v2.row) && LineX(anMap, v2.row, v1.col, v1.col)) {
	//		Vertex v = { v2.row,v1.col,BLANK };
	//		AddVertex(v);
	//		return true;
	//	}
	//}
	return false;
}

//����������
bool CGameLogic::TwoCornerLink(CGraph& graph, Vertex v1, Vertex v2) {
	//Ѱ���йյ�
	//for (int i = v1.col; i < v2.col; i++) {
	//	if (anMap[v1.row][i] == BLANK && anMap[v2.row][i] == BLANK) {
	//		if (LineY(anMap, i, v1.row, v2.row)) {
	//			if (LineX(anMap, v1.row, v1.col, i) && LineX(anMap, v2.row, v2.col, i)) {
	//				Vertex Vx1 = { v1.row,i,BLANK };
	//				Vertex Vx2 = { v2.row,i,BLANK };
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	// Ѱ���йյ�
	//for (int i = v1.row; i < v2.row; i++) {
	//	if (anMap[i][v1.col] == BLANK && anMap[i][v2.col] == BLANK) {
	//		if (LineX(anMap, i, v1.col, v2.col)) {
	//			if (LineY(anMap, v1.col, v1.row, i) && LineY(anMap, v2.col, v2.row, i)) {
	//				Vertex Vx1 = { i,v1.col,BLANK };
	//				Vertex Vx2 = { i,v2.col,BLANK };
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	//Vertex temp = v1;
	//v1 = v2;
	//v2 = temp;
	////Ѱ���йյ�
	//for (int i = v1.col; i < v2.col; i++) {
	//	if (anMap[v1.row][i] == BLANK && anMap[v2.row][i] == BLANK) {
	//		if (LineY(anMap, i, v1.row, v2.row)) {
	//			if (LineX(anMap, v1.row, v1.col, i) && LineX(anMap, v2.row, v2.col, i)) {
	//				Vertex Vx1 = { v1.row,i,BLANK };
	//				Vertex Vx2 = { v2.row,i,BLANK };
	//				//��ӹյ��·��
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	////Ѱ���йյ�
	//for (int i = v1.row; i < v2.row; i++) {
	//	if (anMap[i][v1.col] == BLANK && anMap[i][v2.col] == BLANK) {
	//		if (LineX(anMap, i, v1.col, v2.col)) {
	//			if (LineY(anMap, v1.col, v1.row, i) && LineY(anMap, v2.col, v2.row, i)) {
	//				Vertex Vx1 = { i,v1.col,BLANK };
	//				Vertex Vx2 = { i,v2.col,BLANK };
	//				//��ӹյ��·��
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}

//��ӵ����ͼ·��
void CGameLogic::AddVertex(Vertex v) {
	m_avPath[m_nVertexNum++] = v;
	if (IsCorner()) {	//������ӵĵ��ǹյ���Ҫ���ӹյ���
		m_nCornerNum++;
	}
}

//ɾ����ͼ·����
void CGameLogic::DeleteVertex() {
	if (IsCorner()) {	//���ɾ���ĵ��ǹյ���Ҫɾ���յ���
		m_nCornerNum--;
	}
	m_nVertexNum--;
}

//��ȡ��ͼ·��
int CGameLogic::GetVertexPath(Vertex avPath[MAX_VERTEX_NUM]) {
	for (int i = 0; i < m_nVertexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVertexNum;
}

//���±�
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol) {
	int nIndex1 = nRow * 14 + nCol;
	if (nCol > 0) {		//�������
		int nIndex2 = nIndex1 - 1;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1)|| graph.GetVertex(nIndex1)==BLANK|| graph.GetVertex(nIndex2)==BLANK) {
			graph.AddArc(nIndex1,nIndex2);
		}
	}
	if (nCol < 13) {	//�ұ�����
		int nIndex2 = nIndex1 + 1;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow > 0) {		//�Ϸ�����
		int nIndex2 = nIndex1 - 14;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow < 9) {		//�·�����
		int nIndex2 = nIndex1 + 14;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
}

//�����������Ѱ��·��
bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1) {
	//�õ�������
	//int nVexnum = g.GetVexnum();

	//����ͼ��nVo�У���0������nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < MAX_VERTEX_NUM; nVi++) {
		if (g.GetArc(nV0, nVi)==true && IsExist(nVi)) {
			Vertex temp = { nVi / 14 , nVi % 14,g.GetVertex(nVi)};
			AddVertex(temp);
			if (m_nCornerNum > 2) {	//����յ�������2��ɾ���õ�
				DeleteVertex();
				continue;
			}
			if (nVi != nV1) {
				if (g.GetVertex(nVi) != BLANK ) {	//���nVi���ǿ�������ͨ
					DeleteVertex();
					continue;
				}
				if (SearchPath(g, nVi, nV1)) {	//����������������·�����·������
					return true;
				}
			}
			else {
				return true;
			}
		}
	}
	DeleteVertex();	//�жϲ����к�Ҫ��nV0ɾ��������������
	return false;
}

//�ж��������Ƿ���·����
bool CGameLogic::IsExist(int nVi) {
	for (int i = 0; i < m_nVertexNum; i++) {
		if (m_avPath[i].row * 14 + m_avPath[i].col == nVi) {
			return false;
		}
	}
	return true;
}

//�ж�ʤ��
bool CGameLogic::IsWin(CGraph graph) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {	
		if (graph.GetVertex(i) != BLANK) {	//�ж����������Ƿ�Ϊ��
			return false;
		}
	}
	return true;
}

//�жϹյ�
bool CGameLogic::IsCorner() {
	//if (m_nVertexNum >= 3) {
	//	if((v1.row==v2.row&&v2.col==v3.col)||(v1.col==v2.col&&v2.row==v3.row)){
	//		return true;
	//	}
	//}
	//return false;
	if (m_nVertexNum >= 3) {	
		Vertex v1 = m_avPath[m_nVertexNum - 1];
		Vertex v2 = m_avPath[m_nVertexNum - 2];
		Vertex v3 = m_avPath[m_nVertexNum - 3];
		if (v1.col + v3.col != 2 * v2.col && v1.row+v3.row !=2*v2.row) {	//�жϹյ�
			return true;
		}
	}
	return false;
}

//Ѱ�ҿ���·��
bool CGameLogic::SearchValiPath(CGraph& graph) {
	int nVexnum = graph.GetVexnum();			//��ȡ��Ϸ�����
	for (int i = 0; i < nVexnum; i++) {
		if (graph.GetVertex(i) == BLANK) {		//�жϸĽ��Ԫ���Ƿ�Ϊ��
			continue;
		}
		for (int j = 0; j < nVexnum; j++) {		//Ѱ����ͬԪ��
			if (i != j) {
				if (graph.GetVertex(i) == graph.GetVertex(j)) {
					Vertex temp = { i / 14 ,i % 14,graph.GetVertex(i) };
					AddVertex(temp);			//�����ʼ��
					if (SearchPath(graph, i, j) == true) {	//Ѱ���Ƿ���·��
						return true;
					}
					DeleteVertex();		//û��·����ɾ������ʼ��
				}
			}
		}
	}
	return false;
}

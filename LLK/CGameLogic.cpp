#include "pch.h"
#include "CGameLogic.h"
#include<stdlib.h>
#include<time.h>
#include"CGraph.h"

CGameLogic::CGameLogic() {
	m_nVertexNum = 0;
	m_nCornerNum = 0;
}

//初始化游戏地图
void CGameLogic::InitMap(CGraph &graph) {
	srand(time(nullptr));//设置随机数种子
	int anMap[10][14];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			anMap[i][j] = rand() % 6;//-1;	//产生一个随机数
		}
	}
	for (int i = 0; i < 10; i++) {	//最外框设置
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
	////随机产生游戏地图
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		m_anMap[i][j] = rand() % 6;//产生一个随机数
	//	}
	//}
}

//连接判断
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2) {
	////一条直线连通
	//AddVertex(v1);	//添加起点进画图路径
	//if (v1.row == v2.row) {
	//	if(LinkInRow(graph, v1, v2)){
	//		AddVertex(v2);	//添加起点进画图路径
	//		return true;
	//	}
	//}
	//if (v1.col == v2.col) {
	//	if (LinkInCol(graph, v1, v2)) {
	//		AddVertex(v2);	//添加起点进画图路径
	//		return true;
	//	}
	//}
	////两条直线连通
	//if (OneCornerLink(graph, v1, v2)) {
	//	AddVertex(v2);	//添加起点进画图路径
	//	return true;
	//}
	////三条直线
	//if (TwoCornerLink(graph, v1, v2)) {
	//	AddVertex(v2);	//添加起点进画图路径
	//	return true;
	//}
	AddVertex(v1);
	//获取在顶点数组中的索引号
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

//消子
bool CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2) {
	//m_anMap[v1.row][v1.col] = BLANK;
	//m_anMap[v2.row][v2.col] = BLANK;
	
	//获取索引号
	int nIndex1 = v1.row * 14 + v1.col;
	int nIndex2 = v2.row * 14 + v2.col;

	//更新顶点
	graph.UpdateVertex(nIndex1,BLANK);
	graph.UpdateVertex(nIndex2, BLANK);

	//更新边信息
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			UpdateArc(graph, i, j);
		}
	}
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
	return true;
}

//一条线消子
bool CGameLogic::LinkInRow(CGraph& graph, Vertex v1, Vertex v2) {
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	//调换大小顺序
	if (nCol1>nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	//连接判断
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

//一条线消子
bool CGameLogic::LinkInCol(CGraph& graph, Vertex v1, Vertex v2) {
	int nCol = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	//调换大小顺序
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	///连接判断
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

//行两点连接判断
bool CGameLogic::LineX(CGraph& graph, int nRow,int nCol1,int nCol2) {
	//调换大小顺序
	if (nCol1 > nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	//连接判断
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

//列两点连接判断
bool CGameLogic::LineY(CGraph& graph, int nCol, int nRow1, int nRow2) {
	//调换大小顺序
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	//连接判断
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

//两条线消子
bool CGameLogic::OneCornerLink(CGraph& graph, Vertex v1, Vertex v2) {
	//寻找行拐点
	//if (anMap[v1.row][v2.col] == BLANK) {
	//	if (LineY(anMap, v2.col,v1.row, v2.row) && LineX(anMap, v1.row, v1.col, v2.col)) {
	//		Vertex v = { v1.row,v2.col,BLANK };
	//		AddVertex(v);
	//		return true;
	//	}
	//}
	// 寻找列拐点
	//if (anMap[v2.row][v1.col] == BLANK) {
	//	if (LineY(anMap, v1.col, v1.row, v2.row) && LineX(anMap, v2.row, v1.col, v1.col)) {
	//		Vertex v = { v2.row,v1.col,BLANK };
	//		AddVertex(v);
	//		return true;
	//	}
	//}
	return false;
}

//三条线消字
bool CGameLogic::TwoCornerLink(CGraph& graph, Vertex v1, Vertex v2) {
	//寻找行拐点
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
	// 寻找列拐点
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
	////寻找行拐点
	//for (int i = v1.col; i < v2.col; i++) {
	//	if (anMap[v1.row][i] == BLANK && anMap[v2.row][i] == BLANK) {
	//		if (LineY(anMap, i, v1.row, v2.row)) {
	//			if (LineX(anMap, v1.row, v1.col, i) && LineX(anMap, v2.row, v2.col, i)) {
	//				Vertex Vx1 = { v1.row,i,BLANK };
	//				Vertex Vx2 = { v2.row,i,BLANK };
	//				//添加拐点进路径
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	////寻找列拐点
	//for (int i = v1.row; i < v2.row; i++) {
	//	if (anMap[i][v1.col] == BLANK && anMap[i][v2.col] == BLANK) {
	//		if (LineX(anMap, i, v1.col, v2.col)) {
	//			if (LineY(anMap, v1.col, v1.row, i) && LineY(anMap, v2.col, v2.row, i)) {
	//				Vertex Vx1 = { i,v1.col,BLANK };
	//				Vertex Vx2 = { i,v2.col,BLANK };
	//				//添加拐点进路径
	//				AddVertex(Vx1);
	//				AddVertex(Vx2);
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}

//添加点进画图路径
void CGameLogic::AddVertex(Vertex v) {
	m_avPath[m_nVertexNum++] = v;
	if (IsCorner()) {	//如果增加的点是拐点则要增加拐点数
		m_nCornerNum++;
	}
}

//删除画图路径点
void CGameLogic::DeleteVertex() {
	if (IsCorner()) {	//如果删掉的点是拐点则要删除拐点数
		m_nCornerNum--;
	}
	m_nVertexNum--;
}

//获取画图路径
int CGameLogic::GetVertexPath(Vertex avPath[MAX_VERTEX_NUM]) {
	for (int i = 0; i < m_nVertexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVertexNum;
}

//更新边
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol) {
	int nIndex1 = nRow * 14 + nCol;
	if (nCol > 0) {		//左边相邻
		int nIndex2 = nIndex1 - 1;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1)|| graph.GetVertex(nIndex1)==BLANK|| graph.GetVertex(nIndex2)==BLANK) {
			graph.AddArc(nIndex1,nIndex2);
		}
	}
	if (nCol < 13) {	//右边相邻
		int nIndex2 = nIndex1 + 1;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow > 0) {		//上方相邻
		int nIndex2 = nIndex1 - 14;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if (nRow < 9) {		//下方相邻
		int nIndex2 = nIndex1 + 14;
		if (graph.GetVertex(nIndex2) == graph.GetVertex(nIndex1) || graph.GetVertex(nIndex1) == BLANK || graph.GetVertex(nIndex2) == BLANK) {
			graph.AddArc(nIndex1, nIndex2);
		}
	}
}

//深度优先搜索寻找路径
bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1) {
	//得到顶点数
	//int nVexnum = g.GetVexnum();

	//遍历图中nVo行，从0列数到nVexnum列，值为true的点
	for (int nVi = 0; nVi < MAX_VERTEX_NUM; nVi++) {
		if (g.GetArc(nV0, nVi)==true && IsExist(nVi)) {
			Vertex temp = { nVi / 14 , nVi % 14,g.GetVertex(nVi)};
			AddVertex(temp);
			if (m_nCornerNum > 2) {	//如果拐点数大于2则删除该点
				DeleteVertex();
				continue;
			}
			if (nVi != nV1) {
				if (g.GetVertex(nVi) != BLANK ) {	//如果nVi不是空则不能连通
					DeleteVertex();
					continue;
				}
				if (SearchPath(g, nVi, nV1)) {	//如果深度优先搜索有路径则该路径可行
					return true;
				}
			}
			else {
				return true;
			}
		}
	}
	DeleteVertex();	//判断不可行后要把nV0删掉！！！！！！
	return false;
}

//判断新增点是否在路径上
bool CGameLogic::IsExist(int nVi) {
	for (int i = 0; i < m_nVertexNum; i++) {
		if (m_avPath[i].row * 14 + m_avPath[i].col == nVi) {
			return false;
		}
	}
	return true;
}

//判断胜负
bool CGameLogic::IsWin(CGraph graph) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {	
		if (graph.GetVertex(i) != BLANK) {	//判断整个数组是否为空
			return false;
		}
	}
	return true;
}

//判断拐点
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
		if (v1.col + v3.col != 2 * v2.col && v1.row+v3.row !=2*v2.row) {	//判断拐点
			return true;
		}
	}
	return false;
}

//寻找可行路径
bool CGameLogic::SearchValiPath(CGraph& graph) {
	int nVexnum = graph.GetVexnum();			//获取游戏结点数
	for (int i = 0; i < nVexnum; i++) {
		if (graph.GetVertex(i) == BLANK) {		//判断改结点元素是否为空
			continue;
		}
		for (int j = 0; j < nVexnum; j++) {		//寻找相同元素
			if (i != j) {
				if (graph.GetVertex(i) == graph.GetVertex(j)) {
					Vertex temp = { i / 14 ,i % 14,graph.GetVertex(i) };
					AddVertex(temp);			//添加起始点
					if (SearchPath(graph, i, j) == true) {	//寻找是否有路径
						return true;
					}
					DeleteVertex();		//没有路径则删除该起始点
				}
			}
		}
	}
	return false;
}

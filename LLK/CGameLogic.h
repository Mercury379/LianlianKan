#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
private:
	//Vertex m_avPath[4];		//连接路径
	Vertex m_avPath[MAX_VERTEX_NUM];
	int m_nVertexNum;		//连接路径点数
	int m_nCornerNum;		//拐点数
public:
	CGameLogic();
	void InitMap(CGraph &graph);	//初始化游戏地图
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);	//连接判断
	bool LinkInRow(CGraph& graph,Vertex v1,Vertex v2);	//一条线消子
	bool LinkInCol(CGraph& graph, Vertex v1, Vertex v2);//一条线消子
	bool Clear(CGraph& graph, Vertex v1, Vertex v2);	//消子
	bool LineX(CGraph& graph, int nRow, int nCol1, int nCol2);//行两点连接判断
	bool LineY(CGraph& graph, int nCol, int nRow1, int nRow2);//列两点连接判断
	bool OneCornerLink(CGraph& graph, Vertex v1, Vertex v2);	//两条线消子
	bool TwoCornerLink(CGraph& graph, Vertex v1, Vertex v2);	//三条线消字
	void AddVertex(Vertex v);	//添加点进画图路径
	void DeleteVertex();		//删除画图路径点
	int GetVertexPath(Vertex avPath[MAX_VERTEX_NUM]);//获取画图路径
	void UpdateArc(CGraph& graph, int nRow, int nCol);//添加图结构边
	bool SearchPath(CGraph& g, int nV0, int nV1);	//深度优先搜索寻找路径
	bool IsExist(int nVi);	//判断新增点在路径上是否存在
	bool IsWin(CGraph graph);	//判断胜负
	bool IsCorner();	//判断拐点
	bool SearchValiPath(CGraph& graph);	//寻找有效路径
};


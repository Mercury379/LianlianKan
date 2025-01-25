#pragma once
//图数据结构类
class CGraph {
public:
	CGraph();
#define MAX_VERTEX_NUM 140				 //图顶点数
	typedef int Vertices[MAX_VERTEX_NUM];//图顶点
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵
protected:
	Vertices m_Vertices;				//图顶点数组
	int m_nVertexNum;					//图定点数
	AdjMatrix m_AdjMatrix;				//边
	int m_nArcnum;						//邻接矩阵
public:
	void InitGraph();					//初始化图
	int AddVertex(int nInfo);			//添加顶点
	void AddArc(int nIndex1, int nIndex2);//添加边
	int GetVertex(int nIndex);			//获取顶点号
	void TestGraph();					//调试图
	bool GetArc(int nIndex1, int nIndex2);//获取边
	void UpdateVertex(int nIndex, int nInfo);//更新顶点
	int GetVexnum();					//获取图顶点数
};


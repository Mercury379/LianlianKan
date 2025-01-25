#pragma once
#include"CGameLogic.h"
#include"CGraph.h"

class CGameControl
{
private:
	//int m_anMap[10][14];
	CGameLogic gamelogic;//游戏逻辑判断
	CGraph m_graph;		//游戏地图
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;	//选中的第二个点
public:
	void StartGame();	//开始游戏
	void SetFirstPoint(int nRow, int nCol);	//设置选中的第一个点
	void SetSecPoint(int nRow, int nCol);	//设置选中的第二个点
	int GetElement(int nRow, int nCol);		//获取地图中的元素
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVertex);//连接判断
	void Clear();	//消除两个点
	Vertex GetFirstPoint();	//获取选中的第一个点
	Vertex GetSecPoint();	//获取选中的第二个点
	bool Win();	//胜负判断
	void Flush();	//重排
	bool Help(Vertex avPath[], int& nVexnum);	//提示
};


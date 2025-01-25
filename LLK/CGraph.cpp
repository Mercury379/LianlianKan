#include "pch.h"
#include"CGraph.h"
#include<fstream>
#include<iostream>
using namespace std;

CGraph::CGraph() {
	InitGraph();
}

//初始化图
void CGraph::InitGraph() {
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
	}
	//初始化边
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
	m_nVertexNum = 0;
}

//添加顶点
int CGraph::AddVertex(int nInfo) {
	if (m_nVertexNum >= MAX_VERTEX_NUM) {
		return -1;
	}
	m_Vertices[m_nVertexNum] = nInfo;
	m_nVertexNum++;
	return m_nVertexNum;
}

//添加边
void CGraph::AddArc(int nInex1, int nInex2) {
	m_AdjMatrix[nInex1][nInex2] = true;
	m_AdjMatrix[nInex2][nInex1] = true;
}

int CGraph::GetVertex(int nIndex) {
	return m_Vertices[nIndex];
}

//测试图
void CGraph::TestGraph() {
	ofstream fout;
	fout.open("D:\\数据结构与算法综合实验\\欢乐连连看游戏\\test.txt");
	if (!fout) {
		cout << "文件打开失败！" << endl;
	}
	char buf[256];
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		int pos = 0;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			if (m_AdjMatrix[i][j] == true) {
				buf[pos++] = '1';
			}
			else {
				buf[pos++] = '0';
			}
		}
		buf[pos] = '\0';
		fout << buf<< endl;
	}
	fout.close();
}

//获取边
bool CGraph::GetArc(int nIndex1, int nIndex2) {
	return m_AdjMatrix[nIndex1][nIndex2];
}

//更新点
void CGraph::UpdateVertex(int nIndex, int nInfo) {
	m_Vertices[nIndex] = nInfo;
}

//得到图顶点数
int CGraph::GetVexnum() {
	return m_nVertexNum;
}
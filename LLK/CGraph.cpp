#include "pch.h"
#include"CGraph.h"
#include<fstream>
#include<iostream>
using namespace std;

CGraph::CGraph() {
	InitGraph();
}

//��ʼ��ͼ
void CGraph::InitGraph() {
	//��ʼ������
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
	}
	//��ʼ����
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
	m_nVertexNum = 0;
}

//��Ӷ���
int CGraph::AddVertex(int nInfo) {
	if (m_nVertexNum >= MAX_VERTEX_NUM) {
		return -1;
	}
	m_Vertices[m_nVertexNum] = nInfo;
	m_nVertexNum++;
	return m_nVertexNum;
}

//��ӱ�
void CGraph::AddArc(int nInex1, int nInex2) {
	m_AdjMatrix[nInex1][nInex2] = true;
	m_AdjMatrix[nInex2][nInex1] = true;
}

int CGraph::GetVertex(int nIndex) {
	return m_Vertices[nIndex];
}

//����ͼ
void CGraph::TestGraph() {
	ofstream fout;
	fout.open("D:\\���ݽṹ���㷨�ۺ�ʵ��\\������������Ϸ\\test.txt");
	if (!fout) {
		cout << "�ļ���ʧ�ܣ�" << endl;
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

//��ȡ��
bool CGraph::GetArc(int nIndex1, int nIndex2) {
	return m_AdjMatrix[nIndex1][nIndex2];
}

//���µ�
void CGraph::UpdateVertex(int nIndex, int nInfo) {
	m_Vertices[nIndex] = nInfo;
}

//�õ�ͼ������
int CGraph::GetVexnum() {
	return m_nVertexNum;
}
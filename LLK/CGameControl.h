#pragma once
#include"CGameLogic.h"
#include"CGraph.h"

class CGameControl
{
private:
	//int m_anMap[10][14];
	CGameLogic gamelogic;//��Ϸ�߼��ж�
	CGraph m_graph;		//��Ϸ��ͼ
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;	//ѡ�еĵڶ�����
public:
	void StartGame();	//��ʼ��Ϸ
	void SetFirstPoint(int nRow, int nCol);	//����ѡ�еĵ�һ����
	void SetSecPoint(int nRow, int nCol);	//����ѡ�еĵڶ�����
	int GetElement(int nRow, int nCol);		//��ȡ��ͼ�е�Ԫ��
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVertex);//�����ж�
	void Clear();	//����������
	Vertex GetFirstPoint();	//��ȡѡ�еĵ�һ����
	Vertex GetSecPoint();	//��ȡѡ�еĵڶ�����
	bool Win();	//ʤ���ж�
	void Flush();	//����
	bool Help(Vertex avPath[], int& nVexnum);	//��ʾ
};


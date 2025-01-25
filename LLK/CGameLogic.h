#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
private:
	//Vertex m_avPath[4];		//����·��
	Vertex m_avPath[MAX_VERTEX_NUM];
	int m_nVertexNum;		//����·������
	int m_nCornerNum;		//�յ���
public:
	CGameLogic();
	void InitMap(CGraph &graph);	//��ʼ����Ϸ��ͼ
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);	//�����ж�
	bool LinkInRow(CGraph& graph,Vertex v1,Vertex v2);	//һ��������
	bool LinkInCol(CGraph& graph, Vertex v1, Vertex v2);//һ��������
	bool Clear(CGraph& graph, Vertex v1, Vertex v2);	//����
	bool LineX(CGraph& graph, int nRow, int nCol1, int nCol2);//�����������ж�
	bool LineY(CGraph& graph, int nCol, int nRow1, int nRow2);//�����������ж�
	bool OneCornerLink(CGraph& graph, Vertex v1, Vertex v2);	//����������
	bool TwoCornerLink(CGraph& graph, Vertex v1, Vertex v2);	//����������
	void AddVertex(Vertex v);	//��ӵ����ͼ·��
	void DeleteVertex();		//ɾ����ͼ·����
	int GetVertexPath(Vertex avPath[MAX_VERTEX_NUM]);//��ȡ��ͼ·��
	void UpdateArc(CGraph& graph, int nRow, int nCol);//���ͼ�ṹ��
	bool SearchPath(CGraph& g, int nV0, int nV1);	//�����������Ѱ��·��
	bool IsExist(int nVi);	//�ж���������·�����Ƿ����
	bool IsWin(CGraph graph);	//�ж�ʤ��
	bool IsCorner();	//�жϹյ�
	bool SearchValiPath(CGraph& graph);	//Ѱ����Ч·��
};


#pragma once
//ͼ���ݽṹ��
class CGraph {
public:
	CGraph();
#define MAX_VERTEX_NUM 140				 //ͼ������
	typedef int Vertices[MAX_VERTEX_NUM];//ͼ����
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�ڽӾ���
protected:
	Vertices m_Vertices;				//ͼ��������
	int m_nVertexNum;					//ͼ������
	AdjMatrix m_AdjMatrix;				//��
	int m_nArcnum;						//�ڽӾ���
public:
	void InitGraph();					//��ʼ��ͼ
	int AddVertex(int nInfo);			//��Ӷ���
	void AddArc(int nIndex1, int nIndex2);//��ӱ�
	int GetVertex(int nIndex);			//��ȡ�����
	void TestGraph();					//����ͼ
	bool GetArc(int nIndex1, int nIndex2);//��ȡ��
	void UpdateVertex(int nIndex, int nInfo);//���¶���
	int GetVexnum();					//��ȡͼ������
};


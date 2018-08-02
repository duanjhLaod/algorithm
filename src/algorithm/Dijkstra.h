/************************************************************/
/*					�����˳�����ͼ�㷨ʵ��					*/
/*	Dijkstra ���·��*/
/* Kruskal Prim ��С������*/
/* ���鼯 Union-Find set*/
/************************************************************/
#pragma once

#include <stdio.h>
#include <vector>

using namespace std;

namespace DjhAlg
{
	struct edge  //��
	{
		int u, v, w; //�ߵĶ��㡢Ȩֵ
		edge() {}
		edge(int x, int y, int z)
		{
			u = x;
			v = y;
			w = z;
		}
	};

	//���鼯
	class UnionFindSet
	{
	private:
		vector<int> parent; // �ڵ�index-->root, ���rootΪ<0,�����ڵ�Ϊroot�ڵ�
	public:
		UnionFindSet(int n);
		~UnionFindSet();

		int Find(int x); //����x��root
		void Union(int r1, int r2); //�ϲ�root�ڵ�r1��r2
	};

	struct DijkstraNode
	{
		int index; //�ڵ���
		int distance; //�ߵ�Ȩ��

		DijkstraNode() {};
		DijkstraNode(int src, int y) {
			index = src;
			distance = y;
		}

		//Ҫʹ��STL�����ȶ���,��Ҫ����<
		bool operator < (const DijkstraNode &a) const
		{
			if (distance == a.distance)
				return index >= a.index;
			return distance>=a.distance; //��ΪҪʵ����С���ȶ���
		}
	};

	//nΪ������, edgesΪ����ɵ�����
	void Kruskal(vector<edge> &edges, int n);
	void Prim();

	/**
	*�Ͽ�˹���㷨�����˹�����ȵ�˼��,�����ڼ���㵽������С���ʱ���Ƚ϶�,�����������,����ñ�����ʽ��ʱ�临�Ӷ�ΪO(n2),���ʹ������С�ѵ����ݽṹ���Խ�����O(nlgn+E)
	*source Դ������֮��Ĺ�ϵ��ע��,dijkstra���ܴ���Ȩ�رߣ�
	*s��ʼ��
	*disΪ���������,����ÿ���±��ʾ��Դ�㵽�������̾���(dis�ĳ���Ӧ�ô��ڵ��ڵ����n+1)
	*n Ϊ�ڵ���
	*/
	void Dijkstra(vector<vector<DijkstraNode>> &source,int s, int dis[], int n);

	/**
	*������-�����㷨,��ͼ��v-1�α���,��ÿ���������ɳڲ���,�����Եó����,ͬʱ�����ҳ�ͼ���Ƿ���ڸ�Ȩ�ػ�·
	*edges Ϊ���б�
	*v ������
	*e ������
	*s ������
	*dis ���������
	*/
	bool BellmanFord(vector<edge> &edges, int v, int e, int dis[], int s);

	void test_BellnanFord();
}

/************************************************************/
/*					包括了常见的图算法实现					*/
/*	Dijkstra 最短路径*/
/* Kruskal Prim 最小生成树*/
/* 并查集 Union-Find set*/
/************************************************************/
#pragma once

#include <stdio.h>
#include <vector>

using namespace std;

namespace DjhAlg
{
	struct edge  //边
	{
		int u, v, w; //边的顶点、权值
		edge() {}
		edge(int x, int y, int z)
		{
			u = x;
			v = y;
			w = z;
		}
	};

	//并查集
	class UnionFindSet
	{
	private:
		vector<int> parent; // 节点index-->root, 如果root为<0,表明节点为root节点
	public:
		UnionFindSet(int n);
		~UnionFindSet();

		int Find(int x); //查找x的root
		void Union(int r1, int r2); //合并root节点r1和r2
	};

	struct DijkstraNode
	{
		int index; //节点编号
		int distance; //边的权重

		DijkstraNode() {};
		DijkstraNode(int src, int y) {
			index = src;
			distance = y;
		}

		//要使用STL的优先队列,需要重载<
		bool operator < (const DijkstraNode &a) const
		{
			if (distance == a.distance)
				return index >= a.index;
			return distance>=a.distance; //因为要实现最小优先队列
		}
	};

	//n为顶点数, edges为边组成的数组
	void Kruskal(vector<edge> &edges, int n);
	void Prim();

	/**
	*迪克斯切算法，用了广度优先的思想,但是在计算点到附近最小点的时候会比较多,对于这种情况,如果用暴力方式，时间复杂度为O(n2),如果使用如最小堆等数据结构可以降低至O(nlgn+E)
	*source 源边两点之间的关系（注意,dijkstra不能处理负权重边）
	*s起始点
	*dis为输出的数组,里面每个下标表示从源点到各点的最短距离(dis的长度应该大于等于点个数n+1)
	*n 为节点数
	*/
	void Dijkstra(vector<vector<DijkstraNode>> &source,int s, int dis[], int n);

	/**
	*贝尔曼-福特算法,对图做v-1次遍历,对每个顶点做松弛操作,最后可以得出结果,同时还能找出图中是否存在负权重环路
	*edges 为边列表
	*v 顶点数
	*e 边数量
	*s 出发点
	*dis 点距离数组
	*/
	bool BellmanFord(vector<edge> &edges, int v, int e, int dis[], int s);

	void test_BellnanFord();
}

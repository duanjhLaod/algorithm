#include "Dijkstra.h"
#include <algorithm>
#include <queue>

namespace DjhAlg
{
	UnionFindSet::UnionFindSet(int n)
	{
		this->parent = vector<int>(n);
		for (int i = 0; i < n; ++i)
		{
			this->parent[i] = -1;
		}
	}

	UnionFindSet::~UnionFindSet()
	{
		if (this->parent.size()>0)
		{
			this->parent = vector<int>(0);
		}
	}

	int UnionFindSet::Find(int x)
	{
		int s = x;
		while (this->parent[s] >= 0) //�ҵ�root��
		{
			s = this->parent[s];
		}

		while (s != x) //����������·��ѹ��,ֱ����x·���ϵĽڵ��parent��ֱ����Ϊroot
		{
			int tmp = parent[x];
			parent[x] = s;
			x = tmp;
		}

		return s;
	}

	void UnionFindSet::Union(int r1, int r2)
	{
		int p1 = this->Find(r1);
		int p2 = this->Find(r2);

		if (p1 != p2)
		{
			//�ϲ�������һ������,�ڵ��ٵ��������ڵ�����
			if (this->parent[p1] > this->parent[p2])
			{
				this->parent[p2] += this->parent[p1];
				this->parent[p1] = p2;
			}
			else
			{
				this->parent[p1] += this->parent[p2];
				this->parent[p2] = p1;
			}
		}
	}

	bool cmp(edge a, edge b) //ʵ�ִ�С��������ıȽϺ���
	{
		return a.w <= b.w;
	}

	void Kruskal(vector<edge> &edges, int n)
	{
		int sumweight = 0;
		int num = 0;
		int u, v;

		sort(edges.begin(),edges.end(), cmp); //������
		UnionFindSet ufset(n);
		for (vector<edge>::iterator it = edges.begin(); it != edges.end(); ++it)
		{
			u = it->u;
			v = it->v;
			if (ufset.Find(u) != ufset.Find(v)) //���u��v����һ���Ӽ�
			{
				sumweight += it->w;
				++num;

				ufset.Union(u, v);
				printf("%d %d %d\n", u, v, it->w);
			}

			if(num>=n-1) //�Ѿ��ҵ�n-1������
				break;
		}

		printf("total weight of MST is %d\n", sumweight);
	}

	void test_Kruskal()
	{

	}

	void Dijkstra(vector<vector<DijkstraNode>> &source,int s, int dis[], int n)
	{
		for (int i = 0; i <= n; ++i)
		{
			dis[i] = INT_MAX;
		}
		dis[s] = 0;

		std::priority_queue<DijkstraNode> nq;
		nq.push(DijkstraNode(s, dis[s]));

		while (nq.size()>0)
		{
			DijkstraNode node = nq.top();
			nq.pop();

			for (vector<DijkstraNode>::iterator it = source[node.index].begin(); it != source[node.index].end(); ++it)
			{
				if (dis[it->index] > dis[node.index] + it->distance)
				{
					dis[it->index] = dis[node.index] + it->distance;
					nq.push(DijkstraNode(it->index, it->distance));
				}
			}
		}
	}

	bool BellmanFord(vector<edge> &edges, int v, int e, int dis[], int s)
	{
		for (int i = 1; i <= v; ++i)
		{
			dis[i] = INT_MAX;
		}
		dis[s] = 0;

		for (int i = 1; i < v; ++i)
		{
			for (int j = 0; j < e; ++j)
			{
				if (dis[edges[j].v] > dis[edges[j].u] + edges[j].w)
				{
					dis[edges[j].v] = dis[edges[j].u] + edges[j].w;
				}
			}
		}

		for (int j = 0; j < e; ++j)
		{
			if (dis[edges[j].v] > dis[edges[j].u] + edges[j].w)
			{
				return false;
			}
		}

		return true;
	}

	void test_BellnanFord()
	{
		int v = 6;
		int e = 10;
		int dis[7];
		vector<edge> edges(10);
		edges[0] = edge(1, 2, 1);
		edges[1] = edge(1, 4, -4);
		edges[2] = edge(2, 3, 2);
		edges[3] = edge(2, 5, 7);
		edges[4] = edge(2, 6, 5);
		edges[5] = edge(3, 6, 10);
		edges[6] = edge(4, 2, 2);

		edges[7] = edge(5, 1, -1);
		edges[8] = edge(5, 4, 3);
		edges[9] = edge(6, 3, -8);

		bool flag = BellmanFord(edges, v, e, dis, 1);

		printf("Is there have a answer?%s\n",flag ? "yes" : "no");

		printf("the dis array:");
		for (int i = 1; i < 7; ++i)
		{
			printf("%d ", dis[i]);
		}
		printf("\n");
	}
}
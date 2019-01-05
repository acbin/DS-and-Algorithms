/*
题目描述

假设有向图G的邻接矩阵存储结构为MGraph，邻接表存储结构为AdjGraph。根据输入建立图G的邻接矩阵存储，

实现MGraph的成员函数:

AdjGraph &ToAdjGraph()

将其转换为邻接表存储并返回。

为AdjGraph添加成员函数，计算各顶点的入度并输出。

输入

测试次数

每组测试数据如下:

顶点数n

n个顶点

弧数m

m条弧信息

输出

对每组测试数据，输出各顶点入度

样例输入

2
4
A B C D
4
A B
A C
B D
C D
6
1 2 3 4 5 6
8
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5


样例输出

A 0
B 1
C 1
D 2
1 0
2 2
3 1
4 2
5 3
6 0
*/

#include <iostream>
#define MAXSIZE 10

using namespace std;
typedef struct mgraph
{
	char verx[MAXSIZE];
	int arcs[MAXSIZE][MAXSIZE];
	int numEdges, numVexs;
} mgraph, *MGraph;

typedef struct EdgeNode
{
	int adjvex;
	struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode
{
	char data;
	EdgeNode *firstEdge;
} VertexNode, AdjList[MAXSIZE];

typedef struct
{
	AdjList adjlist;
	int numEdges, numVexs;
} adjgraph, *AdjGraph;

void createMGraph(MGraph g)
{
	int i, j;
	char c1, c2;
	int row, col;
	for (i = 0; i < MAXSIZE; ++i)
	{
		for (j = 0; j < MAXSIZE; ++j)
		{
			g->arcs[i][j] = 0;
		}
	}
	cin >> g->numVexs;
	for (i = 0; i < g->numVexs; ++i)
	{
		cin >> g->verx[i];
	}
	cin >> g->numEdges;
	for (i = 0; i < g->numEdges; ++i)
	{
		cin >> c1 >> c2;
		for (j = 0; j < g->numEdges; ++j)
		{
			if (c1 == g->verx[j])
			{
				row = j;
			}
			if (c2 == g->verx[j])
			{
				col = j;
			}
		}
		g->arcs[row][col] = 1;
	}
}

void ToAdjGraph(MGraph g, AdjGraph ag)
{
	EdgeNode *e;
	ag->numVexs = g->numVexs;
	ag->numEdges = g->numEdges;
	int i, j;
	for (i = 0; i < ag->numVexs; ++i)
	{
		ag->adjlist[i].data = g->verx[i];
		ag->adjlist[i].firstEdge = NULL;
	}
	for (i = 0; i < ag->numEdges; ++i)
	{
		for (j = 0; j < ag->numEdges; ++j)
		{
			if (g->arcs[i][j] == 1)
			{
				e = new EdgeNode;
				e->next = ag->adjlist[i].firstEdge;
				e->adjvex = j;
				ag->adjlist[i].firstEdge = e;
			}
		}
	}
	return;
}

void countIndegree(AdjGraph ag)
{
	int i, j;
	int a[MAXSIZE] = {0};
	for (i = 0; i < ag->numVexs; ++i)
	{
		EdgeNode *t = ag->adjlist[i].firstEdge;
		while (t)
		{
			for (j = 0; j < ag->numVexs; ++j)
			{
				if (t->adjvex == j)
				{
					++a[j];
				}
			}
			t = t->next;
		}
	}
	for (i = 0; i < ag->numVexs; ++i)
	{
		cout << ag->adjlist[i].data << ' ' << a[i] << endl;
	}
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		mgraph g;
		createMGraph(&g);
		adjgraph ag;
		ToAdjGraph(&g, &ag);
		countIndegree(&ag);
	}
	return 0;
}

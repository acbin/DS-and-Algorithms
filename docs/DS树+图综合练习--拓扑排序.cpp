
//DS树+图综合练习--拓扑排序
/*
题目描述

已知有向图，顶点从0开始编号，求它的求拓扑有序序列。
拓扑排序算法：给出有向图邻接矩阵
1.逐列扫描矩阵，找出入度为0且编号最小的顶点v
2.输出v，并标识v已访问
3.把矩阵第v行全清0
重复上述步骤，直到所有顶点输出为止
输入

第一行输入一个整数t，表示有t个有向图
第二行输入n，表示图有n个顶点
第三行起，输入n行整数，表示图对应的邻接矩阵
以此类推输入下一个图的顶点数和邻接矩阵
输出

每行输出一个图的拓扑有序序列
样例输入

2
5
0 1 0 1 1
0 0 1 0 0
0 0 0 0 1
0 0 1 0 0
0 0 0 0 0
7
0 0 0 0 0 0 0
1 0 1 1 0 0 0
1 0 0 0 0 0 0
1 0 1 0 0 0 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 0 0 1 0 1 0
样例输出

0 1 3 2 4 
4 6 5 1 3 2 0 
*/
#include <iostream>
using namespace std;
//常量
const int MAX_VERT = 10;
//图的结构体
struct Graphic
{
	int vertNum;
	int VertValue[MAX_VERT];
	int AdjMatrix[MAX_VERT][MAX_VERT];
	bool visited[MAX_VERT];
};
//图初始化
void initGraphic(Graphic &G, int n)
{
	G.vertNum = n;
	int i, j;
	//输入邻接矩阵
	for (i = 0; i < G.vertNum; i++)
	{
		for (j = 0; j < G.vertNum; j++)
			cin >> G.AdjMatrix[i][j];
	}
	//顶点赋值
	for (i = 0; i < G.vertNum; i++)
	{
		G.VertValue[i] = i;
		G.visited[i] = false;
	}
}
//拓扑排序
void TopoSort(Graphic G)
{
	int i, j, k, m;
	for (m = 0; m < G.vertNum; m++)
	{
		for (i = 0; i < G.vertNum; i++)
		{
			for (j = 0; j < G.vertNum; j++)
			{
				if (G.AdjMatrix[j][i])
					break;
			}
			if (j == G.vertNum && !G.visited[i])
				break;
		}
		cout << i << " ";
		for (k = 0; k < G.vertNum; k++)
			G.AdjMatrix[i][k] = 0;
		G.visited[i] = true;
	}
	cout << endl;
}
//主函数
int main()
{
	int t, n, i;
	Graphic G[2];
	//文本输入
	//freopen("cin2.txt", "r", stdin);
	//输入有向图个数
	cin >> t;
	for (i = 0; i < t; i++)
	{
		//输入顶点个数
		cin >> n;
		//图初始化
		initGraphic(G[i], n);
		//拓扑排序
		TopoSort(G[i]);
	}
	//结束
	return 0;
}
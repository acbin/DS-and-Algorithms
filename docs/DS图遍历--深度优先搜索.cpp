
//DS图遍历--深度优先搜索
/*
题目描述

给出一个图的邻接矩阵，对图进行深度优先搜索，图的结点编号从0到n-1

输入

第一行输入t，表示有t个测试实例

第二行输入n，表示第1个图有n个结点

第三行起，每行输入邻接矩阵的一行，以此类推输入n行

第i个结点与其他结点如果相连则为1，无连接则为0，数据之间用空格隔开

以此类推输入下一个示例

输出

每行输出一个图的深度优先搜索结果，结点编号之间用空格隔开

样例输入

2
4
0 0 1 1
0 0 1 1
1 1 0 1
1 1 1 0
5
0 0 0 1 1
0 0 1 0 0
0 1 0 1 1
1 0 1 0 0
1 0 1 0 0
样例输出

0 2 1 3 
0 3 2 1 4 
*/
#include <iostream>
using namespace std;

const int MaxLen = 20;

class Map
{
  private:
    bool Visit[MaxLen];
    int Matrix[MaxLen][MaxLen];
    int Vexnum;
    void DFS(int v);

  public:
    void SetMatrix(int vnum, int mx[MaxLen][MaxLen]);
    void DFSTraverse();
};

//设置邻接矩阵
void Map::SetMatrix(int vnum, int mx[MaxLen][MaxLen])
{
    int i, j;
    Vexnum = vnum;
    for (i = -1; ++i < MaxLen;)
        for (j = -1; ++j < MaxLen;)
            Matrix[i][j] = 0;
    for (i = -1; ++i < Vexnum;)
        for (j = -1; ++j < Vexnum;)
            Matrix[i][j] = mx[i][j];
}

void Map::DFSTraverse()
{
    int v;
    //将所有的Visit赋值为false
    for (v = -1; ++v < Vexnum;)
        Visit[v] = false;
    //开始逐个遍历未访问结点
    for (v = -1; ++v < Vexnum;)
    {
        if (!Visit[v])
        {
            DFS(v);
        } //if
    }     //for
    cout << endl;
}

void Map::DFS(int v)
{
    int w, i, k;
    Visit[v] = true;
    //输出访问的结点
    cout << v << " ";
    //初始化AdjVex
    int *AdjVex = new int[Vexnum];
    for (i = -1; ++i < Vexnum;)
        AdjVex[i] = -1;
    //开始遍历这个顶点能到达的邻接顶点
    k = 0;
    for (i = -1; ++i < Vexnum;)
    {
        if (Matrix[v][i])
        {
            //把这个顶点的邻接顶点赋值给AdjVex
            AdjVex[k++] = i;
        } //if
    }     //for
          //开始逐个遍历邻接结点，此处用了递归，会把将要遍历的结点的Visit赋值为true
    i = 0;
    for (; w = AdjVex[i++], w != -1;)
    {
        if (!Visit[w])
        {
            DFS(w);
        } //if
    }     //for
    delete[] AdjVex;
}

int main()
{
    int t, n, i, j;
    Map m;

    cin >> t;
    while (t--)
    {
        cin >> n;
        int mx[20][20];
        for (i = -1; ++i < n;)
            for (j = -1; ++j < n;)
                cin >> mx[i][j];
        m.SetMatrix(n, mx);
        m.DFSTraverse();
    }
    return 0;
}

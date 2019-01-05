//DS图应用--最短路径
/*
给出一个图的邻接矩阵，再给出指定顶点v0，求顶点v0到其他顶点的最短路径
代码框架如下：






输入

第一行输入t，表示有t个测试实例

第二行输入n，表示第1个图有n个结点

第三行起，每行输入邻接矩阵的一行，以此类推输入n行

第i个结点与其他结点如果相连则为1，无连接则为0，数据之间用空格隔开

第四行输入v0，表示求v0到其他顶点的最短路径距离

以此类推输入下一个示例

输出

每行输出v0到某个顶点的最短距离和最短路径

每行格式：v0编号-其他顶点编号----[最短路径]，具体请参考示范数据

样例输入

1
5
0 5 0 7 15
0 0 5 0 0
0 0 0 0 1
0 0 2 0 0
0 0 0 0 0
0
样例输出

0-1-5----[0 1 ]
0-2-9----[0 3 2 ]
0-3-7----[0 3 ]
0-4-10----[0 3 2 4 ]
*/
#include <iostream>
using namespace std;

const int MaxLen = 20;
const int MaxDist = 9999;

class Map
{
  private:
    int Matrix[MaxLen][MaxLen];
    int Vexnum;

  public:
    void SetMatrix(int vnum, int mx[MaxLen][MaxLen]);
    void ShortestPath_DIJ(int v0);
};

void Map::SetMatrix(int vnum, int mx[MaxLen][MaxLen])
{ //给矩阵赋值
    int i, j;
    Vexnum = vnum; //定点数量赋值
                   //先给所有的矩阵初始化为9999
    for (i = -1; ++i < MaxLen;)
        for (j = -1; ++j < MaxLen;)
            Matrix[i][j] = MaxDist;
    //把mx矩阵的内容赋给Matrix
    for (i = -1; ++i < Vexnum;)
        for (j = -1; ++j < Vexnum;)
        {
            if (mx[i][j])
                Matrix[i][j] = mx[i][j];
        }
}

void Map::ShortestPath_DIJ(int v0)
{
    int i, j, v, w, min;
    int *dist = new int[Vexnum];
    bool *final = new bool[Vexnum];
    int path[MaxLen][MaxLen];
    int len[MaxLen];
    //给final初始化为false,将Matrix指定行的值赋给dist
    //path数组全部赋值为-1
    for (i = -1; ++i < Vexnum;)
    {
        final[i] = false;
        dist[i] = Matrix[v0][i];
        for (j = -1; ++j < MaxLen;)
            path[i][j] = -1;
    }

    //如果dist中的值小于9999的话
    //path指定列赋值为v0
    //path的左上右下对角线赋值为v
    //指定顶点的长度赋值为Vexnum
    for (v = -1; ++v < Vexnum;)
    {
        //path的作用是一个顶点有一行，这一行里从左到右表示依次到达的结点
        //例如第二行下标为1
        //0 2 3 1表示从0到2到3到1
        //若为最终结果即为从0到1的所有路径中的最短路径
        //0行则没必要标出了。
        //path的赋值是从列开始的
        //这个时候dist[0]=9999
        if (dist[v] < MaxDist)
        {
            path[v][v0] = v0;
            path[v][v] = v;
        }
        len[v] = Vexnum;
    }

    //dist指定位置的值赋值为0
    //v0设置为已经访问
    dist[v0] = 0;
    final[v0] = true;

    //最小值等于9999
    //判断是否未访问
    //若未访问，如果dist[w]小于最小值，就记录w和dist[w],分别赋给v和min
    //v位置为最小值的位置，设定为true
    //如果final[w]未访问且最小值加上矩阵vw位置的值仍然小于dist[w]
    //dist[w]取值min+Matrix[v][w]
    //然后领把v行的path值赋给w行
    //在w行末尾加个w
    //w行的长度等于v行加1
    for (i = 0; ++i < Vexnum;)
    {   //跳过0
        //找到dist中的未被标记为true的最小值，然后标记为true，然后遍历邻接结点
        min = MaxDist;
        for (w = -1; ++w < Vexnum;)
        {
            if (!final[w])
                if (dist[w] < min)
                {
                    v = w;
                    min = dist[w];
                } //if
        }         //for
        final[v] = true;
        for (w = -1; ++w < Vexnum;)
        {
            //min+Matrix[v][w]<dist[w]有这个判断的原因是
            //比如我想从A点到B点，它的权值为30
            //但是我从A点先到C点，再到B点，它的权值和为25
            //那这样的话明显是先经过C点再到B点这个路径更好
            //!final[w]是遍历其余的为遍历过的结点，避免与上一个已访问过的结点遍历
            if (!final[w] && (min + Matrix[v][w] < dist[w]))
            {
                dist[w] = min + Matrix[v][w];
                for (j = -1; ++j < len[v];)
                {
                    //赋值的原因是从这个路径path[v](0-XXX-v)再到(w)能获得更短的路径
                    path[w][j] = path[v][j];
                } //for
                  //在行尾加上当前结点，即从(0-XXX-v-w)
                path[w][j] = w;
                len[w] = len[v] + 1;
            } //if
        }     //for
    }         //for

    //输出
    for (i = -1; ++i < Vexnum;)
    {
        if (i != v0)
        {
            cout << v0 << "-" << i << "-" << dist[i] << "-";
            cout << "---[";
            for (j = -1; ++j < MaxLen;)
            {
                if (path[i][j] != -1)
                    cout << path[i][j] << " ";
            } //for
            cout << "]" << endl;
        } //if
    }     //for
    delete[] dist;
    delete[] final;
}

int main()
{
    int i, j, k, t;
    int vnum, v0;
    int mx[MaxLen][MaxLen];
    Map myMap;
    cin >> t;
    for (k = 0; k < t; k++)
    {
        for (i = 0; i < MaxLen; i++)
            for (j = 0; j < MaxLen; j++)
                mx[i][j] = 0;
        cin >> vnum;
        for (i = -1; ++i < vnum;)
            for (j = -1; ++j < vnum;)
                cin >> mx[i][j];
        myMap.SetMatrix(vnum, mx);
        cin >> v0;
        myMap.ShortestPath_DIJ(v0);
    }
    return 0;
}

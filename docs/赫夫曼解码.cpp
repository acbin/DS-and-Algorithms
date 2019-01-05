/*
已知赫夫曼编码算法和程序，在此基础上进行赫夫曼解码
在赫夫曼树的类定义中增加了一个公有方法：
	int  Decode(const string codestr, char txtstr[]);	//输入编码串codestr，输出解码串txtstr
该方法如果解码成功则返回1，解码失败则返回-1，本程序增加宏定义ok表示1，error表示-1
解码方法的代码框架如下：

输入

第一行输入t，表示有t个测试实例
第二行先输入n，表示第1个实例有n个权值，接着输入n个权值，权值全是小于1万的正整数
第三行输入n个字母，表示与权值对应的字符
第四行输入k，表示要输入k个编码串
第五行起输入k个编码串
以此类推输入下一个示例
输出

每行输出解码后的字符串，如果解码失败直接输出字符串“error”，不要输出部分解码结果

样例输入

2
5 15 4 4 3 2
A B C D E
3
11111
10100001001
00000101100
4 7 5 2 4
A B C D
3
1010000
111011
111110111
样例输出

AAAAA
ABEAD
error
BBAAA
error
DCD
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define ok 1
#define error -1
#include <stdio.h>

const int MaxW = 9999;

class HuffNode
{
  public:
    int weight;     //权值
    int parent;     //父结点下标
    int leftchild;  //左孩子下标
    int rightchild; //右孩子下标
    char data;
};

class HuffMan
{
  private:
    void MakeTree();
    void SelectMin(int pos, int *s1, int *s2);

  public:
    int len;
    int lnum;
    HuffNode *huffTree;
    string *huffCode;
    void MakeTree(int n, int wt[], char data[]);
    void Coding();
    void Destroy();
    int Decode(const string codestr, char txtstr[]); //输入编码串codestr，输出解码串txtstr
};

void HuffMan::MakeTree()
{
    int i, s1, s2;
    for (i = lnum + 1; i <= len; i++)
    {
        SelectMin(i - 1, &s1, &s2);
        huffTree[s1].parent = i;
        huffTree[s2].parent = i;
        huffTree[i].leftchild = s1;
        huffTree[i].rightchild = s2;
        huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
    } //for
} //MakeTree

void HuffMan::SelectMin(int pos, int *s1, int *s2)
{
    int w1, w2, i;
    w1 = w2 = MaxW;
    *s1 = *s2 = 0;
    for (i = 1; i <= pos; i++)
    {
        if (huffTree[i].weight < w1 && !huffTree[i].parent)
        {
            w2 = w1;
            *s2 = *s1;
            w1 = huffTree[i].weight;
            *s1 = i;
        } //if
        else if (huffTree[i].weight < w2 && !huffTree[i].parent)
        {
            w2 = huffTree[i].weight;
            *s2 = i;
        } //else
    }     //for
} //SelectMin

void HuffMan::MakeTree(int n, int wt[], char data[])
{
    int i;
    lnum = n;
    len = 2 * n - 1;
    huffTree = new HuffNode[2 * n];
    huffCode = new string[lnum + 1];
    for (i = 1; i <= lnum; i++)
    {
        huffTree[i].weight = wt[i - 1];
        huffTree[i].data = data[i - 1];
    }
    for (i = 1; i <= len; i++)
    {
        if (i > n)
            huffTree[i].weight = 0;
        huffTree[i].parent = 0;
        huffTree[i].leftchild = 0;
        huffTree[i].rightchild = 0;
    } //for
    MakeTree();
} //MakeTree

void HuffMan::Coding()
{

    char *cd;
    int i, c, f, start;
    cd = new char[lnum];
    cd[lnum - 1] = '\0';
    for (i = 1; i <= lnum; ++i)
    {
        start = lnum - 1;
        for (c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent)
        {

            if (huffTree[f].leftchild == c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
        } //for
        huffCode[i].assign(&cd[start]);
    } //for
    delete[] cd;
} //Coding

void HuffMan::Destroy()
{
    len = 0;
    lnum = 0;
    delete[] huffTree;
    delete[] huffCode;
}

int HuffMan::Decode(const string codestr, char txtstr[]) //输入编码串codestr，输出解码串txtstr
{
    int i, k, c;
    char ch;
    c = len;
    k = 0;
    for (i = 0; i < codestr.length(); i++)
    {
        ch = codestr[i];
        switch (ch)
        {
        case '0':
            c = huffTree[c].leftchild;
            break;
        case '1':
            c = huffTree[c].rightchild;
            break;
        default:
            return error;
        } //switch
        if (!huffTree[c].leftchild && !huffTree[c].rightchild)
        {
            txtstr[k] = huffTree[c].data;
            k++;
            c = len;
        } //if
        else
        {
            ch = '\0';
        } //else
    }     //for
    if (ch == '\0')
        return error;
    else
        txtstr[k] = '\0';
    return ok;
} //Decode

int main()
{
    int t, n, i, j, k;
    int wt[800];
    char data[800];
    char txtstr[800];
    HuffMan myHuff;
    string codestr;
    cin >> t;
    for (i = 0; i < t; i++)
    {
        cin >> n;
        for (j = 0; j < n; j++)
            cin >> wt[j];
        for (j = 0; j < n; j++)
            cin >> data[j];
        myHuff.MakeTree(n, wt, data);
        myHuff.Coding();
        cin >> k;
        while (k--)
        {
            cin >> codestr;
            if (myHuff.Decode(codestr, txtstr) == 1)
            {
                cout << txtstr << endl;
            }
            else
                cout << "error" << endl;
        }
        myHuff.Destroy();
    }
    return 0;
}
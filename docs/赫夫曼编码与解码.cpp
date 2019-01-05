
/*
1、问题描述

给定n个字符及其对应的权值，构造Huffman树，并进行huffman编码和译（解）码。

构造Huffman树时，要求左子树根的权值小于右子树根的权值。

进行Huffman编码时，假定Huffman树的左分支上编码为‘0’，右分支上编码为‘1’。

2、算法

构造Huffman树算法：

⑴、根据给定的n个权值(w1, w2, …, wn)构成n棵二叉树的集合F={T1, T2, …, Tn}，其中每棵二叉树Ti中只有一个权值为wi的根结点。

⑵、在F中选取两棵根结点的权值最小的树，作为左、右子树构造一棵新的二叉树，且置其根结点的权值为其左、右子树权值之和。

⑶、在F中删除这两棵树，同时将新得到的二叉树加入F中。

(4)、重复⑵, ⑶，直到F只含一棵树为止。

3、Huffman编码算法：

⑴、从Huffman树的每一个叶子结点开始。

⑵、依次沿结点到根的路径，判断该结点是父亲结点的左孩子还是右孩子，如果是左孩子则得到编码‘0’，否则得到编码‘1’，先得到的编码放在后面。

⑶、直到到达根结点，编码序列即为该叶子结点对应的Huffman编码。

4、Huffman译（解）码算法：

⑴、指针指向Huffman树的根结点，取第一个Huffman码。

⑵、如果Huffman码为‘0’，将指针指向当前结点的左子树的根结点；如果Huffman码为‘1’，将指针指向当前结点的右子树的根结点。

⑶、如果指针指向的当前结点为叶子结点，则输出叶子结点对应的字符；否则，取下一个Huffman码，并返回⑵。

⑷、如果Huffman码序列未结束，则返回⑴继续译码。

输入

第一行测试次数

第2行：第一组测试数据的字符个数n，后跟n个字符

第3行：第一组测试数据的字符权重

待编码的字符串s1

编码串s2

其它组测试数据类推

输出

第一行~第n行,第一组测试数据各字符编码值

第n+1行，串s1的编码值

第n+2行，串s2的解码值，若解码不成功，输出error!

其它组测试数据类推

样例输入

2
5 A B C D E
15 4 4 3 2
ABDEC
00000101100
4 A B C D
7 5 2 4
ABAD
1110110
样例输出

A :1
B :010
C :011
D :001
E :000
1010001000011
error!
A :0
B :10
C :110
D :111
0100111
DAC
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
    char str[800];
    cin >> t;
    for (i = 0; i < t; i++)
    {
        cin >> n; //5
        for (j = 0; j < n; j++)
            cin >> data[j]; //A B C D E
        for (j = 0; j < n; j++)
            cin >> wt[j]; //15 4 4 3 2
        myHuff.MakeTree(n, wt, data);
        myHuff.Coding();

        cin >> str;
        int len = strlen(str);
        cin >> codestr;
        for (j = 1; j <= n; j++)
        {
            cout << myHuff.huffTree[j].data << " :";
            cout << myHuff.huffCode[j] << endl;
        }

        for (k = 0; k < len; k++)
        {
            for (j = 1; j <= n; j++)
            {
                if (str[k] == myHuff.huffTree[j].data)
                {
                    cout << myHuff.huffCode[j];
                }
            }
        }
        cout << endl;
        if (myHuff.Decode(codestr, txtstr) == 1)
        {
            cout << txtstr << endl;
        }
        else
            cout << "error!" << endl;
        myHuff.Destroy();
    }
    return 0;
}
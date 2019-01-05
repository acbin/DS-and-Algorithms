/*
计算一棵二叉树的带权路径总和，即求赫夫曼树的带权路径和。
已知一棵二叉树的叶子权值，该二叉树的带权案路径和APL等于叶子权值乘于根节点到叶子的分支数，然后求总和。如下图中，叶子都用大写字母表示，权值对应为：A-7，B-6，C-2，D-3
树的带权路径和 = 7*1 + 6*2 + 2*3 + 3*3 = 34

本题二叉树的创建参考前面的方法
输入

第一行输入一个整数t，表示有t个二叉树

第二行输入一棵二叉树的先序遍历结果，空树用字符‘0’表示，注意输入全是英文字母和0，其中大写字母表示叶子

第三行先输入n表示有n个叶子，接着输入n个数据表示n个叶子的权值，权值的顺序和前面输入的大写字母顺序对应

以此类推输入下一棵二叉树

输出

输出每一棵二叉树的带权路径和

样例输入

2
xA00tB00zC00D00
4 7 6 2 3
ab0C00D00
2 10 20
样例输出

34
40
*/
#include <iostream>
#include <string>
using namespace std;

class BiTreeNode
{
  public:
    char data;
    int weight;
    int weight_sum;
    BiTreeNode *LeftChild;
    BiTreeNode *RightChild;
    BiTreeNode() : LeftChild(NULL), RightChild(NULL) {}
    ~BiTreeNode() {}
};

class BiTree
{
  private:
    BiTreeNode *Root;
    int pos;
    int pos1;
    int num;
    int max_weight;
    string strTree;
    BiTreeNode *CreateBiTree();
    void PreOrder(BiTreeNode *t, int weight[]);
    void WeightingCalculation(BiTreeNode *t, int depth);
    void InOrder(BiTreeNode *t);
    void PostOrder(BiTreeNode *t);

  public:
    BiTree(){};
    ~BiTree(){};
    void CreateTree(string TreeArray);
    void PreOrder(int weight[]);
    void WeightingCalculation();
    void InOrder();
    void PostOrder();
    int getmax_weight_sum();
};

int BiTree::getmax_weight_sum()
{
    return max_weight;
}

void BiTree::CreateTree(string TreeArray)
{
    pos = 0;
    pos1 = 0;
    max_weight = 0;
    strTree.assign(TreeArray);
    Root = CreateBiTree();
}

BiTreeNode *BiTree::CreateBiTree()
{
    BiTreeNode *T;
    char ch;
    ch = strTree[pos++];
    if (ch == '0')
        T = NULL;
    else
    {
        T = new BiTreeNode();
        T->data = ch;
        T->LeftChild = CreateBiTree();
        T->RightChild = CreateBiTree();
    }
    return T;
}

void BiTree::PreOrder(int weight[])
{
    num = 0;
    PreOrder(Root, weight);
}

void BiTree::PreOrder(BiTreeNode *t, int weight[])
{
    if (t)
    {
        if (!t->LeftChild && !t->RightChild)
        {
            t->weight = weight[num++];
        }
        PreOrder(t->LeftChild, weight);
        PreOrder(t->RightChild, weight);
    }
}

void BiTree::InOrder()
{
    InOrder(Root);
}

void BiTree::InOrder(BiTreeNode *t)
{
    if (t)
    {
        InOrder(t->LeftChild);
        cout << t->data;
        InOrder(t->RightChild);
    }
}

void BiTree::WeightingCalculation()
{
    max_weight = 0;
    WeightingCalculation(Root, 0);
}

void BiTree::WeightingCalculation(BiTreeNode *t, int depth)
{
    if (t)
    {
        WeightingCalculation(t->LeftChild, depth + 1);
        WeightingCalculation(t->RightChild, depth + 1);
        if (!t->LeftChild && !t->RightChild)
        {
            max_weight += t->weight * depth;
        }
    }
}

void BiTree::PostOrder()
{
    PostOrder(Root);
}

void BiTree::PostOrder(BiTreeNode *t)
{
    if (t)
    {
        PostOrder(t->LeftChild);
        PostOrder(t->RightChild);
        cout << t->data;
    }
}

int main()
{
    int t, num, i;
    string str;
    BiTree BT;
    int *weight;
    cin >> t;
    while (t--)
    {
        cin >> str;
        cin >> num;
        weight = new int[num];
        for (i = 0; i < num; i++)
        {
            cin >> weight[i];
        }
        BT.CreateTree(str);
        BT.PreOrder(weight);
        BT.WeightingCalculation();
        cout << BT.getmax_weight_sum() << endl;
        delete[] weight;
    }
    return 0;
}
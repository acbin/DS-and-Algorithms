/*
给定一颗二叉树的逻辑结构（先序遍历的结果，空树用字符‘0’表示，例如AB0C00D00），建立该二叉树的二叉链式存储结构
二叉树的每个结点都有一个权值，从根结点到每个叶子结点将形成一条路径，每条路径的权值等于路径上所有结点的权值和。编程求出二叉树的最大路径权值。如下图所示，共有4个叶子即有4条路径，
路径1权值=5 + 4 + 11 + 7 = 27          路径2权值=5 + 4 + 11 + 2 = 22
路径3权值=5 + 8 + 13 = 26                路径4权值=5 + 8 + 4 + 1 = 18
可计算出最大路径权值是27。
该树输入的先序遍历结果为ABCD00E000FG00H0I00，各结点权值为：
A-5，B-4，C-11，D-7，E-2，F-8，G-13，H-4，I-1


输入

第一行输入一个整数t，表示有t个测试数据
第二行输入一棵二叉树的先序遍历，每个结点用字母表示
第三行先输入n表示二叉树的结点数量，然后输入每个结点的权值，权值顺序与前面结点输入顺序对应
以此类推输入下一棵二叉树
输出

每行输出每棵二叉树的最大路径权值，如果最大路径权值有重复，只输出1个

样例输入

2
AB0C00D00
4 5 3 2 6
ABCD00E000FG00H0I00
9 5 4 11 7 2 8 13 4 1
样例输出

11
27
*/
#include<iostream>  
#include<string>  
using namespace std;  
    
class BiTreeNode{  
public:  
    char data;  
    int weight; 
    int weight_sum; 
    BiTreeNode *LeftChild;  
    BiTreeNode *RightChild;  
    BiTreeNode():LeftChild(NULL),RightChild(NULL){}  
    ~BiTreeNode(){}  
};  
    
class BiTree{  
private:  
    BiTreeNode *Root;  
    int pos;  
    int pos1; 
    int max_weight; 
    string strTree;  
    BiTreeNode* CreateBiTree(int weight[]);  
    void PreOrder(BiTreeNode* t); 
    void WeightingCalculation(BiTreeNode* t,int weight);  
    void InOrder(BiTreeNode* t); 
    void PostOrder(BiTreeNode* t);  
public:  
    BiTree(){};  
    ~BiTree(){};  
    void CreateTree(string TreeArray,int weight[]);  
    void PreOrder(); 
    void WeightingCalculation(); 
    void InOrder(); 
    void PostOrder();  
    int getmax_weight_sum(); 
};  
    
int BiTree::getmax_weight_sum() 
{ 
    return max_weight; 
} 
void BiTree::CreateTree(string TreeArray,int weight[])  
{  
    pos=0;  
    pos1=0; 
    max_weight=0; 
    strTree.assign(TreeArray);  
    Root=CreateBiTree(weight);  
    WeightingCalculation();  
}  
  
BiTreeNode* BiTree::CreateBiTree(int weight[])  
{  
    BiTreeNode* T;  
    char ch;  
    int ch1; 
    ch=strTree[pos++]; 
      
    if(ch=='0')  
        T=NULL;  
    else
    {  
        ch1=weight[pos1++]; 
        T=new BiTreeNode();  
        T->data=ch;  
        T->weight=ch1; 
        T->weight_sum=ch1; 
        T->LeftChild=CreateBiTree(weight);  
        T->RightChild=CreateBiTree(weight);  
    } 
    return T;  
}  
    
void BiTree::PreOrder()  
{  
    PreOrder(Root);  
}  
    
void BiTree::PreOrder(BiTreeNode* t)  
{  
    if(t)  
    { 
        cout<<t->data; 
        PreOrder(t->LeftChild);  
        PreOrder(t->RightChild);  
    } 
} 
  
void BiTree::InOrder() 
{ 
    InOrder(Root); 
} 
  
void BiTree::InOrder(BiTreeNode *t) 
{ 
    if(t) 
    { 
        InOrder(t->LeftChild); 
        cout<<t->data; 
        InOrder(t->RightChild); 
    } 
} 
  
void BiTree::WeightingCalculation()  
{  
    WeightingCalculation(Root,0);  
}  
    
void BiTree::WeightingCalculation(BiTreeNode* t,int weight_sum)  
{  
    if(t)  
    {  
        t->weight_sum+=weight_sum; 
        WeightingCalculation(t->LeftChild,t->weight_sum);  
        WeightingCalculation(t->RightChild,t->weight_sum);  
        if(!t->LeftChild && !t->RightChild) 
        { 
            if(max_weight<t->weight_sum)max_weight=t->weight_sum; 
        } 
    }  
}  
    
void BiTree::PostOrder()  
{  
    PostOrder(Root);  
}  
    
void BiTree::PostOrder(BiTreeNode*t)  
{  
    if(t)  
    {  
        PostOrder(t->LeftChild);  
        PostOrder(t->RightChild);  
        cout<<t->data; 
    }  
} 
  
int main()  
{  
    int t,num,i;  
    string str;  
    BiTree BT; 
    int *weight; 
    cin>>t;  
    while(t--)  
    {  
        cin>>str;  
        cin>>num; 
        weight=new int[num]; 
        for(i=0;i<num;i++) 
        { 
            cin>>weight[i]; 
        } 
        BT.CreateTree(str,weight); 
        cout<<BT.getmax_weight_sum()<<endl; 
        delete[]weight; 
    }  
    return 0;  
} 

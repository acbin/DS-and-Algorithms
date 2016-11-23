/*
题目描述
给定一颗二叉树的逻辑结构如下图，（先序遍历的结果，空树用字符‘0’表示，例如AB0C00D00），建立该二叉树的二叉链式存储结构，并输出该二叉树的先序遍历、中序遍历和后序遍历结果
本题目的代码框架参考如下
三种遍历的代码框架
输入
第一行输入一个整数t，表示有t个二叉树
第二行起输入每个二叉树的先序遍历结果，空树用字符‘0’表示，连续输入t行
输出
输出每个二叉树的先序遍历、中序遍历和后序遍历结果
样例输入
2
AB0C00D00
AB00C00
样例输出
ABCD
BCAD
CBDA
ABC
BAC
BCA
*/
#include<iostream>
#include<string>
using namespace std;

class BiTreeNode{
	public:
		char data;
		BiTreeNode* LeftChild;
		BiTreeNode* RightChild;
		BiTreeNode():LeftChild(NULL),RightChild(NULL){}
		~BiTreeNode(){}
};

class BiTree{
	private:
		BiTreeNode *Root;
		int pos;
		string strTree;
		BiTreeNode* CreateBiTree();
		void PreOrder(BiTreeNode* t);
		void InOrder(BiTreeNode* t);
		void PostOrder(BiTreeNode* t);
	public:
		BiTree(){};
		~BiTree(){};
		void CreateTree(string TreeArray);
		void PreOrder();
		void InOrder();
		void PostOrder();
};

void BiTree::CreateTree(string TreeArray)
{
	pos=0;
	strTree.assign(TreeArray);
	Root = CreateBiTree();
}

BiTreeNode* BiTree::CreateBiTree()
{
	BiTreeNode *T;
	char ch;
	ch=strTree[pos++];
	if(ch=='0')
		T = NULL;
	else
	{
		T=new BiTreeNode();
		T->data = ch;
		T->LeftChild = CreateBiTree();
		T->RightChild = CreateBiTree();
	}
	return T;
}

void BiTree::PreOrder()
{
	PreOrder(Root);
}

void BiTree::PreOrder(BiTreeNode* t)
{
	if(t!=NULL){
		cout<<t->data;
		PreOrder(t->LeftChild);
		PreOrder(t->RightChild);
	}
}

void BiTree::InOrder()
{
	InOrder(Root);
}

void BiTree::InOrder(BiTreeNode* t)
{
	if(t!=NULL){
		InOrder(t->LeftChild);
		cout<<t->data;
		InOrder(t->RightChild);
	}
}

void BiTree::PostOrder()
{
	PostOrder(Root);
}

void BiTree::PostOrder(BiTreeNode* t)
{
	if(t!=NULL){
		PostOrder(t->LeftChild);
		PostOrder(t->RightChild);
		cout<<t->data;
	}
}

int main(void)
{
	BiTree bitree;
	string str;
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>str;
		bitree.CreateTree(str);
		bitree.PreOrder();
		cout<<endl;
		bitree.InOrder();
		cout<<endl;
		bitree.PostOrder();
		cout<<endl;
	}
	return 0;
}

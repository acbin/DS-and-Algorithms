/*
层次遍历二叉树，是从根结点开始遍历，按层次次序“自上而下，从左至右”访问树中的各结点。

建树方法采用“先序遍历+空树用0表示”的方法

要求：采用队列对象实现，函数框架如下：



输入

第一行输入一个整数t，表示有t个测试数据

第二行起输入二叉树先序遍历的结果，空树用字符‘0’表示，输入t行

输出

逐行输出每个二叉树的层次遍历结果

样例输入

2
AB0C00D00
ABCD00E000FG00H0I00
样例输出

ABDC
ABFCGHDEI
*/ 
#include<iostream>
#include<string>
#include <queue>
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
		int count;
		string strTree;
		BiTreeNode* CreateBiTree();
		void PreOrder(BiTreeNode* t);
		void InOrder(BiTreeNode* t);
		void PostOrder(BiTreeNode* t);
		void Leaves(BiTreeNode* t);
		void LevelOrder(BiTreeNode *t);
	public:
		BiTree(){};
		~BiTree(){};
		void CreateTree(string TreeArray);
		void PreOrder();
		void InOrder();
		void PostOrder();
		int Leaves();
		void LevelOrder();
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

int BiTree::Leaves()
{
	count=0;
	Leaves(Root);
	return count;
}

void BiTree::Leaves(BiTreeNode* t)
{
	if(t!=NULL){
		if(t->LeftChild==NULL&&t->RightChild==NULL){
			count++;	
		}
		Leaves(t->LeftChild);
		Leaves(t->RightChild);
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

void BiTree::LevelOrder()
{
	LevelOrder(Root);
}

void BiTree::LevelOrder(BiTreeNode *t)
{
	queue<BiTreeNode*> tq;
	BiTreeNode* p=t;
	if(p!=NULL){
		tq.push(p);
	}
	while(!tq.empty()){
		p=tq.front();
		cout<<p->data;
		tq.pop();
		if(p->LeftChild){
			tq.push(p->LeftChild);
		}
		if(p->RightChild){
			tq.push(p->RightChild);
		}
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
		bitree.LevelOrder();
		cout<<endl;
	}
	return 0;
}

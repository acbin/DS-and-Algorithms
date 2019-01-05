/*
题目描述

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

#include <iostream>
#include <queue>
using namespace std;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree creatBiTree()
{
	BiTree T = NULL;
	char ch;
	cin >> ch;
	if (ch == '0')
	{
		return NULL;
	}
	T = new BiTNode;
	T->data = ch;
	T->lchild = creatBiTree();
	T->rchild = creatBiTree();
	return T;
}

void LevelOrder(BiTree T)
{
	queue<BiTree> q;
	if (T)
	{
		q.push(T);
		while (!q.empty())
		{
			BiTree r = q.front();
			if (r->lchild)
			{
				q.push(r->lchild);
			}
			if (r->rchild)
			{
				q.push(r->rchild);
			}
			cout << r->data;
			q.pop();
		}
	}
	cout << endl;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		BiTree T = creatBiTree();
		LevelOrder(T);
	}
	return 0;
}
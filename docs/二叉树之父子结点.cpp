/*
题目描述

给定一颗二叉树的逻辑结构如下图，（先序遍历的结果，空树用字符‘0’表示，例如AB0C00D00），建立该二叉树的二叉链式存储结构。

编写程序输出该树的所有叶子结点和它们的父亲结点



输入

第一行输入一个整数t，表示有t个二叉树

第二行起，按照题目表示的输入方法，输入每个二叉树的先序遍历，连续输入t行

输出

第一行按先序遍历，输出第1个示例的叶子节点

第二行输出第1个示例中与叶子相对应的父亲节点

以此类推输出其它示例的结果

 

样例输入

3
AB0C00D00
AB00C00
ABCD0000EF000
样例输出

C D 
B A 
B C 
A A 
D F 
C E 
*/
#include <iostream>
#define ok 0
#define error -1
using namespace std;

//链表结点类定义
class ListNode
{
  public:
	int data;
	ListNode *next;
	ListNode() { next = NULL; }
};

class LinkList
{
  public:
	ListNode *head;
	int len;
	LinkList();
	~LinkList();
	ListNode *LL_index(int i);
	int LL_get(int i);
	int LL_insert(int i, int item);
	int LL_del(int i);
	void LL_display();
};

LinkList::LinkList()
{
	head = new ListNode();
	len = 0;
}
LinkList::~LinkList()
{
	ListNode *p, *q;
	p = head;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
	len = 0;
	head = NULL;
}

ListNode *LinkList::LL_index(int i)
{
	ListNode *p;
	p = head;
	if (i < 0 || i > len + 1)
	{
		return NULL;
	}
	while (i--)
	{
		p = p->next;
	}
	return p;
}

int LinkList::LL_insert(int i, int item)
{
	if (i < 1 || i > len + 1)
	{
		return error;
	}
	ListNode *p;
	p = LL_index(i - 1);
	ListNode *pNew;
	pNew = new ListNode();
	pNew->data = item;
	pNew->next = p->next;
	p->next = pNew;
	len++;
	return ok;
}

int LinkList::LL_del(int i)
{
	if (i < 1 || i > len + 1)
	{
		return error;
	}
	ListNode *p, *tmp;
	p = LL_index(i - 1);
	tmp = p->next;
	p->next = tmp->next;
	delete tmp;
	--len;
	return ok;
}

int LinkList::LL_get(int i)
{
	if (i < 1 || i > len + 1)
	{
		return error;
	}
	ListNode *p;
	p = LL_index(i);
	return p->data;
}

void LinkList::LL_display()
{
	ListNode *p;
	p = head->next;
	while (p)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

int main()
{

	int n, i, j = 2, data, ret;
	LinkList list;
	cin >> n;
	for (i = 0; i < n; ++i)
	{
		cin >> data;
		list.LL_insert(i + 1, data);
	}
	list.LL_display();

	//插入两次
	while (j--)
	{
		cin >> i >> data;
		ret = list.LL_insert(i, data);
		if (ret == error)
		{
			cout << "error" << endl;
		}
		else
		{
			list.LL_display();
		}
	}

	//删除两次
	j = 2;
	while (j--)
	{
		cin >> i;
		ret = list.LL_del(i);
		if (ret == error)
		{
			cout << "error" << endl;
		}
		else
		{
			list.LL_display();
		}
	}

	//查找两次
	j = 2;
	while (j--)
	{
		cin >> i;
		ret = list.LL_get(i);
		if (ret == error)
		{
			cout << "error" << endl;
		}
		else
		{
			cout << ret << endl;
		}
	}
	return 0;
}
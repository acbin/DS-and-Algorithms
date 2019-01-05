/*
题目描述

用C++语言和类实现单链表，含头结点

属性包括：data数据域、next指针域

操作包括：插入、删除、查找

注意：单链表不是数组，所以位置从1开始对应首结点，头结点不放数据

类定义参考



输入

n
第1行先输入n表示有n个数据，接着输入n个数据
第2行输入要插入的位置和新数据
第3行输入要插入的位置和新数据
第4行输入要删除的位置
第5行输入要删除的位置
第6行输入要查找的位置
第7行输入要查找的位置
输出

n
数据之间用空格隔开，

第1行输出创建后的单链表的数据

每成功执行一次操作（插入或删除），输出执行后的单链表数据

每成功执行一次查找，输出查找到的数据

如果执行操作失败（包括插入、删除、查找等失败），输出字符串error，不必输出单链表

样例输入

6 11 22 33 44 55 66
3 777
1 888
1
11
0
5
样例输出

11 22 33 44 55 66 
11 22 777 33 44 55 66 
888 11 22 777 33 44 55 66 
11 22 777 33 44 55 66 
error
error
44
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

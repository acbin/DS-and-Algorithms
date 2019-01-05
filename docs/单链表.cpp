/*
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
#include <stdlib.h>
using namespace std;

typedef struct Node
{
	int data;
	struct Node *next;
} Node;
void show_list(Node *pHead);
Node *init_list()
{
	int len, i, val;
	cin >> len;
	Node *pHead = NULL, *pCur, *pNew;
	pHead = (Node *)malloc(sizeof(Node));
	if (pHead == NULL)
	{
		return NULL;
	}
	pHead->data = len;
	pHead->next = NULL;
	pCur = pHead;
	for (i = 0; i < len; ++i)
	{
		cin >> val;
		pNew = (Node *)malloc(sizeof(Node));
		pNew->data = val;
		pNew->next = NULL;
		pCur->next = pNew;
		pCur = pNew;
	}
	return pHead;
}

void insert_list(Node *pHead)
{
	int pos, data, i;
	cin >> pos >> data;
	if (pos < 1 || pos > pHead->data)
	{
		cout << "error" << endl;
		return;
	}
	Node *pCur = pHead;
	for (i = 0; i < pos - 1; ++i)
	{
		pCur = pCur->next;
	}
	Node *pNew = (Node *)malloc(sizeof(Node));
	pNew->data = data;
	pNew->next = pCur->next;
	pCur->next = pNew;
	pHead->data++;
	show_list(pHead);
}

void delete_list(Node *pHead)
{
	int pos, i, val;
	cin >> pos;
	if (pos < 1 || pos > pHead->data)
	{
		cout << "error" << endl;
		return;
	}
	Node *pCur = pHead;
	for (i = 0; i < pos - 1; ++i)
	{
		pCur = pCur->next;
	}
	Node *pTmp = pCur->next;
	pCur->next = pTmp->next;
	val = pTmp->data;
	free(pTmp);
	pHead->data--;
	show_list(pHead);
}

void search_list(Node *pHead)
{
	int pos, i;
	cin >> pos;
	if (pos < 1 || pos > pHead->data)
	{
		cout << "error" << endl;
		return;
	}
	Node *pCur = pHead;
	for (i = 0; i < pos; ++i)
	{
		pCur = pCur->next;
	}
	cout << pCur->data << endl;
}

void show_list(Node *pHead)
{
	int i;
	cout << pHead->data << " ";
	Node *pTmp = pHead->next;
	for (i = 0; i < pHead->data; ++i)
	{
		cout << pTmp->data << " ";
		pTmp = pTmp->next;
	}
	cout << endl;
}

int main()
{
	Node *pNode = NULL;
	pNode = init_list();
	show_list(pNode);
	insert_list(pNode);
	insert_list(pNode);
	delete_list(pNode);
	delete_list(pNode);
	search_list(pNode);
	search_list(pNode);
	return 0;
}
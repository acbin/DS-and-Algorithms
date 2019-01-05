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
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *next;
} Node, *PNODE;

//创建链表
PNODE create_list()
{
	int i, len, val;
	PNODE pHead = (PNODE)malloc(sizeof(Node));
	if (pHead == NULL)
	{
		return NULL;
	}
	PNODE pCur = pHead;
	scanf("%d", &len);
	for (i = 0; i < len; ++i)
	{
		scanf("%d", &val);
		PNODE pNew = (PNODE)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			return NULL;
		}
		pNew->data = val;
		pNew->next = NULL;
		pCur->next = pNew;
		pCur = pNew;
	}
	return pHead;
}

//遍历链表
void traverse_list(PNODE pHead)
{
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	PNODE pCur = pHead->next;
	while (pCur)
	{
		printf("%d ", pCur->data);
		pCur = pCur->next;
	}
	printf("\n");
	return;
}

//求链表长度
int length_list(PNODE pHead)
{
	int len = 0;
	if (pHead == NULL || pHead->next == NULL)
	{
		return len;
	}
	PNODE pCur = pHead->next;
	while (pCur)
	{
		++len;
		pCur = pCur->next;
	}
	return len;
}

//插入元素
void insert_list(PNODE pHead, int pos, int val)
{
	int i;
	if (pos < 1 || pos > length_list(pHead))
	{
		printf("error\n");
		return;
	}
	PNODE pPre = pHead;
	PNODE pCur = pPre->next;
	for (i = 0; i < pos - 1; ++i)
	{
		pPre = pCur;
		pCur = pCur->next;
	}
	PNODE pNew = (PNODE)malloc(sizeof(Node));
	pNew->data = val;
	pNew->next = pCur;
	pPre->next = pNew;
	traverse_list(pHead);
}

//删除元素
void delete_list(PNODE pHead, int pos)
{
	int i;
	if (pos < 1 || pos > length_list(pHead))
	{
		printf("error\n");
		return;
	}
	PNODE pPre = pHead;
	PNODE pCur = pPre->next;
	for (i = 0; i < pos - 1; ++i)
	{
		pPre = pCur;
		pCur = pCur->next;
	}
	pPre->next = pCur->next;
	free(pCur);
	traverse_list(pHead);
	return;
}

//求某个位置的值
void index_list(PNODE pHead, int pos)
{
	int i;
	if (pos < 1 || pos > length_list(pHead))
	{
		printf("error\n");
		return;
	}
	PNODE pCur = pHead->next;
	for (i = 0; i < pos - 1; ++i)
	{
		pCur = pCur->next;
	}
	printf("%d\n", pCur->data);
}

//链表逆置
void inverse_list(PNODE pHead)
{
	if (pHead == NULL || pHead->next == NULL || pHead->next->next == NULL)
	{
		return;
	}
	PNODE p = pHead->next, q = p->next, t;
	while (q)
	{
		t = q->next;
		q->next = p;
		p = q;
		q = t;
	}
	pHead->next->next = NULL;
	pHead->next = p;
	return;
}

int main()
{
	int i, val, pos;
	PNODE pHead = NULL;
	pHead = create_list();
	traverse_list(pHead);
	for (i = 0; i < 2; ++i)
	{
		scanf("%d %d", &pos, &val);
		insert_list(pHead, pos, val);
	}
	for (i = 0; i < 2; ++i)
	{
		scanf("%d", &pos);
		delete_list(pHead, pos);
	}
	for (i = 0; i < 2; ++i)
	{
		scanf("%d", &pos);
		index_list(pHead, pos);
	}
	return 0;
}

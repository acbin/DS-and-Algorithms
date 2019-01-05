
/*
定长顺序表--FixedLenArray类实现
输入

第1行先输入n表示有n个数据，即n是实际长度；接着输入n个数据
第2行输入要插入的位置和新数据
第3行输入要插入的位置和新数据
第4行输入要删除的位置
第5行输入要删除的位置
第6行输入要查找的位置
第7行输入要查找的位置
输出

数据之间用空格隔开

第1行输出创建后的顺序表内容，包括顺序表实际长度和数据

每成功执行一次操作（插入或删除），输出执行后的顺序表内容

每成功执行一次查找，输出查找到的数据

如果执行操作失败（包括插入、删除、查找等失败），输出字符串error，不必输出顺序表内容

样例输入

6 11 22 33 44 55 66
3 666
1 888
1
9
0
5
样例输出

6 11 22 33 44 55 66 
7 11 22 666 33 44 55 66 
8 888 11 22 666 33 44 55 66 
7 11 22 666 33 44 55 66 
error
error
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Array
{
	int *pBase;
	int len;
	int capacity;
	int data;
} Array, *pArray;

void show_array(pArray pArr);

void init_array(pArray pArr)
{
	int i, val, len;
	pArr->pBase = (int *)malloc(sizeof(int) * 1000);
	if (pArr->pBase == NULL)
	{
		return;
	}
	scanf("%d", &len);
	pArr->len = len;
	for (i = 0; i < len; ++i)
	{
		scanf("%d", &val);
		pArr->pBase[i] = val;
	}
	show_array(pArr);
	return;
}

//1 2 3 4 5

void insert_array(pArray pArr)
{
	int i, pos, val;
	scanf("%d %d", &pos, &val);
	if (pos < 1 || pos > pArr->len)
	{
		printf("error\n");
		return;
	}
	for (i = pArr->len; i > pos - 1; --i)
	{
		pArr->pBase[i] = pArr->pBase[i - 1];
	}
	pArr->pBase[pos - 1] = val;
	pArr->len++;
	show_array(pArr);
}

//1 2 3 4 5

void delete_array(pArray pArr)
{
	int i, pos, val;
	scanf("%d", &pos);
	if (pos < 1 || pos > pArr->len)
	{
		printf("error\n");
		return;
	}
	val = pArr->pBase[pos - 1];
	for (i = pos; i < pArr->len; ++i)
	{
		pArr->pBase[i - 1] = pArr->pBase[i];
	}
	pArr->len--;
	show_array(pArr);
}

void search_array(pArray pArr)
{
	int i, pos;
	scanf("%d", &pos);
	if (pos < 1 || pos > pArr->len)
	{
		printf("error\n");
		return;
	}
	printf("%d\n", pArr->pBase[pos - 1]);
}

void show_array(pArray pArr)
{

	int i = 0;
	printf("%d ", pArr->len);
	for (; i < pArr->len; ++i)
	{
		printf("%d ", pArr->pBase[i]);
	}
	printf("\n");
}

int main()
{
	int pos, val;
	Array arr;
	init_array(&arr);
	insert_array(&arr);
	insert_array(&arr);
	delete_array(&arr);
	delete_array(&arr);
	search_array(&arr);
	search_array(&arr);
	return 0;
}
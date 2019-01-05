/*
题目描述

C++中已经自带堆栈对象stack，无需编写堆栈操作的具体实现代码。

本题目主要帮助大家熟悉stack对象的使用，然后实现字符串的逆序输出

输入一个字符串，按字符按输入顺序压入堆栈，然后根据堆栈后进先出的特点，做逆序输出

stack类使用的参考代码

n包含头文件<stack>  ：  #include <stack>

n创建一个堆栈对象s（注意stack是模板类）：stack <char>  s; //堆栈的数据类型是字符型
n把一个字符ct压入堆栈： s.push(ct);
n把栈顶元素弹出：s.pop();
n获取栈顶元素，放入变量c2： c2 = s.top();
n判断堆栈是否空： s.empty()，如果为空则函数返回true，如果不空则返回false
输入

第一行输入t，表示有t个测试实例
第二起，每一行输入一个字符串，注意字符串不要包含空格

字符串的输入可以考虑一下代码：

#include <string>

int main()

{ string str;

  Int len;

  cin>>str; //把输入的字符串保存在变量str中

  len = str.length()  //获取输入字符串的长度

}

输出

每行逆序输出每一个字符串

样例输入

2
abcdef
aabbcc
样例输出

fedcba
ccbbaa
*/
#include <iostream>
#include <string>
using namespace std;

typedef struct Node
{
	char ch;
	struct Node *next;
} NODE, *PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
} STACK, *PSTACK;

void init_stack(PSTACK pS)
{
	pS->pBottom = (PNODE)malloc(sizeof(NODE));
	if (pS->pBottom == NULL)
	{
		exit(-1);
	}
	pS->pBottom->next = NULL;
	pS->pTop = pS->pBottom;
	return;
}

void push_stack(PSTACK pS, char ch)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL)
	{
		exit(-1);
	}
	pNew->ch = ch;
	pNew->next = pS->pTop;
	pS->pTop = pNew;
}

void pop_stack(PSTACK pS, char *ch)
{
	if (pS->pBottom == pS->pTop)
	{
		return;
	}
	*ch = pS->pTop->ch;
	PNODE pCur = pS->pTop->next;
	free(pS->pTop); //因为push的时候分配了内存，所以pop的时候应该把内存释放掉
	pS->pTop = pCur;
	return;
}

//获取栈顶元素
char get_stack(PSTACK pS)
{
	char ch;
	if (pS->pBottom == pS->pTop)
	{
		return NULL;
	}
	ch = pS->pTop->ch;
	return ch;
}

//求栈的长度
int length_stack(PSTACK pS)
{
	int len = 0;
	if (pS->pBottom == pS->pTop)
	{
		return len;
	}
	PNODE pCur = pS->pTop;
	while (pCur != pS->pBottom)
	{
		++len;
		pCur = pCur->next;
	}
	return len;
}
void traverse_stack(PSTACK pS)
{
	if (pS->pBottom == pS->pTop)
	{
		return;
	}
	PNODE pCur = pS->pTop;
	while (pCur != pS->pBottom)
	{
		cout << pCur->ch;
		pCur = pCur->next;
	}
	cout << endl;
	return;
}

void clear_stack(PSTACK pS)
{
	if (pS->pBottom == pS->pTop)
	{
		return;
	}
	PNODE pPre = pS->pTop;
	PNODE pCur = pPre->next;
	while (pPre != pS->pBottom)
	{
		free(pPre);
		pPre = pCur;
		pCur = pCur->next;
	}
	pS->pTop = pS->pBottom;
}
int main()
{
	string str;
	int i, t;
	//char ch;
	cin >> t;
	STACK S;
	init_stack(&S);
	while (t--)
	{
		cin >> str;
		for (i = 0; i < str.length(); ++i)
		{
			push_stack(&S, str[i]);
		}
		traverse_stack(&S);
		//int len=length_stack(&S);
		//cout<<"len="<<len<<endl;
		//pop_stack(&S,&ch);
		clear_stack(&S);
	}
	return 0;
}

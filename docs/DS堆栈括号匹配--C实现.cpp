/*
题目描述

处理表达式过程中需要对括号匹配进行检验，括号匹配包括三种：“(”和“)”，“[”和“]”，“{”和“}”。例如表达式中包含括号如下：

(	)	[	(	)	(	[	]	)	]	{	}
1	2	3	4	5	6	7	8	9	10	11	12
从上例可以看出第1和第2个括号匹配，第3和第10个括号匹配，4和5匹配，6和9匹配，7和8匹配，11和12匹配。从中可以看到括号嵌套的的情况是比较复杂的，使用堆栈可以很方便的处理这种括号匹配检验，可以遵循以下规则：

1、 当接收第1个左括号，表示新的一组匹配检查开始；随后如果连续接收到左括号，则不断进堆栈。

2、 当接受第1个右括号，则和最新进栈的左括号进行匹配，表示嵌套中1组括号已经匹配消除

3、 若到最后，括号不能完全匹配，则说明输入的表达式有错

建议使用C++自带的stack对象来实现

stack类使用的参考代码

n包含头文件<stack>  ：  #include <stack>

n创建一个堆栈对象s（注意stack是模板类）：stack <char>  s; //堆栈的数据类型是字符型
n把一个字符ct压入堆栈： s.push(ct);
n把栈顶元素弹出：s.pop();
n获取栈顶元素，放入变量c2： c2 = s.top();
n判断堆栈是否空： s.empty()，如果为空则函数返回true，如果不空则返回false

输入

第一行输入一个t，表示下面将有t组测试数据。接下来的t行的每行输入一个表达式，表达式只考虑英文半角状态输入，无需考虑中文全角输入

输出

对于每一行的表达式，检查括号是否匹配，匹配则输入ok，不匹配则输出error

样例输入

2
(a+b)[4*5+(-6)]
[5*8]/{(a+b)-6
样例输出

ok
error
提示

算法流程


1、初始化，i=0，建立堆栈，栈为空

2、输入表达式，建立指针指向表达式的头部

3、读入表达式的第i个字符

4、如果第i个字符是左括号，入栈

5、如果第i个字符是右括号，检查栈顶元素是否匹配

A.如果匹配，弹出栈顶元素

B.如果不匹配，报错退出

6、i++，指向下一个字符，是否已经表达式末尾

A. 未到末尾，重复步骤3

B. 已到达末尾

a. 堆栈为空，输出ok

b. 堆栈不为空，输出error
*/
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
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
//判断是否是左符号
int isLeft(char c)
{
	int ret = 0;
	switch (c)
	{
	case '<':
	case '(':
	case '[':
	case '{':
	case '\'': //单引号
	case '\"': //双引号
		ret = 1;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

//判断是否是右符号
int isRight(char c)
{
	int ret = 0;
	switch (c)
	{
	case '>':
	case ')':
	case ']':
	case '}':
	case '\'': //单引号
	case '\"': //双引号
		ret = 1;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

int match(char left, char right)
{
	int ret = 0;
	switch (left)
	{
	case '<':
		ret = (right == '>');
		break;
	case '(':
		ret = (right == ')');
		break;
	case '[':
		ret = (right == ']');
		break;
	case '{':
		ret = (right == '}');
		break;
	case '\'':
		ret = (right == '\'');
		break;
	case '\"':
		ret = (right == '\"');
		break;
	}
	return ret;
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

/*
栈应用--括号匹配


1.从第一个字符开始扫描

2.当遇见普通字符时忽略；当遇见左括号时压入栈中

3.当遇见右符号时，从栈中弹出栈顶符号，并进行匹配
匹配成功：继续读入下一个字符
匹配失败：立即停止，并报错

4.结束：
成功：所有字符扫描完毕，且栈为空
失败：匹配失败或所有字符扫描完毕但栈非空

当需要检测承兑出现但又互不相邻的食物时，可以使用后进先出的特性，栈非常适用需要就近匹配的场合
*/
int main()
{
	string str;
	int i, t;
	cin >> t;
	STACK S;
	init_stack(&S);
	while (t--)
	{
		cin >> str;
		char ch;
		for (i = 0; i < str.length(); ++i)
		{
			if (isLeft(str[i]))
			{
				push_stack(&S, str[i]);
			}
			if (isRight(str[i]))
			{
				pop_stack(&S, &ch);
				if (ch == NULL || !match(ch, str[i]))
				{
					cout << "error" << endl;
					break;
				}
			}
		}
		if (length_stack(&S) == 0)
		{
			cout << "ok" << endl;
		}
		else
		{
			cout << "error" << endl;
		}

		clear_stack(&S);
	}
	return 0;
}
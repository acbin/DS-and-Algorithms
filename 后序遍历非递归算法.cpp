/*
求一颗树的后序遍历的非递归算法
要求：必须是非递归算法，使用堆栈对象来实现
建树方法采用“先序遍历+空树用0表示”的方法
算法流程：

输入

第一行输入一个整数t，表示有t个测试数据

第二行起输入二叉树先序遍历的结果，空树用字符‘0’表示，输入t行

输出

逐行输出每个二叉树的后序遍历结果

样例输入

3
AB0C00D00
ABC00D00EF000
ABCD0000E0F00
样例输出

CBDA
CDBFEA
DCBFEA
*/
#include <iostream>
#include <malloc.h>
#define Maxsize 100
using namespace std;
typedef struct TREE{
	struct TREE *lTree;
	struct TREE *rTree;
	char data;
}Tree;


Tree *createNode();//创建二叉树
void LastOrderTraverse(Tree *tree);//后序遍历非递归

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
		Tree *headNode=NULL;
		headNode=createNode();
		LastOrderTraverse(headNode);//后序遍历非递归
		cout<<endl;
	}
	return 0;
}

Tree *createNode()
{
	Tree *node;
	char x;
	cin>>x;
	if(x=='0')
	{
		node=NULL;
	}
	else
	{
		node=(Tree *)malloc(sizeof(Tree));
		node->data=x;
		node->lTree=createNode();
		node->rTree=createNode();
	}
	return node;
}

void LastOrderTraverse(Tree *tree)//后序遍历非递归
{
	Tree *stack[Maxsize]={NULL},*p;
	p=tree;
	int top=0,tag=1,i=0,k=0;
	while(p!=NULL || top)
	{
		i=1;
		while(p!=NULL)
		{
			stack[++top]=p;
			p=p->lTree;
		}
		if(top!=0)
			p=stack[top]->rTree;
		if(p==NULL)
		{
			cout<<stack[top--]->data;
			if(stack[top]!=NULL)
			{
				while(i)
				{
					if(stack[top]!=NULL)
					{
						if(stack[top]->rTree!=NULL)
						{
							if(stack[top]->rTree->data==stack[top+1]->data)
								cout<<stack[top--]->data;
							else
								i=0;
						}
						else
							i=0;
					}
					else
						i=0;
				}
			}
			if(top!=0)
				p=stack[top]->rTree;
			else
				p=NULL;
		}
	}
}

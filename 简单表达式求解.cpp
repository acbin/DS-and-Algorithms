/*
题目描述

输入不带括号且数值为[1,9]正整数的四则运算表达式，按照算符*,/计算的优先级高于+,-，同一优先级自左向右方式构造表达式二叉树，输出该表达式对应的二叉树的后序遍历；输出整数计算结果。注意：用于测试的表达式个数事先是不确定的。

输入

样本四则运算表达2+3*4+5/6 。注意：用于测试的表达式数量事先是不确定的。

输出

输出后序遍历：234*+56/+

输出计算结果：14

样例输入

7*8+3*4-6/3
4-2-5/3*2/4+3*6
样例输出

78*34*+63/-
66
42-53/2*4/-36*+
20	
*/
#include <stdio.h>
#include <string.h>
#include <string>
#include <malloc.h>


#define MaxSize 100
using namespace std;
typedef char ElemType;
typedef struct node
{
    ElemType data; 
    struct node *lchild;
    struct node *rchild;
} BTNode;
void CreateBTNode(BTNode *&b,char *str)
{
    BTNode *St[MaxSize],*p=NULL;
    int top=-1,k,j=0;
    char ch;
    b=NULL;
    ch=str[j];
    while (ch!='\0')
    {
        switch(ch)
        {
        case '(':
            top++;
            St[top]=p;
            k=1;
            break;
        case ')':
            top--;
            break;
        case ',':
            k=2;
            break;
        default:
            p=(BTNode *)malloc(sizeof(BTNode));
            p->data=ch;
            p->lchild=p->rchild=NULL;
            if (b==NULL)
                b=p;
            else
            {
                switch(k)
                {
                case 1:
                    St[top]->lchild=p;
                    break;
                case 2:
                    St[top]->rchild=p;
                    break;
                }
            }
        }
        j++;
        ch=str[j];
    }
}
void DestroyBTNode(BTNode *&b)
{
    if (b!=NULL)
    {
        DestroyBTNode(b->lchild);
        DestroyBTNode(b->rchild);
        free(b);
    }
}

BTNode *CRTree(char s[],int i,int j)
{
    BTNode *p;
    int k,plus=0,posi;
    if (i==j)
    {
        p=(BTNode *)malloc(sizeof(BTNode));
        p->data=s[i];
        p->lchild=NULL;
        p->rchild=NULL;
        return p;
    }
    //以下为i!=j的情况
    for (k=i; k<=j; k++)
        if (s[k]=='+' || s[k]=='-')
        {
            plus++;
            posi=k;
        }
    if (plus==0) 
        for (k=i; k<=j; k++)
            if (s[k]=='*' || s[k]=='/')
            {
                plus++;
                posi=k;
            }
    if (plus!=0)
    {
        p=(BTNode *)malloc(sizeof(BTNode));
        p->data=s[posi];  
        p->lchild=CRTree(s,i,posi-1);
        p->rchild=CRTree(s,posi+1,j); 
        return p;
    }
    else
        return NULL;
}

void postorder(BTNode *b)
{
	if(b)
	{
		postorder(b->lchild);
		postorder(b->rchild);
		printf("%c",b->data);
	}
}
int Comp(BTNode *b)
{
    int v1,v2;
    if (b==NULL)
        return 0;
    if (b->lchild==NULL && b->rchild==NULL)
        return b->data-'0'; 
	v1=Comp(b->lchild);
    v2=Comp(b->rchild);
    switch(b->data)
    {
    case '+':
        return v1+v2;
    case '-':
        return v1-v2;
    case '*':
        return v1*v2;
    case '/':
        if (v2!=0)
            return v1/v2;
    }
}

int main()
{
    BTNode *b;
    char s[MaxSize]="0";
    while(scanf("%s",&s)!=EOF){
	    b=CRTree(s,0,strlen(s)-1);
	    postorder(b);
	    printf("\n%d\n",Comp(b));
	    DestroyBTNode(b);
	}
    return 0;
}

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
#include <iostream>
#include <stack>

using namespace std;

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
	
}BiTNode,*BiTree;


int is_Num(char c){
	if(c>='1'&&c<='9'){
		return 1;
	}
	return 0;
}

int is_Left(char c){
	if(c=='('){
		return 1;
	}
	return 0;
}

int is_Right(char c){
	if(c==')'){
		return 1;
	}
	return 0;
}

int is_Operator(char c){
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
		default:
			return 0;
	}
}

int prority(char c){
	switch(c){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return 0;
	}
}


void CreateNode(stack<char> &s1,stack<BiTree> &s2){
	BiTree NewT=new BiTNode;
	NewT->data=s1.top();
	s1.pop();
	NewT->rchild=s2.top();
	s2.pop();
	NewT->lchild=s2.top();
	s2.pop();
	s2.push(NewT);
} 
void PostOrder(BiTree T){
	if(T){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout<<T->data;
	}
}

int Comp(BiTree T){
	if(T){
		if(!T->lchild&&!T->rchild){
			return T->data-'0';
		}
		int v1=Comp(T->lchild);
		int v2=Comp(T->rchild);
		switch(T->data){
			case '+':
				return v1+v2;
			case '-':
				return v1-v2;
			case '*':
				return v1*v2;
			case '/':
				return v1/v2;
				
		}
	}
}


int main(){
	string str;
	while(cin>>str){
		stack<char> s1;
		stack<BiTree> s2;
		int len=str.length();
		for(int i=0;i<len;++i){
			if(is_Left(str[i])){
				s1.push(str[i]);
			}
			else if(is_Num(str[i])){
				BiTree NewT=new BiTNode;
				NewT->data=str[i];
				NewT->lchild=NULL;
				NewT->rchild=NULL;
				s2.push(NewT);
			}
			else if(is_Right(str[i])){
				while(!s1.empty()&&!is_Left(s1.top())){
					CreateNode(s1,s2);
				}
			}
			else if(is_Operator(str[i])){
				while(!s1.empty()&&prority(str[i])<=prority(s1.top())){
					CreateNode(s1,s2);
				}
				s1.push(str[i]);
			}
		}
		while(!s1.empty()){
			CreateNode(s1,s2);
		}
		PostOrder(s2.top());
		cout<<endl<<Comp(s2.top())<<endl;
	}

	return 0;
}

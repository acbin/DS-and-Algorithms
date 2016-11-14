#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string>
using namespace std;


typedef struct Node{
	char ch;
	struct Node* next;
}NODE,*PNODE;

typedef struct Stack{
	PNODE pTop;
	PNODE pBottom;
}STACK,*PSTACK;

void init_stack(PSTACK pS){
	pS->pBottom=(PNODE)malloc(sizeof(NODE));
	if(pS->pBottom==NULL){
		exit(-1);
	}
	pS->pBottom->next=NULL;
	pS->pTop=pS->pBottom;
	return;
}

void push_stack(PSTACK pS,char ch){
	PNODE pNew=(PNODE)malloc(sizeof(NODE));
	if(pNew==NULL){
		exit(-1);
	}
	pNew->ch=ch;
	pNew->next=pS->pTop;
	pS->pTop=pNew;
}

void pop_stack(PSTACK pS){
	if(pS->pBottom==pS->pTop){
		return;
	}
	PNODE pCur=pS->pTop->next;
	free(pS->pTop);//因为push的时候分配了内存，所以pop的时候应该把内存释放掉
	pS->pTop=pCur;
	return;
}

//获取栈顶元素
char get_stack(PSTACK pS){
	char ch;
	if(pS->pBottom==pS->pTop){
		return NULL;
	}
	ch=pS->pTop->ch;
	return ch;
}

//求栈的长度
int length_stack(PSTACK pS){
	int len=0;
	if(pS->pBottom==pS->pTop){
		return len;
	}
	PNODE pCur=pS->pTop;
	while(pCur!=pS->pBottom){
		++len;
		pCur=pCur->next;
	}
	return len;
}
void traverse_stack(PSTACK pS){
	if(pS->pBottom==pS->pTop){
		return;
	}
	PNODE pCur=pS->pTop;
	while(pCur!=pS->pBottom){
		cout<<pCur->ch;
		pCur=pCur->next;
	}
	cout<<endl;
	return;
}

//判断是不是数字
int isNumber(char c){
	return ('0'<=c)&&(c<='9');
}
//判断是否是左符号
int isLeft(char c){
	int ret=0;
	switch(c){
	case '<':
	case '(':
	case '[':
	case '{':
	case '\''://单引号
	case '\"'://双引号
		ret=1;
		break;
	default:
		ret=0;
		break;
	}
	return ret;
}

//判断是否是右符号
int isRight(char c){
	int ret=0;
	switch(c){
	case '>':
	case ')':
	case ']':
	case '}':
	case '\''://单引号
	case '\"'://双引号
		ret=1;
		break;
	default:
		ret=0;
		break;
	}
	return ret;
}

//判断是不是运算符
int isOperator(char c){
	return (c=='+')||(c=='-')||(c=='*')||(c=='/');
}

//优先级
int priority(char c){
	int ret=0;
	if((c=='+')||(c=='-')){
		ret=1;
	}
	if((c=='*')||(c=='/')){
		ret=2;
	}
	return ret;
}
int match(char left,char right){
	int ret=0;
	switch(left){
	case '<':
		ret=(right=='>');
		break;
	case '(':
		ret=(right==')');
		break;
	case '[':
		ret=(right==']');
		break;
	case '{':
		ret=(right=='}');
		break;
	case '\'':
		ret=(right=='\'');
		break;
	case '\"':
		ret=(right=='\"');
		break;
	}
	return ret;
}

void clear_stack(PSTACK pS){
	if(pS->pBottom==pS->pTop){
		return;
	}
	PNODE pPre=pS->pTop;
	PNODE pCur=pPre->next;
	while(pPre!=pS->pBottom){
		free(pPre);
		pPre=pCur;
		pCur=pCur->next;
	}
	pS->pTop=pS->pBottom;
}

int main(){
	string str;
	int i,t;
	cin>>t;
	STACK S;
	init_stack(&S);
	while(t--){
		cin>>str;
		for(i=0;i<str.length();++i){
			if(isNumber(str[i])){
				cout<<str[i];
			}
			else if(isLeft(str[i])){
				push_stack(&S,str[i]);
			}
			else if(isOperator(str[i])){
				while(priority(get_stack(&S))>priority(str[i])){
					cout<<get_stack(&S);
					pop_stack(&S);
				}
				push_stack(&S,str[i]);
			}
			else if(isRight(str[i])){
				while(!isLeft(get_stack(&S))){
					cout<<get_stack(&S);
					pop_stack(&S);
				}
				pop_stack(&S);
			}
			else{
				break;
			}
		}
		while(length_stack(&S)){
			cout<<get_stack(&S);
			pop_stack(&S);
		}
		clear_stack(&S);
		cout<<endl;
	}
	return 0;
}

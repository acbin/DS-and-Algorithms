/*
题目描述

用C++实现含头结点的单链表，然后实现单链表的两个结点交换位置。

注意不能简单交换两个结点包含数据，必须通过修改指针来实现两个结点的位置交换

交换函数定义可以参考：

swap（int  pa, int pb)  //pa和pb表示两个结点在单链表的位置序号

swap (ListNode * p, ListNode * q)  //p和q表示指向两个结点的指针

输入

第1行先输入n表示有n个数据，接着输入n个数据

第2行输入要交换的两个结点位置

第3行输入要交换的两个结点位置

输出

第一行输出单链表创建后的所有数据，数据之间用空格隔开

第二行输出执行第1次交换操作后的单链表数据，数据之间用空格隔开

第三行输出执行第2次交换操作后的单链表数据，数据之间用空格隔开

如果发现输入位置不合法，输出字符串error，不必输出单链表

样例输入

5 11 22 33 44 55
1 4
2 6
样例输出

11 22 33 44 55 
44 22 33 11 55 
error
*/
#include <iostream>

using namespace std;

typedef struct Node{
	int data;
	struct Node *next;
}NODE,*PNODE;

PNODE create_list(){
	int i,n,val;
	PNODE pHead=(PNODE)malloc(sizeof(NODE));
	if(pHead==NULL){
		return NULL;
	}
	pHead->next=NULL;
	PNODE pCur=pHead;
	cin>>n;
	for(i=0;i<n;++i){
		cin>>val;
		PNODE pNew=(PNODE)malloc(sizeof(NODE));
		if(pNew==NULL){
			return NULL;
		}
		pNew->data=val;
		pNew->next=NULL;
		pCur->next=pNew;
		pCur=pNew;
	}
	return pHead;
}

void traverse_list(PNODE pHead){
	if(pHead==NULL||pHead->next==NULL){
		return;
	}
	PNODE pCur=pHead->next;
	while(pCur){
		cout<<pCur->data<<' ';
		pCur=pCur->next;
	}
	cout<<endl;
	return;
}

int length_list(PNODE pHead){
	int len=0;
	if(pHead==NULL||pHead->next==NULL){
		return 0;
	}
	PNODE pCur=pHead->next;
	while(pCur){
		++len;
		pCur=pCur->next;
	}
	return len;
}

PNODE get(PNODE pHead,int pos){
	int i;
	if(pHead==NULL||pos<0||pos>length_list(pHead)){
		return NULL;
	}
	PNODE pCur=pHead;
	for(i=0;i<pos;++i){
		pCur=pCur->next;
	}
	return pCur;

}

void swap(PNODE pHead,int pos1,int pos2){
	int len=length_list(pHead);
	if(pos1<1||pos1>len||pos2<1||pos2>len||pos1>=pos2){
		cout<<"error"<<endl;
		return;
	}
	PNODE pPre=get(pHead,pos1-1);
	PNODE p=pPre->next;
	PNODE qPre=get(pHead,pos2-1);
	PNODE q=qPre->next;
	PNODE t=NULL;
	t=q->next;
	pPre->next=q;
	if(pos2-pos1>1){
		q->next=p->next;
		qPre->next=p;
	}
	else{
		q->next=p;
	}
	p->next=t;
	traverse_list(pHead);
	return;
}

int main(){
	int i=2,pos1,pos2;
	PNODE pHead=NULL;
	pHead=create_list();
	traverse_list(pHead);
	while(i--){
		cin>>pos1>>pos2;
		swap(pHead,pos1,pos2);
	}
	system("pause");
	return 0;
}

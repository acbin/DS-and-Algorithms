#include <iostream>

using namespace std;
typedef enum
{
	Link,
	Thread
} PointerTag;
typedef struct BiThrNode
{
	char data;
	struct BiThrNode *lchild, *rchild;
	PointerTag ltag, rtag;
} BiThrNode, *BiThrTree;

BiThrTree pre; //全局变量始终指向刚刚访问过的结点

//#法先序创建树
BiThrTree createBiThrTree()
{
	char c;
	cin >> c;
	if (c == '#')
	{
		return NULL;
	}
	BiThrTree T = NULL;
	T = (BiThrTree)malloc(sizeof(BiThrNode));
	T->data = c;
	T->ltag = Link;
	T->rtag = Link;
	T->lchild = createBiThrTree();
	T->rchild = createBiThrTree();
	return T;
}

void InThreading(BiThrTree T)
{
	if (T == NULL)
	{
		return;
	}
	InThreading(T->lchild); //递归左孩子线索化
	if (T->lchild == NULL)
	{ //如果该结点没有左孩子，设置ltag为Thread 并把lchild指向刚刚访问过的结点
		T->ltag = Thread;
		T->lchild = pre;
	}
	if (pre->rchild == NULL)
	{
		pre->rtag = Thread;
		pre->rchild = T;
	}
	pre = T;
	InThreading(T->rchild); //递归右孩子线索化
}

void InorderThreading(BiThrTree &p, BiThrTree T)
{
	p = (BiThrTree)malloc(sizeof(BiThrNode));
	p->ltag = Link;
	p->rtag = Thread;
	p->rchild = p;
	if (T == NULL)
	{ //如果是空树，指向自己本身
		p->lchild = p;
	}
	else
	{
		p->lchild = T; //如果树不为空，指向树的根节点
		pre = p;
		InThreading(T);
		pre->rchild = p;
		pre->rtag = Thread;
		p->rchild = pre;
	}
}

//中序遍历非递归
void inorderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;
	while (p != T)
	{
		while (p->ltag == Link)
		{
			p = p->lchild;
		}
		cout << p->data << ' ';
		while (p->rtag == Thread && p->rchild != T)
		{
			p = p->rchild;
			cout << p->data << ' ';
		}
		p = p->rchild;
	}
}

int main()
{
	BiThrTree p = NULL, T = NULL;
	T = createBiThrTree();
	InorderThreading(p, T);
	inorderTraverse(p);
	return 0;
}
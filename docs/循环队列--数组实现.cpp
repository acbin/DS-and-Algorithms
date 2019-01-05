#include <iostream>

using namespace std;

typedef struct Queue
{
	int *pBase;
	int front;
	int rear;
} QUEUE;

void init_queue(QUEUE *pQ)
{
	pQ->pBase = (int *)malloc(sizeof(int) * 6);
	pQ->front = 0;
	pQ->rear = 0;
}

bool is_full(QUEUE *pQ)
{
	if ((pQ->rear + 1) % 6 == pQ->front)
	{
		return true;
	}
	return false;
}

bool isempty(QUEUE *pQ)
{
	if (pQ->front == pQ->rear)
	{
		return true;
	}
	return false;
}

//入队尾部
void en_queue(QUEUE *pQ, int val)
{
	if (is_full(pQ))
	{
		return;
	}
	pQ->pBase[pQ->rear] = val;
	pQ->rear = (pQ->rear + 1) % 6;
	return;
}

//出队
void out_queue(QUEUE *pQ, int *val)
{
	if (isempty(pQ))
	{
		return;
	}
	*val = pQ->pBase[pQ->front];
	pQ->front = (pQ->front + 1) % 6;
	return;
}

void traverse_queue(QUEUE *pQ)
{
	if (isempty(pQ))
	{
		return;
	}
	int Cur = pQ->front;
	while (Cur != pQ->rear)
	{
		cout << pQ->pBase[Cur];
		Cur = (Cur + 1) % 6;
	}
	cout << endl;
	return;
}
int main()
{
	int i;
	QUEUE Q;
	init_queue(&Q);
	en_queue(&Q, 2);
	en_queue(&Q, 3);
	en_queue(&Q, 6);
	out_queue(&Q, &i);
	traverse_queue(&Q);
	cout << "hello..." << endl;
	system("pause");
	return 0;
}
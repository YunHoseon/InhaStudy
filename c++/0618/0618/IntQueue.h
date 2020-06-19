#pragma once

typedef struct IntQueue
{
	int max;	//�ִ� �뷮
	int num;	//���� ������ ����
	int head;	//ù��° ��� �ε���
	int tail;	//���� ������ �ε���
	int *que;	//ť�� ����� �迭
}IntQueue;

int Initialize(IntQueue *iq, int max);
int EnQue(IntQueue *iq, int x);
int Deque(IntQueue *iq, int *x);
int Peek(const IntQueue *iq, int *x);
void Clear(IntQueue *iq);
int Capacity(const IntQueue *iq);
int Size(const IntQueue *iq);
int IsEmpty(const IntQueue *iq);
int IsFull(const IntQueue *iq);
int Search(const IntQueue *iq, int x);
void Print(const IntQueue *iq);
void Terminate(IntQueue *iq);
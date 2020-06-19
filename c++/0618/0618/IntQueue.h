#pragma once

typedef struct IntQueue
{
	int max;	//최대 용량
	int num;	//현재 데이터 개수
	int head;	//첫번째 요소 인덱스
	int tail;	//가장 마지막 인덱스
	int *que;	//큐로 사용할 배열
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
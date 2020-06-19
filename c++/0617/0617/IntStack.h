#pragma once

#define ___IntStack

typedef struct IntStack
{
	int max;	//스택 최대용량
	int ptr;	//스택에 쌓인 메모리 수
	int *stk;	//데이터 저장할 배열의 포인터
}IntStack;

int Initialize(IntStack *s, int max);
int Push(IntStack *s, int x);
int Pop(IntStack *s, int *x);
int Peek(const IntStack *s, int x);
int Clear(IntStack *s);
int Capacity(const IntStack *s);
int size(const IntStack * s);
int IsEmpty(const IntStack *s);
int Isfull(const IntStack *s);
int Search(const IntStack s, int x);
void Print(const IntStack *s);
void Terminate(IntStack *s);
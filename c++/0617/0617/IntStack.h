#pragma once

#define ___IntStack

typedef struct IntStack
{
	int max;	//���� �ִ�뷮
	int ptr;	//���ÿ� ���� �޸� ��
	int *stk;	//������ ������ �迭�� ������
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
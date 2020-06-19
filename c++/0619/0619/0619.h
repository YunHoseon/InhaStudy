#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

typedef struct CharStack
{
	int max;	//���� �ִ�뷮
	int ptr;	//���ÿ� ���� �޸� ��
	char *stk;	//������ ������ �迭�� ������
}CharStack;

typedef struct CharQueue
{
	int max;	//�ִ� �뷮
	int num;	//���� ������ ����
	int head;	//ù��° ��� �ε���
	int tail;	//���� ������ �ε���
	char *que;	//ť�� ����� �迭
}CharQueue;

string ReadFile(string s);
void SplitStr(string s, CharStack *cs, CharQueue *cq);

/*stack*/
int StackInitialize(CharStack *s, char max);
int Push(CharStack *s, char x);
int Pop(CharStack *s, char *x);
int StackPeek(const CharStack *s, char *x);
void StackClear(CharStack *s);
int StackSearch(const CharStack *s, int x);
void StackPrint(const CharStack *s);
void StackTerminate(CharStack *s);

/*queue*/
int QueueInitialize(CharQueue *iq, char max);
int EnQue(CharQueue *iq, char x);
int Deque(CharQueue *iq, char *x);
int QueuePeek(const CharQueue *iq, char *x);
void QueueClear(CharQueue *iq);
int QueueSearch(const CharQueue *iq, int x);
void QueuePrint(const CharQueue *iq);
void QueueTerminate(CharQueue *iq);
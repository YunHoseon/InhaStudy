#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

typedef struct CharStack
{
	int max;	//스택 최대용량
	int ptr;	//스택에 쌓인 메모리 수
	char *stk;	//데이터 저장할 배열의 포인터
}CharStack;

typedef struct CharQueue
{
	int max;	//최대 용량
	int num;	//현재 데이터 개수
	int head;	//첫번째 요소 인덱스
	int tail;	//가장 마지막 인덱스
	char *que;	//큐로 사용할 배열
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
#include<iostream>
#include "IntStack.h"
#include <processthreadsapi.h>

using namespace std;

int main()
{
	int nInput = 0;
	IntStack *intStk = new IntStack;

	cout << "스택의 최대 메모리 : ";
	cin >> nInput;

	Initialize(intStk, nInput);

}

void __cdecl MyNewHandler()
{
	printf("메모리 할당이 실패했습니다. \r\n");
	ExitProcess(FALSE);
	return;
}

int Initialize(IntStack * s, int max)
{
	set_new_handler(MyNewHandler);
	
	s->ptr = 0;
	s->max = max;

	return 0;
}

int Push(IntStack * s, int x)
{
	if (s->ptr >= s->max)
		return -1;
	
	s->stk[s->ptr++] = x;
	return 0;
}

int Pop(IntStack * s, int * x)
{
	if (s->ptr <= 0)
		return -1;

	*x = s->stk[s->ptr - 1];
	s->ptr--;
	return 0;
}

int Peek(const IntStack * s, int x)
{

	return 0;
}

int Clear(IntStack * s)
{
	return 0;
}

int Capacity(const IntStack * s)
{
	return 0;
}

int size(const IntStack * s)
{
	return 0;
}

int IsEmpty(const IntStack * s)
{
	return 0;
}

int Isfull(const IntStack * s)
{
	return 0;
}

int Search(const IntStack s, int x)
{
	return 0;
}

void Print(const IntStack * s)
{
}

void Terminate(IntStack * s)
{
}

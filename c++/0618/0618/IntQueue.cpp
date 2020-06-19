#include "IntQueue.h"
#include <iostream>

using namespace std;

int main()
{
	IntQueue *iq = new IntQueue;
	Initialize(iq, 6);

	while (1)
	{
		int nInput = -1;
		int x = 0;
		int ret = 0;
		printf("현재 데이터 수 : %d/%d\n", Size(iq), Capacity(iq));
		printf("(1) 인큐 (2) 디큐 (3) 피크 (4) 출력 (5) 검색 (0)종료");
		cin >> nInput;

		switch (nInput)
		{
		case 0:
			Terminate(iq);
			exit(0);

		case 1:
			cout << "데이터 : ";
			cin >> x;
			ret = EnQue(iq, x);

			if (ret == -1)
				cout << "인큐 실패!";
			break;

		case 2:
			if (Deque(iq, &x) == -1)
				cout << "디큐 실패!";
			else
				printf("디큐한 데이터는 %d입니다.\n", x);
			break;

		case 3:
			if (Peek(iq, &x) == -1)
				cout << "피크 실패!";
			else
				printf("피크한 데이터는 %d입니다.\n", x);
			break;

		case 4:
			cout << "큐의 모든데이터 출력" << endl;
			Print(iq);
			break;

		case 5:
			cout << "찾을 값을 입력하세요 : ";
			cin >> x;
			ret = Search(iq, x);

			if (ret == -1)
				cout << "검색 실패";
			else
				printf("값 %d는 que[%d]에 있습니다.", x, ret);
			break;
		}
	}
}

int Initialize(IntQueue * iq, int max)
{
	iq->que = new int[max];
	iq->head = 0;
	iq->tail = 0;
	iq->num = 0;

	iq->max = max;

	return 0;
}

int EnQue(IntQueue * iq, int x)
{
	if (iq->num == iq->max)
		return -1;

	iq->num++;
	iq->que[iq->tail++] = x;

	if (iq->tail == iq->max)
		iq->tail = 0;
	return 0;
}

int Deque(IntQueue * iq, int *x)
{
	if (iq->num <= 0)
		return -1;

	iq->num--;
	*x = iq->que[iq->head++];

	if (iq->head == iq->max)
		iq->head = 0;
}

int Peek(const IntQueue * iq, int *x)
{
	if (iq->num <= 0)
		return -1;

	*x = iq->que[iq->head];
	return 0;
}

void Clear(IntQueue * iq)
{
	iq->num = 0;
	iq->head = 0;
	iq->tail = 0;
}

int Capacity(const IntQueue * iq)
{
	return iq->max;
}

int Size(const IntQueue * iq)
{
	return iq->num;
}

int IsEmpty(const IntQueue * iq)
{
	if (iq->num == 0)
		return 1;
	else
		return 0;
}

int IsFull(const IntQueue * iq)
{
	if (iq->num == iq->max)
		return 1;
	else
		return 0;
}

int Search(const IntQueue * iq, int x)
{
	for (int i = 0; i < iq->num; i++)
	{
		if (x == iq->que[(i + iq->head) % iq->max])
			return i;
	}
	return -1;
}

void Print(const IntQueue * iq)
{
	for (int i = 0; i < iq->num; i++)
	{
		cout << iq->que[(i + iq->head) % iq->max] << " ";
	}
}

void Terminate(IntQueue * iq)
{
	if(iq->que != NULL)
		delete iq->que;

	iq->head = 0;
	iq->tail = 0;
	iq->num = 0;
	iq->max = 0;
}

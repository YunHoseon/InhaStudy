#include "Stopwatch.h"
#include <iostream>
#include <time.h>
#include <math.h>

#define SIZE 9

using namespace std;

bool CheckSort(int arr[])
{
	for (int i = 0; i < SIZE - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
}

void HeapSort(int arr[])
{
	int tmp = 0;
	int cnt = 0;
	int parent = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE/3; j++)
		{
			if (arr[(i - 1) / 2] < arr[i])	//자신이 부모보다 크다면
			{
				tmp = arr[(i - 1) / 2];
				arr[(i - 1) / 2] = arr[i];
				arr[i] = tmp;

				i = (i - 1) / 2;	//자신위치 업데이트
			}
			else
				break;
		}
	}

	cout << "힙 배열 :  ";
	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << endl;
	

	for (int i = 0; i < SIZE - i; i++)
	{
		tmp = arr[0];
		arr[0] = arr[SIZE -1- i];
		arr[SIZE -1- i] = tmp;
		int moveIdx = 0;

		for (int j = 0; j < SIZE; j++)
		{
			if (i * 2 + 1 < SIZE - i && arr[i] > arr[i * 2 + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i * 2 + 1];
				arr[i * 2 + 1] = tmp;

				i = i * 2 + 1;
			}
			else if (i * 2 + 2 < SIZE - i && arr[i] > arr[i * 2 + 2])
			{
				tmp = arr[i];
				arr[i] = arr[i * 2 + 2];
				arr[i * 2 + 2] = tmp;

				i = i * 2 + 2;
			}
			else
				break;
		}
	}

	//while (1)
	//{
	//	if (cnt >= SIZE-1)
	//		break;
	//
	//	for (int i = 0; i < SIZE-cnt; i++)
	//	{
	//		for (int j = 0; j < SIZE / 3; j++)
	//		{
	//			if (arr[(i - 1) / 2] < arr[i])	//자신이 부모보다 크다면
	//			{
	//				tmp = arr[(i - 1) / 2];
	//				arr[(i - 1) / 2] = arr[i];
	//				arr[i] = tmp;
	//
	//				i = (i - 1) / 2;	//자신위치 업데이트
	//			}
	//			else
	//				break;
	//		}
	//
	//		/*if (arr[i] > arr[i * 2 + 1] && arr[i] > arr[i * 2 + 2])
	//			continue;*/
	//	}
	//
	//	tmp = arr[0];
	//	arr[0] = arr[SIZE - 1 - cnt];
	//	arr[SIZE - 1 - cnt] = tmp;
	//
	//	cnt++;
	//}
}

int QuickSort(int randNumArr[], int _left, int _right)		//배열, 왼쪽 인덱스, 오른쪽 인덱스
{
	int pivot = _left;										//맨 왼쪽 값
	int pl = _left, pr = _right + 1;						//while에서 --pr하므로 +1
	int tmp = 0;

	if (pr - _left <= 0 || _right - pl <= 0)				//리스트 크기 <= 0 일 때 종료
		return 0;

	for (; ; )
	{
		if (pl > pr)	//두 인덱스가 교차됐을 때
			break;

		while (pl < _right && randNumArr[++pl] < randNumArr[pivot]);	//pl이 가장 마지막 인덱스보다 작고, 피벗보다 값이 작을 때 ++pl
		while (pr > _left && randNumArr[--pr] > randNumArr[pivot]);		//pr이 가장 첫번째 인덱스보다 크고, 피벗보다 값이 클 때 --pr

		if (pl < pr)	//아직 교차하지 않았고, pr과 pl이 둘다 멈췄을 때
		{
			tmp = randNumArr[pl];
			randNumArr[pl] = randNumArr[pr];
			randNumArr[pr] = tmp;
		}
	}

	if (randNumArr[pivot] > randNumArr[pl])	//pr이 pl보다 작을 때
	{
		tmp = randNumArr[pivot];
		randNumArr[pivot] = randNumArr[pl];
		randNumArr[pl] = tmp;
	}
	else									//피벗과 [pr]값 교환
	{
		tmp = randNumArr[pivot];
		randNumArr[pivot] = randNumArr[pr];
		randNumArr[pr] = tmp;
	}

	/*for (int i = 0; i < SIZE; i++)
		cout << randNumArr[i] << " ";
	cout << "| pl : " << pl << " pr : " << pr << " pivot : " << pivot << endl;*/

	QuickSort(randNumArr, _left, pr);	//왼쪽 정렬
	QuickSort(randNumArr, pl, _right);	//오른쪽 정렬
}

int main()
{
	int arr[SIZE] = { 5,1,7,4,6,2,3,9,8 };
	Stopwatch stopwatch;

	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(1, SIZE*SIZE);

	srand((unsigned)time(NULL));
	int randNumArr[SIZE] = { 0 };
	int randNumArr2[SIZE] = { 0 };

	for (int i = 0; i < SIZE; i++)
	{
		int randNum = dis(gen);
		randNumArr[i] = randNum;
	}

	for (int i = 0; i < SIZE; i++)
		randNumArr2[i] = randNumArr[i];

	/*stopwatch.StartTimer();
	QuickSort(randNumArr2, 0, SIZE - 1);
	stopwatch.StopTimer();

	if (CheckSort(randNumArr2))
		cout << "quick : true" << endl;
	else
		cout << "quick : false" << endl;

	cout << "퀵 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;*/

	stopwatch.StartTimer();
	HeapSort(arr);
	stopwatch.StopTimer();

	if (CheckSort(arr))
		cout << "heap : true" << endl;
	else
		cout << "heap : false" << endl;

	cout << "힙 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;
	
	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << endl;
}
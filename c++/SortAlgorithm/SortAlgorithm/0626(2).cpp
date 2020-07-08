#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Stopwatch.h"

#define SIZE 100000

using namespace std;

void InsertSort(int arr[], int n)
{
	int tmp;
	int idx;

	for (int i = 1; i < n; i++)
	{
		idx = i;
		for (int j = i-1; j >= 0; j--)
		{
			if (arr[idx] < arr[j])
			{
				tmp = arr[idx];
				arr[idx] = arr[j];
				arr[j] = tmp;
				idx--;
			}
			else
				break;
		}
	}
}

//int main()
//{
//	Stopwatch stopwatch;
//
//	random_device rd;
//	mt19937_64 gen(rd());
//	uniform_int_distribution<int> dis(1, SIZE*SIZE);
//
//	srand((unsigned)time(NULL));
//	int randNumArr[SIZE] = { 0 };
//
//	for (int i = 0; i < SIZE; i++)
//	{
//		int randNum = dis(gen);
//		randNumArr[i] = randNum;
//	}
//
//	stopwatch.StartTimer();
//	InsertSort(randNumArr, SIZE);
//	stopwatch.StopTimer();
//
//	cout << "삽입 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;
//}
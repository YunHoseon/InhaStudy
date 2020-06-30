#include <iostream>
#include <time.h>
#include "Stopwatch.h"

#define SIZE 100000
using namespace std;

bool CheckSort(int arr[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
}

void ShellSort(int arr[], int n)
{
	int tmp;
	int idx;
	int h = 0;

	for (h = n / 2; h > 0; h /= 2)
	{
		for (int i = h; i < n; i++)
		{
			idx = i;
			for (int j = i - h; j >= 0; j -= h)
			{
				if (arr[idx] < arr[j])
				{
					tmp = arr[idx];
					arr[idx] = arr[j];
					arr[j] = tmp;
					idx -= h;
				}
				else
					break;
			}
		}
	}

	if(CheckSort(arr, SIZE))
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

int main()
{
	Stopwatch stopwatch;

	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(1, SIZE*SIZE);

	srand((unsigned)time(NULL));
	int randNumArr[SIZE] = { 0 };

	for (int i = 0; i < SIZE; i++)
	{
		int randNum = dis(gen);
		randNumArr[i] = randNum;
	}

	stopwatch.StartTimer();
	ShellSort(randNumArr, SIZE);
	stopwatch.StopTimer();

	cout << "셸 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;
}
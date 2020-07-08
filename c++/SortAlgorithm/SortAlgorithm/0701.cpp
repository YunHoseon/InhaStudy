#include <iostream>
#include <vector>
#include <time.h>
#include "Stopwatch.h"

#define SIZE 10

using namespace std;

bool CheckSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
}

int QuickSort(int randNumArr[], int _left, int _right)		//배열, 왼쪽 인덱스, 오른쪽 인덱스
{
	int pivot = _left;										//맨 왼쪽 값
	int pl = _left, pr = _right + 1;						//while에서 --pr하므로 +1
	int tmp = 0;

	if (pr - _left <= 0 || _right - pl <= 0)				//리스트 크기 <= 0 일 때 종료
		return 0;

	for ( ; ; )
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
		
		//for (int j = 0; j < arr.size() - 1; j++)
		//{
		//	if (arr[pl] > arr[pivot])
		//	{
		//		pl_search = true;
		//		break;
		//	}
		//	pl++;
		//}
		//
		//for (int j = 0; j < arr.size() - 1; j++)
		//{
		//	if (arr[pr] < arr[pivot])
		//	{
		//		pr_search = true;
		//		break;
		//	}
		//	pr--;
		//}
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
	
	for (int i = 0; i < SIZE; i++)
		cout << randNumArr[i] << " ";
	cout << "| pl : " << pl << " pr : " << pr << " pivot : " << pivot << endl;

	QuickSort(randNumArr, _left, pr);	//왼쪽 정렬
	QuickSort(randNumArr, pl, _right);	//오른쪽 정렬
}

int main()
{
	vector<double> arr = { 2,5,1,7,4,6,2,2,2,3,9,8 , 2,-2, 12};
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

	for (int i = 0; i < SIZE; i++)
	{
		cout << randNumArr[i] << " ";
	}
	cout << endl;

	stopwatch.StartTimer();
	QuickSort(randNumArr, 0, SIZE - 1);
	stopwatch.StopTimer();

	if (CheckSort(randNumArr, SIZE))
		cout << "true" << endl;
	else
		cout << "false" << endl;

	cout << "퀵 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;
	/*for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";*/
}

//void Solution(vector<string> order_times, int k)
//{
//	int max = 0, tmp = 0;
//	vector<int> order_minutes;
//	vector<int> answer;
//
//	//order_minutes 대입
//	for (int i = 0; i < order_times.size(); i++)
//		order_minutes.push_back(((((order_times[i][0] - '0') * 10) + (order_times[i][1] - '0')) * 60) + 
//							((order_times[i][3] - '0') * 10) + (order_times[i][4] - '0'));
//
//	for (int i = 0; i < order_minutes.size()-1; i++)
//	{
//		for (int j = i + 1; j <  order_minutes.size(); j++)
//		{
//			if (abs(order_minutes[i] - order_minutes[j]) <= k)
//				answer.push_back(j - i + 1);
//			else 
//				break;
//		}
//	}
//
//	max = answer[0];
//	for (int i = 0; i < answer.size(); i++)
//	{
//		if (max < answer[i])
//		{
//			tmp = max;
//			max = answer[i];
//			answer[i] = tmp;
//		}
//	}
//
//	////order_minutes 출력
//	//vector<int>::iterator it;
//	//for (it = order_minutes.begin(); it <order_minutes.end(); it++)
//	//	cout << *it << " ";
//
//	cout << max << endl;
//}
//
//int main()
//{
//	vector<string> order_times;
//	order_times.push_back("12:10");
//	order_times.push_back("12:20");
//	order_times.push_back("12:40");
//	order_times.push_back("12:40");
//	order_times.push_back("12:50");
//	order_times.push_back("12:59");
//	order_times.push_back("13:20");
//
//	Solution(order_times, 20);
//}
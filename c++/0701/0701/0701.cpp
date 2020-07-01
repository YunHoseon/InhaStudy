#include <iostream>
#include <vector>
#include <time.h>

#define SIZE 10

using namespace std;

int QuickSort(vector<int>& arr, int n, int _pl, int _pr)		//배열, 개수, 왼쪽 인덱스, 오른쪽 인덱스
{
	int pivot = _pl - 1;
	int tmp = 0;
	bool pl_search = false, pr_search = false;
	int pl = _pl, pr = _pr;

	if (pr - _pl <= 0 || _pr - pl <= 0)
		return 0;

	for (int i = 0; i < n - 1; i++)
	{
		if (pl > pr)
			break;

		for (int j = 0; j < n - 1; j++)
		{
			if (arr[pl] > arr[pivot])
			{
				pl_search = true;
				break;
			}
			pl++;
		}

		for (int j = 0; j < n - 1; j++)
		{
			if (arr[pr] < arr[pivot])
			{
				pr_search = true;
				break;
			}
			pr--;
		}

		if (pl_search && pr_search)
		{
			tmp = arr[pl];
			arr[pl] = arr[pr];
			arr[pr] = tmp;
			pl_search = false;
			pr_search = false;
		}
		
	}
	tmp = arr[pivot];
	arr[pivot] = arr[pl];
	arr[pl] = tmp;

	pivot = pr;

	if (pivot > _pl)
		QuickSort(arr, pr - _pl + 1, _pl, pr - 1);
	if (_pr > pivot)
		QuickSort(arr, _pr - pl + 1, pl + 1, _pr);
}

int main()
{
	vector<int> arr = { 5,1,7,4,6,2,3,9,8 };

	QuickSort(arr, 9, 1, 9-1);

	for (int i = 0; i < arr.size(); i++)
	{
	cout << arr[i] << " ";
	}
	cout << endl;
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
#include <iostream>
#include <vector>
#include <time.h>

#define SIZE 10

using namespace std;

int QuickSort(vector<double> &arr, int _left, int _right)		//배열, 개수, 왼쪽 인덱스, 오른쪽 인덱스
{
	int pivot = _left;
	int tmp = 0;
	bool pl_search = false, pr_search = false;
	int pl = _left, pr = _right + 1;

	if (pr - _left <= 0 || _right - pl <= 0)
		return 0;

	for ( ; ; )
	{
		if (pl > pr)
			break;

		while (pl < _right && arr[++pl] < arr[pivot]);
		while (pr > _left && arr[--pr] > arr[pivot]);

		if (pl < pr)
		{
			tmp = arr[pl];
			arr[pl] = arr[pr];
			arr[pr] = tmp;
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
		//
		//if (pl_search && pr_search)
		//{
		//	tmp = arr[pl];
		//	arr[pl] = arr[pr];
		//	arr[pr] = tmp;
		//	pl_search = false;
		//	pr_search = false;
		//}
	}
	if (arr[pivot] > arr[pl])
	{
		tmp = arr[pivot];
		arr[pivot] = arr[pl];
		arr[pl] = tmp;
	}
	tmp = arr[pivot];
	arr[pivot] = arr[pr];
	arr[pr] = tmp;


	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << "pl : " << pl << " pr : " << pr << endl;
	QuickSort(arr, _left, pr);
	QuickSort(arr, pl, _right);
}

int main()
{
	vector<double> arr = { 2,5,1,7,4,6,2,2,2,3,9,8 , 2,-2, 12};

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
	QuickSort(arr, 0, arr.size() - 1);

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
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
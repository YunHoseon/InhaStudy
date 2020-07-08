#include <iostream>
#include <time.h>
#include <random>

#define SIZE 9

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

int MergeSort(int arr[], int left, int right)
{
	int pl = left, pr = right;
	int tmp;
	int tmpArr[SIZE] = { 0 };

	//if ((left + right) / 2 <= 0 || right <= 0)				//리스트 크기 <= 0 일 때 종료
	//	return 0;

	return 0;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	MergeSort(arr, left, (left + right) / 2);
	MergeSort(arr, (left + right) / 2 + 1, right);

	/*while(1)
	{
		
	}*/
}

int main()
{
	int arr[9] = { 5,1,7,4,6,2,3,9,8 };
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

	//MergeSort(randNumArr, 0, SIZE - 1);
	MergeSort(arr, 0, SIZE-1);

	for (int i = 0; i < SIZE; i++)	//정렬된 배열 출력
		cout << arr[i] << " ";
	cout << endl;

}
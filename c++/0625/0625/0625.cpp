#include "Stopwatch.h"
#include "Rectangle.h"
#include "MyPoint.h"

#define SIZE 100000
#define swap(type,x,y) do {type t = x; x = y; y = t;} while(0)

void BubbleSort(int arr[], int n)
{
	for (int i = 0; i < n -1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (arr[j-1] > arr[j])
			{
				swap(int, arr[j-1], arr[j]);
			}
		}
	}
}

void SelectionSort(int arr[], int n)
{
	int min = 0;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min])
				min = j;		
		}
		swap(int, arr[i], arr[min]);
	}
}

int main()
{
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
		randNumArr2[i] = randNumArr[i];
	}

	stopwatch.StartTimer();
	SelectionSort(randNumArr2, SIZE);
	stopwatch.StopTimer();

	cout << "선택 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;

	//for (int i = 0; i < SIZE; i++)
	//{
	//	cout << randNumArr2[i] << " ";
	//}

	stopwatch.StartTimer();
	BubbleSort(randNumArr, SIZE);
	stopwatch.StopTimer();

	cout << "버블 정렬에 걸린 시간 : " << (double)stopwatch.getElapsedTime() / 1000 << endl;

	//for (int i = 0; i < SIZE; i++)
	//{
	//	cout << randNumArr[i] << " ";
	//}
	/*for (int i = 0; i < sizeof(randNumArr) / sizeof(int); i++)
	{
		cout << randNumArr[i] << " ";
	}*/
}

//int main()
//{
//	MyPoint pt1;
//	MyPoint pt2(10, 30.5);
//
//	printf("pt1(%.2f, %.2f)와 pt2(%.2f, %.2f) 사이의 거리 : %.2f", pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY(), pt1.Distance(&pt2));
//}

//int main()
//{
//	Rectangle rect1(4, 40);
//	Rectangle rect2(3.5, 35.9);
//	Rectangle rect3;
//
//	printf("첫 번째 객체\t width = %.2f, height = %.2f, area = %.2f, Perimeter = %.2f\n", rect1.GetWidth(), rect1.GetHeight(), rect1.GetArea(), rect1.GetPerimeter());
//	printf("두 번째 객체\t width = %.2f, height = %.2f, area = %.2f, Perimeter = %.2f\n", rect2.GetWidth(), rect2.GetHeight(), rect2.GetArea(), rect2.GetPerimeter());
//	printf("세 번째 객체\t width = %.2f, height = %.2f, area = %.2f, Perimeter = %.2f\n", rect3.GetWidth(), rect3.GetHeight(), rect3.GetArea(), rect3.GetPerimeter());
//}
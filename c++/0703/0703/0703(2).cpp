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
			if (arr[(i - 1) / 2] < arr[i])	//�ڽ��� �θ𺸴� ũ�ٸ�
			{
				tmp = arr[(i - 1) / 2];
				arr[(i - 1) / 2] = arr[i];
				arr[i] = tmp;

				i = (i - 1) / 2;	//�ڽ���ġ ������Ʈ
			}
			else
				break;
		}
	}

	cout << "�� �迭 :  ";
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
	//			if (arr[(i - 1) / 2] < arr[i])	//�ڽ��� �θ𺸴� ũ�ٸ�
	//			{
	//				tmp = arr[(i - 1) / 2];
	//				arr[(i - 1) / 2] = arr[i];
	//				arr[i] = tmp;
	//
	//				i = (i - 1) / 2;	//�ڽ���ġ ������Ʈ
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

int QuickSort(int randNumArr[], int _left, int _right)		//�迭, ���� �ε���, ������ �ε���
{
	int pivot = _left;										//�� ���� ��
	int pl = _left, pr = _right + 1;						//while���� --pr�ϹǷ� +1
	int tmp = 0;

	if (pr - _left <= 0 || _right - pl <= 0)				//����Ʈ ũ�� <= 0 �� �� ����
		return 0;

	for (; ; )
	{
		if (pl > pr)	//�� �ε����� �������� ��
			break;

		while (pl < _right && randNumArr[++pl] < randNumArr[pivot]);	//pl�� ���� ������ �ε������� �۰�, �ǹ����� ���� ���� �� ++pl
		while (pr > _left && randNumArr[--pr] > randNumArr[pivot]);		//pr�� ���� ù��° �ε������� ũ��, �ǹ����� ���� Ŭ �� --pr

		if (pl < pr)	//���� �������� �ʾҰ�, pr�� pl�� �Ѵ� ������ ��
		{
			tmp = randNumArr[pl];
			randNumArr[pl] = randNumArr[pr];
			randNumArr[pr] = tmp;
		}
	}

	if (randNumArr[pivot] > randNumArr[pl])	//pr�� pl���� ���� ��
	{
		tmp = randNumArr[pivot];
		randNumArr[pivot] = randNumArr[pl];
		randNumArr[pl] = tmp;
	}
	else									//�ǹ��� [pr]�� ��ȯ
	{
		tmp = randNumArr[pivot];
		randNumArr[pivot] = randNumArr[pr];
		randNumArr[pr] = tmp;
	}

	/*for (int i = 0; i < SIZE; i++)
		cout << randNumArr[i] << " ";
	cout << "| pl : " << pl << " pr : " << pr << " pivot : " << pivot << endl;*/

	QuickSort(randNumArr, _left, pr);	//���� ����
	QuickSort(randNumArr, pl, _right);	//������ ����
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

	cout << "�� ���Ŀ� �ɸ� �ð� : " << (double)stopwatch.getElapsedTime() / 1000 << endl;*/

	stopwatch.StartTimer();
	HeapSort(arr);
	stopwatch.StopTimer();

	if (CheckSort(arr))
		cout << "heap : true" << endl;
	else
		cout << "heap : false" << endl;

	cout << "�� ���Ŀ� �ɸ� �ð� : " << (double)stopwatch.getElapsedTime() / 1000 << endl;
	
	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << " ";
	cout << endl;
}
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

const int MAX = 10;

void RadixSort()
{

}

int main()
{
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(0, MAX);

	srand((unsigned)time(NULL));
	vector<int> arr;

	for (int i = 0; i < MAX; i++)
	{
		int randNum = dis(gen);
		arr.push_back(randNum);
	}
}

//const int MAX = 10;
//
//void fSort(vector<int> arr)	//�迭
//{
//	int maxNum;	//�迭 �� ���� ū ��
//	vector<int> cntArr;	
//	int cnt = 0;
//
//	maxNum = arr[0];
//	for (int i = 1; i < arr.size(); i++)	//�迭 �� ���� ū �� ���ϱ�
//	{
//		if (maxNum < arr[i])
//			maxNum = arr[i];
//	}
//
//	for (int i = 0; i < maxNum+1; i++)		//���� ū ����ŭ �迭 ����
//		cntArr.push_back(0);
//
//	for (int i = 0; i <arr.size(); i++)		//���� ����
//		cntArr[arr[i]] += 1;
//		
//	for (int i = 0; i < cntArr.size(); i++)	//���
//		cout << cntArr[i] << " ";
//	cout << endl;
//
//	for (int i = 0; i < cntArr.size(); i++)	//����
//	{
//		for (int j = 0; j < cntArr[i]; j++)
//		{
//			arr[cnt] = i;
//			cnt++;
//		}
//	}
//
//	for (int i = 0; i < arr.size(); i++)	//���
//		cout << arr[i] << " ";
//	cout << endl;
//}
//
//int main()
//{
//	random_device rd;
//	mt19937_64 gen(rd());
//	uniform_int_distribution<int> dis(0, MAX);
//
//	srand((unsigned)time(NULL));
//	vector<int> arr;
//
//	for (int i = 0; i < MAX; i++)
//	{
//		int randNum = dis(gen);
//		arr.push_back(randNum);
//	}
//
//	fSort(arr);
//}
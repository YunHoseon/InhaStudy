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
//void fSort(vector<int> arr)	//배열
//{
//	int maxNum;	//배열 중 가장 큰 값
//	vector<int> cntArr;	
//	int cnt = 0;
//
//	maxNum = arr[0];
//	for (int i = 1; i < arr.size(); i++)	//배열 중 가장 큰 값 구하기
//	{
//		if (maxNum < arr[i])
//			maxNum = arr[i];
//	}
//
//	for (int i = 0; i < maxNum+1; i++)		//가장 큰 값만큼 배열 생성
//		cntArr.push_back(0);
//
//	for (int i = 0; i <arr.size(); i++)		//개수 대입
//		cntArr[arr[i]] += 1;
//		
//	for (int i = 0; i < cntArr.size(); i++)	//출력
//		cout << cntArr[i] << " ";
//	cout << endl;
//
//	for (int i = 0; i < cntArr.size(); i++)	//정렬
//	{
//		for (int j = 0; j < cntArr[i]; j++)
//		{
//			arr[cnt] = i;
//			cnt++;
//		}
//	}
//
//	for (int i = 0; i < arr.size(); i++)	//출력
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
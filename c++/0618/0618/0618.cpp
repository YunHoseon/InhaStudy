#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

//int main()
//{
//
//}

//typedef struct POINT
//{
//	float x;
//	float y;
//}POINT;
//
//bool IsInCircle(POINT pt)
//{
//	float len = pow(pow(pt.x, 2) + pow(pt.y, 2), 0.5);
//
//	if (len <= 10)
//		return true;
//	else
//		return false;
//}
//
//int main()
//{
//	POINT *pt = new POINT;
//
//	cout << "점의 좌표를 입력하세요 : ";
//	cin >> pt->x >> pt->y;
//
//	if (IsInCircle(*pt))
//		printf(" 점 (%.2f, %.2f)는 반지름 10인 원 안에 있습니다.", pt->x, pt->y);
//	else
//		printf(" 점 (%.2f, %.2f)는 반지름 10인 원 안에 있지 않습니다.", pt->x, pt->y);
//}

//typedef struct POINT
//{
//	float x;
//	float y;
//}POINT;
//
//float CalDist(vector<POINT> pt, int idx, int idx2)
//{
//	float len = 0;
//	len = pow(abs(pow(pt[idx].x, 2) - pow(pt[idx2].x, 2)) + abs(pow(pt[idx].y, 2) - pow(pt[idx2].y, 2)), 0.5);
//
//	return len;
//}
//
//void NearPoint(vector<POINT> pt, int nInput)
//{
//	int calNum = 0, nInput_ = nInput;
//	POINT tmp[2];
//	float shortestLen = 0, len = 0;
//
//	shortestLen = CalDist(pt, 0, 1);
//	tmp[0] = pt[0];
//	tmp[1] = pt[1];
//
//	for (int i = 0; i < nInput - 1; i++)
//	{
//		for (int j =i+1; j < nInput_; j++)
//		{
//			len = CalDist(pt, i, j);
//
//			if (len < shortestLen)
//			{
//				tmp[0] = pt[i];
//				tmp[1] = pt[j];
//			}
//		}
//	}
//	printf("가장 가까운 점들은 (%.2f, %.2f) , (%.2f, %.2f)", tmp[0].x, tmp[0].y, tmp[1].x, tmp[1].y);
//}
//
//int main()
//{
//	int cnt = 0;
//	vector<POINT> pt;
//
//	do 
//	{
//		POINT tmp;
//		cout << cnt + 1 << "번째 점의 좌표를 입력하세요 (중지 = !) : ";
//		cin >> tmp.x >> tmp.y;
//		pt.push_back(tmp);
//		cnt++;
//	} while (getchar() != '!');
//
//	NearPoint(pt, cnt);
//}

//string version1(const string &s1, const string &s2);
//const string &version2( string &s1, const string &s2);
//const string &version3( string &s1, const string &s2);;
//
//int main()
//{
//	string input;
//	string copy;
//	string result;
//
//	cout << "문자열을 입력하시오 : ";
//	getline(cin, input);
//	copy = input;
//
//	cout << "입력한 문자열 : " << input << endl;
//	result = version1(input, "***");
//	cout << "바뀐 문자열 : " << result << endl;
//	cout << "원래 문자열 : " << input << endl;
//
//	result = version2(input, "###");
//	cout << "바뀐 문자열 : " << result << endl;
//	cout << "원래 문자열 : " << input << endl;
//
//	cout << "원래 문자열 재설정\n";
//	input = copy;
//	result = version3(input, "@@@");
//	cout << "바뀐 문자열 : " << result << endl;
//	cout << "원래 문자열 : " << input << endl;
//}
//
//string version1(const string &s1, const string &s2)
//{
//	string temp;
//
//	temp = s2 + s1 + s2;
//	return temp;
//}
//
//const string &version2(string &s1, const string &s2)
//{
//	s1 = s2 + s1 + s2;
//	return s1;
//}
//
//const string &version3(string &s1, const string &s2)
//{
//	string temp;
//
//	temp = s2 + s1 + s2;
//	return temp;
//}

/*void swapr(int &a, int &b);
void swapp(int *p, int *q);
void swapv(int a, int b);

int main()
{
	int wallet1 = 3000;
	int wallet2 = 3500;

	cout << "지갑 1 = " << wallet1 << "원";
	cout << "지갑 2 = " << wallet2 << "원\n";

	cout << "참조를 이용한 내용들을 교환 : \n";
	swapr(wallet1, wallet2);
	cout << "지갑 1 = " << wallet1 << "원";
	cout << "지갑 2 = " << wallet2 << "원\n";

	cout << "포인터를 이용한 내용들을 다시 교환 : \n";
	swapp(&wallet1, &wallet2);
	cout << "지갑 1 = " << wallet1 << "원";
	cout << "지갑 2 = " << wallet2 << "원\n";

	cout << "값으로 전달하여 내용 교환 시도 : \n";
	swapv(wallet1, wallet2);
	cout << "지갑 1 = " << wallet1 << "원";
	cout << "지갑 2 = " << wallet2 << "원\n";
}

void swapr(int &a, int &b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
}

void swapp(int *p, int *q)
{
	int temp;

	temp = *p;
	*p = *q;
	*q = temp;
}

void swapv(int a, int b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
}*/

//int main()
//{
//	int rats = 101;
//	int &rodents = rats;
//
//	cout << "rats = " << rats;
//	cout << ",  rodents = " << rodents << endl;
//	rodents++;
//	cout << "rats = " << rats;
//	cout << ",  rodents = " << rodents << endl;
//
//	cout << "rats의 주소 = " << &rats;
//	cout << ",  rodents의 주소 = " << &rodents << endl;
//}
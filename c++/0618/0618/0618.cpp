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
//	cout << "���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> pt->x >> pt->y;
//
//	if (IsInCircle(*pt))
//		printf(" �� (%.2f, %.2f)�� ������ 10�� �� �ȿ� �ֽ��ϴ�.", pt->x, pt->y);
//	else
//		printf(" �� (%.2f, %.2f)�� ������ 10�� �� �ȿ� ���� �ʽ��ϴ�.", pt->x, pt->y);
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
//	printf("���� ����� ������ (%.2f, %.2f) , (%.2f, %.2f)", tmp[0].x, tmp[0].y, tmp[1].x, tmp[1].y);
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
//		cout << cnt + 1 << "��° ���� ��ǥ�� �Է��ϼ��� (���� = !) : ";
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
//	cout << "���ڿ��� �Է��Ͻÿ� : ";
//	getline(cin, input);
//	copy = input;
//
//	cout << "�Է��� ���ڿ� : " << input << endl;
//	result = version1(input, "***");
//	cout << "�ٲ� ���ڿ� : " << result << endl;
//	cout << "���� ���ڿ� : " << input << endl;
//
//	result = version2(input, "###");
//	cout << "�ٲ� ���ڿ� : " << result << endl;
//	cout << "���� ���ڿ� : " << input << endl;
//
//	cout << "���� ���ڿ� �缳��\n";
//	input = copy;
//	result = version3(input, "@@@");
//	cout << "�ٲ� ���ڿ� : " << result << endl;
//	cout << "���� ���ڿ� : " << input << endl;
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

	cout << "���� 1 = " << wallet1 << "��";
	cout << "���� 2 = " << wallet2 << "��\n";

	cout << "������ �̿��� ������� ��ȯ : \n";
	swapr(wallet1, wallet2);
	cout << "���� 1 = " << wallet1 << "��";
	cout << "���� 2 = " << wallet2 << "��\n";

	cout << "�����͸� �̿��� ������� �ٽ� ��ȯ : \n";
	swapp(&wallet1, &wallet2);
	cout << "���� 1 = " << wallet1 << "��";
	cout << "���� 2 = " << wallet2 << "��\n";

	cout << "������ �����Ͽ� ���� ��ȯ �õ� : \n";
	swapv(wallet1, wallet2);
	cout << "���� 1 = " << wallet1 << "��";
	cout << "���� 2 = " << wallet2 << "��\n";
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
//	cout << "rats�� �ּ� = " << &rats;
//	cout << ",  rodents�� �ּ� = " << &rodents << endl;
//}
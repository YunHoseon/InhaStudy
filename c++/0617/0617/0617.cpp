//#include<iostream>
//#include <fstream>
//#include <string>
//#include <cctype>
//#include <cmath>
//#include <array>
//
//using namespace std;
//
//typedef struct RECT
//{
//	float x;
//	float y;
//
//	float h;
//	float w;
//}RECT;
//
//typedef struct CIRCLE
//{
//	float x;
//	float y;
//
//	float r;
//}CIRCLE;
//
//int IsInRect(RECT* rc, RECT* rc2)
//{
//	float rc_right, rc_left, rc_top, rc_bottom;
//	float rc2_right, rc2_left, rc2_top, rc2_bottom;
//
//	rc_right = rc->x + rc->w / 2;
//	rc_left = rc->x - rc->w / 2;
//	rc_top = rc->y + rc->h / 2;
//	rc_bottom = rc->y - rc->h / 2;
//
//	rc2_right = rc2->x + rc2->w / 2;
//	rc2_left = rc2->x - rc2->w / 2;
//	rc2_top = rc2->y + rc2->h / 2;
//	rc2_bottom = rc2->y - rc2->h / 2;
//
//	if ((rc2_right >= rc_left && rc2_top >= rc_bottom && rc2_bottom <= rc_top) || (rc2_right >= rc_left && rc2_bottom <= rc_top && rc2_top >= rc_bottom) ||
//		(rc2_left <= rc_right && rc2_bottom <= rc_top && rc2_top >= rc_bottom) || (rc2_left <= rc_right && rc2_top >= rc_bottom && rc2_bottom <= rc_top))
//	{
//		if (rc2_right <= rc_right && rc2_left <= rc_left && rc2_top <= rc_top && rc2_bottom >= rc_bottom)
//			return 30;
//		else
//			return 10;
//	}
//	else
//		return 20;
//}
//
//int IsInCircle(CIRCLE* cr, CIRCLE* cr2)
//{
//	float len = pow(pow((cr2->x - cr->x), 2) + pow((cr2->y - cr->y), 2), 0.5);
//
//	if (len <= cr->r + cr2->r)
//	{
//		if (cr->r - cr2->r > len)
//			return 30;
//		else
//			return 10;
//	}
//	else
//		return 20;
//}
//
//int main()
//{
//	CIRCLE *cr = new CIRCLE;
//	CIRCLE *cr2 = new CIRCLE;
//
//	cout << "ù��° ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> cr->x >> cr->y;
//	cout << "ù��° ���� �������� �Է��ϼ��� : ";
//	cin >> cr->r;
//
//	cout << "�ι�° ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> cr2->x >> cr2->y;
//	cout << "�ι�° ���� �������� �Է��ϼ��� : ";
//	cin >> cr2->r;
//
//	if(IsInCircle(cr, cr2) == 10)
//		cout << "R2�� R1�� ���Ŀ�." << endl;
//	else if(IsInCircle(cr, cr2) == 30)
//		cout << "R2�� R1�� ���Եſ�." << endl;
//	else if(IsInCircle(cr, cr2) == 20)
//		cout << "R2�� R1�ܺο� �־��." << endl;
//
//	RECT *rc = new RECT;
//	RECT *rc2 = new RECT;
//
//	cout << "ù��° ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> rc->x >> rc->y;
//	cout << "ù��° �簢���� ���̿� ���α��̸� �Է��ϼ��� : ";
//	cin >> rc->h >> rc->w;
//
//	cout << "�ι�° ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> rc2->x >> rc2->y;
//	cout << "�ι�° �簢���� ���̿� ���α��̸� �Է��ϼ��� : ";
//	cin >> rc2->h >> rc2->w;
//
//	if (IsInRect(rc, rc2) == 10)
//		cout << "R2�� R1�� ���Ŀ�." << endl;
//	else if (IsInRect(rc, rc2) == 30)
//		cout << "R2�� R1�� ���Եſ�." << endl;
//	else if (IsInRect(rc, rc2) == 20)
//		cout << "R2�� R1�ܺο� �־��." << endl;
//}

//const int Len = 66;
//const int Divs = 6;
//void subdivide(char ar[], int low, int high, int level, int nInput);
//
//int main()
//{
//	char ruler[Len];
//	int i;
//	for (i = 0; i < Len - 2; i++)
//		ruler[i] = ' ';
//	ruler[Len - 1] = '\0';
//	int max = Len - 2;
//	int min = 0;
//	int nInput;
//
//	cin >> nInput;
//
//	ruler[min] = ruler[max] = '|';
//	//cout << ruler << endl;
//
//	for (i = 1; i <= Divs; i++)
//	{
//		subdivide(ruler, min, max, i, nInput);
//		for (int j = 1; j < Len - 2; j++)
//			ruler[j] = ' ';
//	}
//}
//
//void subdivide(char ar[], int low, int high, int level, int nInput)
//{
//	if (level == 0)
//		return;
//
//	int mid = (high + low) / 2;
//	ar[mid] = '|';
//	subdivide(ar, low, mid, level - 1, nInput);
//	cin.get();
//		cout << ar << endl;
//	subdivide(ar, mid, high, level - 1, nInput);
//}

//const int Seasons = 4;
//const array<string, Seasons> Sname =
//{ "Spring", "Summer", "Fall", "Winter" };
//
//void fill(array<double, Seasons> *pa);
//void show(array<double, Seasons> da);
//
//int main()
//{
//	array<double, Seasons> expenses;
//	fill(&expenses);
//	show(expenses);
//}
//
//void fill(array<double, Seasons> *pa)
//{
//	for (int i = 0; i < Seasons; i++)
//	{
//		cout << Sname[i] << "�� �ҿ�Ǵ� ��� : ";
//		cin >> (*pa)[i];
//	}
//}
//
//void show(array<double, Seasons> da)
//{
//	double total = 0.0;
//	cout << "\n������ ���\n";
//
//	for (int i = 0; i < Seasons; i++)
//	{
//		cout << Sname[i] << " : $" << da[i] << endl;
//		total += (da)[i];
//	}
//	cout << "�� ��� : $" << total << endl;
//}

//typedef struct POINT
//{
//	double x;
//	double y;
//}POINT;
//
//bool IsInCircle(POINT* pt)
//{
//	if (pow((pt->x*pt->x) + (pt->y*pt->y), 0.5) <= 10)
//		return true;
//	else
//		return false;
//}
//
//bool IsInRect(POINT* pt)
//{
//	if (pt->x <= 5 && pt->x >= -5 && pt->y <= 2.5 && pt->y >= -2.5)
//		return true;
//	else
//		return false;
//}
//
//int main()
//{
//	POINT *pt = new POINT;
//
//	cout << "�� ���� ��ǥ�� �Է��ϼ��� : ";
//	cin >> pt->x >> pt->y;
//
//	if (IsInCircle(pt))
//		cout << "���� �� ���ο� �����մϴ�." << endl;
//	else
//		cout << "���� �� ���ο� �������� �ʽ��ϴ�." << endl;
//
//	if(IsInRect(pt))
//		cout << "���� �簢�� ���ο� �����մϴ�." << endl;
//	else
//		cout << "���� �簢�� ���ο� �������� �ʽ��ϴ�." << endl;
//}
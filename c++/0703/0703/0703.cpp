#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//class Grand
//{
//	int hold;
//public:
//	Grand(int h = 0) : hold(h) { }
//	virtual void Speak() const { cout << "���� Grand Ŭ������!\n"; }
//	virtual int Value() const { return hold; }
//};
//
//class Superb : public Grand
//{
//public:
//	Superb(int h = 0) : Grand(h) { }
//	void Speak() const { cout << "���� Superb Ŭ������!!\n"; }
//	virtual void Say() const { cout << "���� ������ �ִ� Superb���� " << Value() << "�̴�.\n"; }
//};
//
//class Magnificent : public Superb
//{
//	char ch;
//public:
//	Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) { }
//	void Speak() const { cout << "���� Magnificent Ŭ������!!!\n"; }
//	void Say()const { cout << "���� ������ �ִ� ���ڴ� : " << ch << "�̰�, ������ " << Value() << "�̴�.\n"; }
//};
//
//Grand *GetOne();
//
//int main()
//{
//	srand(time(0));
//	Grand *pg;
//	Superb *ps;
//	
//	for (int i = 0; i < 5; i++)
//	{
//		pg = GetOne();
//		pg->Speak();
//		if (ps = dynamic_cast<Superb *> (pg))
//			ps->Say();
//	}
//}
//
//Grand * GetOne()
//{
//	Grand *p;
//	switch (rand() % 3)
//	{
//	case 0:
//		p = new Grand(rand() % 100);
//		break;
//	case 1:
//		p = new Superb(rand() % 100);
//		break;
//	case 2:
//		p = new Magnificent(rand() % 100, 'A' + rand() % 26);
//		break;
//	}
//	return p;
//}

//double hmean(double a, double b);
//
//int main()
//{
//	double x, y, z;
//
//	cout << "�μ��� �Է��ϼ��� : ";
//	while (cin >> x >> y)
//	{
//		try
//		{
//			z = hmean(x, y);
//		}
//		catch(const char *s)
//		{
//			cout << s << endl;
//			cout << "�� ���� ���� �Է��ϼ��� : ";
//			continue;
//		}
//		cout << x << ", " << y << "�� ��ȭ����� " << z << "�Դϴ�.\n";
//		cout << "�ٸ� �� ���� �Է��Ͻʽÿ�(�������� q) : ";
//	}
//	cout << "���α׷��� �����մϴ�.\n";
//}
//
//double hmean(double a, double b)
//{
//	if (a == -b)
//		throw "�߸��� hmean() �Ű����� : a = -b�� ������ �ʽ��ϴ�.";
//	return 2.0 * a * b / (a + b);
//}

//bool hmean(double a, double b, double *ans);
//
//int main()
//{
//	double x, y, z;
//
//	cout << "�μ��� �Է��ϼ��� : ";
//	while (cin >> x >> y)
//	{
//		if (hmean(x, y, &z))
//			cout << x << ", " << y << "�� ��ȭ����� " << z << "�Դϴ�.\n";
//		else
//			cout << "���� ������ �� ���� ��ȭ����� ���� �� ����.\n";
//		cout << "�ٸ� �� ���� �Է��Ͻʽÿ�(�������� q) : ";
//	}
//	cout << "���α׷��� �����մϴ�.\n";
//}
//
//bool hmean(double a, double b, double * ans)
//{
//	if (a == -b)
//	{
//		*ans = DBL_MAX;
//		return false;
//	}
//	else
//	{
//		*ans = 2.0 * a * b / (a + b);
//		return true;
//	}
//}

//double hmean(double a, double b);
//
//int main()
//{
//	double x, y, z;
//
//	cout << "�μ��� �Է��ϼ��� : ";
//	while (cin >> x >> y)
//	{
//		z = hmean(x, y);
//		cout << x << ", " << y << "�� ��ȭ����� " << z << "�Դϴ�.\n";
//		cout << "�ٸ� �� ���� �Է��Ͻʽÿ�(�������� q) : ";
//	}
//	cout << "���α׷��� �����մϴ�.\n";
//}
//
//double hmean(double a, double b)
//{
//	if (a == -b)
//	{
//		cout << "�Ű��������� hmean�� ������ �� �����ϴ�.\n";
//		abort();
//	}
//	return 2.0 * a * b / (a + b);
//}

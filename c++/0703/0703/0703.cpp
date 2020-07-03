#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//class Grand
//{
//	int hold;
//public:
//	Grand(int h = 0) : hold(h) { }
//	virtual void Speak() const { cout << "나는 Grand 클래스다!\n"; }
//	virtual int Value() const { return hold; }
//};
//
//class Superb : public Grand
//{
//public:
//	Superb(int h = 0) : Grand(h) { }
//	void Speak() const { cout << "나는 Superb 클래스다!!\n"; }
//	virtual void Say() const { cout << "내가 가지고 있는 Superb값은 " << Value() << "이다.\n"; }
//};
//
//class Magnificent : public Superb
//{
//	char ch;
//public:
//	Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) { }
//	void Speak() const { cout << "나는 Magnificent 클래스다!!!\n"; }
//	void Say()const { cout << "내가 가지고 있는 문자는 : " << ch << "이고, 정수는 " << Value() << "이다.\n"; }
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
//	cout << "두수를 입력하세요 : ";
//	while (cin >> x >> y)
//	{
//		try
//		{
//			z = hmean(x, y);
//		}
//		catch(const char *s)
//		{
//			cout << s << endl;
//			cout << "두 수를 새로 입력하세요 : ";
//			continue;
//		}
//		cout << x << ", " << y << "의 조화평균은 " << z << "입니다.\n";
//		cout << "다른 두 수를 입력하십시오(끝내려면 q) : ";
//	}
//	cout << "프로그램을 종료합니다.\n";
//}
//
//double hmean(double a, double b)
//{
//	if (a == -b)
//		throw "잘못된 hmean() 매개변수 : a = -b는 허용되지 않습니다.";
//	return 2.0 * a * b / (a + b);
//}

//bool hmean(double a, double b, double *ans);
//
//int main()
//{
//	double x, y, z;
//
//	cout << "두수를 입력하세요 : ";
//	while (cin >> x >> y)
//	{
//		if (hmean(x, y, &z))
//			cout << x << ", " << y << "의 조화평균은 " << z << "입니다.\n";
//		else
//			cout << "서로 부정인 두 수의 조화평균은 구할 수 없다.\n";
//		cout << "다른 두 수를 입력하십시오(끝내려면 q) : ";
//	}
//	cout << "프로그램을 종료합니다.\n";
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
//	cout << "두수를 입력하세요 : ";
//	while (cin >> x >> y)
//	{
//		z = hmean(x, y);
//		cout << x << ", " << y << "의 조화평균은 " << z << "입니다.\n";
//		cout << "다른 두 수를 입력하십시오(끝내려면 q) : ";
//	}
//	cout << "프로그램을 종료합니다.\n";
//}
//
//double hmean(double a, double b)
//{
//	if (a == -b)
//	{
//		cout << "매개변수들을 hmean에 전달할 수 없습니다.\n";
//		abort();
//	}
//	return 2.0 * a * b / (a + b);
//}

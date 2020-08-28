#include <iostream>
#include <list>
#include "GeometricObject.h"

using namespace std;

void Tri()
{
	double sides[3] = { 0 };
	string tColor;
	bool isTriangleFull = false;

	cout << "�ﰢ���� ������ ���̸� �Է��ϼ��� : " << endl;

	for (int i = 0; i < 3; i++)
		cin >> sides[i];

	cout << "�ﰢ���� ������ �Է��ϼ��� : " << endl;
	cin >> tColor;

	cout << "�ﰢ���� ä�����ֳ���? (yes 1/ no 0) : " << endl;
	cin >> isTriangleFull;

	Triangle2 tri2(sides, tColor, isTriangleFull);

	cout << "�ﰢ���� �� ���� ���� : ";
	for (int i = 0; i < 3; i++)
		 cout << sides[i] << " ";
	cout << endl;

	cout << "�ﰢ���� ���� : " << tri2.GetArea() << endl;
	cout << "�ﰢ���� �ѷ� : " << tri2.GetPerimeter() << endl;
	cout << "�ﰢ���� ���� : " << tri2.GetColor() << endl;
	if(tri2.GetFull())
		cout << "�ﰢ���� ä�����ֳ���? : " << "true" << endl;
	else
		cout << "�ﰢ���� ä�����ֳ���? : " << "false" << endl;
}

void Rec()
{
	double width, height;

	cout << "�簢���� ���̿� ���� ���̸� �Է��ϼ��� : ";
	cin >> height >> width;

	Rectangle2 rec2(width, height);

	cout << "�簢���� ���� : " << rec2.GetArea() << endl;
	cout << "�簢���� �ѷ� : " << rec2.GetPerimeter() << endl;
}

void Cir()
{
	double radius;

	cout << "���� �������� �Է��ϼ��� : ";
	cin >> radius;

	Circle2 cir2(radius);

	cout << "���� ���� : " << cir2.GetArea() << endl;
	cout << "���� �ѷ� : " << cir2.GetPerimeter() << endl;
}

int main()
{
	Tri();
	cout << endl;
	Rec();
	cout << endl;
	Cir();
}

//class A
//{
//public:
//	A();
//	virtual ~A();
//
//private:
//
//};
//
//A::A()
//{
//	cout << "A()" << endl;
//}
//
//A::~A()
//{
//	cout << "~A()" << endl;
//}
//
//class AB : public A
//{
//public:
//	AB() { cout << "AB()" << endl; }
//	~AB() { cout << "~AB()" << endl; }
//};
//
//class AC : public A
//{
//public:
//	AC() { cout << "AC()" << endl; }
//	~AC() { cout << "~AC()" << endl; }
//};
//
//int main()
//{
//	list < class A* > cl;
//	AB* ab = new AB;
//	AC* ac = new AC;
//	cl.push_back((A*)ab);
//	cl.push_back((A*)ac);
//
//	for (list<class A*>::iterator it = cl.begin(); it != cl.end();)
//	{
//		A* a = (*it);
//		delete a;
//		it = cl.erase(it);
//	}
//}
#include <iostream>
#include <list>
#include "GeometricObject.h"

using namespace std;

void Tri()
{
	double sides[3] = { 0 };
	string tColor;
	bool isTriangleFull = false;

	cout << "삼각형의 세변의 길이를 입력하세요 : " << endl;

	for (int i = 0; i < 3; i++)
		cin >> sides[i];

	cout << "삼각형의 색깔을 입력하세요 : " << endl;
	cin >> tColor;

	cout << "삼각형이 채워져있나요? (yes 1/ no 0) : " << endl;
	cin >> isTriangleFull;

	Triangle2 tri2(sides, tColor, isTriangleFull);

	cout << "삼각형의 세 변의 길이 : ";
	for (int i = 0; i < 3; i++)
		 cout << sides[i] << " ";
	cout << endl;

	cout << "삼각형의 면적 : " << tri2.GetArea() << endl;
	cout << "삼각형의 둘레 : " << tri2.GetPerimeter() << endl;
	cout << "삼각형의 색깔 : " << tri2.GetColor() << endl;
	if(tri2.GetFull())
		cout << "삼각형이 채워져있나요? : " << "true" << endl;
	else
		cout << "삼각형이 채워져있나요? : " << "false" << endl;
}

void Rec()
{
	double width, height;

	cout << "사각형의 높이와 가로 길이를 입력하세요 : ";
	cin >> height >> width;

	Rectangle2 rec2(width, height);

	cout << "사각형의 넓이 : " << rec2.GetArea() << endl;
	cout << "사각형의 둘레 : " << rec2.GetPerimeter() << endl;
}

void Cir()
{
	double radius;

	cout << "원의 반지름을 입력하세요 : ";
	cin >> radius;

	Circle2 cir2(radius);

	cout << "원의 넓이 : " << cir2.GetArea() << endl;
	cout << "원의 둘레 : " << cir2.GetPerimeter() << endl;
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
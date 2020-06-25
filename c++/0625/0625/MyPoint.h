#pragma once
class MyPoint
{
	double x;
	double y;

public:
	MyPoint();
	MyPoint(double _x, double _y);
	~MyPoint();

	double GetX() { return x; }
	double GetY() { return y; }

	double Distance(MyPoint *_pt);	//���۷����� �޴� ���� ����
};


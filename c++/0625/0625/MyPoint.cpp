#include "MyPoint.h"
#include <iostream>

MyPoint::MyPoint() : x(0), y(0) {}
MyPoint::MyPoint(double _x, double _y) : x(_x), y(_y) {}

MyPoint::~MyPoint() {}

double MyPoint::Distance(MyPoint *_pt)
{
	return pow(pow(((*_pt).GetX()- this->GetX()), 2) + pow(((*_pt).GetY() - this->GetY()), 2), 0.5);
}

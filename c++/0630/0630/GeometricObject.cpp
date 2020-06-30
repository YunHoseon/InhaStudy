#include "GeometricObject.h"

GeometricObject::GeometricObject()
{
}
double GeometricObject::GetArea()
{
	return 0.0;
}
double GeometricObject::GetPerimeter()
{
	return 0.0;
}
GeometricObject::~GeometricObject()
{
}


Triangle2::Triangle2()
{
	side[0] = 1.0;
	side[1] = 1.0;
	side[2] = 1.0;

	isTriangleFull = false;
}

Triangle2::Triangle2(double _side[], string _tColor, bool _isTriangleFull)
{
	SetSide(_side);
	tColor = _tColor;
	isTriangleFull = _isTriangleFull;
}

void Triangle2::SetSide(double _side[])
{
	for (int i = 0; i < 3; i++)
		side[i] = _side[i];
}

double Triangle2::GetArea()
{
	double s, a, b, c;

	a = side[0];
	b = side[1];
	c = side[2];
	s = (a + b + c) / 2;

	return sqrt(s * abs((s - a)*(s - b)*(s - c)));
}

double Triangle2::GetPerimeter()
{
	return side[0] + side[1] + side[2];
}

Triangle2::~Triangle2()
{
}

Rectangle2::Rectangle2()
{
	SetWidth(1.0);
	SetHeight(1.0);
}

Rectangle2::Rectangle2(double _width, double _height)
{
	SetWidth(_width);
	SetHeight(_height);
}

double Rectangle2::GetArea()
{
	return width * height;
}

double Rectangle2::GetPerimeter()
{
	return (width + height) * 2;
}

Rectangle2::~Rectangle2()
{
}

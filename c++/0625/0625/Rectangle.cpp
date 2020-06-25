#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle()
{
	SetHeight(1);
	SetWidth(1);
}

Rectangle::Rectangle(double _width, double _height)
{
	SetHeight(_height);
	SetWidth(_width);
}

double Rectangle::GetArea()
{
	return this->GetWidth() * this->GetHeight();
}

double Rectangle::GetPerimeter()
{
	return (this->GetWidth()+ this->GetHeight()) * 2;
}

Rectangle::~Rectangle()
{
}

#pragma once
class Rectangle
{
	double width;
	double height;

public:
	Rectangle();
	Rectangle(double _width, double _height);
	double GetArea();
	double GetPerimeter();
	~Rectangle();

	void SetWidth(double _width) { width = _width; };
	double GetWidth() { return width; };
	void SetHeight(double _height) { height = _height; };
	double GetHeight() { return height; };
};
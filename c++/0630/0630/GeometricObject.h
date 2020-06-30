#pragma once
#include <iostream>
#include <string>

using namespace std;

class GeometricObject
{
public:
	GeometricObject();

	virtual double GetArea();
	virtual double GetPerimeter();

	~GeometricObject();
};

class Triangle2 : public GeometricObject
{
	double side[3];
	string tColor;
	bool isTriangleFull;

public:
	Triangle2();
	Triangle2(double _side[], string _tColor, bool _isTriangleFull);

	void SetSide(double _side[]);
	bool GetFull() { return isTriangleFull; };
	string GetColor() { return tColor; };
	double GetArea();
	double GetPerimeter();

	~Triangle2();
};

class Rectangle2 : public GeometricObject
{
	double width;
	double height;

public:
	Rectangle2();
	Rectangle2(double _width, double _height);

	void SetWidth(double _width) { width = _width; };
	void SetHeight(double _height) { height = _height; };
	double GetArea();
	double GetPerimeter();
	~Rectangle2();
};
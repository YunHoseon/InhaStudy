#include "Shape.h"
#include "stdafx.h"

CShape::CShape()
{
}


CShape::~CShape()
{
}

CRectangle::CRectangle(int _x , int _y)
{
	srand(time(NULL));

	x = _x;
	y = _y;

	size = 30;
	type = 1;
	speed = 15;

	dir = rand() % 2;

	if (dir == 0)
		moveToX = 1;
	else
		moveToX = -1;

	dir = rand() % 2;

	if (dir == 0)
		moveToY = 1;
	else
		moveToY = -1;

	points = new MYPOINT[4];
	vertexNum = 4;

	/*for (int i = 0; i < vertexNum; i++)
	{
		points[i].x = x + (size * sin(90 * i * PI / 180));
		points[i].y = y - (size * cos(90 * i * PI / 180));
	}*/

	points[0].x = x - size;
	points[0].y = y - size;
	points[1].x = x + size;
	points[1].y = y - size;
	points[2].x = x + size;
	points[2].y = y + size;
	points[3].x = x - size;
	points[3].y = y + size;
}

CRectangle::~CRectangle()
{
}

void CRectangle::Update()
{
	
}

void CRectangle::Collision()
{

}

void CRectangle::DrawShape(HDC hdc)
{
	POINT pt[4];

	for (int i = 0; i < vertexNum; i++)
	{
		pt[i].x = points[i].x;
		pt[i].y = points[i].y;
	}

	Polygon(hdc, pt, vertexNum);
}

#include "Shape.h"
#include "stdafx.h"

CShape::CShape()
{
}


CShape::~CShape()
{
}

CRectangle::CRectangle()
{
	srand(time(NULL));
	dir = rand();

	size = 50;
	type = 1;
	speed = 10;
	moveToX = 1;
	moveToY = 1;
}

CRectangle::~CRectangle()
{
}

void CRectangle::Update()
{
	/*for (CShape *cRect : cShapes)
	{
		if (cRect->dir % 4 == 0)
		{
			cRect->x += cRect->GetSpeed() * cRect->moveToX;
			cRect->y += cRect->GetSpeed() * cRect->moveToY;
		}
		else if (cRect->dir % 4 == 1)
		{
			cRect->x -= cRect->GetSpeed() * cRect->moveToX;
			cRect->y -= cRect->GetSpeed() * cRect->moveToY;
		}
		else if (cRect->dir % 4 == 2)
		{
			cRect->x -= cRect->GetSpeed() * cRect->moveToX;
			cRect->y += cRect->GetSpeed() * cRect->moveToY;
		}
		else if (cRect->dir % 4 == 3)
		{
			cRect->x += cRect->GetSpeed() * cRect->moveToX;
			cRect->y -= cRect->GetSpeed() * cRect->moveToY;
		}

		if (cRect->y + (cRect->size * 0.5) <= rectRange.top + cRect->size || cRect->y + (cRect->size * 0.5) >= rectRange.bottom)
			cRect->SetmoveToY(cRect->moveToY * -1);
		if (cRect->x + (cRect->size * 0.5) <= rectRange.left + cRect->size || cRect->x + (cRect->size * 0.5) >= rectRange.right)
			cRect->SetmoveToX(cRect->moveToX * -1);
	}*/
}

void CRectangle::Collision()
{

}

void CRectangle::DrawShape(HDC hdc)
{
	Rectangle(hdc, x - (size * 0.5), y - (size * 0.5), x + (size * 0.5), y + (size * 0.5));
}

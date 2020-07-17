#include "stdafx.h"
#include "Objects.h"

extern vector<CObjects*> objects;

CObjects::CObjects()
{
}


CObjects::~CObjects()
{
}

/*PlayerObject*/

PlayerObj::PlayerObj()
{
	objType = type_Player;
}

PlayerObj::~PlayerObj()
{
}

/*BlockObject*/

BlockObj::BlockObj(float _x, float _y)
{
	objType = type_Block;
	center.x = _x;
	center.y = _y;
	size = 40;

	points = new MYPOINT[4];
	vertexNum = 4;

	points[0].x = center.x - size;
	points[0].y = center.y - size;
	points[1].x = center.x + size;
	points[1].y = center.y - size;
	points[2].x = center.x + size;
	points[2].y = center.y + size;
	points[3].x = center.x - size;
	points[3].y = center.y + size;
}

BlockObj::~BlockObj()
{
}

void BlockObj::DrawObj(HDC hdc)
{
	POINT pt[4];

	for (int i = 0; i < vertexNum; i++)
	{
		pt[i].x = points[i].x;
		pt[i].y = points[i].y;
	}

	Polygon(hdc, pt, vertexNum);
}

void BlockObj::CreateObj()
{
	for (int i = 0; i < 6; i++)			//블록 생성
	{
		BlockObj *blocks = new BlockObj(40 + (i * 80), 720);
		objects.push_back(blocks);
	}
}

/*EnemyObject*/

EnemyObj::EnemyObj(float _x, float _y)
{
	objType = type_Enemy;
	center.x = _x;
	center.y = _y;
	size = 30;

	points = new MYPOINT[10];
	vertexNum = 10;

	for (int i = 0; i < 9; i += 2)
	{
		points[i].x = center.x + (size * sin(72 * (i / 2) * PI / 180));
		points[i].y = center.y - (size * cos(72 * (i / 2) * PI / 180));
	}

	float a = points[0].y - points[4].y;
	float b = -(points[0].x - points[4].x);
	float c = points[2].y - points[8].y;
	float d = -(points[2].x - points[8].x);
	float e = a * points[0].x + b * points[0].y;
	float f = c * points[2].x + d * points[2].y;

	points[1].x = (e*d - b*f) / (a*d - b*c);
	points[1].y = (a*f - e*c) / (a*d - b*c);

	double r2 = pow(pow(center.x - points[1].x, 2) + pow(center.y - points[1].y, 2), 0.5);

	for (int i = 3; i < 10; i += 2)
	{
		points[i].x = center.x + (r2 * sin((72 * (i / 2) + 36) * PI / 180));
		points[i].y = center.y - (r2 * cos((72 * (i / 2) + 36) * PI / 180));
	}
}

EnemyObj::~EnemyObj()
{
}

void EnemyObj::DrawObj(HDC hdc)
{
	POINT pt[10];

	for (int i = 0; i < vertexNum; i++)
	{
		pt[i].x = points[i].x;
		pt[i].y = points[i].y;
	}

	Polygon(hdc, pt, 10);
}

void EnemyObj::CreateObj()
{
	EnemyObj *enemeis = new EnemyObj(40 + 80, 100);
	objects.push_back(enemeis);
}

void EnemyObj::RotateEnemy(EnemyObj *enemeis)
{
	for (int i = 0; i < enemeis->vertexNum; i++)		//도형 회전
	{
		float xTmp = enemeis->points[i].x - enemeis->center.x;
		float yTmp = enemeis->points[i].y - enemeis->center.y;

		enemeis->points[i].x = cos(20 * PI / 180) * xTmp - sin(20 * PI / 180) * yTmp + enemeis->center.x;
		enemeis->points[i].y = sin(20 * PI / 180) * xTmp + cos(20 * PI / 180) * yTmp + enemeis->center.y;
	}
}

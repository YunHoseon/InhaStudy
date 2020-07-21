#include "stdafx.h"
#include "Objects.h"

extern list<EnemyObj*> enemyList;
extern list<BlockObj*> blockList;
extern list<BulletObj*> bulletList;

extern Player player;

CObjects::CObjects()
{
}

CObjects::~CObjects()
{
}

void CObjects::Collision()
{
	list<EnemyObj*>::iterator iter = enemyList.begin();
	list<BlockObj*>::iterator iter2 = blockList.begin();
	list<BulletObj*>::iterator iter3 = bulletList.begin();

	for (iter = enemyList.begin(); iter != enemyList.end();)
	{
		for (iter2 = blockList.begin(); iter2 != blockList.end();)
		{
			int dir = pow(pow((*iter)->center.x - (*iter2)->center.x, 2) + pow((*iter)->center.y - (*iter2)->center.y, 2), 0.5);

			if (dir <= (*iter2)->size + (*iter)->size)
			{
				iter = enemyList.erase(iter);
				iter2 = blockList.erase(iter2);
				break;
			}
			else
				iter2++;
		}

		for (iter3 = bulletList.begin(); iter3 != bulletList.end();)
		{
			int dir = pow(pow((*iter)->center.x - (*iter3)->center.x, 2) + pow((*iter)->center.y - (*iter3)->center.y, 2), 0.5);

			if (dir <= (*iter3)->size + (*iter)->size)
			{
				iter = enemyList.erase(iter);
				iter3 = bulletList.erase(iter3);

				int score = player.GetScore();
				player.SetScore(score + 100);
				break;
			}
			else
				iter3++;
		}
		if(iter != enemyList.end())
			iter++;
	}
}

/*PlayerObject*/

PlayerObj::PlayerObj(float _x, float _y)
{
	objType = type_Player;
	center.x = _x;
	center.y = _y;
	size = 40;

	points = new MYPOINT[2];
	vertexNum = 2;

	points[0].x = center.x;
	points[0].y = center.y;

	points[1].x = center.x;
	points[1].y = center.y - (size + 20);
}

PlayerObj::~PlayerObj()
{
}

void PlayerObj::DrawObj(HDC hdc)
{
	Ellipse(hdc, center.x - size, center.y - size, center.x + size, center.y + size);
	
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, points[1].x, points[1].y);
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

BulletObj::BulletObj(float _x, float _y)
{
	objType = type_Bullet;
	center.x = _x;
	center.y = _y;
	size = 10;
}

BulletObj::~BulletObj()
{
}

void BulletObj::DrawObj(HDC hdc)
{
	Ellipse(hdc, center.x - size, center.y - size, center.x + size, center.y + size);
}

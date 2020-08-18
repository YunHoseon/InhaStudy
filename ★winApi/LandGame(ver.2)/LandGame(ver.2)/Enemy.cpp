#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	srand(time(NULL));

	ex = rand() % 600 + 200;
	ey = rand() % 500 + 200;

	size = 5;
	speed = 5;

	dir = rand() % 2;
	moveToX = dir == 0 ? 1 : -1;
	dir = rand() % 2;
	moveToY = dir == 0 ? 1 : -1;
}

Enemy::~Enemy()
{
}

void Enemy::DrawEnemy(HDC hdc)
{
	Ellipse(hdc, ex - size, ey - size, ex + size, ey + size);
}

void Enemy::MoveEnemy()
{
	ex += speed * moveToX;
	ey += speed * moveToY;

	if (ey + (size * 0.5) <= 20 + size)
		moveToY = 1;

	if (ey + (size * 0.5) >= 653)
		moveToY = -1;

	if (ex + (size * 0.5) <= 15 + size)
		moveToX = 1;

	if (ex + (size * 0.5) >= 765)
		moveToX = -1;
}

bool Enemy::CheckCollision()
{
	
	return false;
}

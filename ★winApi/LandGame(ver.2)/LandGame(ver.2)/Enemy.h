#pragma once
class Enemy
{
public:
	int ex;
	int ey;

	int size;
	int speed;
	int dir;

	int moveToX;
	int moveToY;

	Enemy();
	~Enemy();

	void DrawEnemy(HDC hdc);
	void MoveEnemy();
	bool CheckCollision();
};


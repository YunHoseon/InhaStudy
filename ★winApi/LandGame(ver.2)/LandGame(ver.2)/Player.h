#pragma once
class Player
{
public:
	POINT playerPos;
	int size;
	int speed;
	int dir;

	bool drawMode;
	bool moved;

	Player();
	virtual ~Player();

	void DrawPlayer(HDC hdc);
};


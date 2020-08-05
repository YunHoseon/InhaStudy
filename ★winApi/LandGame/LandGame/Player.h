#pragma once
class Player
{
public:
	POINT playerPos;

	int size;
	int speed;
	bool research;
	bool moved;
	int dir;

	//typedef struct PlayerRect
	//{
	//	RECT playerRect;
	//	int px;
	//	int py;
	//}PlayerRect;

	//PlayerRect pr;

	Player();
	~Player();

	void DrawPlayer(HDC hdc);
	void FootPrint(HDC hdc, int _x, int _y);
};


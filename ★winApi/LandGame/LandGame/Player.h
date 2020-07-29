#pragma once
class Player
{
public:
	int PosX;
	int PosY;

	int size;

	typedef struct PlayerRect
	{
		RECT playerRect;
		int px;
		int py;
	}PlayerRect;

	PlayerRect pr;

	Player();
	~Player();

	void DrawPlayer(HDC hdc);
	void FootPrint(HDC hdc, int _x, int _y);
};


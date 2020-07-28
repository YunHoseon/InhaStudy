#pragma once
class Player
{
public:
	int PosX;
	int PosY;

	int size;

	Player();
	~Player();

	void DrawPlayer(HDC hdc);
	void PlayerMove();
};


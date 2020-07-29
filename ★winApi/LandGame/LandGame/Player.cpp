#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	PosX = 15;
	PosY = 20;
	size = 5;

	pr.playerRect = { PosX - size, PosY - size, PosX + size, PosY + size };
	pr.px = PosX;
	pr.py = PosY;
}

Player::~Player()
{
}

void Player::DrawPlayer(HDC hdc)
{
	Ellipse(hdc, PosX - size, PosY - size, PosX + size, PosY + size);
}

void Player::FootPrint(HDC hdc, int _x, int _y)
{
	//MoveToEx(hdc, _x, _y, NULL);
	LineTo(hdc, _x, _y);
}

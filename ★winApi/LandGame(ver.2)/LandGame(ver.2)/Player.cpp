#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	playerPos.x = 100;
	playerPos.y = 60;
	size = 8;
	speed = 2;

	drawMode = false;
	moved = false;
}


Player::~Player()
{
}

void Player::DrawPlayer(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 200, 215));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, playerPos.x - size, playerPos.y - size, playerPos.x + size, playerPos.y + size);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

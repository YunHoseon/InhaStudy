#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	playerPos.x = 15;
	playerPos.y = 20;

	size = 7;
	speed = 3;
	dir = 0;

	research = false;
	moved = false;

	/*pr.playerRect = { playerPos.x - size, playerPos.y - size, playerPos.x + size, playerPos.y + size };
	pr.px = playerPos.x;
	pr.py = playerPos.y;*/
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

void Player::FootPrint(HDC hdc, int _x, int _y)
{
	MoveToEx(hdc, _x, _y, NULL);
	LineTo(hdc, playerPos.x, playerPos.x);
}

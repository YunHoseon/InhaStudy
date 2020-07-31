#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	playerPos.x = 15;
	playerPos.y = 20;

	size = 5;
	speed = 3;

	research = false;
	moved = false;

	pr.playerRect = { playerPos.x - size, playerPos.y - size, playerPos.x + size, playerPos.y + size };
	pr.px = playerPos.x;
	pr.py = playerPos.y;
}

Player::~Player()
{
}

void Player::DrawPlayer(HDC hdc)
{
	Ellipse(hdc, playerPos.x - size, playerPos.y - size, playerPos.x + size, playerPos.y + size);
}

void Player::FootPrint(HDC hdc, int _x, int _y)
{
	MoveToEx(hdc, _x, _y, NULL);
	LineTo(hdc, playerPos.x, playerPos.x);
}

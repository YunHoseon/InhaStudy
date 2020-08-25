#include "stdafx.h"
#include "Player.h"

extern TileMap tileMap;

Player::Player()
{
	pt = { 100, 100 };
	speed = 2;

	playerCollider.left = pt.x - 10;
	playerCollider.top = pt.y - 15;
	playerCollider.right = pt.x + 10;
	playerCollider.bottom = pt.y + 15;
}

Player::~Player()
{
}

void Player::UpdatePlayer(UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT curPos;
	curPos = pt;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		curPos.x -= speed;

		if (tileMap.map[curPos.y / tileMap.gap][curPos.x / tileMap.gap].cell == 'k')
		{
			curPos = pt;
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		curPos.x += speed;
		if (tileMap.map[curPos.y / tileMap.gap][curPos.x / tileMap.gap].cell == 'k')
		{
			curPos = pt;
		}
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		curPos.y -= speed;
		if (tileMap.map[curPos.y / tileMap.gap][curPos.x / tileMap.gap].cell == 'k')
		{
			curPos = pt;
		}
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		curPos.y += speed;
		if (tileMap.map[curPos.y / tileMap.gap][curPos.x / tileMap.gap].cell == 'k')
		{
			curPos = pt;
		}
	}
	pt = curPos;

	playerCollider.left = pt.x - 10;
	playerCollider.top = pt.y - 15;
	playerCollider.right = pt.x + 10;
	playerCollider.bottom = pt.y + 15;
}

void Player::DrawPlayer(HDC hdc)
{
	Rectangle(hdc, playerCollider.left, playerCollider.top, playerCollider.right, playerCollider.bottom);
}

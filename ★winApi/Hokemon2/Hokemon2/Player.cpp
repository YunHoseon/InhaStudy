#include "stdafx.h"
#include "Player.h"

extern Singleton *singleton;
extern TileMap tileMap;

Player::Player()
{
	pt = { 300, 230 };
	speed = 5;

	playerCollider.left = pt.x - 20;
	playerCollider.top = pt.y - 25;
	playerCollider.right = pt.x + 20;
	playerCollider.bottom = pt.y + 25;
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
		if (tileMap.map[(curPos.y - POSY) / tileMap.gap][(curPos.x - POSX) / tileMap.gap].cell == 'k')
		{
			curPos = pt;
			singleton->movable = false;
		}
		else
			singleton->movable = true;
		curPos.x += speed;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		curPos.x += speed;
		if (tileMap.map[(curPos.y - POSY) / tileMap.gap][(curPos.x - POSX) / tileMap.gap].cell == 'k')
		{
			curPos = pt;
			singleton->movable = false;
		}
		else
			singleton->movable = true;
		curPos.x -= speed;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		curPos.y -= speed;
		if (tileMap.map[(curPos.y - POSY) / tileMap.gap][(curPos.x - POSX) / tileMap.gap].cell == 'k')
		{
			curPos = pt;
			singleton->movable = false;
		}
		else
			singleton->movable = true;
		curPos.y += speed;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		curPos.y += speed;
		if (tileMap.map[(curPos.y - POSY) / tileMap.gap][(curPos.x - POSX) / tileMap.gap].cell == 'k')
		{
			curPos = pt;
			singleton->movable = false;
		}
		else
			singleton->movable = true;
		curPos.y -= speed;
	}
	pt = curPos;

	playerCollider.left = pt.x - 20;
	playerCollider.top = pt.y - 25;
	playerCollider.right = pt.x + 20;
	playerCollider.bottom = pt.y + 25;
}

void Player::DrawPlayer(HDC hdc)
{
	Rectangle(hdc, playerCollider.left, playerCollider.top, playerCollider.right, playerCollider.bottom);
}

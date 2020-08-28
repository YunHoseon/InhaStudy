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
	/*RECT intersectRc;
	POINT curPos;
	curPos = pt;
	RECT tmpPlayerCol;


	tmpPlayerCol.left = pt.x - 20;
	tmpPlayerCol.top = pt.y - 25;
	tmpPlayerCol.right = pt.x + 20;
	tmpPlayerCol.bottom = pt.y + 25;

	if (GetKeyState(VK_LEFT) & 0x8000 || (GetKeyState(VK_RIGHT) & 0x8000) || 
		(GetKeyState(VK_UP) & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
	{
		for (int i = 0; i < COL - 5; i++)		//15
		{
			for (int j = 0; j < ROW - 1; j++)	//19
			{
				if (IntersectRect(&intersectRc, &tmpPlayerCol, &tileMap.map[i][j].collider) == true
					&& tileMap.map[i][j].cell == 'k')
				{
					curPos = pt;
					singleton->movable = false;
					i = COL;
					break;
				}
				else
					singleton->movable = true;
			}
		}
	}

	pt = curPos;
	if (singleton->movable == true)
	{
		playerCollider.left = pt.x - 20;
		playerCollider.top = pt.y - 25;
		playerCollider.right = pt.x + 20;
		playerCollider.bottom = pt.y + 25;
	}*/
}

void Player::DrawPlayer(HDC hdc)
{
	Rectangle(hdc, playerCollider.left, playerCollider.top, playerCollider.right, playerCollider.bottom);
}

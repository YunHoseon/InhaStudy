#include "stdafx.h"
#include "Player.h"

#pragma comment(lib, "msimg32.lib")

#define Sprite_Size_X 49
#define Sprite_Size_Y 49

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

	run_Frame_max = 0;
	run_Frame_min = 0;
	cur_Frame = run_Frame_min;
	dir = 0;
	ax = 300, ay = 100;

	hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images\\player\\player_.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hAniImage, sizeof(BITMAP), &bitAni);
	run_Frame_max = bitAni.bmWidth / Sprite_Size_X - 1;
	run_Frame_min = 0;
	cur_Frame = run_Frame_min;
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

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		dir = 1;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		dir = 3;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		dir = 2;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		dir = 0;
	}
}

void Player::DrawPlayer(HWND hWnd, HDC hdc)
{
	hMemDC = CreateCompatibleDC(hdc);	
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
	by = bitAni.bmHeight / 4;

	int xStart = bx;
	int yStart = 0 + by * dir;

	BOOL ret = TransparentBlt(hdc, playerCollider.left, playerCollider.top, Sprite_Size_X, Sprite_Size_Y, hMemDC,
		xStart, yStart, Sprite_Size_X, Sprite_Size_Y, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	UpdateFrame(hWnd);
	//Rectangle(hdc, playerCollider.left, playerCollider.top, playerCollider.right, playerCollider.bottom);
}

void Player::UpdateFrame(HWND hWnd)
{
	static const UINT animation_change_frame = 5;
	cur_Frame++;

	if (cur_Frame % animation_change_frame == 0)
	{
		bx += Sprite_Size_X;
		if (!(bx < bitAni.bmWidth))
			bx = 0;
	}

}
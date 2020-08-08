#include "stdafx.h"
#include "GameScene.h"
#include "Bitmap.h"
#include "Player.h"

extern Singleton *singleton;

GameScene::GameScene()
{
	bitmap = new Bitmap;
	player = new Player;
	bitmap->CreateBitmap();
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	mapPoint[0] = { 15, 20 };
	mapPoint[1] = { 765, 20 };
	mapPoint[2] = { 765, 653 };
	mapPoint[3] = { 15, 653 };
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	int tmpDir = player->dir;
	POINT curPos;

	curPos.x = player->playerPos.x;
	curPos.y = player->playerPos.y;

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		player->drawMode = true;
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			player->dir = 1;
			player->playerPos.x -= player->speed;
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			player->dir = 2;
			player->playerPos.x += player->speed;
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			player->dir = 3;
			player->playerPos.y -= player->speed;
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			player->dir = 4;
			player->playerPos.y += player->speed;
		}
	}
	else
	{
		player->drawMode = false;
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			player->dir = 1;
			player->playerPos.x -= player->speed;
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			player->dir = 2;
			player->playerPos.x += player->speed;
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			player->dir = 3;
			player->playerPos.y -= player->speed;
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			player->dir = 4;
			player->playerPos.y += player->speed;
		}
	}
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	static HBITMAP backHBit = NULL;

	if (backHBit == NULL)
	{
		singleton->backHDC = CreateCompatibleDC(hdc);
		backHBit = CreateCompatibleBitmap(hdc, bitmap->bitBack.bmWidth + 15, bitmap->bitBack.bmHeight + 20);
		SelectObject(singleton->backHDC, backHBit);
	}

	bitmap->DrawBitmap(hWnd, singleton->backHDC);
	DrawBox(hWnd, singleton->backHDC);
	
	BitBlt(hdc, 15, 20, bitmap->bitBack.bmWidth, bitmap->bitBack.bmHeight, singleton->backHDC, 15, 20, SRCCOPY);

	player->DrawPlayer(hdc);
}

void GameScene::Free(HWND hWnd)
{
	KillTimer(hWnd, 1);
}

void GameScene::DrawBox(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hBit = NULL, oldBit;
	{
		HBRUSH hBrush, oldBrush;
		hMemDC = CreateCompatibleDC(hdc);

		hBrush = CreateSolidBrush(RGB(220, 245, 215));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		if (hBit == NULL)
			hBit = CreateCompatibleBitmap(hdc, 800, 700);
		oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

		Rectangle(hMemDC, 15, 20, 765, 653);

		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		//폴리곤 그리기

		TransparentBlt(hdc, 15, 20, 750, 633, hMemDC, 15, 20, 750, 633, RGB(255, 0, 255));

		SelectObject(hMemDC, oldBrush);
		SelectObject(hMemDC, oldBit);

		DeleteObject(oldBit);
		DeleteObject(hBrush);
		DeleteDC(hMemDC);
	}
}

bool GameScene::isInOutline()
{
	if(player->playerPos.x )
	return false;
}

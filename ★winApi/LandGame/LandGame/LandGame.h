#pragma once

#include "resource.h"

Player player;
Map map;
extern list<POINT*> points;

void DrawBox(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hBit = NULL, oldBit;
	{
		HBRUSH hBrush, oldBrush;
		hMemDC = CreateCompatibleDC(hdc);

		hBrush = CreateSolidBrush(RGB(220, 240, 215));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		if (hBit == NULL)
			hBit = CreateCompatibleBitmap(hdc, 800, 700);	//hdc에 호환되는 이미지
		oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

		Rectangle(hMemDC, 15, 20, 765, 653);

		//BitBlt(hdc, 15, 20, 750, 633, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hdc, 15, 20, 750, 633, hMemDC, 15, 20, 750, 633, RGB(255,255,255));
		SelectObject(hMemDC, oldBrush);
		SelectObject(hMemDC, oldBit);

		DeleteObject(oldBit);
		DeleteObject(hBrush);
		DeleteDC(hMemDC);
	}
}

void DrawRect(HDC hdc, int centerX, int centerY, int r)
{
	Rectangle(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void CreateBitmap(HBITMAP &hBackImage, BITMAP &bitBack)
{
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\fom.bmp"), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}
}

void DrawBitmap(HWND hWnd, HDC hdc, const HBITMAP &hBackImage, const BITMAP &bitBack)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 15, 20, bx, by, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void DeleteBitmap(HBITMAP &hBackImage)
{
	DeleteObject(hBackImage);
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc = GetDC(hWnd);
	static int dir = 0;
	int tmpDir = dir;

	int currentX = player.playerPos.x;
	int currentY = player.playerPos.y;

	int tmpX = currentX;
	int tmpY = currentY;

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (map.board[currentY][currentX - player.speed] != WALL && map.board[currentY][currentX - player.speed] != OPEN
				&& map.board[currentY][currentX - player.speed] != FOOTPRINT)
			{
				dir = 1;
				player.playerPos.x -= player.speed;
				player.pr.px -= player.speed;
			}
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (map.board[currentY + player.speed][currentX] != WALL && map.board[currentY + player.speed][currentX] != OPEN
				&& map.board[currentY + player.speed][currentX] != FOOTPRINT)
			{
				dir = 2;
				player.playerPos.y += player.speed;
				player.pr.py += player.speed;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (map.board[currentY][currentX + player.speed] != WALL && map.board[currentY][currentX + player.speed] != OPEN
				&& map.board[currentY][currentX + player.speed] != FOOTPRINT)
			{
				dir = 3;
				player.playerPos.x += player.speed;
				player.pr.px += player.speed;
			}
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (map.board[currentY - player.speed][currentX] != WALL && map.board[currentY - player.speed][currentX] != OPEN
				&& map.board[currentY - player.speed][currentX] != FOOTPRINT)
			{
				dir = 4;
				player.playerPos.y -= player.speed;
				player.pr.py -= player.speed;
			}
		}
	}

	
	points.push_back(&player.playerPos);

	map.UpdateMap(hdc);

	if(map.board[currentY][currentX] == CLOSE)
		map.board[currentY][currentX] = FOOTPRINT;

	else if (map.board[currentY][currentX] == ROAD)
	{
		points.push_back(&player.playerPos);
		player.research = true;
	}
		

	player.pr.playerRect = { player.playerPos.x - player.size - player.speed, player.playerPos.y - player.size - player.speed,
		player.playerPos.x + player.size + player.speed, player.playerPos.y + player.size + player.speed };
	InvalidateRect(hWnd, &player.pr.playerRect, TRUE);

	ReleaseDC(hWnd, hdc);
}
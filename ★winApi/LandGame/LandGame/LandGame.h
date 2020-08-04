#pragma once

#include "resource.h"

Player player;
Map map;
extern vector<POINT> *points;

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

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		map.DrawPloygon(hMemDC);

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

bool IsInside(int _x, int _y)
{
	int crosses = 0;

	for (int i = 0; i < points->size(); i++)
	{
		int j = (i + 1) % points->size();
		if (((*points)[i].y > _y) != ((*points)[j].y > _y))
		{
			double atX = ((*points)[j].x - (*points)[i].x) * (_y - (*points)[i].y) / ((*points)[j].y - (*points)[i].y) + (*points)[i].x;
			if (_x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc = GetDC(hWnd);
	static int dir = 0;
	int tmpDir = dir;
	POINT curPos;

	curPos.x = player.playerPos.x;
	curPos.y = player.playerPos.y;

	int tmpX = curPos.x;
	int tmpY = curPos.y;

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x - player.speed] == ROAD || map.board[curPos.y][curPos.x - player.speed] == CLOSE)
			{
				dir = 1;
				if (tmpDir != dir)
					points->push_back(player.playerPos);

				player.playerPos.x -= player.speed;
				player.pr.px -= player.speed;
			}
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
  			if (map.board[curPos.y + player.speed][curPos.x] == ROAD || map.board[curPos.y + player.speed][curPos.x] == CLOSE)
			{
				dir = 2;
				if (tmpDir != dir)
					points->push_back(player.playerPos);

				player.playerPos.y += player.speed;
				player.pr.py += player.speed;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x + player.speed] == ROAD || map.board[curPos.y][curPos.x + player.speed] == CLOSE)
			{
				dir = 3;
				if (tmpDir != dir)
					points->push_back(player.playerPos);

				player.playerPos.x += player.speed;
				player.pr.px += player.speed;

			}
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (map.board[curPos.y - player.speed][curPos.x] == ROAD || map.board[curPos.y - player.speed][curPos.x] == CLOSE)
			{
				dir = 4;
				if (tmpDir != dir)
					points->push_back(player.playerPos);

				player.playerPos.y -= player.speed;
				player.pr.py -= player.speed;
			}
		}

		map.UpdateMap(hdc);

		if (map.board[curPos.y][curPos.x] == CLOSE)
		{
			map.board[curPos.y][curPos.x] = FOOTPRINT;
			player.moved = true;
		}
		else if (map.board[curPos.y][curPos.x] == ROAD && player.moved)		//도형 다 그렸을 때
		{
			points->push_back(curPos);
			//내부 점 판단, 플러드 필
			if (IsInside((*points)[1].x + 1, (*points)[1].y + 1))
				map.FloodFill(hdc, (*points)[1].x + 1, (*points)[1].y + 1);
			else if(IsInside((*points)[1].x - 1, (*points)[1].y + 1))
				map.FloodFill(hdc, (*points)[1].x - 1, (*points)[1].y + 1);
			else if(IsInside((*points)[1].x - 1, (*points)[1].y - 1))
				map.FloodFill(hdc, (*points)[1].x - 1, (*points)[1].y - 1);
			else if(IsInside((*points)[1].x + 1, (*points)[1].y - 1))
				map.FloodFill(hdc, (*points)[1].x + 1, (*points)[1].y - 1);

			player.research = true;
			player.moved = false;
		}
	}
	else
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x - player.speed] == ROAD)
			{
				dir = 1;
				player.playerPos.x -= player.speed;
			}
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (map.board[curPos.y + player.speed][curPos.x] == ROAD)
			{
				dir = 2;
				player.playerPos.y += player.speed;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x + player.speed] == ROAD)
			{
				dir = 3;
				player.playerPos.x += player.speed;

			}
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (map.board[curPos.y - player.speed][curPos.x] == ROAD)
			{
				dir = 4;
				player.playerPos.y -= player.speed;
			}
		}
	}

	player.pr.playerRect = { player.playerPos.x - player.size - player.speed, player.playerPos.y - player.size - player.speed,
		player.playerPos.x + player.size + player.speed, player.playerPos.y + player.size + player.speed };
	InvalidateRect(hWnd, /*&player.pr.playerRect*/NULL, FALSE);

	ReleaseDC(hWnd, hdc);
}
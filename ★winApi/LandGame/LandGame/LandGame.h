#pragma once

#include "resource.h"

Player player;
Map map;
HDC hdc;
HDC backHDC;

extern vector<POINT> *points;
static bool keydown = false;
static bool drawFill = false;

bool IsInside(int _x, int _y);
void FloodFill(int _x, int _y);
void DrawExtension(HDC hdc);

void DrawBox(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hBit = NULL, oldBit;
	{
		HBRUSH hBrush, oldBrush;
		hMemDC = CreateCompatibleDC(hdc);

		hBrush = CreateSolidBrush(RGB(220, 245, 215));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		if (hBit == NULL)
			hBit = CreateCompatibleBitmap(hdc, 800, 700);	//hdc에 호환되는 이미지
		oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

		Rectangle(hMemDC, 15, 20, 765, 653);

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		map.DrawPloygon(hMemDC);

		for (int i = 15; i <= 765; i++)
		{
			for (int j = 20; j <= 653; j++)
			{
				if (map.board[j][i] == OPEN)
					SetPixel(hMemDC, i, j, RGB(255, 255, 255));
			}
		}
		TransparentBlt(hdc, 15, 20, 750, 633, hMemDC, 15, 20, 750, 633, RGB(255, 255, 255));

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

void FloodFill(int _x, int _y)
{
	if (map.board[_y][_x] == OPEN || map.board[_y][_x] == WALL || map.board[_y][_x] == ROAD)
		return;

	if (map.board[_y][_x] == CLOSE)
	{
		map.board[_y][_x] = OPEN;

		FloodFill(_x + 1, _y);
		FloodFill(_x - 1, _y);
		FloodFill(_x, _y + 1);
		FloodFill(_x, _y - 1);
		FloodFill(_x + 1, _y + 1);
		FloodFill(_x - 1, _y - 1);
		FloodFill(_x - 1, _y + 1);
		FloodFill(_x + 1, _y - 1);
	}
}

void Update(HDC hdc)
{
	DrawExtension(hdc);
	if (keydown)
	{
		map.UpdateMap(hdc);

		if (map.board[player.playerPos.y][player.playerPos.x] == CLOSE)
		{
			switch (player.dir)
			{
			case 1:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y][player.playerPos.x + i] = FOOTPRINT;
				break;
			case 2:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y - i][player.playerPos.x] = FOOTPRINT;
				break;
			case 3:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y][player.playerPos.x - i] = FOOTPRINT;
				break;
			case 4:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y + i][player.playerPos.x] = FOOTPRINT;
				break;
			default:
				break;
			}
			player.moved = true;
		}
		else if (map.board[player.playerPos.y][player.playerPos.x] == ROAD && player.moved)		//도형 다 그렸을 때
		{
			points->push_back(player.playerPos);

			switch (player.dir)
			{
			case 1:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y][player.playerPos.x + i] = FOOTPRINT;
				break;
			case 2:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y - i][player.playerPos.x] = FOOTPRINT;
				break;
			case 3:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y][player.playerPos.x - i] = FOOTPRINT;
				break;
			case 4:
				for (int i = 0; i < player.speed; i++)
					map.board[player.playerPos.y + i][player.playerPos.x] = FOOTPRINT;
				break;
			default:
				break;
			}

			if (IsInside((*points)[1].x + 1, (*points)[1].y + 1))
				FloodFill((*points)[1].x + 1, (*points)[1].y + 1);
			else if (IsInside((*points)[1].x - 1, (*points)[1].y + 1))
				FloodFill((*points)[1].x - 1, (*points)[1].y + 1);
			else if (IsInside((*points)[1].x - 1, (*points)[1].y - 1))
				FloodFill((*points)[1].x - 1, (*points)[1].y - 1);
			else if (IsInside((*points)[1].x + 1, (*points)[1].y - 1))
				FloodFill((*points)[1].x + 1, (*points)[1].y - 1);

			drawFill = true;
			player.moved = false;
			player.research = true;
		}
	}
}

void DrawExtension(HDC hdc)
{
	RECT rc_Score = { 600, 30, 700, 50 };
	DrawText(hdc, to_wstring(map.extension).c_str(), _tcslen(to_wstring(map.extension).c_str()), &rc_Score, DT_SINGLELINE | DT_RIGHT);

	RECT rc_ScorePercent = { 600, 30, 710, 50 };
	DrawText(hdc, _T("%"), _tcslen(_T("%")), &rc_ScorePercent, DT_SINGLELINE | DT_RIGHT);

	RECT rc_Score2 = { 700, 30, 750, 50 };
	DrawText(hdc, _T("80%"), _tcslen(_T("80%")), &rc_Score2, DT_SINGLELINE | DT_RIGHT);
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc = GetDC(hWnd);
	int tmpDir = player.dir;
	POINT curPos;

	curPos.x = player.playerPos.x;
	curPos.y = player.playerPos.y;

	int tmpX = curPos.x;
	int tmpY = curPos.y;

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		keydown = true;
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x - player.speed] == ROAD || map.board[curPos.y][curPos.x - player.speed] == CLOSE)
			{
				player.dir = 1;
				if (tmpDir != player.dir)
					points->push_back(player.playerPos);

				player.playerPos.x -= player.speed;
			}
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
  			if (map.board[curPos.y + player.speed][curPos.x] == ROAD || map.board[curPos.y + player.speed][curPos.x] == CLOSE)
			{
				player.dir = 2;
				if (tmpDir != player.dir)
					points->push_back(player.playerPos);

				player.playerPos.y += player.speed;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x + player.speed] == ROAD || map.board[curPos.y][curPos.x + player.speed] == CLOSE)
			{
				player.dir = 3;
				if (tmpDir != player.dir)
					points->push_back(player.playerPos);

				player.playerPos.x += player.speed;
			}
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (map.board[curPos.y - player.speed][curPos.x] == ROAD || map.board[curPos.y - player.speed][curPos.x] == CLOSE)
			{
				player.dir = 4;
				if (tmpDir != player.dir)
					points->push_back(player.playerPos);

				player.playerPos.y -= player.speed;
			}
		}
	}
	else
	{
		keydown = false;
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x - player.speed] == ROAD)
			{
				player.dir = 1;
				player.playerPos.x -= player.speed;
			}
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (map.board[curPos.y + player.speed][curPos.x] == ROAD)
			{
				player.dir = 2;
				player.playerPos.y += player.speed;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (map.board[curPos.y][curPos.x + player.speed] == ROAD)
			{
				player.dir = 3;
				player.playerPos.x += player.speed;
			}
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			if (map.board[curPos.y - player.speed][curPos.x] == ROAD)
			{
				player.dir = 4;
				player.playerPos.y -= player.speed;
			}
		}
	}

	/*player.pr.playerRect = { player.playerPos.x - player.size - player.speed, player.playerPos.y - player.size - player.speed,
		player.playerPos.x + player.size + player.speed, player.playerPos.y + player.size + player.speed };*/
	InvalidateRect(hWnd, /*&player.pr.playerRect*/NULL, FALSE);

	ReleaseDC(hWnd, hdc);
}
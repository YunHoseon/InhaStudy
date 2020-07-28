#pragma once

#include "resource.h"

enum State { CLOSE, OPEN, ROAD };
State state;
Player player;

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
	if (GetKeyState('A') & 0x8000)
	{
		if (GetKeyState('S') & 0x8000)
			player.PosY += 1;
		else if (GetKeyState('W') & 0x8000)
			player.PosY -= 1;
		player.PosX -= 1;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		if (GetKeyState('D') & 0x8000)
			player.PosX += 1;
		player.PosY += 1;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		if (GetKeyState('W') & 0x8000)
			player.PosY -= 1;
		player.PosX += 1;
	}
	else if (GetKeyState('W') & 0x8000)
	{
		if (GetKeyState('A') & 0x8000)
			player.PosX -= 1;
		player.PosY -= 1;
	}
}
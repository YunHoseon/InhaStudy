#include "stdafx.h"
#include "Bitmap.h"

Bitmap::Bitmap()
{
	CreateBitmap();
}

Bitmap::~Bitmap()
{
}

void Bitmap::CreateBitmap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\board.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage, sizeof(BITMAP), &bitBack);
}

void Bitmap::DrawBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void Bitmap::DeleteBitmap()
{
	DeleteObject(hBackImage);
}

#include "stdafx.h"
#include "Bitmap.h"

#define SPEED 5
extern Singleton *singleton;

Bitmap::Bitmap()
{
	CreateBitmap();
}

Bitmap::~Bitmap()
{
}

void Bitmap::CreateBitmap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\map\\background_NewBarkTown_big_.bmp"), 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage, sizeof(BITMAP), &bitBack);

	hBackImage2 = (HBITMAP)LoadImage(NULL, TEXT("images\\map\\background_root29_big.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage2, sizeof(BITMAP), &bitBack2);

	/*map_Images.insert(std::make_pair(0, (HBITMAP)LoadImage(NULL, TEXT("images\\objects\\tree.bmp"), 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)));
	map_Images.insert(std::make_pair(1, (HBITMAP)LoadImage(NULL, TEXT("images\\objects\\myHouse.bmp"), 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)));
	map_Images.insert(std::make_pair(2, (HBITMAP)LoadImage(NULL, TEXT("images\\objects\\laboratory.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)));*/
}

void Bitmap::DrawBitmap(HWND hWnd, HDC hdc)
{
	switch (singleton->mapState)
	{
	case 1:
	{
		HDC hMemDC;
		HBITMAP hOldBitmap;
		int bx, by;
		static int bitmapX = 380, bitmapY = 100;

		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		if (singleton->movable == true)
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
				bitmapX -= SPEED;
			else if (GetKeyState(VK_RIGHT) & 0x8000)
				bitmapX += SPEED;
			else if (GetKeyState(VK_UP) & 0x8000)
				bitmapY -= SPEED;
			else if (GetKeyState(VK_DOWN) & 0x8000)
				bitmapY += SPEED;
		}

		BitBlt(hdc, 0, 0, bx, by, hMemDC, bitmapX, bitmapY, SRCCOPY);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		break;
	}
	case 2:
	{
		HDC hMemDC;
		HBITMAP hOldBitmap;
		int bx, by;
		static int bitmapX = 700, bitmapY = 150;

		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage2);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		if (singleton->movable == true)
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
				bitmapX -= SPEED;
			else if (GetKeyState(VK_RIGHT) & 0x8000)
				bitmapX += SPEED;
			else if (GetKeyState(VK_UP) & 0x8000)
				bitmapY -= SPEED;
			else if (GetKeyState(VK_DOWN) & 0x8000)
				bitmapY += SPEED;
		}

		BitBlt(hdc, 0, 0, bx, by, hMemDC, bitmapX, bitmapY, SRCCOPY);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
		break;
	}
	default:
		break;
	}
	
}

void Bitmap::DeleteBitmap()
{
	DeleteObject(hBackImage);
}

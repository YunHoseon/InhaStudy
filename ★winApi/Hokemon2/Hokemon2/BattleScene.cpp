#include "stdafx.h"
#include "BattleScene.h"


BattleScene::BattleScene()
{
	background_under = {};
	Btn_battle = {};

	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\ui\\BattleBackground__.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	/*battleUI = (HBITMAP)LoadImage(NULL, TEXT("images\\ui\\BattleBackground__.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);*/
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
}

void BattleScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void BattleScene::Render(HWND hWnd, HDC hdc)
{


	HDC hMemDC;
	HBITMAP hOldBitmap;
	BITMAP tmpBitmap;
	int bx, by;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
	GetObject(hBackImage, sizeof(BITMAP), &tmpBitmap);
	bx = tmpBitmap.bmWidth;
	by = tmpBitmap.bmHeight;
	BitBlt(hdc, 125, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

	/*SelectObject(hMemDC, battleUI);
	GetObject(battleUI, sizeof(BITMAP), &tmpBitmap);
	bx = tmpBitmap.bmWidth;
	by = tmpBitmap.bmHeight;
	BitBlt(hdc, 125, 260, bx, by, hMemDC, 0, 0, SRCCOPY);*/

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void BattleScene::Free(HWND hWnd)
{
}

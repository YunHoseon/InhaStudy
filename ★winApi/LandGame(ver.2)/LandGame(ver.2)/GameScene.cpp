#include "stdafx.h"
#include "GameScene.h"
#include "Bitmap.h"

extern Singleton *singleton;

GameScene::GameScene()
{
	bitmap = new Bitmap;
	bitmap->CreateBitmap();
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	SetTimer(singleton->sceneManager->hWnd, 1, 70, NULL);
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	default:
		break;
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

	bitmap->DrawBitmap(hWnd, hdc);
	DrawBox(hWnd, hdc);

	BitBlt(hdc, 0, 0, bitmap->bitBack.bmWidth, bitmap->bitBack.bmHeight, singleton->backHDC, 15, 20, SRCCOPY);
}

void GameScene::Free()
{
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
			hBit = CreateCompatibleBitmap(hdc, 800, 700);	//hdc에 호환되는 이미지
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
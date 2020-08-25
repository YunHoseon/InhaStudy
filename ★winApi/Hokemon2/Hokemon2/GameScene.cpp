#include "stdafx.h"
#include "GameScene.h"

extern Singleton *singleton;
extern TileMap tileMap;

GameScene::GameScene()
{
	player = new Player;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{

}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	player->UpdatePlayer(message, wParam, lParam);
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	//static HBITMAP backHBit = NULL;

	//if (backHBit == NULL)
	//{
	//	singleton->backHDC = CreateCompatibleDC(hdc);
	//	backHBit = CreateCompatibleBitmap(hdc, bitmap->bitBack.bmWidth + 15, bitmap->bitBack.bmHeight + 20);
	//	SelectObject(singleton->backHDC, backHBit);
	//}
	//bitmap->DrawBitmap(hWnd, singleton->backHDC);
	//DrawBox(hWnd, singleton->backHDC);

	//BitBlt(hdc, 15, 20, bitmap->bitBack.bmWidth, bitmap->bitBack.bmHeight, singleton->backHDC, 15, 20, SRCCOPY);

	tileMap.DrawMap(hdc);
	player->DrawPlayer(hdc);
}

void GameScene::Free(HWND hWnd)
{
	KillTimer(hWnd, 1);
}

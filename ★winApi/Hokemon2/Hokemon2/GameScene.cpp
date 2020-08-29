#include "stdafx.h"
#include "GameScene.h"

extern Singleton *singleton;
extern TileMap tileMap;
extern Bitmap bitmap;

GameScene::GameScene()
{
	player = new Player;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	bitmap.CreateBitmap();
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	player->UpdatePlayer(message, wParam, lParam);
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	bitmap.DrawBitmap(hWnd, hdc);
	tileMap.DrawMap(hdc);

	//격자 그리기
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
			Rectangle(hdc, tileMap.map[i][j].collider.left, tileMap.map[i][j].collider.top, tileMap.map[i][j].collider.right, tileMap.map[i][j].collider.bottom);
	}
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);*/

	player->DrawPlayer(hdc);
}

void GameScene::Free(HWND hWnd)
{
	KillTimer(hWnd, 1);
}

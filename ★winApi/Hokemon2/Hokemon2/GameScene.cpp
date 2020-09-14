#include "stdafx.h"
#include "GameScene.h"
#include "SoundManager.h"

extern Singleton *singleton;
extern TileMap tileMap;
extern Bitmap bitmap;
extern Player player;
extern SoundManager* g_theSoundManager;

GameScene::GameScene()
{
	isInMenu = false;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	bitmap.CreateBitmap();

	if (singleton->mapState == 1)
	{
		g_theSoundManager->AddBGM("sound/New Bark Town.mp3");
		g_theSoundManager->PlayBGM();
	}
	else if (singleton->mapState == 2)
	{
		g_theSoundManager->AddBGM("sound/Route 29.mp3");
		g_theSoundManager->PlayBGM();
	}
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	player.UpdatePlayer(message, wParam, lParam);

	if (singleton->isBattle == true)
		singleton->sceneManager->SceneChange(GameState::BATTLE);

	if (GetKeyState('q') & 0x8000 || GetKeyState('Q') & 0x8000)
		isInMenu = (isInMenu == true) ? false : true;

		singleton->movable = (isInMenu == true) ? false : true;
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	tileMap.DrawMap(hdc);
	bitmap.DrawBitmap(hWnd, hdc);

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

	player.DrawPlayer(hWnd, hdc);
}

void GameScene::Free(HWND hWnd)
{
	g_theSoundManager->Stop();
	KillTimer(hWnd, 1);
}

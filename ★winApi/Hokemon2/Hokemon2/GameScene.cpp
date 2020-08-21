#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"

extern Singleton *singleton;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
}

void GameScene::Free(HWND hWnd)
{
	KillTimer(hWnd, 1);
}

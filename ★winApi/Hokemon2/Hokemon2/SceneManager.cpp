#include "stdafx.h"
#include "SceneManager.h"

#include "Scene.h"
#include "StartScene.h"
#include "GameScene.h"
#include "BattleScene.h"

extern Singleton *singleton;

SceneManager::SceneManager()
{
	curScene = NULL;
	gameScene = NULL;
	battleScene = NULL;
}

SceneManager::~SceneManager()
{
}

void SceneManager::ManagerInit()
{
	gameState = GameState::START;
	timerId = TimerID::TM_START;

	SetTimer(hWnd, (int)timerId, 1000 / 30, NULL);
	curScene = startScene = new StartScene;
	curScene->Init();
}

void SceneManager::ManagerUpdate(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (curScene != NULL)
		curScene->Update(message, wParam, lParam);
}

void SceneManager::ManagerRender(HWND hWnd, HDC hdc)
{
	if (curScene != NULL)
		curScene->Render(hWnd, hdc);
}

void SceneManager::SceneChange(GameState nextState)
{
	if(curScene != NULL)
		curScene->Free(hWnd);

	switch (nextState)
	{
	case GameState::START:

		break;

	case GameState::INGAME:
		if (gameScene == NULL)
			gameScene = new GameScene;

		timerId = TimerID::TM_INGAME;
		curScene = gameScene;
		break;

	case GameState::BATTLE:
		if (battleScene == NULL)
			battleScene = new BattleScene;

		timerId = TimerID::TM_BATTLE;
		curScene = battleScene;
		break;

	default:
		break;
	}

	if(curScene != NULL)
		curScene->Init();
}
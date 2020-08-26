#include "stdafx.h"
#include "SceneManager.h"

#include "Scene.h"
#include "StartScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "BattleScene.h"

extern Singleton *singleton;

SceneManager::SceneManager()
{
	curScene = NULL;
	loadScene = NULL;
	gameScene = NULL;
	battleScene = NULL;
}

SceneManager::~SceneManager()
{
}

void SceneManager::ManagerInit()
{
	gameState = GameState::START;

	SetTimer(hWnd, (int)TimerID::TM_RENDER, 1000 / 30, NULL);
	SetTimer(hWnd, (int)TimerID::TM_UPDATE, 1000 / 30, NULL);
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
		
	case GameState::LOAD:
		if (loadScene == NULL)
			loadScene = new LoadScene;

		curScene = loadScene;
		break;

	case GameState::INGAME:
		if (gameScene == NULL)
			gameScene = new GameScene;

		curScene = gameScene;
		break;

	case GameState::BATTLE:
		if (battleScene == NULL)
			battleScene = new BattleScene;

		curScene = battleScene;
		break;

	default:
		break;
	}

	if(curScene != NULL)
		curScene->Init();
}
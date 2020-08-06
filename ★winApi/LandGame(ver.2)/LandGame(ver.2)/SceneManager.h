#pragma once

#include "StartScene.h"
#include "GameScene.h"
#include "EndScene.h"

class SceneManager
{
public:
	Scene *curScene;
	StartScene *startScene;
	GameScene *gameScene;
	EndScene *endScene;

	SceneManager()
	{
		curScene = NULL;
		startScene = NULL;
		gameScene = NULL;
		endScene = NULL;
	}

	~SceneManager();
};
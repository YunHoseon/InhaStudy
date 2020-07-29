#pragma once

#include "CurScene.h";
#include "StartScene.h";
#include "IngameScene.h";
#include "EndScene.h";

class SceneManager
{
	CurScene	*curScene;
	StartScene	*startScene;
	IngameScene *ingameScene;
	EndScene	*endScene;
	
public:
	SceneManager();
	~SceneManager();
};


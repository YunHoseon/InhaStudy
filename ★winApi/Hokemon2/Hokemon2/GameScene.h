#pragma once

#include "Scene.h"
class Player;

class GameScene :
	public Scene
{
public:
	bool isInMenu;

	GameScene();
	virtual ~GameScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};
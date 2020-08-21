#pragma once
#include "Scene.h"

class BattleScene :
	public Scene
{
public:
	BattleScene();
	~BattleScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};


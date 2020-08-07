#pragma once
#include "Scene.h"
class StartScene :
	public Scene
{
public:
	bool startGame;

	RECT drawTitle;
	RECT drawStartBtn;
	RECT drawQuitBtn;

	StartScene();
	~StartScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free();
};


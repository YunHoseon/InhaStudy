#pragma once
#include "Scene.h"
enum class TimerID;

class StartScene :
	public Scene
{
public:
	bool startGame;
	TimerID timerId;

	RECT drawTitle;
	RECT drawStartBtn;
	RECT drawQuitBtn;

	StartScene();
	virtual ~StartScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};


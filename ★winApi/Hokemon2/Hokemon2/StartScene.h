#pragma once
#include "Scene.h"
enum class TimerID;

class StartScene :
	public Scene
{
public:
	TimerID timerId;

	StartScene();
	virtual ~StartScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};


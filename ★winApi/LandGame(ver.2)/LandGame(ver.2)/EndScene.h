#pragma once
#include "Scene.h"
class EndScene :
	public Scene
{
public:
	EndScene();
	~EndScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free();
};


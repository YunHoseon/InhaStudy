#pragma once
#include "Scene.h"

class BattleScene :
	public Scene
{
	RECT background_under;
	RECT Btn_battle;
	RECT Btn_run;
public:
	HBITMAP hBackImage;
	HBITMAP battleUI;

	BITMAP bitBack;

	BattleScene();
	~BattleScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};


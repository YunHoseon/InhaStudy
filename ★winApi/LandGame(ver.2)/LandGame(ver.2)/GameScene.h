#pragma once

#include "Scene.h"
class Bitmap;

class GameScene :
	public Scene
{
public:
	Bitmap *bitmap;

	GameScene();
	~GameScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free();

	void DrawBox(HWND hWnd, HDC hdc);

};


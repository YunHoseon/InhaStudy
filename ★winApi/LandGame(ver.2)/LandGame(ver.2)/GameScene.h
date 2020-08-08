#pragma once

#include "Scene.h"
class Bitmap;
class Player;

class GameScene :
	public Scene
{
public:
	Bitmap *bitmap;
	Player *player;
	POINT mapPoint[4];
	vector<POINT> *points;

	GameScene();
	virtual ~GameScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);

	void DrawBox(HWND hWnd, HDC hdc);
	bool isInOutline();
};


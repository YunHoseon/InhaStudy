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
	vector<POINT> transparentPolygon;
	vector<POINT> footPrint;

	GameScene();
	virtual ~GameScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);

	void DrawBox(HWND hWnd, HDC hdc);
	void DrawFootPrint(HDC hdc);

	bool isInTpPolyLine(POINT tmpPt, int * lineNum = NULL);
	bool isInsideOutline(POINT tmpPt);
	bool isInsidePoly(int _x, int _y);
	bool isInsideFootprint(POINT tmpPt);
	bool isInLineFootprint(POINT tmpPt);

	bool PolygonMakedCompleteCheck();

	vector<POINT> CollectTpPt(int startLineNum, int endLineNum);
};


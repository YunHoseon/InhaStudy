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
	bool isInsideOutline(POINT tmpPt);							//테두리 안쪽인지
	bool isInsidePoly(int _x, int _y);							//투명도형라인 위인지
	bool isInsideFootprint(POINT tmpPt);						//발자국으로 그려진 도형안에 있는지
	bool isInLineFootprint(POINT tmpPt);						//발자국으로 그려진 도형의 테두리 위인지

	bool PolygonMakedCompleteCheck();

	vector<POINT> CollectTpPt(int startLineNum, int endLineNum);
};


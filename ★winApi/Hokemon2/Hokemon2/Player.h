#pragma once
#include "Hokemon.h"

class Player
{
	char pId[32];
	POINT pt;
	Hokemon myMonster[6];
	int speed;

public:
	HBITMAP hAniImage;
	BITMAP bitAni;

	int run_Frame_max;
	int run_Frame_min;
	int cur_Frame;
	int dir;
	int ax, ay;

	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	RECT playerCollider;

	Player();
	~Player();

	void UpdatePlayer(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawPlayer(HWND hWnd, HDC hdc);
	void UpdateFrame(HWND hWnd);

	/*getter setter*/
	char* GetId() { return pId; }
	void SetId(char* _pId) { strcpy_s(pId, _pId); }

	POINT GetPos() { return pt; }
	void SetPos(POINT _pt) { pt = _pt; }

	Hokemon* GetMyMonster(int _mNum) { return &myMonster[_mNum]; }
	void SetMyMonster(Hokemon* _myMonster, int _mNum) { myMonster[_mNum] = *_myMonster; }
};


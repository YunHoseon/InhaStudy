#pragma once
#include "Hokemon.h"

class Player
{
	char pId[32];
	POINT pt;
	Hokemon myMonster[6];

	int speed;
	RECT playerCollider;

public:
	Player();
	~Player();

	void UpdatePlayer(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawPlayer(HDC hdc);

	/*getter setter*/
	char* GetId() { return pId; }
	void SetId(char* _pId) { strcpy_s(pId, _pId); }

	POINT GetPos() { return pt; }
	void SetPos(POINT _pt) { pt = _pt; }

	Hokemon* GetMyMonster(int _mNum) { return &myMonster[_mNum]; }
	void SetMyMonster(Hokemon* _myMonster, int _mNum) { myMonster[_mNum] = *_myMonster; }
};


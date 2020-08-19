#pragma once
#include <stdio.h>
#include "Monster.h"

typedef class Player
{
private:
	char pName[16] = { NULL };
	int pMoney = 1000;

	int pX = 65;
	int pY = 11;
	Monster MyMonster[6];

public:

	/*Player Class getset*/

	char* GetpName() { return pName; }
	void SetpName(const char* _pName) { strcpy_s(pName, _pName); }

	int GetpMoney() { return pMoney; }
	void SetpMoney(int _pMoney) { pMoney = _pMoney; }

	int GetpX() { return pX; }
	void SetpX(int _pX) { pX = _pX; }

	int GetpY() { return pY; }
	void SetpY(int _pY) { pY = _pY; }

	Monster* GetmyMonster(int mNum) { return &MyMonster[mNum]; }
	void SetmyMonster(Monster* _myMonster, int mNum) { MyMonster[mNum] = *_myMonster; }
}Player;
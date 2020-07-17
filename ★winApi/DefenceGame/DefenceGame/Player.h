#pragma once
#include "stdafx.h"

using namespace std;
class Player
{
	TCHAR ID[9];
	int score;

public:
	Player();
	~Player();

	TCHAR* GetID() { return ID; }
	void SetID(TCHAR *_ID) { lstrcpy(ID, _ID); }

	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; }
};


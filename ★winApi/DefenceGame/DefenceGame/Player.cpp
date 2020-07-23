#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	lstrcpy(ID, _T("user"));
	score = 0;
}


Player::~Player()
{
}

#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	PosX = 15;
	PosY = 20;
	size = 10;
}

Player::~Player()
{
}

void Player::DrawPlayer(HDC hdc)
{
	Ellipse(hdc, PosX - size, PosY - size, PosX + size, PosY + size);
}

void Player::PlayerMove()
{

}

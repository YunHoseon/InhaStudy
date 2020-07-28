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

void Player::PlayerMove(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			PosX -= 1;
			break;

		case VK_RIGHT:
			PosX += 1;
			break;

		case VK_UP:
			PosY -= 1;
			break;

		case VK_DOWN:
			PosY += 1;
			break;
		}
		break;
	}
	
}

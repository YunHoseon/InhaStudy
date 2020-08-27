#include "stdafx.h"
#include "TileMap.h"

#define SPEED 5

extern Singleton *singleton;

TileMap::TileMap()
{
	char tmpMap[COL][ROW+1] =
	{
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k0000000000000000kkk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "k00000000000000000kk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
	};

	gap = 50;

	for (int i = 0; i < COL-5; i++)		//15
	{
		for (int j = 0; j < ROW-1; j++)	//19
		{
			map[i][j].cell = tmpMap[i][j];

			map[i][j].collider.left = j * gap + POSX;
			map[i][j].collider.top = i * gap + POSY;
			map[i][j].collider.right = gap + (j * gap) + POSX;
			map[i][j].collider.bottom = gap + (i * gap) + POSY;

			switch (map[i][j].cell)
			{
			case '0':
				map[i][j].tileState = TileState::ROAD;
				break;
			case '1':
				map[i][j].tileState = TileState::BUSH;
				break;
			case 'k':
				map[i][j].tileState = TileState::BLOCK;
				break;

			default:
				break;
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::DrawMap(HDC hdc)
{
	UpdateMap();
	HBRUSH oldBrush, roadBrush, bushBrush, blockBrush;
	roadBrush = CreateSolidBrush(RGB(240, 240, 240));
	bushBrush = CreateSolidBrush(RGB(110, 215, 110));
	blockBrush = CreateSolidBrush(RGB(60, 60, 75));

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			switch (map[i][j].tileState)
			{
			case TileState::ROAD:
				oldBrush = (HBRUSH)SelectObject(hdc, roadBrush);
				break;

			case TileState::BUSH:
				oldBrush = (HBRUSH)SelectObject(hdc, bushBrush);
				break;

			case TileState::BLOCK:
				oldBrush = (HBRUSH)SelectObject(hdc, blockBrush);
				break;
			default:
				break;
			}

			Rectangle(hdc, map[i][j].collider.left, map[i][j].collider.top, map[i][j].collider.right, map[i][j].collider.bottom);
			SelectObject(hdc, oldBrush);
		}
	}
	DeleteObject(roadBrush);
	DeleteObject(bushBrush);
	DeleteObject(blockBrush);
}

void TileMap::UpdateMap()
{
	static int colliderMoveX = 0, colliderMoveY = 0;

	if (singleton->movable == true)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			colliderMoveX += SPEED;
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			colliderMoveX -= SPEED;
		}
		else if (GetKeyState(VK_UP) & 0x8000)
		{
			colliderMoveY += SPEED;
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			colliderMoveY -= SPEED;
		}

		for (int i = 0; i < COL - 5; i++)
		{
			for (int j = 0; j < ROW - 1; j++)
			{
				map[i][j].collider.left = j * gap + POSX + colliderMoveX;
				map[i][j].collider.top = i * gap + POSY + colliderMoveY;
				map[i][j].collider.right = gap + (j * gap) + POSX + colliderMoveX;
				map[i][j].collider.bottom = gap + (i * gap) + POSY + colliderMoveY;
			}
		}
	}
}

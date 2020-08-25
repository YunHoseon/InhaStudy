#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap()
{
	char tmpMap[COL][ROW+1] =
	{
		{ "kkkkkkkkkk" },
		{ "k00000000k" },
		{ "k00000000k" },
		{ "k00001000k" },
		{ "k00000000k" },
		{ "k00000000k" },
		{ "k01000000k" },
		{ "k00000000k" },
		{ "k00000000k" },
		{ "kkkkkkkkkk" },
	};

	gap = 20;

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			map[i][j].cell = tmpMap[i][j];

			map[i][j].collider.left = j * gap;
			map[i][j].collider.top = i * gap;
			map[i][j].collider.right = gap + (j * gap);
			map[i][j].collider.bottom = gap + (i * gap);

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
			//map[i][j].cPt.x = 20 + (j * gap);
			//map[i][j].cPt.y = 20 + (i * gap);
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::DrawMap(HDC hdc)
{
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

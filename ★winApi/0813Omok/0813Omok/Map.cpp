#include "stdafx.h"
#include "Map.h"

extern Player_Chat chat;
extern Player_Stone stone;

Map::Map()
{
	gap = 38;

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			board[i][j].crossPt = { 25 + (38 * i), 25 + (38 * j) };

			board[i][j].collider.left = board[i][j].crossPt.x - 10;
			board[i][j].collider.top = board[i][j].crossPt.y - 10;
			board[i][j].collider.right = board[i][j].crossPt.x + 10;
			board[i][j].collider.bottom = board[i][j].crossPt.y + 10;

			board[i][j].stoneColor = -1;
		}
	}
}

Map::~Map()
{
}

void Map::DrawMap(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(250, 203, 125));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	
	Rectangle(hdc, 0, 0, 740, 740);

	for (int i = 0; i < ROW; i++)
	{
		MoveToEx(hdc, 25 + gap*i, 25, NULL);
		LineTo(hdc, 25 + gap*i, 709);
	}

	for (int i = 0; i < COL; i++)
	{
		MoveToEx(hdc, 25, 25 + gap*i, NULL);
		LineTo(hdc, 709, 25 + gap*i);
	}

	//for (int i = 0; i < COL; i++)
	//{
	//	for (int j = 0; j < ROW; j++)
	//	{
	//		Rectangle(hdc, board[i][j].collider.left, board[i][j].collider.top, board[i][j].collider.right, board[i][j].collider.bottom);
	//	}
	//}

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

int *Map::LocationStone(int _mx, int _my)
{
	int *loc = new int[2];

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (board[i][j].collider.left < _mx && board[i][j].collider.right > _mx &&
				board[i][j].collider.top < _my && board[i][j].collider.bottom > _my && board[i][j].stoneColor == -1)
			{
				loc[0] = i;
				loc[1] = j;
				board[i][j].stoneColor = stone.myStoneColor;
				return  loc;
			}
		}
	}
	return NULL;
}

void Map::DrawStone(HDC hdc, int _mx, int _my)
{
	int *loc = LocationStone(_mx, _my);

	if (loc != NULL)
	{
		Ellipse(hdc, board[loc[0]][loc[1]].collider.left - 5, board[loc[0]][loc[1]].collider.top - 5,
			board[loc[0]][loc[1]].collider.right + 5, board[loc[0]][loc[1]].collider.bottom + 5);
	}
}

#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	gap = 40;

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			board[i][j].cellState = CellState::NONE;
			board[i][j].g = 0;
			board[i][j].h = 0;
			board[i][j].f = 0;

			board[i][j].collider.left = j * gap;
			board[i][j].collider.top = i * gap;
			board[i][j].collider.right = 40 + (j * gap);
			board[i][j].collider.bottom = 40 + (i * gap);

			board[i][j].cPt.x = 20 + (j * gap);
			board[i][j].cPt.y = 20 + (i * gap);
		}
	}

	min.f = 1000;
	min.g = 1000;
	min.h = 1000;

	for (int i = 0; i < 8; i++)
	{
		fs[i].f = 1000;
		fs[i].g = 1000;
		fs[i].h = 1000;
	}
		
}

Map::~Map()
{
}

void Map::UpdateMap(HDC hdc, POINT _mousePt)
{
	HBRUSH oldBrush, emptyBrush, startBrush, endBrush, blockBrush, searchedBrush;
	emptyBrush = CreateSolidBrush(RGB(240, 240, 240));
	startBrush = CreateSolidBrush(RGB(255, 105, 110));
	endBrush = CreateSolidBrush(RGB(105, 110, 255));
	blockBrush = CreateSolidBrush(RGB(60, 60, 75));
	searchedBrush = CreateSolidBrush(RGB(110, 215, 110));

	int *loc = CheckCellPt(_mousePt);

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++) 
		{
			switch (board[i][j].cellState)
			{
			case CellState::NONE:
				oldBrush = (HBRUSH)SelectObject(hdc, emptyBrush);
				break;

			case CellState::START:
			case CellState::ROAD:
				oldBrush = (HBRUSH)SelectObject(hdc, startBrush);
				break;

			case CellState::END:
				oldBrush = (HBRUSH)SelectObject(hdc, endBrush);
				break;

			case CellState::BLOCK:
				oldBrush = (HBRUSH)SelectObject(hdc, blockBrush);
				break;

			case CellState::SEARCHED:
				oldBrush = (HBRUSH)SelectObject(hdc, searchedBrush);
				break;

			default:
				break;
			}

			Rectangle(hdc, board[i][j].collider.left, board[i][j].collider.top, board[i][j].collider.right, board[i][j].collider.bottom);
			SelectObject(hdc, oldBrush);
		}
	}
	DeleteObject(emptyBrush);
	DeleteObject(startBrush);
	DeleteObject(endBrush);
	DeleteObject(blockBrush);
	DeleteObject(searchedBrush);
}

int* Map::CheckCellPt(POINT _mousePt)
{
	int *loc = new int[2];			//Ä­ À§Ä¡

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (board[i][j].collider.left < _mousePt.x && board[i][j].collider.right > _mousePt.x &&
				board[i][j].collider.top < _mousePt.y && board[i][j].collider.bottom > _mousePt.y && board[i][j].cellState == CellState::NONE)
			{
				loc[0] = i;
				loc[1] = j;
				board[i][j].cellState = CellState::START;
				return  loc;
			}
		}
	}
	return NULL;
}

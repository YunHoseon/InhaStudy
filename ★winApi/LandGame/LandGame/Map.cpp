#include "stdafx.h"
#include "Map.h"

extern list<int*> closes;
extern Player player;
extern vector<POINT> *points;
extern vector<vector<POINT>*> ploygons;
extern int idxPoint;

Map::Map()
{
	for (int i = 0; i <= ROW; i++)
	{
		for (int j = 0; j <= COL; j++)
			board[j][i] = -1;
	}

	/* 게임 판 */
	for (int i = 20; i <= 653; i++)
	{
		for (int j = 15; j <= 765; j++)
			board[i][j] = 0;
	}

	/* 테두리 */
	for (int i = 20; i <= 653; i++)
	{
		board[i][15] = 2;
		board[i][765] = 2;
	}

	for (int i = 15; i < 765; i++)
	{
		board[20][i] = 2;
		board[653][i] = 2;
	}
}

Map::~Map()
{
}

void Map::InitMap()
{
	
}

void Map::UpdateMap(HDC hdc)
{
	if (player.research)
	{
		for (int i = 0; i <= ROW; i++)		//3을 2로
		{
			for (int j = 0; j <= COL; j++)
			{
				if (board[j][i] == FOOTPRINT)
					board[j][i] = ROAD;
			}
		}
		player.research = false;
	}
}

void Map::FloodFill(HDC hdc, int _x, int _y)	//시작점 판단해야함
{
	if (board[_y][_x] == CLOSE)
	{
		board[_y][_x] = OPEN;
		FloodFill(hdc, _x + 1, _y);
		FloodFill(hdc, _x - 1, _y);
		FloodFill(hdc, _x, _y + 1);
		FloodFill(hdc, _x, _y - 1);
		FloodFill(hdc, _x + 1, _y + 1);
		FloodFill(hdc, _x - 1, _y - 1);
		FloodFill(hdc, _x - 1, _y + 1);
		FloodFill(hdc, _x + 1, _y - 1);
	}
}

void Map::DrawPloygon(HDC hdc)
{
	for (vector<POINT> * polygon : ploygons)
		Polygon(hdc, &(*polygon)[0], polygon->size());

	if (player.research)
	{
		POINT *vArr = &(*points)[0];	//벡터를 배열로
		MoveToEx(hdc, player.playerPos.x, player.playerPos.y, NULL);

		ploygons.push_back(points);
		points = new vector<POINT>;
	}
}

#include "stdafx.h"
#include "Map.h"

extern list<int*> closes;
extern Player player;
extern vector<POINT> *points;
extern vector<vector<POINT>*> ploygons;

Map::Map()
{
	opened = 0;
	closed = 0;
	road = 0;
	extension = 0;

	for (int i = 0; i <= ROW; i++)
		for (int j = 0; j <= COL; j++)
			board[j][i] = -1;

	/* 게임 판 */
	for (int i = 20; i <= 653; i++)
		for (int j = 15; j <= 765; j++)
			board[i][j] = 0;

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
		for (int i = 15; i <= 765; i++)		//3을 2로
		{
			for (int j = 20; j <= 653; j++)
			{
				if (board[j][i] == FOOTPRINT)
					board[j][i] = ROAD;
			}
		}

		for (int i = 15; i <= 765; i++)		//보드의 open, close, road탐색
		{
			for (int j = 20; j <= 653; j++)
			{
				if (board[j][i] == OPEN)
					opened += 1;
				else if (board[j][i] == CLOSE)
					closed += 1;
				else if (board[j][i] == ROAD)
					road += 1;
			}
		}

		extension = (((double)opened + (double)road) / (double)closed) * 100;	//몇 퍼센트 확장되었는지
		player.research = false;
	}
}

void Map::DrawPloygon(HDC _hdc)
{
	/*for (vector<POINT> * polygon : ploygons)
		Polygon(_hdc, &(*polygon)[0], polygon->size());*/

	if (player.research)
	{
		POINT *vArr = &(*points)[0];	//벡터를 배열로
		MoveToEx(_hdc, player.playerPos.x, player.playerPos.y, NULL);

		ploygons.push_back(points);
		points = new vector<POINT>;
	}
}

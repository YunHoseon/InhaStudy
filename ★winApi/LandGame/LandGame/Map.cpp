#include "stdafx.h"
#include "Map.h"

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

void Map::UpdateMap()
{

}

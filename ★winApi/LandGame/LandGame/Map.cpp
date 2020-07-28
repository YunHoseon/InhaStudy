#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			map[i][j] = 0;
	}


}

Map::~Map()
{
}

void Map::InitMap()
{

}

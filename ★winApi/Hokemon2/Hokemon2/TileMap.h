#pragma once

typedef struct Tile
{
	TileState tileState;
	int size;
	POINT pt;
};

class TileMap
{
	Tile map[100][100];
public:
	TileMap();
	~TileMap();

	/*getter setter*/

};


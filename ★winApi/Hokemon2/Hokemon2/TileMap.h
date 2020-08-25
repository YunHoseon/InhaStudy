#pragma once

#define ROW 10
#define COL 10
enum class TileState;

typedef struct Tile
{
	char cell;
	TileState tileState;
	RECT collider;
};

class TileMap
{
public:
	Tile map[COL][ROW];
	int gap;
	TileMap();
	~TileMap();

	void DrawMap(HDC hdc);
};


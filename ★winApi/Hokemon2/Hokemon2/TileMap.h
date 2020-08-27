#pragma once

#define ROW 20
#define COL 20
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
	void UpdateMap();
};


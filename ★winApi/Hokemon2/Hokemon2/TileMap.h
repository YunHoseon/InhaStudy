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

	char Map_Town[COL][ROW + 1];
	char Map_Forest[COL][ROW + 1];

	TileMap();
	~TileMap();

	void DrawMap(HDC hdc);
	void UpdateMap();
};


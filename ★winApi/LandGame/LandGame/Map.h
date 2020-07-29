#pragma once
#define ROW 800
#define COL 700

class Map
{
public:
	int board[COL][ROW];

	Map();
	~Map();

	void InitMap();
	void UpdateMap();
};


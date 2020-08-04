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
	void UpdateMap(HDC hdc);
	void FloodFill(int _x, int _y);
	void DrawPloygon(HDC hdc);
};


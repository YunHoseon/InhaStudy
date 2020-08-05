#pragma once
#define ROW 800
#define COL 700

class Map
{
public:
	int board[COL][ROW];
	int opened;
	int closed;
	int road;
	double extension;

	Map();
	~Map();

	void InitMap();
	void UpdateMap(HDC hdc);
	void DrawPloygon(HDC _hdc);
};


#pragma once

#define ROW 19
#define COL 19

class Map
{
public:
	int gap;

	typedef struct Board
	{
		POINT crossPt;
		RECT collider;
		int stoneColor;		// 0 : empty   1 : white   2 : black
	}Board;
	Board board[COL][ROW];

	Map();
	~Map();

	void DrawMap(HDC hdc);
	int *LocationStone(int _mx, int _my);
	void DrawStone(HDC hdc, int _mx, int _my);
};


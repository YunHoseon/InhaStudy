#pragma once
#include <vector>

#define COL 15
#define ROW 15

using namespace std;
enum class CellState;

class Map
{
public:
	int gap;

	typedef struct Cell
	{
		CellState cellState;
		double g;
		double h;
		double f;
		RECT collider;
		POINT cPt;
	};

	Cell board[COL][ROW];
	Cell min;

	vector<Cell> footprint;
	Cell fs[8];

	Map();
	~Map();

	void UpdateMap(HDC hdc, POINT _mousePt);
	int* CheckCellPt(POINT _mousePt);
};


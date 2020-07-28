#pragma once
#define ROW 800
#define COL 700

class Map
{
public:
	int map[COL][ROW];

	Map();
	~Map();

	void InitMap();
};


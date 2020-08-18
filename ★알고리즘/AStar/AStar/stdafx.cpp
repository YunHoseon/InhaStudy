// stdafx.cpp : source file that includes just the standard includes
// AStar.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

Map map;

void AStar(POINT _startNend[])
{
	map.footprint.push_back(map.board[_startNend[0].y][_startNend[0].x]);	//경로 저장

	while (1)
	{
		for (int i = 0; i < WAYS; i++)			//8방향 탐색
		{
			int sx = _startNend[0].x + Ways[i][0], sy = _startNend[0].y + Ways[i][1];
			int ex = _startNend[1].x, ey = _startNend[1].y;

			if (sx < 0 || sy < 0 || sx > ROW || sy > COL || map.board[sy][sx].cellState == CellState::BLOCK)
				continue;

			if (i < 4)	//0 ~ 3
				map.board[sy][sx].g += 10;
			else        //4 ~ 7
				map.board[sy][sx].g += 14;

			map.board[sy][sx].h = pow(pow(ex - sx, 2) + pow(ey - sy, 2), 0.5f);
			map.board[sy][sx].f = map.board[sy][sx].g + map.board[sy][sx].h;

			map.board[sy][sx].cellState = CellState::SEARCHED;
			map.fs[i].f = map.board[sy][sx].f;
		}

		map.min = map.fs[0];					//목적지에 가장 가까운 곳 찾기
		for (int i = 1; i < WAYS; i++)
		{
			if (map.min.f > map.fs[i].f)
				map.min = map.fs[i];
			else if (map.min.f == map.fs[i].f)
			{
				if (map.min.h > map.fs[i].h)
					map.min = map.fs[i];
			}
		}
		map.footprint.push_back(map.min);		//가장 가까운 곳 저장

		for (int i = 0; i < map.footprint.size(); i++)
			map.footprint[i].cellState = CellState::ROAD;
		
		for (int i = 0; i < COL; i++)
		{
			for (int j = 0; j < ROW; j++)
			{
				if (map.board[i][j].collider.left < map.min.cPt.x && map.board[i][j].collider.right >  map.min.cPt.x &&
					map.board[i][j].collider.top < map.min.cPt.y && map.board[i][j].collider.bottom > map.min.cPt.y)
				{
					_startNend[0] = map.min.cPt;
					break;
				}
			}
		}

		for (int i = 0; i < WAYS; i++)
		{
			map.fs[i].f = 1000;
			map.fs[i].g = 1000;
			map.fs[i].h = 1000;
		}

		if(map.min.h <= 0)
			break;
	}
}
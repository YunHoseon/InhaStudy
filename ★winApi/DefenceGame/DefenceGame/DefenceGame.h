#pragma once

#include "resource.h"

enum GameState { START = 100, INGAME, END };	//게임 상태
enum GameState gameState;

extern vector<CObjects*> objects;

Player player;					//플레이어 정보

void delay(unsigned int sec)     // 특정 시간(초)만큼 기다리는 함수
{
	clock_t ticks1 = clock();
	clock_t ticks2 = ticks1;
	while ((ticks2 / CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < (clock_t)sec)
		ticks2 = clock();
}

void GameStartMenu(HWND hWnd, WPARAM wParam, int *charNum, TCHAR* playerID)
{
	if (wParam == VK_BACK && charNum > 0)
	{
		(*charNum)--;
		playerID[*charNum] = NULL;
	}
	else if (*charNum < 8)
	{
		playerID[(*charNum)++] = wParam;
		playerID[*charNum] = NULL;
	}

	if (wParam == VK_RETURN && *charNum > 0)	//게임 진입
	{
		player.SetID(playerID);
		gameState = INGAME;

		//CreateObj();
		for (int i = 0; i < 6; i++)			//블록 생성
		{
			BlockObj *blocks = new BlockObj(40 + (i * 80), 720);
			objects.push_back(blocks);
		}
		/*EnemyObj *enemeis = new EnemyObj(40 + 80, 100);
		objects.push_back(enemeis);*/
		
		SetTimer(hWnd, 1, 70, NULL);		//오브젝트 움직임 타이머
		SetTimer(hWnd, 2, 800, NULL);		//적 생성 타이머
	}
	InvalidateRgn(hWnd, NULL, TRUE);
}
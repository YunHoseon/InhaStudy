#pragma once

#include "resource.h"

enum GameState { START = 100, INGAME, END };	//게임 상태
enum GameState gameState;

extern CObjects *cObject;
extern list<EnemyObj*> enemyList;
extern list<BlockObj*> blockList;
extern list<BulletObj*> bulletList;

PlayerObj playerObj(240, 680);
extern Player player;									//플레이어 정보

//void delay(unsigned int sec)     // 특정 시간(초)만큼 기다리는 함수
//{
//	clock_t ticks1 = clock();
//	clock_t ticks2 = ticks1;
//	while ((ticks2 / CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < (clock_t)sec)
//		ticks2 = clock();
//}

void CreateObjects()
{
	for (int i = 0; i < 6; i++)					//블록 생성
	{
		BlockObj *blocks = new BlockObj(40 + (i * 80), 720);
		blockList.push_back(blocks);
	}
}

void GameStartMenu(HWND hWnd, WPARAM wParam, int *charNum, TCHAR* playerID)
{
	if (wParam == VK_BACK && charNum > 0)
	{
		(*charNum)--;
		playerID[*charNum] = NULL;
	}
	else if (*charNum < 8 && wParam != VK_RETURN)
	{
		playerID[(*charNum)++] = wParam;
		playerID[*charNum] = NULL;
	}

	if (wParam == VK_RETURN && *charNum > 1)	//게임 진입
	{
		player.SetID(playerID);
		gameState = INGAME;
		//gameState = END;

		CreateObjects();
		
		SetTimer(hWnd, 1, 70, NULL);		//오브젝트 움직임 타이머
		SetTimer(hWnd, 2, 1000, NULL);		//적 생성 타이머
	}
	InvalidateRgn(hWnd, NULL, TRUE);
}
#pragma once

#include "resource.h"

enum GameState { START = 100, INGAME, END };	//���� ����
enum GameState gameState;

extern vector<CObjects*> objects;

Player player;					//�÷��̾� ����

void delay(unsigned int sec)     // Ư�� �ð�(��)��ŭ ��ٸ��� �Լ�
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

	if (wParam == VK_RETURN && *charNum > 0)	//���� ����
	{
		player.SetID(playerID);
		gameState = INGAME;

		//CreateObj();
		for (int i = 0; i < 6; i++)			//��� ����
		{
			BlockObj *blocks = new BlockObj(40 + (i * 80), 720);
			objects.push_back(blocks);
		}
		/*EnemyObj *enemeis = new EnemyObj(40 + 80, 100);
		objects.push_back(enemeis);*/
		
		SetTimer(hWnd, 1, 70, NULL);		//������Ʈ ������ Ÿ�̸�
		SetTimer(hWnd, 2, 800, NULL);		//�� ���� Ÿ�̸�
	}
	InvalidateRgn(hWnd, NULL, TRUE);
}
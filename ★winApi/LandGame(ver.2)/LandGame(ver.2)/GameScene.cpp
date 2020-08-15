#include "stdafx.h"
#include "GameScene.h"
#include "Bitmap.h"
#include "Player.h"
#include "Enemy.h"

extern Singleton *singleton;

GameScene::GameScene()
{
	bitmap = new Bitmap;
	player = new Player;
	bitmap->CreateBitmap();
	Enemy enemies[5];
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	mapPoint[0] = { 15, 20 };
	mapPoint[1] = { 765, 20 };
	mapPoint[2] = { 765, 653 };
	mapPoint[3] = { 15, 653 };

	transparentPolygon.push_back({ 100, 60 });
	transparentPolygon.push_back({ 150, 60 });
	transparentPolygon.push_back({ 150, 100 });
	transparentPolygon.push_back({ 100, 100 });
}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	int prevDir = player->dir;
	POINT curPos;

	curPos.x = player->playerPos.x;
	curPos.y = player->playerPos.y;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		player->dir = 1;
		curPos.x -= player->speed;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		player->dir = 2;
		curPos.x += player->speed;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		player->dir = 3;
		curPos.y -= player->speed;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		player->dir = 4;
		curPos.y += player->speed;
	}

	if (isInTpPolyLine(curPos))
	{
		if (player->drawMode == true)
		{
			if (prevDir != player->dir)
				footPrint.push_back(player->playerPos);
			player->drawMode = false;
			footPrint.push_back(curPos);

			int startLineNum = 0;
			int endLineNum = 0;

			isInTpPolyLine(footPrint.front(), &startLineNum);
			isInTpPolyLine(footPrint.back(), &endLineNum);
			
			if (PolygonMakedCompleteCheck() == false)
			{
				vector<POINT> tmpFootprint;

				tmpFootprint = footPrint;
				footPrint = CollectTpPt(startLineNum, endLineNum);

				if (PolygonMakedCompleteCheck() == false)
				{
					footPrint = tmpFootprint;
					reverse(footPrint.begin(), footPrint.end());
					swap(startLineNum, endLineNum);
					footPrint = CollectTpPt(startLineNum, endLineNum);
				}
			}
			transparentPolygon = footPrint;
			footPrint.clear();
		}
		player->playerPos = curPos;
	}
	else if (isInsideOutline(curPos) && isInsidePoly(curPos.x,curPos.y) == false)
	{
		if (player->drawMode == true)
		{
			if (prevDir != player->dir)
			{
				footPrint.push_back(player->playerPos);
			}
			player->playerPos = curPos;
		}
		if (player->drawMode == false)
		{
			if (GetKeyState(VK_SPACE) & 0x8000)
			{
				player->drawMode = true;
				footPrint.push_back(player->playerPos);
				player->playerPos = curPos;
			}
		}
	}
}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	static HBITMAP backHBit = NULL;

	if (backHBit == NULL)
	{
		singleton->backHDC = CreateCompatibleDC(hdc);
		backHBit = CreateCompatibleBitmap(hdc, bitmap->bitBack.bmWidth + 15, bitmap->bitBack.bmHeight + 20);
		SelectObject(singleton->backHDC, backHBit);
	}
	bitmap->DrawBitmap(hWnd, singleton->backHDC);
	DrawBox(hWnd, singleton->backHDC);

	BitBlt(hdc, 15, 20, bitmap->bitBack.bmWidth, bitmap->bitBack.bmHeight, singleton->backHDC, 15, 20, SRCCOPY);

	if (player->drawMode == true)
		DrawFootPrint(hdc);

	player->DrawPlayer(hdc);
}

void GameScene::Free(HWND hWnd)
{
	KillTimer(hWnd, 1);
}

void GameScene::DrawBox(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hBit = NULL, oldBit;
	{
		HBRUSH hBrush, oldBrush;
		hMemDC = CreateCompatibleDC(hdc);

		hBrush = CreateSolidBrush(RGB(220, 245, 215));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		if (hBit == NULL)
			hBit = CreateCompatibleBitmap(hdc, 800, 700);
		oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

		Rectangle(hMemDC, 15, 20, 765, 653);

		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

		Polygon(hMemDC, &(transparentPolygon[0]), transparentPolygon.size());

		TransparentBlt(hdc, 15, 20, 750, 633, hMemDC, 15, 20, 750, 633, RGB(255, 0, 255));

		SelectObject(hMemDC, oldBrush);
		SelectObject(hMemDC, oldBit);

		DeleteObject(oldBit);
		DeleteObject(hBrush);
		DeleteDC(hMemDC);
	}
}

void GameScene::DrawFootPrint(HDC hdc)
{
	MoveToEx(hdc, footPrint[0].x, footPrint[0].y, NULL);

	for (int i = 1; i < footPrint.size(); i++)
	{
		LineTo(hdc, footPrint[i].x, footPrint[i].y);
	}
	LineTo(hdc, player->playerPos.x, player->playerPos.y);
}

bool GameScene::isInTpPolyLine(POINT tmpPt, int * lineNum)
{
	int left, right, top, bottom;
	size_t tpPolySize = transparentPolygon.size();

	for (int i = 0; i < tpPolySize; i++)
	{
		int j = (i + 1) % tpPolySize;
		if (transparentPolygon[i].x < transparentPolygon[j].x)
		{
			left = transparentPolygon[i].x;
			right = transparentPolygon[j].x;
		}
		else
		{
			left = transparentPolygon[j].x;
			right = transparentPolygon[i].x;
		}

		if (transparentPolygon[i].y < transparentPolygon[j].y)
		{
			top = transparentPolygon[i].y;
			bottom = transparentPolygon[j].y;
		}
		else
		{
			top = transparentPolygon[j].y;
			bottom = transparentPolygon[i].y;
		}

		if (tmpPt.x >= left && tmpPt.x <= right &&
			tmpPt.y >= top && tmpPt.y <= bottom)
		{
			if (lineNum != NULL)
				*lineNum = i;
			return true;
		}
	}
	return false;
}

bool GameScene::isInsideOutline(POINT tmpPt)
{
	if (tmpPt.x > mapPoint[0].x && tmpPt.x < mapPoint[2].x &&
		tmpPt.y > mapPoint[0].y && tmpPt.y < mapPoint[2].y)
		return true;
	else
		return false;
	return false;
}

bool GameScene::isInsidePoly(int _x, int _y)
{
	int crosses = 0;

	for (int i = 0; i < transparentPolygon.size(); i++)
	{
		int j = (i + 1) % transparentPolygon.size();
		if (((transparentPolygon)[i].y > _y) != ((transparentPolygon)[j].y > _y))
		{
			double atX = ((transparentPolygon)[j].x - (transparentPolygon)[i].x) * (_y - (transparentPolygon)[i].y) / ((transparentPolygon)[j].y - (transparentPolygon)[i].y) + (transparentPolygon)[i].x;
			if (_x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

bool GameScene::isInsideFootprint(POINT tmpPt)
{
	int crosses = 0;

	for (int i = 0; i < footPrint.size(); i++)
	{
		int j = (i + 1) % footPrint.size();
		if ((footPrint[i].y > tmpPt.y) != (footPrint[j].y > tmpPt.y))
		{
			double atX = (footPrint[j].x - footPrint[i].x) * (tmpPt.y - footPrint[i].y) / (footPrint[j].y - footPrint[i].y) + footPrint[i].x;
			if (tmpPt.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

bool GameScene::isInLineFootprint(POINT tmpPt)
{
	int left, right, top, bottom;
	size_t footPrintSize = footPrint.size();

	for (int i = 0; i < footPrintSize; i++)
	{
		int j = (i + 1) % footPrintSize;
		if (footPrint[i].x < footPrint[j].x)
		{
			left = footPrint[i].x;
			right = footPrint[j].x;
		}
		else
		{
			left = footPrint[j].x;
			right = footPrint[i].x;
		}

		if (footPrint[i].y < footPrint[j].y)
		{
			top = footPrint[i].y;
			bottom = footPrint[j].y;
		}
		else
		{
			top = footPrint[j].y;
			bottom = footPrint[i].y;
		}

		if (tmpPt.x >= left && tmpPt.x <= right &&
			tmpPt.y >= top && tmpPt.y <= bottom)
			return true;
	}
	return false;
}

bool GameScene::PolygonMakedCompleteCheck()
{
	for (int i = 0; i < transparentPolygon.size(); i++)
	{
		if (isInsideFootprint(transparentPolygon[i]) == false && isInLineFootprint(transparentPolygon[i]) == false)
			return false;
	}
	return true;
}

vector<POINT> GameScene::CollectTpPt(int startLineNum, int endLineNum)
{
	int tpSize = transparentPolygon.size();
	int searchPointNum = (endLineNum + 1) % tpSize;

	vector<POINT> MergedPolygon;
	MergedPolygon = footPrint;

	while (searchPointNum != startLineNum)
	{
		MergedPolygon.push_back(transparentPolygon[searchPointNum]);
		searchPointNum += 1;

		if (searchPointNum == tpSize)
		{
			searchPointNum = 0;
		}
	}

	if (transparentPolygon[startLineNum] != footPrint[0])
	{
		MergedPolygon.push_back(transparentPolygon[startLineNum]);
	}
	return MergedPolygon;
}

#include "stdafx.h"
#include "TileMap.h"

#define SPEED 5

extern Singleton *singleton;
extern Player player;
extern Bitmap bitmap;

TileMap::TileMap()
{
	char tmpMap_Town[COL][ROW + 1] =
	{
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "kkkkkkkkkk00kkkkkkkk" },
		{ "kkkk00000000kkkkkkkk" },
		{ "p000000000000000kkkk" },
		{ "p0000000000000000kkk" },
		{ "p00kkk00000000000kkk" },
		{ "kkkkkk0000kkk00kkkkk" },
		{ "kkk00k000kkkk00kkkkk" },
		{ "k00000000000k00kkkkk" },
		{ "kkkkk0000000000kkkkk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
	};
	memcpy(Map_Town, tmpMap_Town, sizeof(tmpMap_Town));

	char tmpMap_Forest[COL][ROW + 1] =
	{
		{ "kkkkkkkkkkkkkkkkkkkk" },
		{ "kkbb0bbbb00kkkkkkkkk" },
		{ "kkbbbbbbb00kkkkkkkkk" },
		{ "k000bbb0kkkkkkkkkkkk" },
		{ "k0kkbbbkkkkkkkkkkkkk" },
		{ "kbkk000kkkk00000000k" },
		{ "kbkkbbb00000000000pk" },
		{ "kbkkbbb00000000000pk" },
		{ "k000bbb00bbb0000kkkk" },
		{ "kkk00b000bbbbbbbkkkk" },
		{ "kkk0000000bbkkkkkkkk" },
		{ "kkkbbbbb000kkkkkkkkk" },
		{ "k0000bbbkkkkkkkkkkkk" },
		{ "kkkkkkkkkkkkkkkkkkkk" },
	};
	memcpy(Map_Forest, tmpMap_Forest, sizeof(tmpMap_Forest));

	gap = 50;

	for (int i = 0; i < COL-6; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			map[i][j].cell = Map_Town[i][j];

			map[i][j].collider.left = j * gap + POSX;
			map[i][j].collider.top = i * gap + POSY;
			map[i][j].collider.right = gap + (j * gap) + POSX;
			map[i][j].collider.bottom = gap + (i * gap) + POSY;

			switch (map[i][j].cell)
			{
			case '0':
				map[i][j].tileState = TileState::ROAD;
				break;
			case '1':
				map[i][j].tileState = TileState::BUSH;
				break;
			case 'k':
				map[i][j].tileState = TileState::BLOCK;
				break;
			case 'p':
				map[i][j].tileState = TileState::POTAL;
				break;

			default:
				break;
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::DrawMap(HDC hdc)	//마을인지 숲인지에 따라 다르게
{
	UpdateMap();

	HBRUSH oldBrush, roadBrush, bushBrush, blockBrush;

	roadBrush = CreateSolidBrush(RGB(240, 240, 240));
	bushBrush = CreateSolidBrush(RGB(110, 215, 110));
	blockBrush = CreateSolidBrush(RGB(60, 60, 75));

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			switch (map[i][j].tileState)
			{
			case TileState::ROAD:
				oldBrush = (HBRUSH)SelectObject(hdc, roadBrush);
				break;

			case TileState::BUSH:
				oldBrush = (HBRUSH)SelectObject(hdc, bushBrush);
				break;

			case TileState::BLOCK:
				oldBrush = (HBRUSH)SelectObject(hdc, blockBrush);
				
				break;
			default:
				break;
			}
			//Rectangle(hdc, map[i][j].collider.left, map[i][j].collider.top, map[i][j].collider.right, map[i][j].collider.bottom);
			SelectObject(hdc, oldBrush);
		}
	}
	DeleteObject(roadBrush);
	DeleteObject(bushBrush);
	DeleteObject(blockBrush);
}

void TileMap::UpdateMap()
{
	RECT intersectRc;
	RECT tmpMapCol;

	static int colliderMoveX = 0, colliderMoveY = 0;
	int tmpMoveX, tmpMoveY;
	tmpMoveX = colliderMoveX;
	tmpMoveY = colliderMoveY;

		if (GetKeyState(VK_LEFT) & 0x8000)
			colliderMoveX += SPEED;
		else if (GetKeyState(VK_RIGHT) & 0x8000)
			colliderMoveX -= SPEED;
		else if (GetKeyState(VK_UP) & 0x8000)
			colliderMoveY += SPEED;
		else if (GetKeyState(VK_DOWN) & 0x8000)
			colliderMoveY -= SPEED;
		else
			return;
	
	for (int i = 0; i < COL - 5; i++)
	{
		for (int j = 0; j < ROW - 1; j++)
		{
			switch (singleton->mapState)
			{
			case 1:
				tmpMapCol.left = j * gap + POSX + colliderMoveX;
				tmpMapCol.top = i * gap + POSY + colliderMoveY;
				tmpMapCol.right = gap + (j * gap) + POSX + colliderMoveX;
				tmpMapCol.bottom = gap + (i * gap) + POSY + colliderMoveY;
				break;

			case 2:
				tmpMapCol.left = j * gap + POSX2 + colliderMoveX;
				tmpMapCol.top = i * gap + POSY2 + colliderMoveY;
				tmpMapCol.right = gap + (j * gap) + POSX2 + colliderMoveX;
				tmpMapCol.bottom = gap + (i * gap) + POSY2 + colliderMoveY;
				break;

			default:
				break;
			}

			switch (singleton->mapState)
			{
			case 1:
				map[i][j].cell = Map_Town[i][j];

				map[i][j].collider.left = j * gap + POSX;
				map[i][j].collider.top = i * gap + POSY;
				map[i][j].collider.right = gap + (j * gap) + POSX;
				map[i][j].collider.bottom = gap + (i * gap) + POSY;
				break;
			case 2:
				map[i][j].cell = Map_Forest[i][j];

				map[i][j].collider.left = j * gap + POSX2;
				map[i][j].collider.top = i * gap + POSY2;
				map[i][j].collider.right = gap + (j * gap) + POSX2;
				map[i][j].collider.bottom = gap + (i * gap) + POSY2;
				break;

			default:
				break;
			}

			switch (map[i][j].cell)
			{
			case '0':
				map[i][j].tileState = TileState::ROAD;
				break;
			case '1':
				map[i][j].tileState = TileState::BUSH;
				break;
			case 'k':
				map[i][j].tileState = TileState::BLOCK;
				break;
			case 'p':
				map[i][j].tileState = TileState::POTAL;
				break;

			default:
				break;
			}

			if (map[i][j].cell == 'k' && IntersectRect(&intersectRc, &tmpMapCol, &player.playerCollider))
			{
				singleton->movable = false;
				colliderMoveX = tmpMoveX;
				colliderMoveY = tmpMoveY;
				return;
			}
			else if (map[i][j].cell == 'b' && IntersectRect(&intersectRc, &tmpMapCol, &player.playerCollider))
			{
				srand((unsigned int)time(NULL));
				int rNum = rand();

				if (rNum % 4 == 0)
					singleton->isBattle = true;
			}
			else if(map[i][j].cell == 'p' && IntersectRect(&intersectRc, &tmpMapCol, &player.playerCollider) && singleton->mapState == 1)	//마을에서 숲
			{
				singleton->mapState = 2;
			}
			else if (map[i][j].cell == 'p' && IntersectRect(&intersectRc, &tmpMapCol, &player.playerCollider) && singleton->mapState == 2)	//숲에서 마을
			{
				singleton->mapState = 1;
			}
		}
	}

	singleton->movable = true;

	if (singleton->movable && singleton->mapState == 1)
	{
		for (int i = 0; i < COL - 5; i++)
		{
			for (int j = 0; j < ROW - 1; j++)
			{
				tmpMapCol.left = j * gap + POSX + colliderMoveX;
				tmpMapCol.top = i * gap + POSY + colliderMoveY;
				tmpMapCol.right = gap + (j * gap) + POSX + colliderMoveX;
				tmpMapCol.bottom = gap + (i * gap) + POSY + colliderMoveY;
				map[i][j].collider = tmpMapCol;
			}
		}
	}
	else if (singleton->movable && singleton->mapState == 2)
	{
		for (int i = 0; i < COL - 5; i++)
		{
			for (int j = 0; j < ROW - 1; j++)
			{
				tmpMapCol.left = j * gap + POSX2 + colliderMoveX;
				tmpMapCol.top = i * gap + POSY2 + colliderMoveY;
				tmpMapCol.right = gap + (j * gap) + POSX2 + colliderMoveX;
				tmpMapCol.bottom = gap + (i * gap) + POSY2 + colliderMoveY;
				map[i][j].collider = tmpMapCol;
			}
		}
	}
	
}

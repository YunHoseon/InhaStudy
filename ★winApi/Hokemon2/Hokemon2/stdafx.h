// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <atlstr.h>
#include <map>

#define POSX	-380
#define POSY	-100

#define POSX2	-1150
#define POSY2	-100

enum class GameState { NONE = 0, LOAD, START, INGAME, BATTLE };
enum class TimerID { TM_RENDER = 0, TM_UPDATE };
enum class TileState { ROAD = 0, BUSH, BLOCK, POTAL };
enum class BattleState { NONE = 0, BATTLE, RUN,  SELECT};
enum MY_TOKEN_TYPE { TOKEN_STRING = 0, TOKEN_NUMBER };	//토큰 종류

struct Hokemon_Data
{
	int hNum;
	TCHAR hName[16];
	int hHp;
	int MaxHp;
	int hAtk;
	int hGrd;
	int hSpd;
	int hNextEvol;
	int hType;
};

struct Skill_Data
{
	int id;
	int accuracy;
	TCHAR sName[32];
	int pp;
	int MaxPp;
	int sDamage;
	int sType;
};

// TODO: reference additional headers your program requires here
#include "Hokemon.h"
#include "Player.h"
#include "TileMap.h"
#include "Singleton.h"
#include "HokemonDB.h"
#include "SceneManager.h"
#include "Bitmap.h"
#include "json/json.h"
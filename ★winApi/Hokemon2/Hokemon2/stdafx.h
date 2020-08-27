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
#include <map>

// TODO: reference additional headers your program requires here
#include "Hokemon.h"
#include "Player.h"
#include "TileMap.h"
#include "Singleton.h"
#include "SceneManager.h"
//#include "Bitmap.h"
#include "json/json.h"

#define POSX	-380
#define POSY	-100

enum class GameState { NONE = 0, LOAD, START, INGAME, BATTLE };
enum class TimerID { TM_RENDER = 0, TM_UPDATE };
enum class TileState { ROAD = 0, BUSH, BLOCK };
enum MY_TOKEN_TYPE { TOKEN_STRING = 0, TOKEN_NUMBER };	//토큰 종류

using namespace std;
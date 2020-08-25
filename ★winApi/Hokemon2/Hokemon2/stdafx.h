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

// TODO: reference additional headers your program requires here
#include "Hokemon.h"
#include "Player.h"
#include "TileMap.h"
#include "Singleton.h"
#include "SceneManager.h"
#include "json/json.h"

enum class GameState { NONE, START, INGAME, BATTLE };
enum class TimerID { TM_START = 50, TM_INGAME, TM_BATTLE };
enum class TileState { ROAD = 100, BUSH, BLOCK };
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment (lib, "Msimg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>

// TODO: reference additional headers your program requires here
#include "Singleton.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace std;

enum class GameState { NONE, START, INGAME, END };
enum class TimerID { TM_START = 100, TM_INGAME, TM_END };

inline bool operator != (POINT pt1, POINT pt2)
{
	if (pt1.x != pt2.x || pt1.y != pt2.y)
		return true;
	return false;
}
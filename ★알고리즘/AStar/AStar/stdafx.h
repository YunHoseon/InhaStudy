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
#include <vector>

// TODO: reference additional headers your program requires here
#include "Map.h"
using namespace std;
extern Map map;

enum class CellState { NONE = 100, BLOCK, START, END, SEARCHED, ROAD };

const int WAYS = 8;
const int Ways[8][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };

static POINT mousePt;
static bool setStart = false;
static POINT startNend[2];

void AStar(POINT _startNend[]);
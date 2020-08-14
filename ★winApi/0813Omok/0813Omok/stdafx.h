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
#include <string>
#include <vector>


// TODO: reference additional headers your program requires here
#include "Bitmap.h"
#include "Map.h"

#define WHITESTONE 10
#define BLACKSTONE 11

using namespace std;

typedef struct Player_Chat
{
	char ID[16];
	char msg[256];
}Player_Chat;

typedef struct Player_Stone
{
	char ID[16];
	int px, py;
	int myStoneColor;
	bool isWin;
	bool isMyTurn;
}Player_Stone;
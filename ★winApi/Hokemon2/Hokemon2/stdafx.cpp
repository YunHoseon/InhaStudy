// stdafx.cpp : source file that includes just the standard includes
// Hokemon2.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "SoundManager.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
Singleton *singleton = Singleton::GetInstance();
HokemonDB *hokemonDB;
Player player;
TileMap tileMap;
Bitmap bitmap;
SoundManager* g_theSoundManager;
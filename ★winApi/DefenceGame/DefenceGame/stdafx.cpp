// stdafx.cpp : source file that includes just the standard includes
// DefenceGame.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

CObjects *cObject;

list<EnemyObj*> enemyList;		//오브젝트 컨테이너
list<BlockObj*> blockList;
list<BulletObj*> bulletList;

Player player;
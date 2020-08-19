#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <io.h>

#include "Player.h"
#include "Monster.h"
#include "Bulbasaur.h"
#include "Squirtle.h"
#include "Charmander.h"
#include "Rattata.h"
#include "Snorlax.h"

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15

void PrintMenu();
void CursorView(char show);
void PlayerMove(int pX, int pY);
void PrintMenu();
void InputPlayerName();
void SelectStartMonster();
void Ingame();
void MenuSelect();
void textcolor(int foreground, int background);
void BattleWild();
void mySkillFunc(int nInput, char* RattataName, int RattataGrd, Monster* enemy);
void eSkillFunc(int rNum, char* RattataSName1, char* RattataSName2, int RattataSDamage, int RattataAtk);
int myCalDamage(int RattataGrd);
int eCalDamage(int RattataSDamage, int RattataAtk);
void LevelUp();
void MyMonsterBox();
void IngameMenu();
void SaveData();
void LoadData();
void RecoveryPokemon();

bool contactWildMonster = false;	//전투 조건 만족시 true

int expPool = 30;	//레벨당 경험치 최대치
int wUpLevel = 0;
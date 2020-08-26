#pragma once
#include "Scene.h"

#define TOKEN_COUNT 200    // 토큰의 최대 개수

enum MY_TOKEN_TYPE;

// 토큰 구조체
struct MY_TOKEN 
{
	MY_TOKEN_TYPE type; // 토큰 종류
	union {             // 두 종류 중 한 종류만 저장할 것이므로 공용체로 만듦
		char *string;   // 문자열 포인터
		double number;  // 실수형 숫자
	};
	bool isArray;       // 현재 토큰이 배열인지 표시
};

// JSON 구조체
struct JSON
{
	MY_TOKEN tokens[TOKEN_COUNT];    // 토큰 배열
};

struct Hokemon_Data
{
	int hNum;
	char hName[16];
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
	char sName[32];
	int pp;
	int MaxPp;
	int sDamage;
	int sType;
};

class LoadScene :
	public Scene
{
public:
	bool noneFile;
	map<int, Hokemon_Data> map_Hokemons;
	map<int, Skill_Data> map_Skills;

	LoadScene();
	~LoadScene();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);

	char* ReadFile(char* fileName, int* readSize);
	void ParseJSON(char* doc, int size, JSON* json);
	void HokemonSaveData(JSON json);
	void SkillSaveData(JSON json);
	void FreeJSON(JSON* json);
};


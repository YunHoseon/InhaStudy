#pragma once
#include "Scene.h"

#define TOKEN_COUNT 200    // ��ū�� �ִ� ����

enum MY_TOKEN_TYPE;

// ��ū ����ü
struct MY_TOKEN 
{
	MY_TOKEN_TYPE type; // ��ū ����
	union {             // �� ���� �� �� ������ ������ ���̹Ƿ� ����ü�� ����
		char *string;   // ���ڿ� ������
		double number;  // �Ǽ��� ����
	};
	bool isArray;       // ���� ��ū�� �迭���� ǥ��
};

// JSON ����ü
struct JSON
{
	MY_TOKEN tokens[TOKEN_COUNT];    // ��ū �迭
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


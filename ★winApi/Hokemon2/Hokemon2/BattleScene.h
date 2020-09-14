#pragma once
#include "Scene.h"

enum class BattleState;

class BattleScene :
	public Scene
{
	RECT ScriptBar;
	RECT background_under;
	RECT Btn_battle;
	RECT Btn_run;
	RECT Btn_back;
	RECT Btn_skills[4];
public:
	BattleState battleState;

	HBITMAP hBackImage;
	HBITMAP battleUI;

	BITMAP bitBack;

	Hokemon *wildMonster;
	Skill_Data *selectedSkill;
	bool isMyTurn;

	BattleScene();
	~BattleScene();

	Hokemon *SpawnWildMonster();
	void TurnBattle();

	void mySkillFunc();
	void eSkillFunc();
	int myCalDamage();
	int eCalDamage();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(HWND hWnd);
};


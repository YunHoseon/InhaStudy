#include "stdafx.h"
#include "BattleScene.h"

extern Singleton *singleton;
extern HokemonDB *hokemonDB;
extern Player player;

BattleScene::BattleScene()
{
	battleState = BattleState::NONE;
	ScriptBar = { 125, 190, 464, 240 };
	background_under = {125, 250, 464, 410};
	Btn_battle = {194, 260, 394, 380};
	Btn_run = {235, 383, 355, 410};
	Btn_back = { 235, 383, 355, 410 };

	Btn_skills[0] = {130, 260, 290, 310};
	Btn_skills[1] = { 300, 260, 460, 310 };

	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\ui\\BattleBackground__.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	/*battleUI = (HBITMAP)LoadImage(NULL, TEXT("images\\ui\\BattleBackground__.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);*/

	wildMonster = SpawnWildMonster();
}

BattleScene::~BattleScene()
{
}

Hokemon BattleScene::SpawnWildMonster()
{
	Hokemon *sentret = new Hokemon;
	sentret->SetData(hokemonDB->map_Hokemons.find(161)->second);
	sentret->SetmLevel(3);
	sentret->SetskillData(hokemonDB->map_Skills.find(8)->second, 0);
	sentret->SetskillData(hokemonDB->map_Skills.find(11)->second, 1);
	return *sentret;
}

void BattleScene::TurnBattle()
{
	srand((unsigned int)time(NULL));
	wildMonster = SpawnWildMonster();
						
	int saveAtk = player.GetMyMonster(0)->GetData().hAtk;	//원래 능력치 저장
	int saveGrd = player.GetMyMonster(0)->GetData().hGrd;

	if (wildMonster.GetData().hSpd > player.GetMyMonster(0)->GetData().hSpd)	//스피드 비교
		isMyTurn = false;
	else if (wildMonster.GetData().hSpd < player.GetMyMonster(0)->GetData().hSpd)
		isMyTurn = true;
	else
		isMyTurn = rand() % 2;

	if (isMyTurn == true)
	{
		mySkillFunc();

		if (player.GetMyMonster(0)->GetData().hHp <= 0)
		{
			player.GetMyMonster(0)->SetmAtk(saveAtk);
			player.GetMyMonster(0)->SetmGrd(saveGrd);
			player.GetMyMonster(0)->SetmExp(player.GetMyMonster(0)->GetmExp() + 10);

			singleton->isBattle = false;
			battleState = BattleState::NONE;
			singleton->sceneManager->SceneChange(GameState::INGAME);
		}
		eSkillFunc();
	}
	else if (isMyTurn == false)
	{
		eSkillFunc();
		if (player.GetMyMonster(0)->GetData().hHp <= 0)
		{
			player.GetMyMonster(0)->SetmAtk(saveAtk);
			player.GetMyMonster(0)->SetmGrd(saveGrd);
			player.GetMyMonster(0)->SetmExp(player.GetMyMonster(0)->GetmExp() + 10);

			singleton->isBattle = false;
			battleState = BattleState::NONE;
			singleton->sceneManager->SceneChange(GameState::INGAME);
		}
		mySkillFunc();
	}

	battleState = BattleState::SELECT;
}

void BattleScene::Init()
{
}

void BattleScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	static int mx, my;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (mx > Btn_battle.left && mx < Btn_battle.right &&		//싸운다
			my > Btn_battle.top && my < Btn_battle.bottom && battleState == BattleState::NONE)
		{
			battleState = BattleState::SELECT;
		}
		else if (battleState == BattleState::SELECT)
		{
			if (mx > Btn_back.left && mx < Btn_back.right &&		//돌아가기
				my > Btn_back.top && my < Btn_back.bottom)
			{
				battleState = BattleState::NONE;
			}
			else if (mx > Btn_skills[0].left && mx < Btn_skills[0].right &&	//스킬0
				my > Btn_skills[0].top && my < Btn_skills[0].bottom)
			{
				selectedSkill = player.GetMyMonster(0)->GetskillData(0);
				battleState = BattleState::BATTLE;
			}
			else if (mx > Btn_skills[1].left && mx < Btn_skills[1].right &&	//스킬1
				my > Btn_skills[1].top && my < Btn_skills[1].bottom)
			{
				selectedSkill = player.GetMyMonster(0)->GetskillData(1);
				battleState = BattleState::BATTLE;
			}
		}
		else if (mx > Btn_run.left && mx < Btn_run.right &&			//도망간다
			my > Btn_run.top && my < Btn_run.bottom && battleState == BattleState::NONE)
		{
			battleState = BattleState::RUN;
		}
		break;

	default:
		break;
	}

	switch (battleState)
	{
	case BattleState::NONE:
		break;
	case BattleState::SELECT:
		//스킬 선택
		break;
	case BattleState::BATTLE:
		TurnBattle();
		battleState = BattleState::NONE;
		break;
	case BattleState::RUN:
		singleton->isBattle = false;
		battleState = BattleState::NONE;
		singleton->sceneManager->SceneChange(GameState::INGAME);
		break;
	default:
		break;
	}
}

void BattleScene::mySkillFunc()
{
	switch (selectedSkill->id)
	{
	case 1:	//몸통박치기
		wildMonster.SetmHp(wildMonster.GetmHp() - myCalDamage());
		if (wildMonster.GetmHp() < 0)
			wildMonster.SetmHp(0);
		break;
	case 2:	//울음소리
		wildMonster.SetmAtk(wildMonster.GetmAtk() - 1);
		if (wildMonster.GetmAtk() < 0)
			wildMonster.SetmAtk(0);
		break;
	case 5:	//째려보기
		wildMonster.SetmGrd(wildMonster.GetmGrd() - 1);
		if (wildMonster.GetmGrd() < 0)
			wildMonster.SetmGrd(0);
		break;
	case 8:	//할퀴기
		wildMonster.SetmHp(wildMonster.GetmHp() - myCalDamage());
		if (wildMonster.GetmHp() < 0)
			wildMonster.SetmHp(0);
		break;
	}
}

void BattleScene::eSkillFunc()
{
	int rNum = rNum % 2;

	switch (rNum)
	{
	case 0:	//할퀴기
		player.GetMyMonster(0)->SetmHp(player.GetMyMonster(0)->GetmHp() - eCalDamage());
		if (player.GetMyMonster(0)->GetmHp() <= 0)
			player.GetMyMonster(0)->SetmHp(0);
		break;
	case 1:	//꿰뚫어보기
		break;
	}
}

int BattleScene::myCalDamage()	//상대 포켓몬에게 줄 데미지
{
	int accuracy = rand() % 100;
	int finalDamage = 0;

	if (accuracy < player.GetMyMonster(0)->GetskillData(0)->accuracy)
	{
		finalDamage = (player.GetMyMonster(0)->GetskillData(0)->sDamage + player.GetMyMonster(0)->GetmAtk()) - (wildMonster.GetmGrd() * 2);

		if (finalDamage <= 0)
			finalDamage = 1;

		return finalDamage;
	}
	else
		return 0;
}

int BattleScene::eCalDamage()
{
	int accuracy = rand() % 100;
	int finalDamage = 0;

	if (accuracy < wildMonster.GetskillData(0)->accuracy)
	{
		finalDamage = ((wildMonster.GetskillData(0)->sDamage / 10) + wildMonster.GetmAtk()) - (player.GetMyMonster(0)->GetmGrd() * 2);

		if (finalDamage <= 0)
			finalDamage = 1;

		return finalDamage;
	}
	else
		return 0;
}

void BattleScene::Render(HWND hWnd, HDC hdc)
{
	Rectangle(hdc, background_under.left, background_under.top, background_under.right, background_under.bottom);
	switch (battleState)
	{
	case BattleState::NONE:
		Rectangle(hdc, Btn_battle.left, Btn_battle.top, Btn_battle.right, Btn_battle.bottom);
		DrawText(hdc, _T("싸운다"), _tcslen(_T("싸운다")), &Btn_battle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rectangle(hdc, Btn_run.left, Btn_run.top, Btn_run.right, Btn_run.bottom);
		DrawText(hdc, _T("도망간다"), _tcslen(_T("도망간다")), &Btn_run, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;
	case BattleState::SELECT:
	{
		Rectangle(hdc, Btn_skills[0].left, Btn_skills[0].top, Btn_skills[0].right, Btn_skills[0].bottom);
		DrawText(hdc, player.GetMyMonster(0)->GetskillData(0)->sName, -1, &Btn_skills[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		Rectangle(hdc, Btn_skills[1].left, Btn_skills[1].top, Btn_skills[1].right, Btn_skills[1].bottom);
		DrawText(hdc, player.GetMyMonster(0)->GetskillData(1)->sName, -1, &Btn_skills[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		Rectangle(hdc, Btn_back.left, Btn_back.top, Btn_back.right, Btn_back.bottom);
		DrawText(hdc, _T("돌아가기"), _tcslen(_T("돌아가기")), &Btn_back, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
		break;
	case BattleState::BATTLE:
		break;
	case BattleState::RUN:
		break;
	default:
		break;
	}
	
	HDC hMemDC;
	HBITMAP hOldBitmap;
	BITMAP tmpBitmap;
	int bx, by;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
	GetObject(hBackImage, sizeof(BITMAP), &tmpBitmap);
	bx = tmpBitmap.bmWidth;
	by = tmpBitmap.bmHeight;
	BitBlt(hdc, 125, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

	/*SelectObject(hMemDC, battleUI);
	GetObject(battleUI, sizeof(BITMAP), &tmpBitmap);
	bx = tmpBitmap.bmWidth;
	by = tmpBitmap.bmHeight;
	BitBlt(hdc, 125, 260, bx, by, hMemDC, 0, 0, SRCCOPY);*/

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	//Rectangle(hdc, ScriptBar.left, ScriptBar.top, ScriptBar.right, ScriptBar.bottom);
}

void BattleScene::Free(HWND hWnd)
{
}

#include "main.h"

class Player Player;

int getEx = 0;	//받은 총 경험치(지금은 30씩 오름)

typedef struct PLAYERDATA
{
	char pName[32];
	int pX;
	int pY;

	int pMonsterLevel;
	int pMonsterHp;
	int pMonsterAtk;
	int pMonsterGrd;
	int pMonsterSpd;
	int pMonsterExp;

	int pMonsterPp[4];

	Monster pMonster[6];
};

/* 길 : 0  벽 : 1  풀숲 : w  땅 : t*/
char map[30][90] = {
	{ "11111111111111111111111111111111111111100000000001111111111111111111111111111111111111111" },
	{ "111tttttttttttttttttttttttttttttttttttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt0000000000ttttttttttttttt.^.tttttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttttttttttttt/-----\\tttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttttttttttt/---------\\tttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt0000000000ttttttttt/-------------\\tttttttttttt1111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt0000000000ttttttttt|     ____    |tttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttttttttt|     |  |    |tttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttttttttt|     |  |    |tttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt0000000000ttttttttt|------hh-----|tttttttttttt1111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt000000000000000000000000000000000000000000000t1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt00000000000000000000000000000000000000000000001111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt00000000000000000000000000000000000000000000001111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt000000000000000000000000000000000000000000000t1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt0000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttttt----------------------ttttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000tttt/                      \\tttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt0000000000ttt/------------------------\\ttttttt1111" },
	{ "111tttttttttttttttttttttwwwwwtwwwwwtttt0000000000ttt|                        |ttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttt|                        |ttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtwwwwwtwwwwwtttt0000000000ttt|                        |ttttttt1111" },
	{ "111tttwwwwwtwwwwwtwwwwwtttttttttttttttt0000000000ttt|                        |ttttttt1111" },
	{ "1111111111111111111111111111111111111110000000000ttt|------------------------|ttttttt1111" },
	{ "1111111111111111111111111111111111111110000000000tttttttttttttttttttttttttttttttttttt1111" },
	{ "11111111111111111111111111111111111111100000000001111111111111111111111111111111111111111" },
	{ "11111111111111111111111111111111111111100000000001111111111111111111111111111111111111111" }
};

void PrintMap()
{
	int i = 0, j = 0;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 90; j++)
		{
			char tmp = map[i][j];

			if (tmp == '0' || tmp == 'h')
				printf(" ");
			else if (tmp == '1')
			{
				textcolor(DARKGRAY, DARKGRAY);
				printf("$");
				textcolor(LIGHTGRAY, BLACK);
			}

			else if (tmp == 'w')
			{
				textcolor(GREEN, BLACK);
				printf("W");
				textcolor(LIGHTGRAY, BLACK);
			}
			else if (tmp == 't')
			{
				textcolor(BROWN, BLACK);
				printf("*");
				textcolor(LIGHTGRAY, BLACK);
			}
			else
				printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	system("mode con cols=90 lines=32 | title Hokemon");	//콘솔창크기 조절
	CursorView(0);
	PrintMenu();
	MenuSelect();
	return 0;
}

void CursorView(char show)	//커서 숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void PlayerMove(int pX, int pY)
{
	int currentX = Player.GetpX();
	int currentY = Player.GetpY();
	gotoxy(currentX, currentY);
	Player.SetpX(currentX);
	Player.SetpY(currentY);
	printf("&");

	int i = 0, j = 0;

	while (1)
	{
		if (_kbhit())
		{
			int pressedKey = _getch();

			if (pressedKey == 'q')
			{
				IngameMenu();
			}

			if (pressedKey == 224 || pressedKey == 0)
			{
				pressedKey = _getch();
				int tmpX = currentX;
				int tmpY = currentY;

				switch (pressedKey)
				{
				case 72:	// 위로 이동
					if (map[currentY - 1][currentX] != '1' && map[currentY - 1][currentX] != '|' && map[currentY - 1][currentX] != '/' && map[currentY - 1][currentX] != '-')
					{
						currentY -= 1;
						if (currentY < 0) { currentY = 0; }
					}
					break;
				case 80:	// 아래로 이동
					if (map[currentY + 1][currentX] != '1' && map[currentY + 1][currentX] != '|' && map[currentY + 1][currentX] != '/'&& map[currentY + 1][currentX] != '-')
					{
						currentY += 1;
						if (currentY > 29) { currentY = 29; }
					}
					break;
				case 75:	// 왼쪽으로 이동
					if (map[currentY][currentX - 1] != '1' && map[currentY][currentX - 1] != '|' && map[currentY][currentX - 1] != '/' && map[currentY][currentX - 1] != '-')
					{
						currentX -= 1;
						if (currentX < 0) { currentX = 0; }
					}
					break;
				case 77:	// 오른쪽으로 이동
					if (map[currentY][currentX + 1] != '1' && map[currentY][currentX + 1] != '|' && map[currentY][currentX + 1] != '/' && map[currentY][currentX + 1] != '-')
					{
						currentX += 1;
						if (currentX > 88) { currentX = 88; }
					}
					break;
				}
				Player.SetpX(currentX);
				Player.SetpY(currentY);

				gotoxy(tmpX, tmpY);

				if (map[tmpY][tmpX] == '0' || map[tmpY][tmpX] == 'h')
					printf(" ");
				else if (map[tmpY][tmpX] == 't')
				{
					textcolor(BROWN, BLACK);
					printf("*");
					textcolor(LIGHTGRAY, BLACK);
				}

				else if (map[tmpY][tmpX] == 'w')
				{
					textcolor(GREEN, BLACK);
					printf("W");
					textcolor(LIGHTGRAY, BLACK);
				}


				gotoxy(currentX, currentY);
				printf("&");

				if (map[currentY][currentX] == 'w')		//풀밭을 밟으면 일정확률로 배틀
				{
					srand((unsigned int)time(NULL));
					int rNum = rand();

					if (rNum % 4 == 0)
					{
						contactWildMonster = true;
						break;
					}
				}
				if (map[currentY][currentX] == 'h')
				{
					RecoveryPokemon();
				}
			}
		}
	}
}

void PrintMenu()
{
	printf("\t _______  _______  ___   _  _______  __   __  _______  __    _ \n");
	printf("\t|       ||       ||   | | ||       ||  |_|  ||       ||  |  | |\n");
	printf("\t|    _  ||   _   ||   |_| ||    ___||       ||   _   ||   |_| |\n");
	printf("\t|   |_| ||  | |  ||      _||   |___ |       ||  | |  ||       |\n");
	printf("\t|    ___||  |_|  ||     |_ |    ___||       ||  |_|  ||  _    |\n");
	printf("\t|   |    |       ||    _  ||   |___ | ||_|| ||       || | |   |\n");
	printf("\t|___|    |_______||___| |_||_______||_|   |_||_______||_|  |__|\n");

	printf("\n\n\n");

	printf("\t\t\t\t 1. 새로하기\n\n");
	printf("\t\t\t\t 2. 이어하기\n\n");
	printf("\t\t\t\t 3. 게임종료\n\n");
}

void InputPlayerName()
{
	char pName[16] = { NULL };
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t 이름을 입력해주세요 : ");
	scanf_s("%s", pName, sizeof(pName));

	Player.SetpName(pName);
}

void SelectStartMonster()
{
	int nInput = 0;
	printf("\n");
	printf("\t\t\t\t스타팅 포켓몬을 선택하세요.");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t     1.이상해씨  2.파이리  3.꼬부기\n");
	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:
	{
		Monster *myBulbasaur = new Bulbasaur();
		Player.SetmyMonster(myBulbasaur, 0);
		printf("\t\t\t\t%s가 동료가 되었다!\n", myBulbasaur->GetmName());
		break;
	}
	case 2:
	{
		Monster *myCharmander = new Charmander();
		Player.SetmyMonster(myCharmander, 0);
		printf("\t\t\t\t%s가 동료가 되었다!\n", myCharmander->GetmName());
		break;
	}
	case 3:
	{
		Monster *mySquirtle = new Squirtle();
		Player.SetmyMonster(mySquirtle, 0);
		printf("\t\t\t\t%s가 동료가 되었다!\n", mySquirtle->GetmName());
		break;
	}
	}
}

void Ingame()
{
	PrintMap();
	printf("~~ 태초마을 ~~\n");
	PlayerMove(Player.GetpX(),Player.GetpY());
	BattleWild();
}

void MenuSelect()
{
	int nInput = 0;
	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:		//새로하기
		system("cls");
		InputPlayerName();
		system("cls");
		SelectStartMonster();
		Sleep(2000);
		system("cls");
		Ingame();
		break;
	case 2:		//이어하기
		system("cls");
		LoadData();
		Ingame();
		break;
	case 3:		//게임종료
		exit(0);
		break;

	default:
		printf("다른 숫자를 입력해주세요.\n");
		break;
	}
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void BattleWild()
{

	if (!contactWildMonster)
		return;

	srand((unsigned int)time(NULL));
	int randMon = rand() % 10;
	Monster* enemy;

	if (randMon > 1)
		enemy = new Rattata();
	else
		enemy = new Snorlax();

	int nInput = 0, nInput2 = 0;
	int myTurn = -1;
	int mPp[4] = { 0 };
	int localPp[4] = { 0 };

	int saveHp = Player.GetmyMonster(0)->GetmHp();
	int saveAtk = Player.GetmyMonster(0)->GetmAtk();
	int saveGrd = Player.GetmyMonster(0)->GetmGrd();

	for (int i = 0; i < 4; i++)
	{
		mPp[i] = Player.GetmyMonster(0)->Getpp(i);
		localPp[i] = mPp[i];
	}
		
	system("cls");
	printf("\t야생의 %s이(가) 나타났다!\n", enemy->GetmName());
	Sleep(1000);
	printf("\t가라! %s!\n", Player.GetmyMonster(0)->GetmName());
	Sleep(1000);

	if (enemy->GetmSpd() < Player.GetmyMonster(0)->GetmSpd())			//자신 턴먼저
		myTurn = 0;
	else if (enemy->GetmSpd() > Player.GetmyMonster(0)->GetmSpd())	//상대 턴먼저
		myTurn = 1;

	while (1)
	{
		system("cls");
		int rNum = rand();
		int eSkillNum = rand();
		int eSkill = eSkillNum % 2;
		if (enemy->GetmSpd() == Player.GetmyMonster(0)->GetmSpd())	//랜덤
			myTurn = rNum % 2;

		printf("\n\t\t\t\tLv.%d %s    Hp : %d/%d\n", enemy->GetmLevel(), enemy->GetmName(), enemy->GetmHp(),enemy->GetMaxHp());
		printf("\n\tLv.%d %s    Hp : %d/%d\n\n", Player.GetmyMonster(0)->GetmLevel() ,Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetmHp(), Player.GetmyMonster(0)->GetMaxHp());
		
		printf("\t무엇을 할까?\n");
		printf("\t1. 싸운다   2.잡는다\n\n");
		scanf_s("%d", &nInput2);

		if (nInput2 == 1)
		{
			for (int i = 0; i < 4; i++)		//포켓몬 스킬 출력
			{
				if (strlen(Player.GetmyMonster(0)->GetsName(i)) > 0)
					printf("\t%d.%s - %d/%d", i + 1, Player.GetmyMonster(0)->GetsName(i), localPp[i], Player.GetmyMonster(0)->GetMaxPp(i));
				printf("\n");
			}
			scanf_s("%d", &nInput);

			if (myTurn == 0)
			{
				Player.GetmyMonster(0)->Setpp(localPp[nInput - 1] -= 1, 0);
				printf("\t%s의 %s!\n", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetsName(nInput - 1));
				mySkillFunc(nInput, enemy->GetmName(), enemy->GetmGrd(),enemy);
				myTurn = 1;

				Sleep(1000);

				if (enemy->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);	//전투 후 hp를 제외한 능력치는 초기화
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s은 쓰러졌다!\n", enemy->GetmName());
					Sleep(1000);
					getEx += 5;
					printf("\t%s는 %d 경험치를 얻었다!\n", Player.GetmyMonster(0)->GetmName(), 30);
					Sleep(2000);
					LevelUp();
					saveHp += 1;
					break;
				}

				printf("\t%s의 %s!\n", enemy->GetmName(), enemy->GetsName(eSkill));
				eSkillFunc(eSkill, enemy->GetsName(0), enemy->GetsName(1), enemy->GetsDamage(0), enemy->GetmAtk());
				Sleep(1000);
				myTurn = 0;

				if (Player.GetmyMonster(0)->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s은 쓰러졌다!\n", Player.GetmyMonster(0)->GetmName());
					Sleep(1000);
					printf("\t%s는 눈앞이 캄캄해졌다!\n", Player.GetpName());
					Sleep(2000);
					Player.GetmyMonster(0)->SetmHp(1);
					break;
				}
			}
			else
			{
				printf("\t%s의 %s!\n", enemy->GetmName(), enemy->GetsName(eSkill));
				eSkillFunc(eSkill, enemy->GetsName(0), enemy->GetsName(1),enemy->GetsDamage(0),enemy->GetmAtk());
				Sleep(1000);
				myTurn = 0;

				if (Player.GetmyMonster(0)->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s은 쓰러졌다!\n", Player.GetmyMonster(0)->GetmName());
					Sleep(1000);
					printf("\t%s는 눈앞이 캄캄해졌다!\n", Player.GetpName());
					Sleep(2000);
					Player.GetmyMonster(0)->SetmHp(1);
					break;
				}

				Player.GetmyMonster(0)->Setpp(localPp[nInput - 1] -= 1, 0);
				printf("\t%s의 %s!\n", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetsName(nInput - 1));
				mySkillFunc(nInput,enemy->GetmName(), enemy->GetmGrd(),enemy);
				myTurn = 1;

				Sleep(1000);
			}
		}
		else if (nInput2 == 2)
		{
			int gotcha = rand();
			int gotchaNum = 0;

			printf("\t가라! 몬스터볼!\n");
			Sleep(1000);
			printf("\t3.."); Sleep(1000); printf("2.."); Sleep(1000); printf("1..\n"); Sleep(1000);

			if (gotcha % 7 == 0)
			{
				printf("\t%s이 몬스터볼에서 나왔다!\n", enemy->GetmName());
				Sleep(1000);
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (strlen(Player.GetmyMonster(i)->GetsName(i)) <= 0)
					{
						gotchaNum = i;
						break;
					}
				}

				Player.SetmyMonster(enemy, gotchaNum);

				printf("\t%s을 잡았다!\n", enemy->GetmName());
				Sleep(2000);
				break;
			}
		}
	}
	contactWildMonster = false;
	Ingame();
}

void mySkillFunc(int nInput, char* RattataName, int RattataGrd, Monster* enemy)
{
	if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "몸통박치기") == 0 || strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "할퀴기") == 0)
	{
		enemy->SetmHp(enemy->GetmHp() - myCalDamage(RattataGrd));
		if (enemy->GetmHp() < 0)
			enemy->SetmHp(0);
		printf("\t%s은 %d의 데미지를 입었다!\n", RattataName, myCalDamage(RattataGrd));
		Sleep(1000);
	}
	else if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "울음소리") == 0)
	{
		enemy->SetmAtk(enemy->GetmAtk() - 1);
		if (enemy->GetmAtk() < 0)
		{
			enemy->SetmAtk(0);
			printf("\t%s의 공격은 더이상 줄지않는다!\n", RattataName);
		}
		else
			printf("\t%s의 공격이 %d 떨어졌다!\n", RattataName, 1);
	}
	else if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "꼬리흔들기") == 0)
	{
		enemy->SetmGrd(enemy->GetmGrd() - 1);
		if (enemy->GetmGrd() < 0)
		{
			enemy->SetmGrd(0);
			printf("\t%s의 방어는 더이상 줄지않는다!\n", RattataName);
		}
		else
			printf("\t%s의 방어가 %d 떨어졌다!\n", RattataName, 1);
	}
}

void eSkillFunc(int rNum, char* RattataSName1, char* RattataSName2, int RattataSDamage, int RattataAtk)
{
	rNum = rNum % 2;

	if (strcmp(RattataSName1, "몸통박치기") == 0)
	{
		Player.GetmyMonster(0)->SetmHp(Player.GetmyMonster(0)->GetmHp() - eCalDamage(RattataSDamage, RattataAtk));
		if (Player.GetmyMonster(0)->GetmHp() <= 0)
			Player.GetmyMonster(0)->SetmHp(0);
		printf("\t%s은 %d의 데미지를 입었다!\n", Player.GetmyMonster(0)->GetmName(), eCalDamage(RattataSDamage, RattataAtk));
		Sleep(1000);
	}
	else if (strcmp(RattataSName2, "꼬리흔들기") == 0)
	{
		Player.GetmyMonster(0)->SetmGrd(Player.GetmyMonster(0)->GetmGrd() - 1);
		if (Player.GetmyMonster(0)->GetmGrd() <= 0)
		{
			Player.GetmyMonster(0)->SetmGrd(0);
			printf("\t%s의 방어는 더이상 줄지않는다!\n", Player.GetmyMonster(0)->GetmName());
		}
		else
			printf("\t%s의 방어가 %d 떨어졌다!\n", Player.GetmyMonster(0)->GetmName(), 1);
		Sleep(1000);
	}
	else if (strcmp(RattataSName2, "울음소리") == 0)
	{
		Player.GetmyMonster(0)->SetmAtk(Player.GetmyMonster(0)->GetmAtk() - 1);
		if (Player.GetmyMonster(0)->GetmAtk() <= 0)
		{
			Player.GetmyMonster(0)->SetmAtk(0);
			printf("\t%s의 공격은 더이상 줄지않는다!\n", Player.GetmyMonster(0)->GetmName());
		}
		else
			printf("\t%s의 공격이 %d 떨어졌다!\n", Player.GetmyMonster(0)->GetmName(), 1);
		Sleep(1000);
	}
}

int myCalDamage(int RattataGrd)	//상대 포켓몬에게 줄 데미지
{
	int finalDamage = 0;

	finalDamage = (Player.GetmyMonster(0)->GetsDamage(0) + Player.GetmyMonster(0)->GetmAtk()) - (RattataGrd * 2);

	if (finalDamage <= 0)
		finalDamage = 1;

	return finalDamage;
}

int eCalDamage(int RattataSDamage,int RattataAtk)
{
	int finalDamage = 0;

	finalDamage = (RattataSDamage + RattataAtk) - (Player.GetmyMonster(0)->GetmGrd() * 2);

	if (finalDamage <= 0)
		finalDamage = 1;

	return finalDamage;
}

void LevelUp()
{
	int upLevel = 0;	//최종적으로 오를 레벨
	int myMonsterLevel = Player.GetmyMonster(0)->GetmLevel();
	int myMonsterExp = Player.GetmyMonster(0)->GetmExp();
	
	for (int i = 0; i < (getEx / expPool); i++)
	{
		getEx -= expPool;
		expPool += 5;
		upLevel += 1;	
	}

	if (upLevel != 0)
	{
		Player.GetmyMonster(0)->SetmLevel(myMonsterLevel + upLevel);
		Player.GetmyMonster(0)->StatusUp();
		printf("\t%s는 %d레벨이 되었다!", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetmLevel());
		Sleep(1500);
	}
}

void MyMonsterBox()
{
	system("cls");

	 //포켓몬 순서 바꿀수있게(0번쨰와 n번째)

	for (int i = 0; i < 6; i++)
	{
		if (strlen(Player.GetmyMonster(i)->GetmName()) > 0)
		{
			printf("\tLv.%d   %s (%d/%d)\n\n", Player.GetmyMonster(i)->GetmLevel(), Player.GetmyMonster(i)->GetmName(), Player.GetmyMonster(i)->GetmHp(), Player.GetmyMonster(i)->GetMaxHp());
			printf("\t공격 : %d", Player.GetmyMonster(i)->GetmAtk());		printf("\t\t%s - %d/%d\n", Player.GetmyMonster(i)->GetsName(0), Player.GetmyMonster(i)->Getpp(0), Player.GetmyMonster(i)->GetMaxPp(0));
			printf("\t방어 : %d", Player.GetmyMonster(i)->GetmGrd());		printf("\t\t%s - %d/%d\n", Player.GetmyMonster(i)->GetsName(1), Player.GetmyMonster(i)->Getpp(1), Player.GetmyMonster(i)->GetMaxPp(1));
			printf("\t스피드 : %d\n", Player.GetmyMonster(i)->GetmSpd());
			printf("\t경험치 : %d\n", Player.GetmyMonster(i)->GetmExp());
			printf("\n\n");
		}
	}
	system("pause");

	IngameMenu();
}

void IngameMenu()
{
	int nInput = 0;
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t      1. 내포켓몬\n\n");
	printf("\t\t\t\t      2. 저장하기\n\n");
	printf("\t\t\t\t      3. 돌아가기\n\n");
	printf("\t\t\t\t      4. 종료하기\n\n");

	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:
		MyMonsterBox();

		break;
	case 2:
		SaveData();
		printf("\t\t\t\t데이터가 저장되었습니다!");
		Sleep(1000);
		Ingame();
		break;
	case 3:
		Ingame();
		break;
	case 4:
		printf("\t\t\t\t게임을 종료합니다.\n");
		exit(0);
		break;
	}
}

void RecoveryPokemon()
{
	for (int i = 0; i < 6; i++)
	{
		if (strlen(Player.GetmyMonster(i)->GetsName(i)) > 0)
		{
			Player.GetmyMonster(i)->SetmHp(Player.GetmyMonster(i)->GetMaxHp());

			for (int j = 0; j < 4; j++)
				Player.GetmyMonster(i)->Setpp(Player.GetmyMonster(i)->GetMaxPp(j), j);
		}
	}
}

void SaveData()
{
	FILE* fp;

	PLAYERDATA* playerData = { NULL };
	playerData = (PLAYERDATA*)malloc(sizeof(PLAYERDATA));

	strcpy_s(playerData->pName,_msize(playerData->pName), Player.GetpName());
	playerData->pX = Player.GetpX();
	playerData->pY = Player.GetpY();

	playerData->pMonsterLevel = Player.GetmyMonster(0)->GetmLevel();
	playerData->pMonsterHp = Player.GetmyMonster(0)->GetmHp();
	playerData->pMonsterAtk = Player.GetmyMonster(0)->GetmAtk();
	playerData->pMonsterGrd = Player.GetmyMonster(0)->GetmGrd();
	playerData->pMonsterSpd = Player.GetmyMonster(0)->GetmSpd();
	playerData->pMonsterExp = Player.GetmyMonster(0)->GetmExp();

	for (int i = 0; i < 4; i++)
	{
		playerData->pMonsterPp[i] = Player.GetmyMonster(0)->Getpp(i);
	}

	for (int i = 0; i < 6;i++)
	{
		playerData->pMonster[i] = *(Player.GetmyMonster(i));
	}

	if (_access("Save.dat", 0) == 0)	//파일이 있을때
		fopen_s(&fp, "Save.dat", "r+b");
	else
		fopen_s(&fp, "Save.dat", "w+b");

	if (playerData == NULL)
		return;

	fwrite(playerData, sizeof(PLAYERDATA), 1, fp);
	fclose(fp);
}

void LoadData()
{
	FILE* fp = NULL;

	PLAYERDATA* playerData = { NULL };
	playerData = (PLAYERDATA*)malloc(sizeof(PLAYERDATA));

	if (_access("Save.dat", 0) == 0)
		fopen_s(&fp, "Save.dat", "r+b");

	while (fread(playerData, sizeof(PLAYERDATA), 1, fp) != 0)   //계속 파일 읽기
		fread(playerData, sizeof(PLAYERDATA), 1, fp);

	Player.SetpName(playerData->pName);
	Player.SetpX(playerData->pX);
	Player.SetpY(playerData->pY);

	Player.GetmyMonster(0)->SetmLevel(playerData->pMonsterLevel);
	Player.GetmyMonster(0)->SetmHp(playerData->pMonsterHp);
	Player.GetmyMonster(0)->SetmAtk(playerData->pMonsterAtk);
	Player.GetmyMonster(0)->SetmGrd(playerData->pMonsterGrd);
	Player.GetmyMonster(0)->SetmSpd(playerData->pMonsterSpd);
	Player.GetmyMonster(0)->SetmExp(playerData->pMonsterExp);

	for (int i = 0; i < 4; i++)
	{
		 Player.GetmyMonster(0)->Setpp(playerData->pMonsterPp[i], i);
	}

	for (int i = 0; i < 6;i++)
	{
		Player.SetmyMonster(&(playerData->pMonster[i]),i);
	}

	fclose(fp);
}
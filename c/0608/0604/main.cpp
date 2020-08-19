#include "main.h"

class Player Player;

int getEx = 0;	//���� �� ����ġ(������ 30�� ����)

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

/* �� : 0  �� : 1  Ǯ�� : w  �� : t*/
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
	system("mode con cols=90 lines=32 | title Hokemon");	//�ܼ�âũ�� ����
	CursorView(0);
	PrintMenu();
	MenuSelect();
	return 0;
}

void CursorView(char show)	//Ŀ�� �����
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
				case 72:	// ���� �̵�
					if (map[currentY - 1][currentX] != '1' && map[currentY - 1][currentX] != '|' && map[currentY - 1][currentX] != '/' && map[currentY - 1][currentX] != '-')
					{
						currentY -= 1;
						if (currentY < 0) { currentY = 0; }
					}
					break;
				case 80:	// �Ʒ��� �̵�
					if (map[currentY + 1][currentX] != '1' && map[currentY + 1][currentX] != '|' && map[currentY + 1][currentX] != '/'&& map[currentY + 1][currentX] != '-')
					{
						currentY += 1;
						if (currentY > 29) { currentY = 29; }
					}
					break;
				case 75:	// �������� �̵�
					if (map[currentY][currentX - 1] != '1' && map[currentY][currentX - 1] != '|' && map[currentY][currentX - 1] != '/' && map[currentY][currentX - 1] != '-')
					{
						currentX -= 1;
						if (currentX < 0) { currentX = 0; }
					}
					break;
				case 77:	// ���������� �̵�
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

				if (map[currentY][currentX] == 'w')		//Ǯ���� ������ ����Ȯ���� ��Ʋ
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

	printf("\t\t\t\t 1. �����ϱ�\n\n");
	printf("\t\t\t\t 2. �̾��ϱ�\n\n");
	printf("\t\t\t\t 3. ��������\n\n");
}

void InputPlayerName()
{
	char pName[16] = { NULL };
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t �̸��� �Է����ּ��� : ");
	scanf_s("%s", pName, sizeof(pName));

	Player.SetpName(pName);
}

void SelectStartMonster()
{
	int nInput = 0;
	printf("\n");
	printf("\t\t\t\t��Ÿ�� ���ϸ��� �����ϼ���.");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t     1.�̻��ؾ�  2.���̸�  3.���α�\n");
	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:
	{
		Monster *myBulbasaur = new Bulbasaur();
		Player.SetmyMonster(myBulbasaur, 0);
		printf("\t\t\t\t%s�� ���ᰡ �Ǿ���!\n", myBulbasaur->GetmName());
		break;
	}
	case 2:
	{
		Monster *myCharmander = new Charmander();
		Player.SetmyMonster(myCharmander, 0);
		printf("\t\t\t\t%s�� ���ᰡ �Ǿ���!\n", myCharmander->GetmName());
		break;
	}
	case 3:
	{
		Monster *mySquirtle = new Squirtle();
		Player.SetmyMonster(mySquirtle, 0);
		printf("\t\t\t\t%s�� ���ᰡ �Ǿ���!\n", mySquirtle->GetmName());
		break;
	}
	}
}

void Ingame()
{
	PrintMap();
	printf("~~ ���ʸ��� ~~\n");
	PlayerMove(Player.GetpX(),Player.GetpY());
	BattleWild();
}

void MenuSelect()
{
	int nInput = 0;
	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:		//�����ϱ�
		system("cls");
		InputPlayerName();
		system("cls");
		SelectStartMonster();
		Sleep(2000);
		system("cls");
		Ingame();
		break;
	case 2:		//�̾��ϱ�
		system("cls");
		LoadData();
		Ingame();
		break;
	case 3:		//��������
		exit(0);
		break;

	default:
		printf("�ٸ� ���ڸ� �Է����ּ���.\n");
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
	printf("\t�߻��� %s��(��) ��Ÿ����!\n", enemy->GetmName());
	Sleep(1000);
	printf("\t����! %s!\n", Player.GetmyMonster(0)->GetmName());
	Sleep(1000);

	if (enemy->GetmSpd() < Player.GetmyMonster(0)->GetmSpd())			//�ڽ� �ϸ���
		myTurn = 0;
	else if (enemy->GetmSpd() > Player.GetmyMonster(0)->GetmSpd())	//��� �ϸ���
		myTurn = 1;

	while (1)
	{
		system("cls");
		int rNum = rand();
		int eSkillNum = rand();
		int eSkill = eSkillNum % 2;
		if (enemy->GetmSpd() == Player.GetmyMonster(0)->GetmSpd())	//����
			myTurn = rNum % 2;

		printf("\n\t\t\t\tLv.%d %s    Hp : %d/%d\n", enemy->GetmLevel(), enemy->GetmName(), enemy->GetmHp(),enemy->GetMaxHp());
		printf("\n\tLv.%d %s    Hp : %d/%d\n\n", Player.GetmyMonster(0)->GetmLevel() ,Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetmHp(), Player.GetmyMonster(0)->GetMaxHp());
		
		printf("\t������ �ұ�?\n");
		printf("\t1. �ο��   2.��´�\n\n");
		scanf_s("%d", &nInput2);

		if (nInput2 == 1)
		{
			for (int i = 0; i < 4; i++)		//���ϸ� ��ų ���
			{
				if (strlen(Player.GetmyMonster(0)->GetsName(i)) > 0)
					printf("\t%d.%s - %d/%d", i + 1, Player.GetmyMonster(0)->GetsName(i), localPp[i], Player.GetmyMonster(0)->GetMaxPp(i));
				printf("\n");
			}
			scanf_s("%d", &nInput);

			if (myTurn == 0)
			{
				Player.GetmyMonster(0)->Setpp(localPp[nInput - 1] -= 1, 0);
				printf("\t%s�� %s!\n", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetsName(nInput - 1));
				mySkillFunc(nInput, enemy->GetmName(), enemy->GetmGrd(),enemy);
				myTurn = 1;

				Sleep(1000);

				if (enemy->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);	//���� �� hp�� ������ �ɷ�ġ�� �ʱ�ȭ
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s�� ��������!\n", enemy->GetmName());
					Sleep(1000);
					getEx += 5;
					printf("\t%s�� %d ����ġ�� �����!\n", Player.GetmyMonster(0)->GetmName(), 30);
					Sleep(2000);
					LevelUp();
					saveHp += 1;
					break;
				}

				printf("\t%s�� %s!\n", enemy->GetmName(), enemy->GetsName(eSkill));
				eSkillFunc(eSkill, enemy->GetsName(0), enemy->GetsName(1), enemy->GetsDamage(0), enemy->GetmAtk());
				Sleep(1000);
				myTurn = 0;

				if (Player.GetmyMonster(0)->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s�� ��������!\n", Player.GetmyMonster(0)->GetmName());
					Sleep(1000);
					printf("\t%s�� ������ įį������!\n", Player.GetpName());
					Sleep(2000);
					Player.GetmyMonster(0)->SetmHp(1);
					break;
				}
			}
			else
			{
				printf("\t%s�� %s!\n", enemy->GetmName(), enemy->GetsName(eSkill));
				eSkillFunc(eSkill, enemy->GetsName(0), enemy->GetsName(1),enemy->GetsDamage(0),enemy->GetmAtk());
				Sleep(1000);
				myTurn = 0;

				if (Player.GetmyMonster(0)->GetmHp() == 0)
				{
					Player.GetmyMonster(0)->SetmAtk(saveAtk);
					Player.GetmyMonster(0)->SetmGrd(saveGrd);

					printf("\t%s�� ��������!\n", Player.GetmyMonster(0)->GetmName());
					Sleep(1000);
					printf("\t%s�� ������ įį������!\n", Player.GetpName());
					Sleep(2000);
					Player.GetmyMonster(0)->SetmHp(1);
					break;
				}

				Player.GetmyMonster(0)->Setpp(localPp[nInput - 1] -= 1, 0);
				printf("\t%s�� %s!\n", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetsName(nInput - 1));
				mySkillFunc(nInput,enemy->GetmName(), enemy->GetmGrd(),enemy);
				myTurn = 1;

				Sleep(1000);
			}
		}
		else if (nInput2 == 2)
		{
			int gotcha = rand();
			int gotchaNum = 0;

			printf("\t����! ���ͺ�!\n");
			Sleep(1000);
			printf("\t3.."); Sleep(1000); printf("2.."); Sleep(1000); printf("1..\n"); Sleep(1000);

			if (gotcha % 7 == 0)
			{
				printf("\t%s�� ���ͺ����� ���Դ�!\n", enemy->GetmName());
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

				printf("\t%s�� ��Ҵ�!\n", enemy->GetmName());
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
	if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "�����ġ��") == 0 || strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "������") == 0)
	{
		enemy->SetmHp(enemy->GetmHp() - myCalDamage(RattataGrd));
		if (enemy->GetmHp() < 0)
			enemy->SetmHp(0);
		printf("\t%s�� %d�� �������� �Ծ���!\n", RattataName, myCalDamage(RattataGrd));
		Sleep(1000);
	}
	else if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "�����Ҹ�") == 0)
	{
		enemy->SetmAtk(enemy->GetmAtk() - 1);
		if (enemy->GetmAtk() < 0)
		{
			enemy->SetmAtk(0);
			printf("\t%s�� ������ ���̻� �����ʴ´�!\n", RattataName);
		}
		else
			printf("\t%s�� ������ %d ��������!\n", RattataName, 1);
	}
	else if (strcmp(Player.GetmyMonster(0)->GetsName(nInput - 1), "��������") == 0)
	{
		enemy->SetmGrd(enemy->GetmGrd() - 1);
		if (enemy->GetmGrd() < 0)
		{
			enemy->SetmGrd(0);
			printf("\t%s�� ���� ���̻� �����ʴ´�!\n", RattataName);
		}
		else
			printf("\t%s�� �� %d ��������!\n", RattataName, 1);
	}
}

void eSkillFunc(int rNum, char* RattataSName1, char* RattataSName2, int RattataSDamage, int RattataAtk)
{
	rNum = rNum % 2;

	if (strcmp(RattataSName1, "�����ġ��") == 0)
	{
		Player.GetmyMonster(0)->SetmHp(Player.GetmyMonster(0)->GetmHp() - eCalDamage(RattataSDamage, RattataAtk));
		if (Player.GetmyMonster(0)->GetmHp() <= 0)
			Player.GetmyMonster(0)->SetmHp(0);
		printf("\t%s�� %d�� �������� �Ծ���!\n", Player.GetmyMonster(0)->GetmName(), eCalDamage(RattataSDamage, RattataAtk));
		Sleep(1000);
	}
	else if (strcmp(RattataSName2, "��������") == 0)
	{
		Player.GetmyMonster(0)->SetmGrd(Player.GetmyMonster(0)->GetmGrd() - 1);
		if (Player.GetmyMonster(0)->GetmGrd() <= 0)
		{
			Player.GetmyMonster(0)->SetmGrd(0);
			printf("\t%s�� ���� ���̻� �����ʴ´�!\n", Player.GetmyMonster(0)->GetmName());
		}
		else
			printf("\t%s�� �� %d ��������!\n", Player.GetmyMonster(0)->GetmName(), 1);
		Sleep(1000);
	}
	else if (strcmp(RattataSName2, "�����Ҹ�") == 0)
	{
		Player.GetmyMonster(0)->SetmAtk(Player.GetmyMonster(0)->GetmAtk() - 1);
		if (Player.GetmyMonster(0)->GetmAtk() <= 0)
		{
			Player.GetmyMonster(0)->SetmAtk(0);
			printf("\t%s�� ������ ���̻� �����ʴ´�!\n", Player.GetmyMonster(0)->GetmName());
		}
		else
			printf("\t%s�� ������ %d ��������!\n", Player.GetmyMonster(0)->GetmName(), 1);
		Sleep(1000);
	}
}

int myCalDamage(int RattataGrd)	//��� ���ϸ󿡰� �� ������
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
	int upLevel = 0;	//���������� ���� ����
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
		printf("\t%s�� %d������ �Ǿ���!", Player.GetmyMonster(0)->GetmName(), Player.GetmyMonster(0)->GetmLevel());
		Sleep(1500);
	}
}

void MyMonsterBox()
{
	system("cls");

	 //���ϸ� ���� �ٲܼ��ְ�(0������ n��°)

	for (int i = 0; i < 6; i++)
	{
		if (strlen(Player.GetmyMonster(i)->GetmName()) > 0)
		{
			printf("\tLv.%d   %s (%d/%d)\n\n", Player.GetmyMonster(i)->GetmLevel(), Player.GetmyMonster(i)->GetmName(), Player.GetmyMonster(i)->GetmHp(), Player.GetmyMonster(i)->GetMaxHp());
			printf("\t���� : %d", Player.GetmyMonster(i)->GetmAtk());		printf("\t\t%s - %d/%d\n", Player.GetmyMonster(i)->GetsName(0), Player.GetmyMonster(i)->Getpp(0), Player.GetmyMonster(i)->GetMaxPp(0));
			printf("\t��� : %d", Player.GetmyMonster(i)->GetmGrd());		printf("\t\t%s - %d/%d\n", Player.GetmyMonster(i)->GetsName(1), Player.GetmyMonster(i)->Getpp(1), Player.GetmyMonster(i)->GetMaxPp(1));
			printf("\t���ǵ� : %d\n", Player.GetmyMonster(i)->GetmSpd());
			printf("\t����ġ : %d\n", Player.GetmyMonster(i)->GetmExp());
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
	printf("\t\t\t\t      1. �����ϸ�\n\n");
	printf("\t\t\t\t      2. �����ϱ�\n\n");
	printf("\t\t\t\t      3. ���ư���\n\n");
	printf("\t\t\t\t      4. �����ϱ�\n\n");

	scanf_s("%d", &nInput);

	switch (nInput)
	{
	case 1:
		MyMonsterBox();

		break;
	case 2:
		SaveData();
		printf("\t\t\t\t�����Ͱ� ����Ǿ����ϴ�!");
		Sleep(1000);
		Ingame();
		break;
	case 3:
		Ingame();
		break;
	case 4:
		printf("\t\t\t\t������ �����մϴ�.\n");
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

	if (_access("Save.dat", 0) == 0)	//������ ������
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

	while (fread(playerData, sizeof(PLAYERDATA), 1, fp) != 0)   //��� ���� �б�
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
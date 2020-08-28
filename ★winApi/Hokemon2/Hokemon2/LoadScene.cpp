#include "stdafx.h"
#include "LoadScene.h"

extern Singleton *singleton;
extern HokemonDB *hokemonDB;

LoadScene::LoadScene()
{
	noneFile = false;

	rc_chikorita = { 120, 210, 180, 240 };
	rc_Cyndaquil = { 270, 210, 330, 240 };
	rc_Totodile = { 420, 210, 480, 240 };
}

LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	Hokemon *chikorita = new Hokemon;
	Hokemon *cyndaquil = new Hokemon;
	Hokemon *totodile = new Hokemon;
}

void LoadScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	int size[2];										// ���� ũ��
	char *doc = ReadFile("Hokemons.json", &size[0]);    // ���Ͽ��� JSON ������ ����, ���� ũ�⸦ ����
	char *sDoc = ReadFile("Skills.json", &size[1]);
	if (doc == NULL || sDoc == NULL)
	{
		noneFile = true;
		return;
	}
		
	/* ���ϸ� �Ľ� */
	JSON hJson;							// JSON ����ü ���� ���� �� �ʱ�ȭ
	memset(&hJson, 0, sizeof(JSON));
	ParseJSON(doc, size[0], &hJson);    // JSON ���� �Ľ�
	HokemonSaveData(hJson);

	FreeJSON(&hJson);    // json�� �Ҵ�� ���� �޸� ����
	free(doc);			// ���� ���� �޸� ����

	/* ��ų �Ľ� */
	JSON sJson;
	memset(&sJson, 0, sizeof(JSON));
	ParseJSON(sDoc, size[1], &sJson);
	SkillSaveData(sJson);

	FreeJSON(&sJson);
	free(sDoc);

	static int mx, my;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (mx > rc_chikorita.left && mx < rc_chikorita.right &&
			my > rc_chikorita.top && my < rc_chikorita.bottom)
		{
			//chikorita->
		}
		else if (mx > rc_Cyndaquil.left && mx < rc_Cyndaquil.right &&
			my > rc_Cyndaquil.top && my < rc_Cyndaquil.bottom)
		{

		}
		else if (mx > rc_Totodile.left && mx < rc_Totodile.right &&
			my > rc_Totodile.top && my < rc_Totodile.bottom)
		{

		}
		break;

	default:
		break;
	}

	//singleton->sceneManager->SceneChange(GameState::INGAME);
}

void LoadScene::Render(HWND hWnd, HDC hdc)
{
	/*if (noneFile)
		TextOut(hdc, 100, 100, L"file not found", 15);
	else
		TextOut(hdc, 100, 100, L"file Loading...", 15);*/

	Rectangle(hdc, 120, 210, 180, 240);
	DrawText(hdc, _T("ġ�ڸ�Ÿ"), _tcslen(_T("ġ�ڸ�Ÿ")), &rc_chikorita, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 270, 210, 330, 240);
	DrawText(hdc, _T("������"), _tcslen(_T("������")), &rc_Cyndaquil, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 420, 210, 480, 240);
	DrawText(hdc, _T("������"), _tcslen(_T("������")), &rc_Totodile, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void LoadScene::Free(HWND hWnd)
{
}

char * LoadScene::ReadFile(char* fileName, int* readSize)
{
	FILE *fp = fopen(fileName, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// ���� ũ�� ���ϱ�
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ���� ũ�� + NULL ������ŭ �޸𸮸� �Ҵ��ϰ� 0���� �ʱ�ȭ
	buffer = (char*)malloc(size + 1);
	memset(buffer, 0, size + 1);

	// ���� ���� �б�
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	*readSize = size;	// ���� ũ�⸦ �Ѱ���
	fclose(fp);			// ���� ������ �ݱ�

	return buffer;
}

void LoadScene::ParseJSON(char * doc, int size, JSON * json)
{
	int tokenIndex = 0;    // ��ū �ε���
	int pos = 0;           // ���� �˻� ��ġ�� �����ϴ� ����

	if (doc[pos] != '[')   // ������ ������ [ ���� �˻�
		return;

	pos++;    // ���� ���ڷ�

	if (doc[pos] != '{')   // ���� ���ڰ� { ���� �˻�
		return;

	while (pos < size)       // ���� ũ�⸸ŭ �ݺ�
	{
		switch (doc[pos])    // ������ ������ ���� �б�
		{
		case '"':            // ���ڰ� "�̸� ���ڿ�
		{
			// ���ڿ��� ���� ��ġ�� ����. �� ���� "�� �����ϱ� ���� + 1
			char *begin = doc + pos + 1;

			// ���ڿ��� �� ��ġ�� ����. ���� "�� ��ġ
			char *end = strchr(begin, '"');
			if (end == NULL)    // "�� ������ �߸��� �����̹Ƿ� 
				break;          // �ݺ��� ����

			int stringLength = end - begin;    // ���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ

			// ��ū �迭�� ���ڿ� ����, ��ū ������ ���ڿ�
			json->tokens[tokenIndex].type = (MY_TOKEN_TYPE)TOKEN_STRING;
			// ���ڿ� ���� + NULL ������ŭ �޸� �Ҵ�
			json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1);
			// �Ҵ��� �޸𸮸� 0���� �ʱ�ȭ
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

			// �������� ���ڿ��� ��ū�� ����
			// ���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);

			tokenIndex++; // ��ū �ε��� ����

			pos = pos + stringLength + 1;    // ���� ��ġ + ���ڿ� ���� + "(+ 1)
		}
		break;

		case '0': case '1': case '2': case '3': case '4': case '5':    // ���ڰ� �����̸�
		case '6': case '7': case '8': case '9': case '-':              // -�� ������ ��
		{
			// ���ڿ��� ���� ��ġ�� ����
			char *begin = doc + pos;
			char *end;
			char *buffer;

			// ���ڿ��� �� ��ġ�� ����. ,�� �����ų�
			end = strchr(doc + pos, ',');
			if (end == NULL)
			{
				// } �� ������ ���ڿ��� ����
				end = strchr(doc + pos, '}');
				if (end == NULL)    // }�� ������ �߸��� �����̹Ƿ�
					break;          // �ݺ��� ����
			}

			int stringLength = end - begin;    // ���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ

											   // ���ڿ� ���� + NULL ������ŭ �޸� �Ҵ�
			buffer = (char*)malloc(stringLength + 1);
			// �Ҵ��� �޸𸮸� 0���� �ʱ�ȭ
			memset(buffer, 0, stringLength + 1);

			// �������� ���ڿ��� ���ۿ� ����
			// ���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����
			memcpy(buffer, begin, stringLength);

			// ��ū ������ ����
			json->tokens[tokenIndex].type = TOKEN_NUMBER;
			// ���ڿ��� ���ڷ� ��ȯ�Ͽ� ��ū�� ����
			json->tokens[tokenIndex].number = atof(buffer);

			free(buffer);    // ���� ����

			tokenIndex++;    // ��ū �ε��� ����

			pos = pos + stringLength + 1;    // ���� ��ġ + ���ڿ� ���� + , �Ǵ� }(+ 1)
		}
		break;
		}
		pos++; // ���� ���ڷ�
	}
}

void LoadScene::HokemonSaveData(JSON json)
{
	Hokemon_Data hData[5];
	
	for (int i = 0; i < 5; i++)
	{
		hData[i].hNum = json.tokens[1 + (i * 17 + i)].number;
		strcpy_s(hData[i].hName, json.tokens[3 + (i * 17 + i)].string);
		hData[i].hHp = json.tokens[5 + (i * 17 + i)].number;
		hData[i].MaxHp = json.tokens[7 + (i * 17 + i)].number;
		hData[i].hAtk = json.tokens[9 + (i * 17 + i)].number;
		hData[i].hGrd = json.tokens[11 + (i * 17 + i)].number;
		hData[i].hSpd = json.tokens[13 + (i * 17 + i)].number;
		hData[i].hNextEvol = json.tokens[15 + (i * 17 + i)].number;
		hData[i].hType = json.tokens[17 + (i * 17 + i)].number;

		hokemonDB->map_Hokemons.insert(std::make_pair(json.tokens[1 + (i * 17 + i)].number, hData[i]));
	}
}

void LoadScene::SkillSaveData(JSON json)
{
	Skill_Data sData[13];

	for (int i = 0; i < 13; i++)
	{
		sData[i].id = json.tokens[1 + (i * 13 + i)].number;
		sData[i].accuracy = json.tokens[3 + (i * 13 + i)].number;
		strcpy_s(sData[i].sName, json.tokens[5 + (i * 13 + i)].string);
		sData[i].pp = json.tokens[7 + (i * 13 + i)].number;
		sData[i].MaxPp = json.tokens[9 + (i * 13 + i)].number;
		sData[i].sDamage = json.tokens[11 + (i * 13 + i)].number;
		sData[i].sType = json.tokens[13 + (i * 13 + i)].number;

		hokemonDB->map_Skills.insert(std::make_pair(json.tokens[1 + (i * 13 + i)].number, sData[i]));
	}
}

void LoadScene::FreeJSON(JSON * json)
{
	for (int i = 0; i < TOKEN_COUNT; i++)            // ��ū ������ŭ �ݺ�
	{
		if (json->tokens[i].type == (MY_TOKEN_TYPE)TOKEN_STRING)    // ��ū ������ ���ڿ��̸�
			free(json->tokens[i].string);            // ���� �޸� ����
	}
}

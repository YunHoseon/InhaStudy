#include "stdafx.h"
#include "LoadScene.h"

extern Singleton *singleton;

LoadScene::LoadScene()
{
	noneFile = false;
}

LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
}

void LoadScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	int size;			// ���� ũ��
	char *doc = ReadFile("Hokemons.json", &size);    // ���Ͽ��� JSON ������ ����, ���� ũ�⸦ ����
	if (doc == NULL)
		noneFile = true;

	JSON json;						// JSON ����ü ���� ���� �� �ʱ�ȭ
	memset(&json, 0, sizeof(JSON));
	ParseJSON(doc, size, &json);    // JSON ���� �Ľ�

	SaveData(json);

	FreeJSON(&json);    // json�� �Ҵ�� ���� �޸� ����
	free(doc);			// ���� ���� �޸� ����

	singleton->sceneManager->SceneChange(GameState::INGAME);
}

void LoadScene::Render(HWND hWnd, HDC hdc)
{
	if (noneFile)
		TextOut(hdc, 100, 100, L"file not found", 15);
	else
		TextOut(hdc, 100, 100, L"file Loading...", 15);
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

void LoadScene::SaveData(JSON json)
{
	Hokemon_Data hData[5];
	Skill_Data sData[13];

	for (int i = 0; i < 5; i++)
	{
		hData[i].hNum = json.tokens[1 + (i * 15 + i)].number;
		strcpy_s(hData[i].hName, json.tokens[3 + (i * 15 + i)].string);
		hData[i].hHp = json.tokens[5 + (i * 15 + i)].number;
		hData[i].MaxHp = json.tokens[7 + (i * 15 + i)].number;
		hData[i].hAtk = json.tokens[9 + (i * 15 + i)].number;
		hData[i].hGrd = json.tokens[11 + (i * 15 + i)].number;
		hData[i].hSpd = json.tokens[13 + (i * 15 + i)].number;
		hData[i].hNextEvol = json.tokens[15 + (i * 15 + i)].number;

		map_Hokemons.insert(make_pair(json.tokens[1 + (i * 15 + i)].number, hData[i]));
	}

	for (int i = 0; i < 13; i++)
	{
		//map_Skills.insert(make_pair(json.tokens[1 + (i * 15 + i)].number, sData[i]));
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

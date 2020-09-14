#include "stdafx.h"
#include "LoadScene.h"
#include "SoundManager.h"


extern Singleton *singleton;
extern HokemonDB *hokemonDB;
extern Player player;
extern SoundManager* g_theSoundManager;

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

}

void LoadScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	int size[2];										// 문서 크기
	char *doc = ReadFile("Hokemons.json", &size[0]);    // 파일에서 JSON 문서를 읽음, 문서 크기를 구함
	char *sDoc = ReadFile("Skills.json", &size[1]);
	if (doc == NULL || sDoc == NULL)
	{
		noneFile = true;
		return;
	}
		
	/* 포켓몬 파싱 */
	JSON hJson;							// JSON 구조체 변수 선언 및 초기화
	memset(&hJson, 0, sizeof(JSON));
	ParseJSON(doc, size[0], &hJson);    // JSON 문서 파싱
	HokemonSaveData(hJson);

	FreeJSON(&hJson);    // json에 할당된 동적 메모리 해제
	free(doc);			// 문서 동적 메모리 해제

	/* 스킬 파싱 */
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
			Hokemon *chikorita = new Hokemon;
			chikorita->SetData(hokemonDB->map_Hokemons.find(152)->second);
			chikorita->SetmLevel(5);
			chikorita->SetskillData(hokemonDB->map_Skills.find(1)->second, 0);
			chikorita->SetskillData(hokemonDB->map_Skills.find(2)->second, 1);

			player.SetMyMonster(chikorita, 0);
			singleton->sceneManager->SceneChange(GameState::INGAME);
		}
		else if (mx > rc_Cyndaquil.left && mx < rc_Cyndaquil.right &&
			my > rc_Cyndaquil.top && my < rc_Cyndaquil.bottom)
		{
			Hokemon *cyndaquil = new Hokemon;
			cyndaquil->SetData(hokemonDB->map_Hokemons.find(155)->second);
			cyndaquil->SetmLevel(5);
			cyndaquil->SetskillData(hokemonDB->map_Skills.find(1)->second, 0);
			cyndaquil->SetskillData(hokemonDB->map_Skills.find(5)->second, 1);

			player.SetMyMonster(cyndaquil, 0);
			singleton->sceneManager->SceneChange(GameState::INGAME);
		}
		else if (mx > rc_Totodile.left && mx < rc_Totodile.right &&
			my > rc_Totodile.top && my < rc_Totodile.bottom)
		{
			Hokemon *totodile = new Hokemon;
			totodile->SetData(hokemonDB->map_Hokemons.find(158)->second);
			totodile->SetmLevel(5);
			totodile->SetskillData(hokemonDB->map_Skills.find(8)->second, 0);
			totodile->SetskillData(hokemonDB->map_Skills.find(5)->second, 1);

			player.SetMyMonster(totodile, 0);
			singleton->sceneManager->SceneChange(GameState::INGAME);
		}
		break;

	default:
		break;
	}
}

void LoadScene::Render(HWND hWnd, HDC hdc)
{
	/*if (noneFile)
		TextOut(hdc, 100, 100, L"file not found", 15);
	else
		TextOut(hdc, 100, 100, L"file Loading...", 15);*/

	Rectangle(hdc, 120, 210, 180, 240);
	DrawText(hdc, _T("치코리타"), _tcslen(_T("치코리타")), &rc_chikorita, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 270, 210, 330, 240);
	DrawText(hdc, _T("브케인"), _tcslen(_T("브케인")), &rc_Cyndaquil, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 420, 210, 480, 240);
	DrawText(hdc, _T("리아코"), _tcslen(_T("리아코")), &rc_Totodile, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void LoadScene::Free(HWND hWnd)
{
	g_theSoundManager->Stop();
}

char * LoadScene::ReadFile(char* fileName, int* readSize)
{
	FILE *fp = fopen(fileName, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// 파일 크기 구하기
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
	buffer = (char*)malloc(size + 1);
	memset(buffer, 0, size + 1);

	// 파일 내용 읽기
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	*readSize = size;	// 파일 크기를 넘겨줌
	fclose(fp);			// 파일 포인터 닫기

	return buffer;
}

void LoadScene::ParseJSON(char * doc, int size, JSON * json)
{
	int tokenIndex = 0;    // 토큰 인덱스
	int pos = 0;           // 문자 검색 위치를 저장하는 변수

	if (doc[pos] != '[')   // 문서의 시작이 [ 인지 검사
		return;

	pos++;    // 다음 문자로

	if (doc[pos] != '{')   // 다음 문자가 { 인지 검사
		return;

	while (pos < size)       // 문서 크기만큼 반복
	{
		switch (doc[pos])    // 문자의 종류에 따라 분기
		{
		case '"':            // 문자가 "이면 문자열
		{
			// 문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 + 1
			char *begin = doc + pos + 1;

			// 문자열의 끝 위치를 구함. 다음 "의 위치
			char *end = strchr(begin, '"');
			if (end == NULL)    // "가 없으면 잘못된 문법이므로 
				break;          // 반복을 종료

			int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

			// 토큰 배열에 문자열 저장, 토큰 종류는 문자열
			json->tokens[tokenIndex].type = (MY_TOKEN_TYPE)TOKEN_STRING;
			// 문자열 길이 + NULL 공간만큼 메모리 할당
			json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1);
			// 할당한 메모리를 0으로 초기화
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

			// 문서에서 문자열을 토큰에 저장
			// 문자열 시작 위치에서 문자열 길이만큼만 복사
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);

			tokenIndex++; // 토큰 인덱스 증가

			pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
		}
		break;

		case '0': case '1': case '2': case '3': case '4': case '5':    // 문자가 숫자이면
		case '6': case '7': case '8': case '9': case '-':              // -는 음수일 때
		{
			// 문자열의 시작 위치를 구함
			char *begin = doc + pos;
			char *end;
			char *buffer;

			// 문자열의 끝 위치를 구함. ,가 나오거나
			end = strchr(doc + pos, ',');
			if (end == NULL)
			{
				// } 가 나오면 문자열이 끝남
				end = strchr(doc + pos, '}');
				if (end == NULL)    // }가 없으면 잘못된 문법이므로
					break;          // 반복을 종료
			}

			int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

											   // 문자열 길이 + NULL 공간만큼 메모리 할당
			buffer = (char*)malloc(stringLength + 1);
			// 할당한 메모리를 0으로 초기화
			memset(buffer, 0, stringLength + 1);

			// 문서에서 문자열을 버퍼에 저장
			// 문자열 시작 위치에서 문자열 길이만큼만 복사
			memcpy(buffer, begin, stringLength);

			// 토큰 종류는 숫자
			json->tokens[tokenIndex].type = TOKEN_NUMBER;
			// 문자열을 숫자로 변환하여 토큰에 저장
			json->tokens[tokenIndex].number = atof(buffer);

			free(buffer);    // 버퍼 해제

			tokenIndex++;    // 토큰 인덱스 증가

			pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + , 또는 }(+ 1)
		}
		break;
		}
		pos++; // 다음 문자로
	}
}

void LoadScene::HokemonSaveData(JSON json)
{
	Hokemon_Data hData[5];
	
	for (int i = 0; i < 5; i++)
	{
		hData[i].hNum = json.tokens[1 + (i * 17 + i)].number;
		USES_CONVERSION;
		_tcscpy(hData[i].hName, A2T(json.tokens[3 + (i * 17 + i)].string));
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
		USES_CONVERSION;
		_tcscpy(sData[i].sName, A2T(json.tokens[5 + (i * 13 + i)].string));
		//strcpy_s(sData[i].sName, json.tokens[5 + (i * 13 + i)].string);
		sData[i].pp = json.tokens[7 + (i * 13 + i)].number;
		sData[i].MaxPp = json.tokens[9 + (i * 13 + i)].number;
		sData[i].sDamage = json.tokens[11 + (i * 13 + i)].number;
		sData[i].sType = json.tokens[13 + (i * 13 + i)].number;

		hokemonDB->map_Skills.insert(std::make_pair(json.tokens[1 + (i * 13 + i)].number, sData[i]));
	}
}

void LoadScene::FreeJSON(JSON * json)
{
	for (int i = 0; i < TOKEN_COUNT; i++)            // 토큰 개수만큼 반복
	{
		if (json->tokens[i].type == (MY_TOKEN_TYPE)TOKEN_STRING)    // 토큰 종류가 문자열이면
			free(json->tokens[i].string);            // 동적 메모리 해제
	}
}

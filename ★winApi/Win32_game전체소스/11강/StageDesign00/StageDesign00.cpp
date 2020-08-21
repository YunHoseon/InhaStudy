// StageDesign00.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "StageDesign00.h"
#include <CommCtrl.h>
#include <CommDlg.h>
#include <stdio.h>
#include "StageInfo.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

CStageInfo g_StageInfo;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static char strFilePath[MAX_PATH], strFileName[100];
	OPENFILENAME ofn;
	char string[200];

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case ID_32771: // 열기
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "stg";
			ofn.lpstrTitle = "읽을 파일을 선택해 주세요";
			ofn.lpstrFilter = "스테이지(*.stg)\0*.stg\0\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				g_StageInfo.Load(strFilePath);				
				sprintf(string, "%d", (g_StageInfo.m_nLimitedTime / 1000) / 60);
				SetDlgItemText( hDlg, IDC_EDIT1, string);				
				
				sprintf(string, "%d", (g_StageInfo.m_nLimitedTime / 1000) % 60 );
				SetDlgItemText(hDlg, IDC_EDIT2, string);				
				
				SetDlgItemInt( hDlg, IDC_EDIT3, g_StageInfo.m_nGoalCount, FALSE);				
				SetDlgItemText(hDlg, IDC_EDIT4, g_StageInfo.m_strEnemyTeamName);			
				SetDlgItemText(hDlg, IDC_EDIT5, g_StageInfo.m_strBackgroundSoundName);
			}
			return (INT_PTR)TRUE;
		case ID_32772: // 저장
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "stg";
			ofn.lpstrTitle = "저장할 파일을 선택해 주세요";
			ofn.lpstrFilter = "스테이지(*.stg)\0*.stg\0\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetSaveFileName(&ofn) != 0 )
			{
				g_StageInfo.m_nLimitedTime = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE)*60*1000 + GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE)*1000;
				g_StageInfo.m_nGoalCount = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
				g_StageInfo.Save(strFilePath);
				sprintf(string, "%s 저장완료", strFileName);
				MessageBox(0, string, "완료", MB_OK);
			}
			return (INT_PTR)TRUE;
		case IDM_EXIT: // 종료
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		case IDC_BUTTON1: // 상대방 선수팀 
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "chr";
			ofn.lpstrTitle = "읽을 파일을 선택해 주세요";
			ofn.lpstrFilter = "상대방 선수팀(*.mob)\0*.mob\0\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				strcpy(g_StageInfo.m_strEnemyTeamName, strFileName);
				SetDlgItemText(hDlg, IDC_EDIT4, strFileName);
			}

			return (INT_PTR)TRUE;

		case IDC_BUTTON2:
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;			
			ofn.lpstrTitle = "읽을 파일을 선택해 주세요";
			ofn.lpstrFilter = "사운드 파일\0*.mp3;*.wav;*.ogg\0\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				strcpy(g_StageInfo.m_strBackgroundSoundName, strFileName);
				SetDlgItemText(hDlg, IDC_EDIT5, strFileName);
			}
			return (INT_PTR)TRUE;
		}		
		break;

	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

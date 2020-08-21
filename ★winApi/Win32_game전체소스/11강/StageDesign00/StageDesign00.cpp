// StageDesign00.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "StageDesign00.h"
#include <CommCtrl.h>
#include <CommDlg.h>
#include <stdio.h>
#include "StageInfo.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

CStageInfo g_StageInfo;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
		case ID_32771: // ����
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "stg";
			ofn.lpstrTitle = "���� ������ ������ �ּ���";
			ofn.lpstrFilter = "��������(*.stg)\0*.stg\0\0";
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
		case ID_32772: // ����
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "stg";
			ofn.lpstrTitle = "������ ������ ������ �ּ���";
			ofn.lpstrFilter = "��������(*.stg)\0*.stg\0\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetSaveFileName(&ofn) != 0 )
			{
				g_StageInfo.m_nLimitedTime = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE)*60*1000 + GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE)*1000;
				g_StageInfo.m_nGoalCount = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
				g_StageInfo.Save(strFilePath);
				sprintf(string, "%s ����Ϸ�", strFileName);
				MessageBox(0, string, "�Ϸ�", MB_OK);
			}
			return (INT_PTR)TRUE;
		case IDM_EXIT: // ����
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		case IDC_BUTTON1: // ���� ������ 
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "chr";
			ofn.lpstrTitle = "���� ������ ������ �ּ���";
			ofn.lpstrFilter = "���� ������(*.mob)\0*.mob\0\0";
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
			ofn.lpstrTitle = "���� ������ ������ �ּ���";
			ofn.lpstrFilter = "���� ����\0*.mp3;*.wav;*.ogg\0\0";
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

// CharTool00.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "CharTool00.h"
#include <CommCtrl.h>
#include <CommDlg.h>
#include <stdio.h>
#include <Windowsx.h>
#include "Pattern.h"
#include "Sprite.h"
#include "Enemy.h"

#define MAX_LOADSTRING 100

struct ENEMY_INDEX {
		int nSprIndex;
		int nPatIndex;
};

// �� ���������� ������ ���� ���� ������ ����� ������ �аų� �����ϱ� ���� ����ü Ŭ�����̴�.
// ����ü�� �ܼ��� �����͸� ���������� �� ����ü�� ������ �Լ��� �����ϰ� �ִ�.
// ����ü�� public ���ε� ������ ����Ѵ�.
struct ENEMY_INFO
{
	// ���� ����
	int nPatCount;
	char (*strPatFileName)[70]; 	

	// ���� ���� ��������Ʈ ����
	int nEnemyCount;
	ENEMY_INDEX *pEnemyIndex;

	void Load(char *filename);
	void Save(char *filename);

	ENEMY_INFO(){
		strPatFileName = NULL;
		pEnemyIndex = NULL;
	}

	~ENEMY_INFO(){
		if(strPatFileName != NULL)
			delete [] strPatFileName;
		if(pEnemyIndex != NULL)
			delete [] pEnemyIndex;
	}
};

void ENEMY_INFO::Load(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "rt");
	fscanf(fp, "%d\n", &nPatCount);
	
	if(strPatFileName != NULL)
		delete [] strPatFileName;
	strPatFileName = new char[nPatCount][70];
	for(int i = 0 ; i < nPatCount ; i++)
		fscanf(fp, "%s\n", strPatFileName[i]);
	fscanf(fp, "%d\n", &nEnemyCount);
	if(pEnemyIndex != NULL)
		delete [] pEnemyIndex;
	pEnemyIndex = new ENEMY_INDEX[nEnemyCount];
	for(int i  = 0; i < nEnemyCount ; i++)
		fscanf(fp, "%d %d\n", &pEnemyIndex[i].nSprIndex, &pEnemyIndex[i].nPatIndex);
	fclose(fp);
}

void ENEMY_INFO::Save(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "wt");
	fprintf(fp, "%d\n", nPatCount);	 // ���� ����
	for(int i = 0 ; i < nPatCount ; i++)
		fprintf(fp, "%s\n", strPatFileName[i]);
	fprintf(fp, "%d\n", nEnemyCount); // �� ĳ���� ����	
	for(int i  = 0; i < nEnemyCount ; i++)
		fprintf(fp, "%d %d\n", pEnemyIndex[i].nSprIndex, pEnemyIndex[i].nPatIndex);
	fclose(fp);
}

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.
HDC g_hBackGroundDC, g_hBackBuffer;
SIZE g_GroundSize = { 600, 600 }; // ��� ũ���̴�. 

CPattern *g_pPattern = NULL;
CSprite g_pSprite[8], g_GoalDae; // �����̹Ƿ� �����͸� ������� �ʾҴ�.
char *g_strSpriteFileName[] = {"enemy1_r.spr", "enemy2_r.spr", "enemy3_r.spr", "enemy4_r.spr", "enemy5_r.spr", "enemy6_r.spr", "enemy7_r.spr", "enemy8_r.spr" };
char *g_strManList[] = {"enemy1_r", "enemy2_r", "enemy3_r", "enemy4_r", "enemy5_r", "enemy6_r", "enemy7_r", "enemy8_r"};
CEnemy *g_pEnemy = NULL;
BOOL g_bIsRender = FALSE;
ENEMY_INFO* g_pEnemyInfo = NULL; // new�� delete�� ����ؼ� �����ڿ� �Ҹ��ڸ� ����ϱ� ���� �����ͷ� ����


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc); 
	return 0;
}

// Note: �޸� DC�� �����ϴ� �Լ�
HDC CreateBitmpDC(HWND hWnd, char *filename)
{
	// ������ ��� �¾�
	HBITMAP hBitmap;
	HDC hMemDC;
	hBitmap = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, 
					LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE ); 
	HDC hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);		
	SelectObject(hMemDC, (HBITMAP)hBitmap);		
	DeleteObject(hBitmap);
	return hMemDC;
}

// Note: ��׶��忡 ��� �׸� �Ŀ� ���� ��Ʈ�ѷ� ����Ѵ�.
void OnPaint(HWND hPicture, HWND hList1, HWND hList2)
{
	char string[200];	
	HDC hPictureDC = GetDC(hPicture);
	PatBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, BLACKNESS);
	BitBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackGroundDC, 0, 0, SRCCOPY);
	int nWidth = g_GoalDae.GetSprWidth(0);
	int	nHeight = g_GoalDae.GetSprHeight(0);
	TransparentBlt(g_hBackBuffer, 230, 70, nWidth, nHeight, g_GoalDae.GetSrcImageDC(), 
			g_GoalDae.GetSprRect(0).left, g_GoalDae.GetSprRect(0).top, nWidth, nHeight, 
			g_GoalDae.GetTransColor());

	int nCount = ListView_GetItemCount(hList2); // ���� ��
	if( nCount > 0 )
	{
		int nManIndex, nPatIndex;
		if(g_pEnemy != NULL)
			delete [] g_pEnemy;
		g_pEnemy = new CEnemy[nCount];

		for(int i = 0 ; i < nCount; i++)
		{ // Note: ��������Ʈ�� ������ ����
			ListView_GetItemText(hList2, i, 1, string, sizeof(string)-1);
			for(int j = 0 ; j < 8 ; j++)
			{
				if( strcmp(string, g_strManList[j]) == 0 )
				{
					nManIndex = j;
					break;
				}
			}

			ListView_GetItemText(hList2, i, 2, string, sizeof(string)-1);
			nPatIndex = atoi(string);

			// ��������Ʈ�� ������ ����
			g_pEnemy[i].Init(&g_pSprite[nManIndex], &g_pPattern[nPatIndex]);					
			g_pEnemy[i].Render(g_hBackBuffer);
		}
	}

	BitBlt(hPictureDC, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackBuffer, 0, 0, SRCCOPY);	
	ReleaseDC(hPicture, hPictureDC);
}


void EnemyDraw(HWND hWnd, int nEnemyCount)
{
	HDC hPicDC = GetDC(hWnd);
	PatBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, BLACKNESS);
	BitBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackGroundDC, 0, 0, SRCCOPY);
	int nWidth = g_GoalDae.GetSprWidth(0);
	int	nHeight = g_GoalDae.GetSprHeight(0);
	TransparentBlt(g_hBackBuffer, 230, 70, nWidth, nHeight, g_GoalDae.GetSrcImageDC(), 
			g_GoalDae.GetSprRect(0).left, g_GoalDae.GetSprRect(0).top, nWidth, nHeight, 
			g_GoalDae.GetTransColor());

	if(g_pEnemy != NULL)
	{		
		for(int i = 0 ; i < nEnemyCount ; i++)			
			g_pEnemy[i].Render(g_hBackBuffer);			
	}		

	BitBlt(hPicDC, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hPicDC);	
}


// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HBITMAP hBitmap;
	HDC hdc, hPicDC;
	PAINTSTRUCT ps;	
	static char strFilePath[MAX_PATH], strFileName[100];
	OPENFILENAME ofn;
	static HWND hList1, hList2, hCombo1, hCombo2, hPicture;	
	int nCount, nIndex, nSelectedIndex = -1, nPatIndex, nManIndex, nWidth, nHeight;
	LVCOLUMN lvColumn;
	LVITEM lvItem;
	char string[100];	
	static DWORD dwOldTime; 	

	switch (message)
	{
	case WM_INITDIALOG:
		hPicture = GetDlgItem(hDlg, IDC_PIC1); // picture control
		hList1 = GetDlgItem(hDlg, IDC_LIST1 );
		hList2 = GetDlgItem(hDlg, IDC_LIST2 );		
		hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
		hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
		ListView_SetExtendedListViewStyle( hList1, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
		ListView_SetExtendedListViewStyle( hList2, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
       	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		lvColumn.cx = 60;
        lvColumn.pszText = "�ε���";
        ListView_InsertColumn( hList1, 0, &lvColumn );	
		lvColumn.cx = 220;
        lvColumn.pszText = "���ϸ�";
        ListView_InsertColumn( hList1, 1, &lvColumn );	

		lvColumn.cx = 50;
        lvColumn.pszText = "�ε���";
        ListView_InsertColumn( hList2, 0, &lvColumn );	
		lvColumn.cx = 140;
        lvColumn.pszText = "���� ����";
        ListView_InsertColumn( hList2, 1, &lvColumn );	
		lvColumn.cx = 100;
        lvColumn.pszText = "�̵����� �ε���";
        ListView_InsertColumn( hList2, 2, &lvColumn );	

		// Note: �޺��ڽ��� �������� ���, 8��		
		hCombo1 = GetDlgItem( hDlg, IDC_COMBO1 ); 
		for(int i = 0; i < 8 ; i++)
		{
			ComboBox_AddString(hCombo1, g_strManList[i]); 
		}

		g_hBackGroundDC = CreateBitmpDC(hDlg, "ground1_r.bmp");
		hdc = GetDC(hDlg);
		hBitmap = CreateCompatibleBitmap(hdc, g_GroundSize.cx, g_GroundSize.cy);
		g_hBackBuffer = CreateCompatibleDC(hdc);
		SelectObject(g_hBackBuffer, (HBITMAP)hBitmap);   // ���� ������� ũ�Ⱑ �����Ƿ�
		DeleteObject(hBitmap);

		for(int i = 0 ; i < 8 ; i++)
		{
			// Load �� LaodBMpImdge�� �ϳ��� 
			g_pSprite[i].Load(hDlg, g_strSpriteFileName[i]);			
		}		

		g_GoalDae.Load(hDlg, "goalpost_r.spr");
		return (INT_PTR)TRUE;
	case WM_PAINT:		
		hdc = BeginPaint(hDlg, &ps);		
		hPicDC = GetDC(hPicture);
		PatBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, BLACKNESS);
		BitBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackGroundDC, 0, 0, SRCCOPY);
		nWidth = g_GoalDae.GetSprWidth(0);
		nHeight = g_GoalDae.GetSprHeight(0);
		TransparentBlt(g_hBackBuffer, 230, 70, nWidth, nHeight, g_GoalDae.GetSrcImageDC(), 
			g_GoalDae.GetSprRect(0).left, g_GoalDae.GetSprRect(0).top, nWidth, nHeight, 
			g_GoalDae.GetTransColor());

		if(g_bIsRender)
		{
			if(g_pEnemy != NULL)
			{
				nCount = ListView_GetItemCount(hList2); //���� ����
				for(int i = 0 ; i < nCount ; i++)			
					g_pEnemy[i].Render(g_hBackBuffer);	
			}
		}		

		BitBlt(hPicDC, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackBuffer, 0, 0, SRCCOPY);
		ReleaseDC(hPicture, hPicDC);		
		EndPaint(hDlg, &ps);		
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam))
		{
		case ID_32771: // ���� ����
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "mob";
			ofn.lpstrTitle = "���� ������ ������ �ּ���";
			ofn.lpstrFilter = "���漱��(*.mob)\0*.mob\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				delete g_pEnemyInfo; // �Ҹ��� ȣ�� 
				g_pEnemyInfo = new ENEMY_INFO(); // ������ ȣ�� �� �ʱ�ȭ			
				g_pEnemyInfo->Load(strFilePath);

				//------------- ��Ʈ�� ���� -----------------------
				ListView_DeleteAllItems(hList1);				
				ComboBox_ResetContent(hCombo2);
				
				for(int i = 0 ; i < g_pEnemyInfo->nPatCount ; i++)
				{				
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
					sprintf(string, "%d", i);
					lvItem.pszText = string; // �ε��� ���				
					ListView_InsertItem( hList1, &lvItem );				
					ListView_SetItemText(hList1, i, 1, g_pEnemyInfo->strPatFileName[i]);
					ComboBox_AddString(hCombo2, string);
				}
				
				ListView_DeleteAllItems(hList2);
				for(int i = 0 ; i < g_pEnemyInfo->nEnemyCount ; i++)
				{
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
					sprintf(string, "%d", i);
					lvItem.pszText = string; // �ε��� ���				
					ListView_InsertItem( hList2, &lvItem );		
					ListView_SetItemText(hList2, i, 1, g_strManList[g_pEnemyInfo->pEnemyIndex[i].nSprIndex]);					
					sprintf(string, "%d", g_pEnemyInfo->pEnemyIndex[i].nPatIndex);					
					ListView_SetItemText(hList2, i, 2, string);					
				}	
				
				delete [] g_pEnemy;
				g_pEnemy = NULL;

				//���� �������� ����
				nCount = ListView_GetItemCount(hList1); //���� ����
				if(g_pPattern != NULL)
					delete [] g_pPattern;
				g_pPattern = new CPattern[nCount];
				for(int i = 0 ; i < nCount; i++)
				{
					ListView_GetItemText(hList1, i, 1, string, sizeof(string)-1);
					if( g_pPattern[i].Load(string) != TRUE)
						MessageBox(0, "���� ������ �ε� ����", "error", MB_OK);
				}				
				
				MessageBox(0, "���� ���� �Ϸ�", "ok", MB_OK);	
				OnPaint(hPicture, hList1, hList2);				
			}
			return (INT_PTR)TRUE;
		case ID_32772: // ���� ����
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "mob";
			ofn.lpstrTitle = "������ ������ ������ �ּ���";
			ofn.lpstrFilter = "���漱��(*.mob)\0*.mob\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetSaveFileName(&ofn) != 0 )
			{
				delete g_pEnemyInfo; // �Ҹ��� ȣ�� 
				g_pEnemyInfo = new ENEMY_INFO(); // ������ ȣ�� �� �ʱ�ȭ
				g_pEnemyInfo->nPatCount = ListView_GetItemCount(hList1);
				g_pEnemyInfo->strPatFileName = new char[g_pEnemyInfo->nPatCount][70];
				for(int i = 0 ; i < g_pEnemyInfo->nPatCount ; i++)
					ListView_GetItemText(hList1, i, 1, g_pEnemyInfo->strPatFileName[i], 69);

				g_pEnemyInfo->nEnemyCount = ListView_GetItemCount(hList2);
				g_pEnemyInfo->pEnemyIndex = new ENEMY_INDEX[g_pEnemyInfo->nEnemyCount];
				for(int i = 0 ; i < g_pEnemyInfo->nEnemyCount ; i++)
				{
					ListView_GetItemText(hList2, i, 1, string, sizeof(string)-1);
					for(int j = 0 ; j < 8 ; j++)
					{
						if( strcmp(string, g_strManList[j]) == 0 )
						{
							g_pEnemyInfo->pEnemyIndex[i].nSprIndex = j;
						}
					}
					ListView_GetItemText(hList2, i, 2, string, sizeof(string)-1);
					g_pEnemyInfo->pEnemyIndex[i].nPatIndex = atoi(string);
				}
				g_pEnemyInfo->Save(strFilePath);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON1: // �̵� ���� ���� ����, ���� ���������� ���⸦ �� �� �ִٰ� �Ѵ�.
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "pat";
			ofn.lpstrTitle = "������ ������ �ּ���";
			ofn.lpstrFilter = "����(*.pat)\0*.pat\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				SetDlgItemText(hDlg, IDC_EDIT1, strFileName);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // ���
			nIndex = lvItem.iItem = ListView_GetItemCount(hList1);// ��ü ������ �ε��� ����
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
			sprintf(string, "%d", nIndex);
			lvItem.pszText = string; // �ε��� ���				
			ListView_InsertItem( hList1, &lvItem );
			GetDlgItemText(hDlg, IDC_EDIT1, string, 99);
			ListView_SetItemText(hList1, nIndex, 1, string);	

			nCount = ListView_GetItemCount(hList1);
			sprintf(string, "%d", nCount - 1);
			ComboBox_AddString(hCombo2, string);			
			return (INT_PTR)TRUE;

		case IDC_BUTTON3: // ����
			nIndex = ListView_GetNextItem( hList1, -1, LVNI_SELECTED ); // ���� �ε���
			GetDlgItemText(hDlg, IDC_EDIT1, string, 99);
			ListView_SetItemText(hList1, nIndex, 1, string);
			return (INT_PTR)TRUE;

		case IDC_BUTTON4: // ����
			nCount = ListView_GetItemCount(hList1);
			if( nCount == 0 )
			{
				MessageBox(hDlg, "������ ������ �����ϴ�", "����", MB_OK);
				return (INT_PTR)TRUE;
			}

			nIndex = ListView_GetNextItem( hList1, -1, LVNI_SELECTED ); // ���� �ε���
			ListView_DeleteItem(hList1, nIndex); // �����Ǹ� �ε����� �����
			nCount = ListView_GetItemCount(hList1);
			for(int i = nIndex ; i < nCount ; i++) 
			{
				sprintf(string, "%d", i);
				ListView_SetItemText(hList1, i, 0, string);
			}

			ComboBox_DeleteString(hCombo2, nCount); // �̵����� �޺��ڽ� �ε��� ����
			return (INT_PTR)TRUE;
		case IDC_BUTTON5: // �ʱ�ȭ			
			if(g_pPattern != NULL)
			{
				delete [] g_pPattern;
				g_pPattern = NULL;
			}
			
			ComboBox_ResetContent(hCombo2);
			ListView_DeleteAllItems(hList1);
			ListView_DeleteAllItems(hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON6: // ���� ����
			nCount = ListView_GetItemCount(hList1); //���� ����
			if(g_pPattern != NULL)
				delete [] g_pPattern;
			g_pPattern = new CPattern[nCount];
			for(int i = 0 ; i < nCount; i++)
			{
				ListView_GetItemText(hList1, i, 1, string, sizeof(string)-1);
				if( g_pPattern[i].Load(string) != TRUE)
					MessageBox(0, "���� ������ �ε� ����", "error", MB_OK);
			}
			MessageBox(0, "���� ���� �Ϸ�", "ok", MB_OK);
			return (INT_PTR)TRUE;
		case IDC_BUTTON7: // �������� ���
			lvItem.iItem = ListView_GetItemCount(hList2);// ��ü ������ �ε��� ����
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
			sprintf(string, "%d", lvItem.iItem);
			lvItem.pszText = string; // �ε��� ���				
			ListView_InsertItem( hList2, &lvItem );                              
					
			nIndex = ComboBox_GetCurSel(hCombo1); // ���� ����
			ListView_SetItemText(hList2, lvItem.iItem, 1, g_strManList[nIndex]);	
			nIndex = ComboBox_GetCurSel(hCombo2); // �̵����� �ε���
			sprintf(string, "%d", nIndex);
			ListView_SetItemText(hList2, lvItem.iItem, 2, string);	
			OnPaint(hPicture, hList1, hList2);					
			return (INT_PTR)TRUE;
		case IDC_BUTTON9: // �������� ����
			nSelectedIndex = ListView_GetNextItem( hList2, -1, LVNI_SELECTED ); // ���� �ε���
			if( nSelectedIndex == -1)
			{
				MessageBox(0, "������ ������ ������ �ּ���!!", "����", MB_OK );
				break;
			}

			nManIndex = ComboBox_GetCurSel(hCombo1); // ���� ���� ����
			if( nManIndex == CB_ERR )
			{
				MessageBox(0, "���������� ������ �ּ���!!", "����", MB_OK );
				break;
			}

			nPatIndex = ComboBox_GetCurSel(hCombo2); // �̵����� �ε���
			if( nPatIndex == CB_ERR )
			{
				MessageBox(0, "�̵����� �ε����� ������ �ּ���!!", "����", MB_OK );
				break;
			}
			
			ListView_SetItemText(hList2, nSelectedIndex, 1, g_strManList[nManIndex]);				
			sprintf(string, "%d", nPatIndex);
			ListView_SetItemText(hList2, nSelectedIndex, 2, string);			
			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON10: // ���� ����
			nCount = ListView_GetItemCount(hList2);
			if( nCount == 0 )
			{
				MessageBox(hDlg, "������ ������ �����ϴ�", "����", MB_OK);
				break;
			}

			nSelectedIndex = ListView_GetNextItem( hList2, -1, LVNI_SELECTED ); // ���� �ε���
			ListView_DeleteItem(hList2, nSelectedIndex); // �����Ǹ� �ε����� �����
			nCount = ListView_GetItemCount(hList2);
			for(int i = nSelectedIndex ; i < nCount ; i++) // �ε��� ����
			{
				sprintf(string, "%d", i);
				ListView_SetItemText(hList2, i, 0, string);
			}			

			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON11: // ���� �ʱ�ȭ
			ListView_DeleteAllItems(hList2);			
			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;

		case IDC_BUTTON12: // ������ ��ư
			g_bIsRender = !g_bIsRender;
			if(g_bIsRender)
			{
				nCount = ListView_GetItemCount(hList2); // ���� ��
				if(g_pEnemy != NULL)
					delete [] g_pEnemy;
				g_pEnemy = new CEnemy[nCount];

				int nManIndex, nPatIndex;
				for(int i = 0 ; i < nCount; i++)
				{ // Note: ��������Ʈ�� ������ ����
					ListView_GetItemText(hList2, i, 1, string, sizeof(string)-1);
					for(int j = 0 ; j < 8 ; j++)
					{
						if( strcmp(string, g_strManList[j]) == 0 )
						{
							nManIndex = j;
							break;
						}
					}

					ListView_GetItemText(hList2, i, 2, string, sizeof(string)-1);
					nPatIndex = atoi(string);
				   // ��������Ʈ�� ������ ����
					g_pEnemy[i].Init(&g_pSprite[nManIndex], &g_pPattern[nPatIndex]);					
				}
				dwOldTime = GetTickCount();
				SetTimer(hDlg, 1, 30, NULL); // Ÿ�̸Ӵ� �񵿱�� �����̹Ƿ� �������� �ؾ� �Ѵ�.
			}else{
				KillTimer(hDlg, 1);
				OnPaint(hPicture, hList1, hList2);
			}			
			return (INT_PTR)TRUE;
		}
		break;	

	case WM_TIMER:
		{
			DWORD dwCurTime = GetTickCount();
			DWORD dwElapsedTime = dwCurTime - dwOldTime; // �� ������ ����ð�
			dwOldTime = dwCurTime;

			nCount = ListView_GetItemCount(hList2); // ���� ��
			for(int i = 0 ; i < nCount; i++)
				g_pEnemy[i].Update(dwCurTime, dwElapsedTime);		

			EnemyDraw(hPicture, nCount);
		}
		return (INT_PTR)TRUE;

	case WM_CLOSE:
		DeleteDC(g_hBackGroundDC);		
		DeleteDC(g_hBackBuffer);
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
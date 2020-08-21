// CharTool00.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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

// 한 스테이지에 적용할 상대방 선수 정보와 연결된 패턴을 읽거나 저장하기 위한 구조체 클래스이다.
// 구조체는 단순히 데이터만 저장하지만 이 구조체는 간단한 함수를 포함하고 있다.
// 구조체는 public 으로된 접근을 허락한다.
struct ENEMY_INFO
{
	// 패턴 정보
	int nPatCount;
	char (*strPatFileName)[70]; 	

	// 상대방 선수 스프라이트 정보
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
	fprintf(fp, "%d\n", nPatCount);	 // 패턴 개수
	for(int i = 0 ; i < nPatCount ; i++)
		fprintf(fp, "%s\n", strPatFileName[i]);
	fprintf(fp, "%d\n", nEnemyCount); // 적 캐릭터 개수	
	for(int i  = 0; i < nEnemyCount ; i++)
		fprintf(fp, "%d %d\n", pEnemyIndex[i].nSprIndex, pEnemyIndex[i].nPatIndex);
	fclose(fp);
}

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.
HDC g_hBackGroundDC, g_hBackBuffer;
SIZE g_GroundSize = { 600, 600 }; // 운동장 크기이다. 

CPattern *g_pPattern = NULL;
CSprite g_pSprite[8], g_GoalDae; // 고정이므로 포인터를 사용하지 않았다.
char *g_strSpriteFileName[] = {"enemy1_r.spr", "enemy2_r.spr", "enemy3_r.spr", "enemy4_r.spr", "enemy5_r.spr", "enemy6_r.spr", "enemy7_r.spr", "enemy8_r.spr" };
char *g_strManList[] = {"enemy1_r", "enemy2_r", "enemy3_r", "enemy4_r", "enemy5_r", "enemy6_r", "enemy7_r", "enemy8_r"};
CEnemy *g_pEnemy = NULL;
BOOL g_bIsRender = FALSE;
ENEMY_INFO* g_pEnemyInfo = NULL; // new와 delete를 사용해서 생성자와 소멸자를 사용하기 위해 포인터로 선언


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

// Note: 메모리 DC를 생성하는 함수
HDC CreateBitmpDC(HWND hWnd, char *filename)
{
	// 렌더링 배경 셋업
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

// Note: 백그라운드에 모두 그린 후에 픽쳐 컨트롤로 출력한다.
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

	int nCount = ListView_GetItemCount(hList2); // 선수 수
	if( nCount > 0 )
	{
		int nManIndex, nPatIndex;
		if(g_pEnemy != NULL)
			delete [] g_pEnemy;
		g_pEnemy = new CEnemy[nCount];

		for(int i = 0 ; i < nCount; i++)
		{ // Note: 스프라이트와 패턴을 연결
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

			// 스프라이트와 패턴을 연결
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


// 정보 대화 상자의 메시지 처리기입니다.
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
        lvColumn.pszText = "인덱스";
        ListView_InsertColumn( hList1, 0, &lvColumn );	
		lvColumn.cx = 220;
        lvColumn.pszText = "패턴명";
        ListView_InsertColumn( hList1, 1, &lvColumn );	

		lvColumn.cx = 50;
        lvColumn.pszText = "인덱스";
        ListView_InsertColumn( hList2, 0, &lvColumn );	
		lvColumn.cx = 140;
        lvColumn.pszText = "선수 유형";
        ListView_InsertColumn( hList2, 1, &lvColumn );	
		lvColumn.cx = 100;
        lvColumn.pszText = "이동패턴 인덱스";
        ListView_InsertColumn( hList2, 2, &lvColumn );	

		// Note: 콤보박스에 선수유형 등록, 8명		
		hCombo1 = GetDlgItem( hDlg, IDC_COMBO1 ); 
		for(int i = 0; i < 8 ; i++)
		{
			ComboBox_AddString(hCombo1, g_strManList[i]); 
		}

		g_hBackGroundDC = CreateBitmpDC(hDlg, "ground1_r.bmp");
		hdc = GetDC(hDlg);
		hBitmap = CreateCompatibleBitmap(hdc, g_GroundSize.cx, g_GroundSize.cy);
		g_hBackBuffer = CreateCompatibleDC(hdc);
		SelectObject(g_hBackBuffer, (HBITMAP)hBitmap);   // 배경과 백버퍼의 크기가 같으므로
		DeleteObject(hBitmap);

		for(int i = 0 ; i < 8 ; i++)
		{
			// Load 와 LaodBMpImdge를 하나로 
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
				nCount = ListView_GetItemCount(hList2); //패턴 개수
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
		case ID_32771: // 파일 열기
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "mob";
			ofn.lpstrTitle = "읽을 파일을 선택해 주세요";
			ofn.lpstrFilter = "상대방선수(*.mob)\0*.mob\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				delete g_pEnemyInfo; // 소멸자 호출 
				g_pEnemyInfo = new ENEMY_INFO(); // 생성자 호출 및 초기화			
				g_pEnemyInfo->Load(strFilePath);

				//------------- 컨트롤 셋팅 -----------------------
				ListView_DeleteAllItems(hList1);				
				ComboBox_ResetContent(hCombo2);
				
				for(int i = 0 ; i < g_pEnemyInfo->nPatCount ; i++)
				{				
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
					sprintf(string, "%d", i);
					lvItem.pszText = string; // 인덱스 등록				
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
					lvItem.pszText = string; // 인덱스 등록				
					ListView_InsertItem( hList2, &lvItem );		
					ListView_SetItemText(hList2, i, 1, g_strManList[g_pEnemyInfo->pEnemyIndex[i].nSprIndex]);					
					sprintf(string, "%d", g_pEnemyInfo->pEnemyIndex[i].nPatIndex);					
					ListView_SetItemText(hList2, i, 2, string);					
				}	
				
				delete [] g_pEnemy;
				g_pEnemy = NULL;

				//패턴 생성까지 진행
				nCount = ListView_GetItemCount(hList1); //패턴 개수
				if(g_pPattern != NULL)
					delete [] g_pPattern;
				g_pPattern = new CPattern[nCount];
				for(int i = 0 ; i < nCount; i++)
				{
					ListView_GetItemText(hList1, i, 1, string, sizeof(string)-1);
					if( g_pPattern[i].Load(string) != TRUE)
						MessageBox(0, "패턴 데이터 로딩 에러", "error", MB_OK);
				}				
				
				MessageBox(0, "패턴 생성 완료", "ok", MB_OK);	
				OnPaint(hPicture, hList1, hList2);				
			}
			return (INT_PTR)TRUE;
		case ID_32772: // 파일 저장
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "mob";
			ofn.lpstrTitle = "저장할 파일을 선택해 주세요";
			ofn.lpstrFilter = "상대방선수(*.mob)\0*.mob\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetSaveFileName(&ofn) != 0 )
			{
				delete g_pEnemyInfo; // 소멸자 호출 
				g_pEnemyInfo = new ENEMY_INFO(); // 생성자 호출 및 초기화
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

		case IDC_BUTTON1: // 이동 패턴 파일 열기, 현재 폴더에서만 열기를 할 수 있다고 한다.
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFileTitle = strFileName;
			ofn.lpstrFile = strFilePath;
			ofn.lpstrDefExt = "pat";
			ofn.lpstrTitle = "파일을 선택해 주세요";
			ofn.lpstrFilter = "패턴(*.pat)\0*.pat\0";
			ofn.nMaxFile = sizeof(strFilePath) - 1;
			ofn.nMaxFileTitle = sizeof(strFileName) - 1;

			if( GetOpenFileName(&ofn) != 0 )
			{
				SetDlgItemText(hDlg, IDC_EDIT1, strFileName);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // 등록
			nIndex = lvItem.iItem = ListView_GetItemCount(hList1);// 전체 개수로 인덱스 결정
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
			sprintf(string, "%d", nIndex);
			lvItem.pszText = string; // 인덱스 등록				
			ListView_InsertItem( hList1, &lvItem );
			GetDlgItemText(hDlg, IDC_EDIT1, string, 99);
			ListView_SetItemText(hList1, nIndex, 1, string);	

			nCount = ListView_GetItemCount(hList1);
			sprintf(string, "%d", nCount - 1);
			ComboBox_AddString(hCombo2, string);			
			return (INT_PTR)TRUE;

		case IDC_BUTTON3: // 수정
			nIndex = ListView_GetNextItem( hList1, -1, LVNI_SELECTED ); // 선택 인덱스
			GetDlgItemText(hDlg, IDC_EDIT1, string, 99);
			ListView_SetItemText(hList1, nIndex, 1, string);
			return (INT_PTR)TRUE;

		case IDC_BUTTON4: // 삭제
			nCount = ListView_GetItemCount(hList1);
			if( nCount == 0 )
			{
				MessageBox(hDlg, "삭제할 패턴이 없습니다", "에러", MB_OK);
				return (INT_PTR)TRUE;
			}

			nIndex = ListView_GetNextItem( hList1, -1, LVNI_SELECTED ); // 선택 인덱스
			ListView_DeleteItem(hList1, nIndex); // 삭제되면 인덱스가 변경됨
			nCount = ListView_GetItemCount(hList1);
			for(int i = nIndex ; i < nCount ; i++) 
			{
				sprintf(string, "%d", i);
				ListView_SetItemText(hList1, i, 0, string);
			}

			ComboBox_DeleteString(hCombo2, nCount); // 이동패턴 콤보박스 인덱스 삭제
			return (INT_PTR)TRUE;
		case IDC_BUTTON5: // 초기화			
			if(g_pPattern != NULL)
			{
				delete [] g_pPattern;
				g_pPattern = NULL;
			}
			
			ComboBox_ResetContent(hCombo2);
			ListView_DeleteAllItems(hList1);
			ListView_DeleteAllItems(hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON6: // 패턴 생성
			nCount = ListView_GetItemCount(hList1); //패턴 개수
			if(g_pPattern != NULL)
				delete [] g_pPattern;
			g_pPattern = new CPattern[nCount];
			for(int i = 0 ; i < nCount; i++)
			{
				ListView_GetItemText(hList1, i, 1, string, sizeof(string)-1);
				if( g_pPattern[i].Load(string) != TRUE)
					MessageBox(0, "패턴 데이터 로딩 에러", "error", MB_OK);
			}
			MessageBox(0, "패턴 생성 완료", "ok", MB_OK);
			return (INT_PTR)TRUE;
		case IDC_BUTTON7: // 선수유형 등록
			lvItem.iItem = ListView_GetItemCount(hList2);// 전체 개수로 인덱스 결정
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_COLFMT | LVIF_TEXT;						
			sprintf(string, "%d", lvItem.iItem);
			lvItem.pszText = string; // 인덱스 등록				
			ListView_InsertItem( hList2, &lvItem );                              
					
			nIndex = ComboBox_GetCurSel(hCombo1); // 선수 유형
			ListView_SetItemText(hList2, lvItem.iItem, 1, g_strManList[nIndex]);	
			nIndex = ComboBox_GetCurSel(hCombo2); // 이동패턴 인덱스
			sprintf(string, "%d", nIndex);
			ListView_SetItemText(hList2, lvItem.iItem, 2, string);	
			OnPaint(hPicture, hList1, hList2);					
			return (INT_PTR)TRUE;
		case IDC_BUTTON9: // 선수유형 수정
			nSelectedIndex = ListView_GetNextItem( hList2, -1, LVNI_SELECTED ); // 선택 인덱스
			if( nSelectedIndex == -1)
			{
				MessageBox(0, "수정할 선수를 선택해 주세요!!", "에러", MB_OK );
				break;
			}

			nManIndex = ComboBox_GetCurSel(hCombo1); // 선수 유형 선택
			if( nManIndex == CB_ERR )
			{
				MessageBox(0, "선수유형을 선택해 주세요!!", "에러", MB_OK );
				break;
			}

			nPatIndex = ComboBox_GetCurSel(hCombo2); // 이동패턴 인덱스
			if( nPatIndex == CB_ERR )
			{
				MessageBox(0, "이동패턴 인덱스를 선택해 주세요!!", "에러", MB_OK );
				break;
			}
			
			ListView_SetItemText(hList2, nSelectedIndex, 1, g_strManList[nManIndex]);				
			sprintf(string, "%d", nPatIndex);
			ListView_SetItemText(hList2, nSelectedIndex, 2, string);			
			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON10: // 선수 삭제
			nCount = ListView_GetItemCount(hList2);
			if( nCount == 0 )
			{
				MessageBox(hDlg, "삭제할 패턴이 없습니다", "에러", MB_OK);
				break;
			}

			nSelectedIndex = ListView_GetNextItem( hList2, -1, LVNI_SELECTED ); // 선택 인덱스
			ListView_DeleteItem(hList2, nSelectedIndex); // 삭제되면 인덱스가 변경됨
			nCount = ListView_GetItemCount(hList2);
			for(int i = nSelectedIndex ; i < nCount ; i++) // 인덱스 정렬
			{
				sprintf(string, "%d", i);
				ListView_SetItemText(hList2, i, 0, string);
			}			

			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;
		case IDC_BUTTON11: // 선수 초기화
			ListView_DeleteAllItems(hList2);			
			OnPaint(hPicture, hList1, hList2);
			return (INT_PTR)TRUE;

		case IDC_BUTTON12: // 렌더링 버튼
			g_bIsRender = !g_bIsRender;
			if(g_bIsRender)
			{
				nCount = ListView_GetItemCount(hList2); // 선수 수
				if(g_pEnemy != NULL)
					delete [] g_pEnemy;
				g_pEnemy = new CEnemy[nCount];

				int nManIndex, nPatIndex;
				for(int i = 0 ; i < nCount; i++)
				{ // Note: 스프라이트와 패턴을 연결
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
				   // 스프라이트와 패턴을 연결
					g_pEnemy[i].Init(&g_pSprite[nManIndex], &g_pPattern[nPatIndex]);					
				}
				dwOldTime = GetTickCount();
				SetTimer(hDlg, 1, 30, NULL); // 타이머는 비동기로 움직이므로 마지막에 해야 한다.
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
			DWORD dwElapsedTime = dwCurTime - dwOldTime; // 한 프레임 경과시간
			dwOldTime = dwCurTime;

			nCount = ListView_GetItemCount(hList2); // 선수 수
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

// 정보 대화 상자의 메시지 처리기입니다.
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
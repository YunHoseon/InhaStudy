// SoccerGamePattern00.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "SoccerGamePattern00.h"
#include <CommCtrl.h>
#include <CommDlg.h>
#include <stdio.h>
#include <Windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Pattern.h"
#include "Sprite.h"

#define MAX_LOADSTRING 100

// 전역 변수:
INT_PTR CALLBACK	DialogProc(HWND, UINT, WPARAM, LPARAM);
HDC g_hBackGroundDC, g_hBackBuffer, g_hCharacterDC;
SIZE g_GroundSize = { 600, 600};
SIZE g_CharacterSize = { 113 - 76 + 1,  245 - 192 + 1};
char *g_strDirection[] = {"TOP", "RIGHT_TOP", "RIGHT", "RIGHT_DOWN", "DOWN", "LEFT_DOWN", "LEFT", "LEFT_TOP", "STOP" };

CPattern g_Pattern;
MOVE_INFO g_sMoveInfo;  // 공통적으로 사용하는 이동경로에 대한 구조체

int g_nMoveCount; // 전체 이동경로 개수
POINT g_ptXY0 = { 280, 170};    // 초기 위치
CSprite g_GoalDae;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), 0, DialogProc); 
	return (int) 0;
}

// Note: 비트맵 메모리 DC 생성
//       hMemDC가 로컬변수여서 생성 후에 삭제 되지만 메모리에는 메모리DC가 남아 있다.
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

POINT ComputeMoveDestXY( int nPreX, int nPreY, DIRECTION nDirection, int nDistance )
{
	POINT nDestXY;

	switch(nDirection)
	{
	case TOP:						
		nDestXY.x = nPreX;
		nDestXY.y = nPreY - nDistance;							
		break;
	case RIGHT_TOP:
		nDestXY.x = nPreX + nDistance;
		nDestXY.y = nPreY - nDistance;
		break;				
	case RIGHT:						
		nDestXY.x = nPreX + nDistance;	
		nDestXY.y = nPreY;						
		break;
	case RIGHT_DOWN:
		nDestXY.x = nPreX + nDistance;
		nDestXY.y = nPreY + nDistance;
		break;
	case DOWN:					
		nDestXY.x = nPreX;
		nDestXY.y = nPreY + nDistance;							
		break;
	case LEFT_DOWN:
		nDestXY.x = nPreX - nDistance;					
		nDestXY.y = nPreY + nDistance;	
		break;				
	case LEFT:						
		nDestXY.x = nPreX - nDistance;					
		nDestXY.y = nPreY;						
		break;				
	case LEFT_TOP:
		nDestXY.x = nPreX - nDistance;					
		nDestXY.y = nPreY - nDistance;	
		break;						
	case STOP:
		nDestXY.x = nPreX;
		nDestXY.y = nPreY;
		break;
	}

	return nDestXY;
}

DIRECTION GetRadioCheck(HWND hDlg)
{
	DIRECTION nDirection;
	if( IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED )
		nDirection = TOP;
	else if(IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED )
		nDirection = RIGHT_TOP;
	else if( IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED )
		nDirection = RIGHT;
	else if( IsDlgButtonChecked(hDlg, IDC_RADIO4) == BST_CHECKED )
		nDirection = RIGHT_DOWN;
	else if( IsDlgButtonChecked(hDlg, IDC_RADIO5) == BST_CHECKED )
		nDirection = DOWN;
	else if(IsDlgButtonChecked(hDlg, IDC_RADIO6) == BST_CHECKED )
		nDirection = LEFT_DOWN;
	else if( IsDlgButtonChecked(hDlg, IDC_RADIO7) == BST_CHECKED )
		nDirection = LEFT;
	else if( IsDlgButtonChecked(hDlg, IDC_RADIO8) == BST_CHECKED )
		nDirection = LEFT_TOP;
	if( IsDlgButtonChecked(hDlg, IDC_RADIO9) == BST_CHECKED )
		nDirection = STOP;	
	return nDirection;
}

// 리스트 뷰 안에 있는 모든 이동경로를 재계산하는 함수이다.
void ComputeAllMoveInfo(HWND hList)
{	
	char string[30];
	int nCount = ListView_GetItemCount(hList); // 이동 경로의 개수 파악
	int nPreX = g_ptXY0.x;
	int nPreY = g_ptXY0.y;
			
	MOVE_INFO sMoveInfo; 
	for(int i = 0 ; i < nCount ; i++)
	{
		ListView_GetItemText(hList, i, 1, string, 20); // 방향 가져오기
		for( int j = 0 ; j < 9 ; j++)
		{
			if(strcmp(string, g_strDirection[j]) == 0) // 같으면
			{
				sMoveInfo.nDirection = (DIRECTION)j; 
				break;
			}
		}

		ListView_GetItemText(hList, i, 2, string, 20); // 속도
		sMoveInfo.fVelocity = atof(string);
		ListView_GetItemText(hList, i, 3, string, 20); // 거리
		sMoveInfo.nAllDistance = atoi(string);
		ListView_GetItemText(hList, i, 4, string, 20); // 정지시간
		sMoveInfo.dwDelayTime = atoi(string);

		//--------------------------도착 x, y 계산-------------//
		POINT ptDestXY = ComputeMoveDestXY(nPreX, nPreY, sMoveInfo.nDirection, sMoveInfo.nAllDistance);
		sMoveInfo.nDestX = ptDestXY.x;
		sMoveInfo.nDestY = ptDestXY.y;				

		//----------- 리스트 컨트롤에 모든 항목의 내용을 전부 넣는다.--------//			
		ListView_SetItemText(hList, i, 1, g_strDirection[sMoveInfo.nDirection]);
		sprintf(string, "%.2f", sMoveInfo.fVelocity);
		ListView_SetItemText(hList, i, 2, string);
		sprintf(string, "%d", sMoveInfo.nAllDistance);
		ListView_SetItemText(hList, i, 3, string);
		sprintf(string, "%d", sMoveInfo.dwDelayTime);
		ListView_SetItemText(hList, i, 4, string);
		sprintf(string, "%d", sMoveInfo.nDestX); // 도착 X
		ListView_SetItemText(hList, i, 5, string);
		sprintf(string, "%d", sMoveInfo.nDestY); // 도착 Y
		ListView_SetItemText(hList, i, 6, string);	

		nPreX = sMoveInfo.nDestX;
		nPreY = sMoveInfo.nDestY;
	}
}

void InsertMoveInfo(HWND hList, int nIndex, MOVE_INFO sMoveInfo )
{
	LVITEM ITEM; 
	char string[30];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nIndex; // Note: 추가 아이템 등록 인덱스

	sprintf( string, "%d", nIndex );
	ITEM.pszText = string;
	ListView_InsertItem( hList, &ITEM);	
	
	ListView_SetItemText( hList, nIndex, 1, g_strDirection[sMoveInfo.nDirection] );
	sprintf(string, "%.2f", sMoveInfo.fVelocity);
	ListView_SetItemText( hList, nIndex, 2, string );
	sprintf(string, "%d", sMoveInfo.nAllDistance);
	ListView_SetItemText( hList, nIndex, 3, string );
	sprintf( string, "%d", sMoveInfo.dwDelayTime );
	ListView_SetItemText( hList, nIndex, 4, string );
	sprintf( string, "%d", sMoveInfo.nDestX );
	ListView_SetItemText( hList, nIndex, 5, string );
	sprintf( string, "%d", sMoveInfo.nDestY );
	ListView_SetItemText( hList, nIndex, 6, string );
}

MOVE_INFO GetMoveInfo(HWND hList, int nIndex)
{
	MOVE_INFO sMoveInfo;
	char string[30];
	ListView_GetItemText(hList, nIndex, 1, string, 20); 
	for( int i = 0 ; i < 9 ; i++)
	{
		if(strcmp(string, g_strDirection[i]) == 0) // 같으면
		{
			sMoveInfo.nDirection = (DIRECTION)i; // LEFT, RIGHT, TOP, DOWN, STOP							
			break;
		}
	}

	ListView_GetItemText(hList, nIndex, 2, string, 20); // 속도
	sMoveInfo.fVelocity = atof(string);
	ListView_GetItemText(hList, nIndex, 3, string, 20); // 거리
	sMoveInfo.nAllDistance = atoi(string);
	ListView_GetItemText(hList, nIndex, 4, string, 20); // 정지시간
	sMoveInfo.dwDelayTime = atoi(string);
	ListView_GetItemText(hList, nIndex, 5, string, 20); // 도착 x
	sMoveInfo.nDestX = atoi(string);
	ListView_GetItemText(hList, nIndex, 6, string, 20); // 도착 y
	sMoveInfo.nDestY = atoi(string);
	return sMoveInfo;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HBITMAP hBitmap;
	HDC hdc, hPictureDC;
	static HWND hPictureCtrl;
	PAINTSTRUCT ps;	
	static char *strMenu[] = { "순번", "이동방향", "이동속도", "전체이동거리", "정지시간", "도착 X", "도착 Y" };
	static int  nMenuSize[] = { 40, 110, 70, 90, 60, 50, 50 };
	LVCOLUMN lvColumn;
	LVITEM lvItem;
	int i, j, nIndex, nSelectIndex, nCount, nWidth, nHeight;
	char string[100];
	static RECT rtBackGround = { 0, 0, 347 - 16, 490 - 13 };
	static float fX = g_ptXY0.x, fY = g_ptXY0.y;
	static int nMoveIndex;	
	static HWND hList, hStopEdit, hVelocityEdit, hDistanceEdit;
	static BOOL bMoveFlag; 
	static DWORD dwOldTime, dwStopElapsedTime;
	static DWORD dwCurTime, dwElapsedTime;	
	float fDistance;
	static float fAddDistance; // 누적 거리
	POINT nMoveXY[2];

	// 파일 관련
	OPENFILENAME OFN;
    static char strFileTitle[MAX_PATH];
    static char strFileExtension[10];
    static char strFile[100];	
	MOVE_INFO sMoveInfo;	

	switch (message)
	{
	case WM_INITDIALOG:
		// 컨트롤 셋업
		hList = GetDlgItem( hDlg, IDC_LIST1 );
		hPictureCtrl = GetDlgItem(hDlg, IDC_PIC1);

		hVelocityEdit = GetDlgItem(hDlg, IDC_EDIT1); // 이동속도 에디트 컨트롤
		hDistanceEdit = GetDlgItem(hDlg, IDC_EDIT2); // 전체이동거리 에디트 컨트롤
		hStopEdit = GetDlgItem(hDlg, IDC_EDIT5);     // 정지 시간 에디트 컨트롤
		ListView_SetExtendedListViewStyle( hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
        nCount = sizeof(strMenu) / sizeof(char *);
		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;

        for( i = 0 ; i < nCount ; i++ )
        {
            lvColumn.cx = nMenuSize[i];
            lvColumn.pszText = strMenu[i];
            ListView_InsertColumn( hList, i, &lvColumn );			
        }

		SetDlgItemInt(hDlg, IDC_EDIT3, fX, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT4, fY, FALSE);

		Edit_Enable(hStopEdit, FALSE); // 정지시간 에디트 컨트롤 비활성화

		// 렌더링 배경 셋업
		g_hBackGroundDC = CreateBitmpDC(hDlg, "ground1_r.bmp");
		g_hCharacterDC = CreateBitmpDC(hDlg, "enemy4_r.bmp");		
		hdc = GetDC(hDlg);
		hBitmap = CreateCompatibleBitmap(hdc, g_GroundSize.cx, g_GroundSize.cy);
		g_hBackBuffer = CreateCompatibleDC(hdc);
		SelectObject(g_hBackBuffer, (HBITMAP)hBitmap);   // 배경과 백버퍼의 크기가 같으므로
		DeleteObject(hBitmap);

		g_GoalDae.Load(hDlg, "goalpost_r.spr");
		
		ReleaseDC(hDlg, hdc);	
		return (INT_PTR)TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		hPictureDC = GetDC(hPictureCtrl);
		PatBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, BLACKNESS);
		BitBlt(g_hBackBuffer, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackGroundDC, 
			     0, 0, SRCCOPY);
		nWidth = g_GoalDae.GetSprWidth(0);
		nHeight = g_GoalDae.GetSprHeight(0);
		TransparentBlt(g_hBackBuffer, 230, 100, nWidth, nHeight, g_GoalDae.GetSrcImageDC(), 
			g_GoalDae.GetSprRect(0).left, g_GoalDae.GetSprRect(0).top, nWidth, nHeight, 
			g_GoalDae.GetTransColor());

		nCount = ListView_GetItemCount(hList); // 개수
		nMoveXY[0] = g_ptXY0;	
		for(i = 0 ; i < nCount ; i++)
		{
			MoveToEx(g_hBackBuffer, nMoveXY[0].x, nMoveXY[0].y, NULL);
			ListView_GetItemText(hList, i, 5, string, 20); // 도착 x
			nMoveXY[1].x = atoi(string);
			ListView_GetItemText(hList, i, 6, string, 20); // 도착 y
			nMoveXY[1].y = atoi(string);
			LineTo(g_hBackBuffer, nMoveXY[1].x, nMoveXY[1].y);
			nMoveXY[0].x = nMoveXY[1].x;
			nMoveXY[0].y = nMoveXY[1].y;
		}

		TransparentBlt(g_hBackBuffer, fX - 19, fY - 52, g_CharacterSize.cx, g_CharacterSize.cy, 
			           g_hCharacterDC, 76, 192, g_CharacterSize.cx, g_CharacterSize.cy, 65280);		
		BitBlt(hPictureDC, 0, 0, g_GroundSize.cx, g_GroundSize.cy, g_hBackBuffer, 0, 0, SRCCOPY);
		EndPaint(hDlg, &ps);
		return (INT_PTR)TRUE;
	case WM_CLOSE:
		DeleteDC(g_hBackGroundDC);
		DeleteDC(g_hCharacterDC);
		DeleteDC(g_hBackBuffer);
		g_Pattern.Release();
		g_GoalDae.Release();
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case ID_32771: // 파일 열기
			memset(strFileTitle, 0, sizeof(strFileTitle));
			memset(strFile, 0, sizeof(strFile));
			memset( &OFN, 0, sizeof( OPENFILENAME ) );
			OFN.lStructSize = sizeof( OPENFILENAME );  
			OFN.hwndOwner = hDlg;
			OFN.lpstrTitle = "파일을 선택해 주세요";
			OFN.lpstrFileTitle = strFileTitle;  // 파일명
			OFN.lpstrFile = strFile; // 전체 경로와 파일명
			OFN.lpstrFilter = "패턴(*.pat)\0*.pat\0";
			OFN.nMaxFile = MAX_PATH;
			OFN.nMaxFileTitle = MAX_PATH;
			if( GetOpenFileName( &OFN ) != 0 )
			{
				g_Pattern.Load(strFile);				
				g_ptXY0 = g_Pattern.GetInitXY();
				SetDlgItemInt(hDlg, IDC_EDIT3, g_ptXY0.x, FALSE);
				SetDlgItemInt(hDlg, IDC_EDIT4, g_ptXY0.y, FALSE);				
				fX = g_ptXY0.x; //캐릭터 초기 위치
				fY = g_ptXY0.y; 
				ListView_DeleteAllItems(hList);
				nCount = g_Pattern.GetMoveCount();

				MOVE_INFO sMoveInfo;
				for(i = 0; i < nCount ; i++)
				{
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.mask = LVIF_COLFMT | LVIF_TEXT;		
					sprintf( string, "%d", i );
					lvItem.pszText = string;
					ListView_InsertItem( hList, &lvItem );
					
					// 입력 받은 데이터를 리스트 컨트롤에 등록한다.
					sMoveInfo = g_Pattern.GetMoveInfo(i);
					ListView_SetItemText(hList, i, 1, g_strDirection[sMoveInfo.nDirection]);

					sprintf(string, "%.2f", sMoveInfo.fVelocity);
					ListView_SetItemText(hList, i, 2, string);
					
					sprintf(string, "%d", sMoveInfo.nAllDistance);
					ListView_SetItemText(hList, i, 3, string);
					
					sprintf(string, "%d", sMoveInfo.dwDelayTime);
					ListView_SetItemText(hList, i, 4, string);
			
					sprintf(string, "%d", sMoveInfo.nDestX); // 도착 X
					ListView_SetItemText(hList, i, 5, string);
					
					sprintf(string, "%d", sMoveInfo.nDestY); // 도착 Y
					ListView_SetItemText(hList, i, 6, string);						
				}					
			
				SetWindowText(hDlg, strFile);
				InvalidateRect(hDlg, &rtBackGround, FALSE);				
			}			
			break;
		case ID_32772: // 파일 저장
			memset(strFileTitle, 0, sizeof(strFileTitle));
			memset(strFile, 0, sizeof(strFile));
			memset( &OFN, 0, sizeof( OPENFILENAME ) );
            OFN.lStructSize = sizeof( OPENFILENAME );
            OFN.hwndOwner = hDlg;
            OFN.lpstrTitle = "저장할 파일을 선택해 주세요";
            OFN.lpstrFileTitle = strFileTitle;  // 파일명
            OFN.lpstrFile = strFile; // 전체 경로와 파일명
            OFN.lpstrFilter = "패턴(*.pat)\0*.pat\0";
			OFN.lpstrDefExt = "pat"; // 기본 확장자 설정
            OFN.nMaxFile = MAX_PATH;
            OFN.nMaxFileTitle = MAX_PATH;
 
			if( GetSaveFileName( &OFN ) != 0 )
			{
				g_Pattern.SetInitXY(g_ptXY0);
				nCount = ListView_GetItemCount(hList);
				g_Pattern.CreateMoveInfo( nCount ); // 이동 경로의 개수설정				
				
				MOVE_INFO sMoveInfo;
				for( i = 0 ; i < nCount ; i++)
				{
					ListView_GetItemText(hList, i, 1, string, 20); 
					for( j = 0 ; j < 9 ; j++) // 8방향과 정지 1개 
					{
						if(strcmp(string, g_strDirection[j]) == 0) // 같으면
						{
							sMoveInfo.nDirection = (DIRECTION)j; // TOP, RIGHT_TOP, RIGHT 등 시계 방향으로
							break;
						}
					}

					ListView_GetItemText(hList, i, 2, string, 20); // 속도
					sMoveInfo.fVelocity = atof(string);
					ListView_GetItemText(hList, i, 3, string, 20); // 거리
					sMoveInfo.nAllDistance = atoi(string);
					ListView_GetItemText(hList, i, 4, string, 20); // 정지시간
					sMoveInfo.dwDelayTime = atoi(string);
					ListView_GetItemText(hList, i, 5, string, 20); // 도착 x
					sMoveInfo.nDestX = atoi(string);
					ListView_GetItemText(hList, i, 6, string, 20); // 도착 y
					sMoveInfo.nDestY = atoi(string);
					g_Pattern.SetMoveInfo(i, sMoveInfo);
				}
				g_Pattern.Save(strFile); // 최종 목적
			}
			break;
		case IDC_RADIO1: // TOP			
		case IDC_RADIO2: // RIGHT_TOP			
		case IDC_RADIO3: // RIGHT					
		case IDC_RADIO4: // RIGHT_DOWN			
		case IDC_RADIO5: //DOWN					
		case IDC_RADIO6: // LEFT_DOWN			
		case IDC_RADIO7: // LEFT			
		case IDC_RADIO8: // LEFT_TOP			
			Edit_Enable(hStopEdit, FALSE);
			Edit_Enable(hVelocityEdit, TRUE);
			Edit_Enable(hDistanceEdit, TRUE);
			break;		
		case IDC_RADIO9: // STOP				
			Edit_Enable(hStopEdit, TRUE);
			Edit_Enable(hVelocityEdit, FALSE);
			Edit_Enable(hDistanceEdit, FALSE);			
			break;

		case IDC_BUTTON7: // 리스트 초기화 버튼
			ListView_DeleteAllItems(hList);
			fX = g_ptXY0.x;
			fY = g_ptXY0.y;
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON8: // 캐릭터 위치 초기화
			fX = g_ptXY0.x;
			fY = g_ptXY0.y;
			nMoveIndex = 0;
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON5: // 초기위치 설정 버튼 => 적용버튼, 초기 위치가 바뀌면 전체가 바뀌어야 한다.
			fX = g_ptXY0.x = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			fY = g_ptXY0.y = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);	

			ComputeAllMoveInfo(hList);			
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON1: // 등록버튼 => 컨트롤로부터 데이터를 가져오는 것			
			sMoveInfo.nDirection = GetRadioCheck(hDlg);
			// 리스트 컨트롤에 행을 추가한다.
			nIndex = lvItem.iItem = ListView_GetItemCount(hList);// 전체 개수로 인덱스 결정
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_COLFMT | LVIF_TEXT;		
			sprintf( string, "%d", nIndex );
			lvItem.pszText = string;
			ListView_InsertItem( hList, &lvItem );

			// 컨트롤의 데이터를 가져오는 부분
			if(sMoveInfo.nDirection == STOP)
			{
				sMoveInfo.fVelocity = 0;
				sMoveInfo.nAllDistance = 0;
				GetDlgItemText(hDlg, IDC_EDIT5, string, 20); // 속도
				sMoveInfo.dwDelayTime = atoi(string);
			}else{
				GetDlgItemText(hDlg, IDC_EDIT1, string, 20); // 속도
				sMoveInfo.fVelocity = atof(string);
				GetDlgItemText(hDlg, IDC_EDIT2, string, 20); // 거리
				sMoveInfo.nAllDistance = atoi(string);				
				sMoveInfo.dwDelayTime = 0;
			}

			// 입력 받은 데이터를 리스트 컨트롤에 등록한다.
			ListView_SetItemText(hList, nIndex, 1, g_strDirection[sMoveInfo.nDirection]);
			sprintf(string, "%.2f", sMoveInfo.fVelocity);
			ListView_SetItemText(hList, nIndex, 2, string);
			sprintf(string, "%d", sMoveInfo.nAllDistance);
			ListView_SetItemText(hList, nIndex, 3, string);
			sprintf(string, "%d", sMoveInfo.dwDelayTime);
			ListView_SetItemText(hList, nIndex, 4, string);
			
			ComputeAllMoveInfo(hList); // 전부 재계산을 한다.	
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON2: // 수정버튼			
			sMoveInfo.nDirection = GetRadioCheck(hDlg); // 클릭된 버튼 체크
			nSelectIndex = ListView_GetNextItem( hList, -1, LVNI_SELECTED ); // 선택 인덱스
				
			// 컨트롤의 데이터를 가져오는 부분
			if(sMoveInfo.nDirection == STOP)
			{
				sMoveInfo.fVelocity = 0;
				sMoveInfo.nAllDistance = 0;
				GetDlgItemText(hDlg, IDC_EDIT5, string, 20); // 속도
				sMoveInfo.dwDelayTime = atoi(string);
			}else{
				GetDlgItemText(hDlg, IDC_EDIT1, string, 20); // 속도
				sMoveInfo.fVelocity = atof(string);
				GetDlgItemText(hDlg, IDC_EDIT2, string, 20); // 거리
				sMoveInfo.nAllDistance = atoi(string);				
				sMoveInfo.dwDelayTime = 0;
			}

			// 입력 받은 데이터를 리스트 컨트롤에 등록한다.
			ListView_SetItemText(hList, nSelectIndex, 1, g_strDirection[sMoveInfo.nDirection]);
			sprintf(string, "%.2f", sMoveInfo.fVelocity);
			ListView_SetItemText(hList, nSelectIndex, 2, string);
			sprintf(string, "%d", sMoveInfo.nAllDistance);
			ListView_SetItemText(hList, nSelectIndex, 3, string);
			sprintf(string, "%d", sMoveInfo.dwDelayTime);
			ListView_SetItemText(hList, nSelectIndex, 4, string);
			
			ComputeAllMoveInfo(hList); // 전부 재계산을 한다.
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;		
			
		case IDC_BUTTON6: // 삽입 버튼, 경로에 대한 재계산이 되어야 한다.
			sMoveInfo.nDirection = GetRadioCheck(hDlg); // 클릭된 버튼 체크			
			nSelectIndex = ListView_GetNextItem( hList, -1, LVNI_SELECTED ); // 선택 인덱스
				
			// 컨트롤의 데이터를 가져오는 부분
			if(sMoveInfo.nDirection == STOP)
			{
				sMoveInfo.fVelocity = 0;
				sMoveInfo.nAllDistance = 0;
				GetDlgItemText(hDlg, IDC_EDIT5, string, 20); // 속도
				sMoveInfo.dwDelayTime = atoi(string);
			}else{
				GetDlgItemText(hDlg, IDC_EDIT1, string, 20); // 속도
				sMoveInfo.fVelocity = atof(string);
				GetDlgItemText(hDlg, IDC_EDIT2, string, 20); // 거리
				sMoveInfo.nAllDistance = atoi(string);				
				sMoveInfo.dwDelayTime = 0;
			}

			InsertMoveInfo(hList, nSelectIndex, sMoveInfo);			
			ComputeAllMoveInfo(hList); // 전부 재계산을 한다.
			nCount = ListView_GetItemCount(hList); // 이동 경로의 개수 파악
			for(i = nSelectIndex ; i < nCount ; i++) // 순번을 다시 설정
			{
				sprintf(string, "%d", i);
				ListView_SetItemText(hList, i, 0, string);
			}
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON3: // 삭제버튼, 경로에 대한 재계산이 되어야 한다.
			nSelectIndex = ListView_GetNextItem( hList, -1, LVNI_SELECTED ); // 선택 인덱스
			nCount = ListView_GetItemCount(hList);
			for(i = nSelectIndex ; i < nCount ; i++) // 하위행도 같이 삭제			
				ListView_DeleteItem(hList, nSelectIndex); // 삭제되면 인덱스가 변경됨'
		
			InvalidateRect(hDlg, &rtBackGround, FALSE);
			break;

		case IDC_BUTTON4: // 렌더링 버튼
			// 리스트 컨트롤에 등록된 모든 데이터를 가져온다.
			bMoveFlag = !bMoveFlag;			
			if(bMoveFlag == FALSE)
			{
				// 초기화 한다.
				KillTimer(hDlg, 1);	
				InvalidateRect(hDlg, &rtBackGround, FALSE);				
				break;
			}else{ // 테스트 시작, 초기화 부분				
				fX = g_ptXY0.x;
				fY = g_ptXY0.y;				
				nMoveIndex = 0;
				fDistance = 0;
				dwElapsedTime = 0;
				dwStopElapsedTime = 0;
				dwOldTime = GetTickCount();
				fAddDistance = 0;				
				SetTimer(hDlg, 1, 20, NULL);				
				break;		
			}
		}
		return (INT_PTR)TRUE;

	case WM_TIMER:
		// 경과시간
		dwCurTime = GetTickCount();
		dwElapsedTime = dwCurTime - dwOldTime; // t1 - t0 경과시간		
		dwOldTime = dwCurTime;				
		nCount = ListView_GetItemCount(hList); //리스트의 전체 항목 수
		sMoveInfo = GetMoveInfo(hList, nMoveIndex); // 리스트에서 가져옴				

		if(sMoveInfo.nDirection == STOP) // STOP 상태일 때는 nX, nY가 바뀌지 않는다. 그러므로 이에대한 처리는 할 필요가 없다.
		{
			dwStopElapsedTime += dwElapsedTime;
			if(dwStopElapsedTime >= sMoveInfo.dwDelayTime) // 시간으로 다음을 결정
			{			
				dwStopElapsedTime = 0;		// <-- 요게 중요
				nMoveIndex = ++nMoveIndex % nCount;
				if(nMoveIndex == 0)
				{
					fX = g_ptXY0.x;
					fY = g_ptXY0.y;
				}
			}
		}else{
			if(fX == sMoveInfo.nDestX && fY == sMoveInfo.nDestY)
			{
				if(nMoveIndex + 1 == nCount )
				{
					fX = g_ptXY0.x;
					fY = g_ptXY0.y;
					nMoveIndex = 0;
				}else{
					nMoveIndex++;					
				}
			}else{
				fDistance = sMoveInfo.fVelocity * dwElapsedTime; // s = v*(t1-t0);				
				fAddDistance += fDistance;	
				if( (int)fAddDistance >= sMoveInfo.nAllDistance ) // 거리로 다음 이동경로를 결정
				{
					fX = sMoveInfo.nDestX;
					fY = sMoveInfo.nDestY;
					fAddDistance = 0.0f;								
				}else{
						switch(sMoveInfo.nDirection)
						{
						case TOP:
							fY -= fDistance;
							break;
						case RIGHT_TOP:
							fX += fDistance;
							fY -= fDistance;
							break; 
						case RIGHT:
							fX += fDistance;
							break;
						case RIGHT_DOWN:
							fX += fDistance;
							fY += fDistance;
							break; 
						case DOWN:					
							fY += fDistance;							
							break;	
						case LEFT_DOWN:
							fX -= fDistance;
							fY += fDistance;
							break;
						case LEFT:						
							fX -= fDistance;														
							break;
						case LEFT_TOP:						
							fX -= fDistance;
							fY -= fDistance;
							break;										
						}					
				}
			}	
		}		
		InvalidateRect(hDlg, &rtBackGround, FALSE);
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

// SpriteTool00.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Prsht.h>
#include <CommDlg.h>
#include <commctrl.h>
#include "SpriteTool00.h"
#include "Sprite.h"
#include <stdio.h>
#include <Windowsx.h>

#define MAX_LOADSTRING 100
#define CLIENT_WIDTH  800
#define CLIENT_HEIGHT 600

enum BOX_STATE { DRAG, CUT, NONE };

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.
char *g_strListMenu[] = {"순서", "x0", "y0", "x1", "y1" };
SIZE g_szWndSize; // 스크롤바에 의해 적용될 윈도우의 크기
SIZE g_szOrginMainWndize;  // 초기화 후에 변경하면 안된다. 클라이언트 영역이 800x600일 때 윈도우 크기이다.
HWND g_hWnd, g_hMenuWnd, g_hCutList, g_hCollisionList, g_hAniTimeList, g_hAniPartList;     
HCURSOR g_hTransparentCursor, g_hNormalCursor, g_hCrossCursor;
BOOL g_bIsBoxDraw, g_bIsTransColorChoice = FALSE;
BOOL g_bIsVScrollBar, g_bIsHScrollBar;
BOX_STATE g_nBoxState = NONE;
RECT g_rtCutRect, g_rtSprRect, g_rtMouseXY;
int g_nCutIndex = -1;
int g_nExpansion = 1, g_nSprIndex = -1;
int g_xMinScroll, g_xMaxScroll, g_yMinScroll, g_yMaxScroll;  
int g_xCurrentScroll, g_yCurrentScroll;
int g_nCurrentMode = 0;
int g_nRate = 1; // 좌표설정에서 사용하는 확대축소 비율
int g_nCollisionListIndex = 0; //충돌좌표 리스트 인덱스
int g_nAniSprIndex = 0; //에니메이션 리스트 컨트롤 선택 인덱스
int g_nAniRate = 1; //에니메이션 모드에서 확대 및 축소 
int g_nAniPartListIndex = -1;
DWORD g_dwOldTime = 0, g_dwAniTime;
RANGE g_sAniPartRange;

HDC g_hMemDC;
CSprite g_Sprite;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MenuDlg(HWND, UINT, WPARAM, LPARAM);

void Box( HDC hMemDC, RECT rtBox )
{			
	HBRUSH OldBrush, NullBrush;	

	NullBrush = (HBRUSH)GetStockObject( NULL_BRUSH );
	OldBrush  = (HBRUSH)SelectObject( hMemDC, NullBrush );	
	Rectangle( hMemDC, rtBox.left - 1, rtBox.top - 1, 
		       rtBox.right + 2 , rtBox.bottom + 2 );
	SelectObject( hMemDC, OldBrush );	 
}

// Note: 리스트 컨트롤을 설정하는 함수로 항목이 4개인 경우만 사용
RECT GetListData( HWND hList, int nIndex )
{
	RECT rect;
	char buffer[100];
	
	ListView_GetItemText( hList, nIndex, 1, buffer, 10 );
	rect.left = atoi( buffer );
	ListView_GetItemText( hList, nIndex, 2, buffer, 10 );
	rect.top	= atoi( buffer );
	ListView_GetItemText( hList, nIndex, 3, buffer, 10 );
	rect.right	= atoi( buffer );						
	ListView_GetItemText( hList, nIndex, 4, buffer, 10 );
	rect.bottom	= atoi( buffer );	

	return rect;
}

// Note: 메모리 DC를 생성하는 함수
HDC CreateMemDC(HWND hWnd, SIZE szSize)
{
	HDC hMemDC, hdc;
	hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, szSize.cx, szSize.cy);
	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap);				
	ReleaseDC(hWnd, hdc);
	return hMemDC;
}

int FileOpenDilaog(HWND hWnd, char *strFilePath, char* strFileName, char* strFilter)
{
	OPENFILENAME ofn;
	char strFileTitle[MAX_PATH] = {0,};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = "읽을 파일을 선택해 주세요";
	ofn.lpstrFileTitle = strFileName; // global, static 변수 사용
	ofn.lpstrFile = strFilePath; // global, static 변수
	ofn.lpstrFilter = strFilter;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;	

	if( GetOpenFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //선택이 안된 경우
}

int FileSaveDilaog(HWND hWnd, char *strFilePath, char* strFileName, char* strFilter)
{
	OPENFILENAME ofn;
	char strFileTitle[MAX_PATH] = {0,};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = "저장할 파일을 선택해 주세요";
	ofn.lpstrFileTitle = strFileName; // global, static 변수 사용
	ofn.lpstrFile = strFilePath; // global, static 변수
	ofn.lpstrFilter = strFilter;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrDefExt = "spr";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //선택이 안된 경우
}

// Note: 스크롤 윈도우의 스크롤바를 활성 또는 비활성시키는 함수
void ScrollProcess(HWND hWnd, int nImageWidth, int nImageHeight )
{
	RECT rect;
	// 가로 세로 크기가 이미지의 크기에 따라 스크롤바가 가변적이다.
	g_xCurrentScroll = 0;
	if( nImageWidth > CLIENT_WIDTH ) 
	{
		if( g_bIsHScrollBar )
		{ // 스크롤바 재설정
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(hWnd, SB_HORZ, TRUE);
			SetScrollRange(hWnd, SB_HORZ, g_xMinScroll, 
				           g_xMaxScroll, FALSE); 
			SetScrollPos(hWnd, SB_HORZ, 0, FALSE);
		}else{ // 스크롤바에 맞춰 윈도우 생성 및 스크롤바 설정			
			g_szWndSize.cy = g_szOrginMainWndize.cy + 17;		
					
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(hWnd, SB_HORZ, TRUE);
			SetScrollRange(hWnd, SB_HORZ, g_xMinScroll, 
				            g_xMaxScroll, FALSE); // 밑에서 InvalidateRect 하므로	
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
			g_bIsHScrollBar = TRUE;
		}					
	}else{ // 이미지가 클리이언트 영역보다 적은 경우
		if( g_bIsHScrollBar ) // 이전에 스크롤바가 있었다면 비활성으로, 윈도우 크기 조정
		{			
			ShowScrollBar(hWnd, SB_HORZ, FALSE); // 스크롤바 숨기기
			g_bIsHScrollBar = FALSE;
			g_szWndSize.cy = g_szOrginMainWndize.cy;
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
		}											
	}					

	g_yCurrentScroll = 0;
	if( nImageHeight > CLIENT_HEIGHT )
	{
		if( g_bIsVScrollBar )
		{
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(hWnd, SB_VERT, TRUE);
			SetScrollRange(hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); 
			SetScrollPos(hWnd, SB_VERT, 0, FALSE);
		}else{
			GetWindowRect(hWnd, &rect); // 높이가 달라지면 
			g_szWndSize.cx = rect.right - rect.left + 17;				
					
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(hWnd, SB_VERT, TRUE);
			SetScrollRange(hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); // 밑에서 InvalidateRect 하므로	
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
			g_bIsVScrollBar = TRUE;
		}
	}else{
		if(g_bIsVScrollBar)
		{
			ShowScrollBar(hWnd, SB_VERT, FALSE);
			g_bIsVScrollBar = FALSE;
			g_szWndSize.cx = g_szOrginMainWndize.cx;
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
		}
	}			
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SPRITETOOL00, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPRITETOOL00));

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPRITETOOL00));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SPRITETOOL00);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;   
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.   	  

   g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//

// Note: 에니 타임에 시간을 추가하는 함수
void AddAniTimeList(HWND hList, DWORD nAniTime)
{
	char string[100];
	LVITEM ITEM; 
	int nIndex = ListView_GetItemCount(hList);

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;	
	ITEM.iItem = nIndex; // Note: 추가 아이템 등록 인덱스 
	ITEM.iSubItem = 0;
	sprintf(string, "%d", nIndex );
	ITEM.pszText = string;
	ListView_InsertItem( g_hAniTimeList, &ITEM); // 순번등록					
	sprintf( string, "%d", g_Sprite.GetAniTime(nIndex) );
	ListView_SetItemText( g_hAniTimeList, nIndex, 1, string ); // 에니타임등록	
}

// Note: 지정된 인덱스에 힝목을 삽입하는 함수
void InsertListData( HWND hList, int nIndex, RECT rect )
{
	LVITEM ITEM; 
	char buffer[100];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nIndex; // Note: 추가 아이템 등록 인덱스 

	sprintf( buffer, "%d", nIndex );
	ITEM.pszText = buffer;
	ListView_InsertItem( hList, &ITEM);
	
	sprintf( buffer, "%d", rect.left );
	ListView_SetItemText( hList, nIndex, 1, buffer );

	sprintf( buffer, "%d", rect.top );
	ListView_SetItemText( hList, nIndex, 2, buffer );

	sprintf( buffer, "%d", rect.right );
	ListView_SetItemText( hList, nIndex, 3, buffer );

	sprintf( buffer, "%d", rect.bottom );
	ListView_SetItemText( hList, nIndex, 4, buffer );

	int nCount =  ListView_GetItemCount( hList );
	for(int i = nIndex + 1 ; i < nCount ; i++ )
	{
		sprintf( buffer, "%d", i );
		ListView_SetItemText( hList, i, 0, buffer );
	}
}

// Note: 리스트의 끝에 추가하는 함수
void AddListData( HWND hList, RECT rect )
{
	LVITEM ITEM; 
	char buffer[100];
	int nIndex = ListView_GetItemCount( hList );

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nIndex; // Note: 추가 아이템 등록 인덱스 

	sprintf( buffer, "%d", nIndex );
	ITEM.pszText = buffer;
	ListView_InsertItem( hList, &ITEM);
	
	sprintf( buffer, "%d", rect.left );
	ListView_SetItemText( hList, nIndex, 1, buffer );

	sprintf( buffer, "%d", rect.top );
	ListView_SetItemText( hList, nIndex, 2, buffer );

	sprintf( buffer, "%d", rect.right );
	ListView_SetItemText( hList, nIndex, 3, buffer );

	sprintf( buffer, "%d", rect.bottom );
	ListView_SetItemText( hList, nIndex, 4, buffer );	
}

// Note: 애니 구간 리스트에 항목을 삽입하는 함수
void InsertAniPartList(HWND hList, int nPartIndex, int nIndex0, int nIndex1)
{
	LVITEM ITEM; 
	char buffer[100];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nPartIndex; // Note: 추가 아이템 등록 인덱스 

	sprintf( buffer, "%d", nPartIndex );
	ITEM.pszText = buffer;
	ListView_InsertItem( hList, &ITEM);
	
	sprintf( buffer, "%d", nIndex0 );
	ListView_SetItemText( hList, nPartIndex, 1, buffer );

	sprintf( buffer, "%d", nIndex1 );
	ListView_SetItemText( hList, nPartIndex, 2, buffer );

	int nCount =  ListView_GetItemCount( hList );
	for(int i = nPartIndex + 1 ; i < nCount ; i++ )
	{
		sprintf( buffer, "%d", i );
		ListView_SetItemText( hList, i, 0, buffer );
	}
}

// Note: 자르기 리스트 컨트롤 초기화
void InitListType0(HWND hList)
{
	LVCOLUMN COL;

	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: 기초 상태 리스트 박스 셋팅
	COL.cx = 40;
	COL.pszText = "순서";
	COL.iSubItem = 0;
	SendMessage( hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

	COL.cx = 70;
	COL.pszText = "X0";
	COL.iSubItem = 1;
	SendMessage( hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );                  
        
	COL.cx = 70;
	COL.pszText = "Y0";                    
	COL.iSubItem = 2;
	SendMessage( hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL );				

	COL.cx = 70;
	COL.pszText = "X1";                    
	COL.iSubItem = 3;
	SendMessage( hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL );

	COL.cx = 70;
	COL.pszText = "Y1";                    
	COL.iSubItem = 4;
	SendMessage( hList, LVM_INSERTCOLUMN, 4, (LPARAM)&COL );
}

// Note: 에니 타입 리스트를 초기화하는 함수
void InitAniTimeListType(HWND hList)
{
	LVCOLUMN COL;
	
	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: 기초 상태 리스트 박스 셋팅
	COL.cx = 40;
	COL.pszText = "순서";
	COL.iSubItem = 0;
	SendMessage( hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

	COL.cx = 100;
	COL.pszText = "time";
	COL.iSubItem = 1;
	SendMessage( hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );   
}

// Note: 에니 구간 리스트를 초기화하는 함수
void InitAniPartListType(HWND hList)
{
	LVCOLUMN COL;

	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: 기초 상태 리스트 박스 셋팅
	COL.cx = 40;
	COL.pszText = "순서";
	COL.iSubItem = 0;
	SendMessage( hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

	COL.cx = 100;
	COL.pszText = "에니 Index0";
	COL.iSubItem = 1;
	SendMessage( hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );   

	COL.cx = 100;
	COL.pszText = "에니 Index1";
	COL.iSubItem = 2;
	SendMessage( hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL );   
}

// Note: 자르기 관련 컨트롤을 활성 및 비활성 시킴
void EnableCutCtrl(HWND hDlg, BOOL bEnable)
{
	Button_Enable( GetDlgItem(hDlg, IDC_BUTTON4), bEnable);
	ListBox_Enable(GetDlgItem(hDlg, IDC_LIST2), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON5), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON6), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON7), bEnable);	
}


// Note: 좌표 설정 컨트롤을 활성 및 비활성 시킴
void EnablePosCtrl(HWND hDlg, BOOL bEnable)
{
	Button_Enable( GetDlgItem(hDlg, IDC_RADIO4), bEnable);
	Button_Enable( GetDlgItem(hDlg, IDC_RADIO5), bEnable);
	Edit_Enable(GetDlgItem(hDlg, IDC_EDIT3), bEnable);
	Edit_Enable(GetDlgItem(hDlg, IDC_EDIT4), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON10), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON11), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON12), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON18), bEnable);
	ListBox_Enable(GetDlgItem(hDlg, IDC_LIST3), bEnable);	
}

// Note: 에니메이션 설정 컨트롤을 활성 및 비활성 시킴
void EnableAniCtrl(HWND hDlg, BOOL bEnable)
{
	Edit_Enable(GetDlgItem(hDlg, IDC_EDIT5), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON13), bEnable);	
	ListBox_Enable(GetDlgItem(hDlg, IDC_LIST4), bEnable);
	ListBox_Enable(GetDlgItem(hDlg, IDC_LIST5), bEnable);
	Edit_Enable(GetDlgItem(hDlg, IDC_EDIT6), bEnable);
	Edit_Enable(GetDlgItem(hDlg, IDC_EDIT7), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON14), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON15), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON16), bEnable);						
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON17), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON19), bEnable);						
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON20), bEnable);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	RECT rect, rtDlg, rtWnd = { 0, 0, 800, 600 };	
	static SIZE szDlgSize;	
	static int nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY;		
	static char strFilePath[MAX_PATH], strFileExtension[10], strFileName[100];	
	static char *strFilter = "비트맵(*.bmp)\0*.bmp\0스프라이트(*.spr)\0*.spr\0";
	static char *strFilter2 = "스프라이트(*.spr)\0*.spr\0";
	
	static HDC hBackBuffer;	// 백버퍼 DC
	static HDC hPosMemDC = NULL;
	SIZE szBitmapSize;
	HBITMAP hBitmap;		
	POINT ptPoint;
	
	int nCount, nX, nY, i, nResult, nIndex0, nIndex1, nWidth, nHeight;
	HDC hAniMemDC;
	DWORD dwCurTime;
	char string[100];

	switch (message)
	{
	case WM_CREATE:
		g_hMenuWnd = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG1), 
			                       hWnd, MenuDlg); 		
		
		AdjustWindowRect(&rtWnd, WS_OVERLAPPEDWINDOW, TRUE);
		GetWindowRect(g_hMenuWnd, &rtDlg);
		g_szOrginMainWndize.cx = g_szWndSize.cx = rtWnd.right - rtWnd.left;
		g_szOrginMainWndize.cy = g_szWndSize.cy = rtWnd.bottom - rtWnd.top ;		
		szDlgSize.cx = rtDlg.right - rtDlg.left;
		szDlgSize.cy = rtDlg.bottom - rtDlg.top;
		MoveWindow(hWnd, 100, 100, g_szWndSize.cx, g_szWndSize.cy, TRUE);
        MoveWindow(g_hMenuWnd, 100 + g_szWndSize.cx, 100, szDlgSize.cx, szDlgSize.cy, TRUE);			

		hdc = GetDC( hWnd );
		hBackBuffer = CreateCompatibleDC( hdc );
		hBitmap = CreateCompatibleBitmap( hdc, 800, 600 );
		SelectObject( hBackBuffer, (HBITMAP)hBitmap );		 
		DeleteObject( hBitmap );
		ReleaseDC( hWnd, hdc );	

		// 자르기 모드 초기화 부분	
		g_nCurrentMode = 0;
		CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 자르기 모드
		sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
		SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);	
		g_hTransparentCursor = LoadCursor( NULL, IDC_HAND ); // hInst가 아닌 NULL로 채워야 한다.
		g_hNormalCursor		 = LoadCursor( NULL, IDC_ARROW );
		g_hCrossCursor       = LoadCursor( NULL, IDC_CROSS);
		ShowScrollBar(hWnd, SB_VERT, FALSE);
		ShowScrollBar(hWnd, SB_HORZ, FALSE);	
		g_bIsVScrollBar = g_bIsHScrollBar = FALSE;
		g_xMinScroll = g_xMaxScroll = g_yMinScroll = g_yMaxScroll = 0;  
		g_xCurrentScroll = g_yCurrentScroll = 0;
		break;

	case WM_SIZE:
		GetWindowRect(hWnd, &rtWnd);
		MoveWindow(hWnd, rtWnd.left, rtWnd.top, g_szWndSize.cx, g_szWndSize.cy, TRUE);
		break;

	case WM_MOVE:
		GetWindowRect(hWnd, &rtWnd);	
		MoveWindow(hWnd, rtWnd.left, rtWnd.top, g_szWndSize.cx, g_szWndSize.cy, TRUE);
		MoveWindow(g_hMenuWnd, rtWnd.left + g_szWndSize.cx, rtWnd.top, szDlgSize.cx, szDlgSize.cy, TRUE);		
		break;

	case WM_SETCURSOR:
		if( g_bIsTransColorChoice )
			SetCursor( g_hTransparentCursor );
		else if( g_nCurrentMode == 1 && IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO4) == BST_CHECKED )
			SetCursor(g_hCrossCursor);
		else
			SetCursor( g_hNormalCursor );
		break;

	case WM_LBUTTONDOWN:
		if(g_nCurrentMode == 0 )
		{
			if( g_bIsTransColorChoice )
			{
				g_Sprite.GetTransColor(LOWORD(lParam) / g_nExpansion, HIWORD(lParam) / g_nExpansion); // 확대축소를 원래 좌표로 환산하여 입력
				g_bIsTransColorChoice = FALSE;

				sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);			
			}else{			
				nOldMouseX = nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; // 매크로 GET_X_LPARAM(), GET_Y_LPARAM()
				nOldMouseY = nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;		
				InvalidateRect( hWnd, NULL, FALSE );
			}
		}else if(g_nCurrentMode == 1){
			if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO4) == BST_CHECKED ) // 중심좌표
			{		
				nWidth = g_Sprite.GetSprWidth(g_nSprIndex); 
				nHeight = g_Sprite.GetSprHeight(g_nSprIndex);
				SetRect(&rect, 0, 0, nWidth, nHeight);		

				ptPoint.x = LOWORD(lParam) / g_nRate;
				ptPoint.y = HIWORD(lParam) / g_nRate;
				
				if(PtInRect(&rect, ptPoint))
				{
					g_Sprite.SetCenterPos(g_nSprIndex, ptPoint);				
					SetDlgItemInt( g_hMenuWnd, IDC_EDIT3, ptPoint.x, FALSE );
					SetDlgItemInt( g_hMenuWnd, IDC_EDIT4, ptPoint.y, FALSE );				
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			else if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED )
			{
				nWidth = g_Sprite.GetSprWidth(g_nSprIndex); 
				nHeight = g_Sprite.GetSprHeight(g_nSprIndex);
				SetRect(&rect, 0, 0, nWidth, nHeight);		
								
				g_bIsBoxDraw = FALSE;
				ptPoint.x = LOWORD(lParam) / g_nRate;
				ptPoint.y = HIWORD(lParam) / g_nRate;

				if(PtInRect(&rect, ptPoint))
				{
					g_rtMouseXY.left = g_rtMouseXY.right = ptPoint.x; 
					g_rtMouseXY.top = g_rtMouseXY.bottom = ptPoint.y;						
					InvalidateRect( hWnd, NULL, FALSE );
				}
			}
		}
		break;

	case WM_MOUSEMOVE : 					
		if( MK_LBUTTON & wParam ) // 마우스가 드래그 상태
		{			
			if(g_nCurrentMode == 0 ) //자르기 모드
			{
				g_nBoxState = DRAG;
				// 출력하려는 원본의 이미지 위치로 설정
				nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; 
				nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;							
				InvalidateRect( hWnd, NULL, FALSE );
			}else if(g_nCurrentMode == 1){ // 좌표 설정 모드 
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED)
				{
					nWidth = g_Sprite.GetSprWidth(g_nSprIndex); 
					nHeight = g_Sprite.GetSprHeight(g_nSprIndex);
					SetRect(&rect, 0, 0, nWidth, nHeight);	

					ptPoint.x = LOWORD(lParam) / g_nRate;
					ptPoint.y = HIWORD(lParam) / g_nRate;
					if(PtInRect(&rect, ptPoint))
					{
						g_rtMouseXY.right = ptPoint.x;
						g_rtMouseXY.bottom = ptPoint.y;					
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
			}
		}
		break;	

	case WM_LBUTTONUP:	// 최적의 영역 설정
		if(g_nCurrentMode == 0)
		{
			if( g_nBoxState == DRAG )
			{
				SetRect(&rect, nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY);
				g_rtSprRect = g_rtCutRect = g_Sprite.ScanBoxRect(rect);
				g_nBoxState = CUT;			
				InvalidateRect(hWnd, 0, FALSE);
			}
		}else if(g_nCurrentMode == 1){
			if(g_bIsBoxDraw)
			{
				g_bIsBoxDraw = FALSE; 
				InvalidateRect( hWnd, NULL, FALSE );
			}
		}
		break;

	case WM_HSCROLL: // LOWORD(wParam) 눌린 부위, HIWORD(wParam)은 위치
		if(LOWORD(wParam) == SB_THUMBTRACK) // 스크롤바의 눌린 위치, 스크롤 박스의 값이 들어온다.
		{			
			g_xCurrentScroll = HIWORD(wParam);			
			SetScrollPos(hWnd, SB_HORZ, g_xCurrentScroll, TRUE);
		}
		
		InvalidateRect(hWnd, 0, FALSE);
		break;	

	case WM_VSCROLL: // LOWORD(wParam) 눌린 부위, HIWORD(wParam)은 위치
		if(LOWORD(wParam) == SB_THUMBTRACK) // 스크롤 박스 이동에 대한 메시지
		{			
			g_yCurrentScroll = HIWORD(wParam);			
			SetScrollPos(hWnd, SB_VERT, g_yCurrentScroll, TRUE);
		}
	
		InvalidateRect(hWnd, 0, FALSE);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case ID_32771: // 파일 읽기
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter);	
			switch(nResult)
			{
			case 1: // 비트맵 읽기		
				g_Sprite.Release();
				g_Sprite.Init();

				g_Sprite.LoadBmpImage(hWnd, strFilePath, strFileName);
			
				// Note: 원본 이미지를 다룰 g_hMemDC 생성과 복사 부분
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(hWnd, g_Sprite.GetImageSize()); // 메모리DC 생성

				// 컨트롤 설정 부분
				// Note: 리스트 컨트롤 전부 지우기 
				ListView_DeleteAllItems(g_hCutList);
				ListView_DeleteAllItems(g_hCollisionList);
				ListView_DeleteAllItems(g_hAniTimeList);
				ListView_DeleteAllItems(g_hAniPartList);

				g_nSprIndex = -1;
				SetDlgItemText(g_hMenuWnd, IDC_EDIT1, g_Sprite.GetBmpFileName());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, ""); 
				CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 자르기 모드
				EnableCutCtrl(g_hMenuWnd, TRUE);
				EnablePosCtrl(g_hMenuWnd, FALSE);
				EnableAniCtrl(g_hMenuWnd, FALSE);
				ScrollProcess(hWnd, g_Sprite.GetImageSize().cx, g_Sprite.GetImageSize().cy);
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			case 2: // 스프라이트 읽기
				g_Sprite.Load(hWnd, strFilePath);
				g_Sprite.LoadBmpImage(hWnd);
				// Note: 원본 이미지를 다룰 g_hMemDC 생성과 복사 부분
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(hWnd, g_Sprite.GetImageSize()); // 메모리DC 생성						

				// 컨트롤 설정 부분
				// Note: 리스트 컨트롤 전부 지우기 
				ListView_DeleteAllItems(g_hCutList);
				ListView_DeleteAllItems(g_hCollisionList);
				ListView_DeleteAllItems(g_hAniTimeList);
				ListView_DeleteAllItems(g_hAniPartList);

				// Note:  이미지 파일명 설정
				SetDlgItemText(g_hMenuWnd, IDC_EDIT1, g_Sprite.GetBmpFileName());

				// Note: 투명색상 설정
				sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);

				// Note: 스프라이트 설정
				nCount = g_Sprite.GetSprCount();

				for(i = 0; i < nCount ; i++)
				{	// Note: 스프라이트 좌표 설정
					AddListData(g_hCutList, g_Sprite.GetSprRect(i));
					//Note: 에니 타임 설정 ==> 스프라이트와 같은 개수를 가지므로 
					AddAniTimeList(g_hAniTimeList, g_Sprite.GetAniTime(i));	
				}

				// Note: 최초 스프라이트 중심좌표 설정
				ptPoint = g_Sprite.GetCenterPos(0);
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT3, ptPoint.x, FALSE);
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT4, ptPoint.y, FALSE);

				// Note: 최초 충돌 좌표 설정						
				for(i = 0; i < g_Sprite.GetCollisionCount(0) ; i++)
					AddListData(g_hCollisionList, g_Sprite.GetCollisionRect(0, i));						
				
				//Note: 에니 구간 설정
				RANGE nRange;
				nCount = g_Sprite.GetAniRangeCount();
				for(i = 0; i < nCount ; i++)
				{
					nRange = g_Sprite.GetAniRange(i);
					InsertAniPartList(g_hAniPartList, i, nRange.nIndex0, nRange.nIndex1);
				}
				
				g_nSprIndex = 0;
				g_nAniPartListIndex = 0;
				g_nAniSprIndex = 0;				
				ScrollProcess(hWnd, g_Sprite.GetImageSize().cx, g_Sprite.GetImageSize().cy);
				SetWindowText(hWnd, strFileName); // 윈도우 타이틀 바에 스프라이트 파일명 출력
				CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 자르기 모드
				EnableCutCtrl(g_hMenuWnd, TRUE);
				EnablePosCtrl(g_hMenuWnd, FALSE);
				EnableAniCtrl(g_hMenuWnd, FALSE);
				InvalidateRect(hWnd, 0, FALSE);
				break;			
			}

			break;

		case ID_32772: // 파일 저장
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter2);	
			if(nResult != -1)
			{
				//에니메이션 정보 가져 올 것
				nCount = g_Sprite.GetSprCount();
				for(int i = 0; i < nCount ; i++)
				{
					ListView_GetItemText( g_hAniTimeList, i, 1, string, 10 );					
					g_Sprite.SetAniTime(i, atoi(string));
				}
				
				// 에니메이션 구간 정보 가져 올 것
				nCount = ListView_GetItemCount(g_hAniPartList);
				g_Sprite.CreateAniRange(nCount);
				for(int i = 0 ; i < nCount ; i++)
				{
					ListView_GetItemText( g_hAniPartList, i, 1, string, 10 );
					nIndex0 = atoi(string);
					ListView_GetItemText( g_hAniPartList, i, 2, string, 10 );
					nIndex1 = atoi(string);
					g_Sprite.SetAniRange(i, nIndex0, nIndex1);
				}

				g_Sprite.Save(strFilePath);
			}

			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_TIMER:
		dwCurTime = GetTickCount();		
		if( dwCurTime - g_dwOldTime >= g_dwAniTime )
		{
			g_dwOldTime = dwCurTime;
			g_nAniSprIndex++;
			if(g_nAniSprIndex > g_sAniPartRange.nIndex1)
				g_nAniSprIndex = g_sAniPartRange.nIndex0;			
		}

		InvalidateRect( hWnd, NULL, FALSE );
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		PatBlt( hBackBuffer, 0, 0, 800, 600, BLACKNESS ); // 배경 지우기

		switch(g_nCurrentMode)
		{
		case 0: // 자르기 모드
				if( g_Sprite.GetSrcImageDC() != NULL )
				{
					szBitmapSize = g_Sprite.GetImageSize();
					BitBlt(g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, g_Sprite.GetSrcImageDC(), 0, 0, SRCCOPY);

					// TODO: 여기에 그리기 코드를 추가합니다.		
					switch( g_nBoxState )
					{
					case DRAG:
						SetRect(&rect, nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY);
						SetROP2(g_hMemDC, R2_WHITE);
						Box(g_hMemDC, rect);
						break;	

					case CUT :				
						SetROP2( g_hMemDC, R2_WHITE );				
						Box(g_hMemDC, g_rtCutRect);		
					}	

					StretchBlt( hBackBuffer, -g_xCurrentScroll, -g_yCurrentScroll, 
						szBitmapSize.cx * g_nExpansion, szBitmapSize.cy * g_nExpansion,
						g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, SRCCOPY );			
				}

			break;
		case 1: // 좌표 설정 모드 
			if(g_Sprite.GetSprCount() > 0 )
			{
				nWidth = g_Sprite.GetSprWidth(g_nSprIndex);
				nHeight = g_Sprite.GetSprHeight(g_nSprIndex);

				if(hPosMemDC != NULL)
					DeleteDC(hPosMemDC);
				hPosMemDC = CreateCompatibleDC( hdc );
				hBitmap = CreateCompatibleBitmap( hdc, nWidth, nHeight ); 			 
				SelectObject( hPosMemDC, (HBITMAP)hBitmap );	// 모든 색상값이 0으로 설정된다.		
				DeleteObject( hBitmap );

				// 투명색상을 빼고 메모리DC로 복사한다.
				rect = g_Sprite.GetSprRect(g_nSprIndex);
				TransparentBlt( hPosMemDC, 0, 0, nWidth, nHeight, g_Sprite.GetSrcImageDC(), rect.left, rect.top,
					nWidth, nHeight, g_Sprite.GetTransColor() );		

				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO4) == BST_CHECKED) // 중심좌표
				{					
					ptPoint = g_Sprite.GetCenterPos(g_nSprIndex);
				
					SetROP2( hPosMemDC, R2_NOTXORPEN);
					MoveToEx( hPosMemDC, 0, ptPoint.y, NULL ); // 가로
					LineTo( hPosMemDC, rect.right, ptPoint.y );

					MoveToEx( hPosMemDC,  ptPoint.x, 0, NULL ); // 세로 상단 
					LineTo( hPosMemDC, ptPoint.x, rect.bottom);							
				}
				else if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED ) //충돌좌표
				{					
					SetROP2( hPosMemDC, R2_NOTXORPEN);
					Rectangle(hPosMemDC, g_rtMouseXY.left, g_rtMouseXY.top, g_rtMouseXY.right, g_rtMouseXY.bottom);

					SetROP2( hPosMemDC, R2_NOTXORPEN);
					nCount = ListView_GetItemCount( g_hCollisionList ); 				
					for(int i = 0 ; i < nCount ; i++)
					{
						rect = GetListData(g_hCollisionList, i);					
						Rectangle(hPosMemDC, rect.left, rect.top, rect.right, rect.bottom);						
					}

					// Note: 선택된 충돌좌표를 마스크하는 부분
					if(g_bIsBoxDraw)
					{
						SetROP2( hPosMemDC, R2_NOTMASKPEN);
						rect = GetListData(g_hCollisionList, g_nCollisionListIndex);					
						Rectangle(hPosMemDC, rect.left, rect.top, rect.right, rect.bottom);
					}
				}

				StretchBlt(hBackBuffer, 0, 0, nWidth*g_nRate, nHeight*g_nRate, hPosMemDC, 0, 0, nWidth, nHeight, SRCCOPY);	
			}			
			break;

		case 2: // 에니메이션 모드 
			nCount = ListView_GetItemCount(g_hAniTimeList);
			if(nCount > 0 ) // 스프라이트 로딩된 것임
			{
				nWidth = g_Sprite.GetSprWidth(g_nAniSprIndex);
				nHeight = g_Sprite.GetSprHeight(g_nAniSprIndex);
				rect = g_Sprite.GetSprRect(g_nAniSprIndex);
				
				ptPoint = g_Sprite.GetCenterPos(g_nAniSprIndex);
				nX = 400 - ptPoint.x*g_nAniRate;
				nY = 400 - ptPoint.y*g_nAniRate;			

				hAniMemDC = CreateCompatibleDC( hdc );
				hBitmap = CreateCompatibleBitmap( hdc, nWidth*g_nAniRate, nHeight*g_nAniRate ); //확대축소한 메모리DC 생성			 
				SelectObject( hAniMemDC, (HBITMAP)hBitmap );	// 모든 색상값이 0으로 설정된다.		
				DeleteObject( hBitmap );

				TransparentBlt( hAniMemDC, 0, 0, nWidth*g_nAniRate, nHeight*g_nAniRate, g_Sprite.GetSrcImageDC(), 
					            rect.left, rect.top, nWidth, nHeight, g_Sprite.GetTransColor()); 
				BitBlt(hBackBuffer, nX, nY, nWidth*g_nAniRate, nHeight*g_nAniRate, hAniMemDC, 0, 0, SRCCOPY);
				DeleteDC(hAniMemDC);
			}						

			SetBkColor(hBackBuffer, RGB(0,0,0));
			SetTextColor(hBackBuffer, RGB(10, 255, 10));
			sprintf(string, "에니 인덱스: %3d", g_nAniSprIndex);
			TextOut(hBackBuffer, 600, 10, string, strlen(string));
		
			SelectObject(hBackBuffer, GetStockObject(DC_PEN)); // 운영체제의 기본 펜을 셋팅해서 사용할 수 있다.
			SetDCPenColor(hBackBuffer, RGB(250, 0, 0));
			MoveToEx(hBackBuffer, 400, 0, NULL);
			LineTo(hBackBuffer, 400, 599);
			MoveToEx(hBackBuffer, 0, 400, NULL);
			LineTo(hBackBuffer, 799, 400);
			break;
		}

		BitBlt( hdc, 0, 0, 800, 600, hBackBuffer, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if(g_hMemDC != NULL)
			DeleteDC(g_hMemDC);

		if(hPosMemDC != NULL) //정적 변수이다.
			DeleteDC(hPosMemDC); 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK MenuDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{	
	static char strFilePath[MAX_PATH];
    static char strFileName[100];
	LVITEM ITEM; 
	int nCount, i;
	char buffer[100];
	SIZE szBmpSize;	
	static int nSelectedListIndex;
	RECT rect;
	int nResult;
	POINT ptCenterXY;
	LPNMHDR hdr;			
	LPNMITEMACTIVATE nia;
	DWORD dwAniTime;
	int nIndex0, nIndex1;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		g_hCutList = GetDlgItem(hDlg, IDC_LIST2);
		g_hCollisionList = GetDlgItem(hDlg, IDC_LIST3);
		g_hAniTimeList = GetDlgItem(hDlg, IDC_LIST4);
		g_hAniPartList = GetDlgItem(hDlg, IDC_LIST5);
		InitListType0(g_hCutList); // 자르기 리스트 컨트롤 초기화
		InitListType0(g_hCollisionList); // 자르기 리스트 컨트롤 초기화
		InitAniTimeListType(g_hAniTimeList);
		InitAniPartListType(g_hAniPartList);
		
		EnablePosCtrl(hDlg, FALSE);	 // 좌표 설정 컨트롤 비활성화			
		EnableAniCtrl(hDlg, FALSE); // 에니메이션 설정 컨트롤 비활성화
		return (INT_PTR)TRUE;

	case WM_NOTIFY: // 리스트 뷰가 선택되면 
		hdr = (LPNMHDR)lParam;

		switch(g_nCurrentMode)
		{
		case 0 :
				if(hdr->hwndFrom == g_hCutList)
				{
					if(hdr->code == NM_CLICK)
					{
						nCount =  ListView_GetItemCount( g_hCutList );
						if( nCount > 0 )
						{
							nResult = ListView_GetNextItem( g_hCutList, -1, LVNI_ALL | LVNI_SELECTED );			
							if( nResult != -1)
							{
								ListView_GetItemText( g_hCutList, nResult, 1, buffer, 10 );
								g_rtCutRect.left = atoi( buffer );
								ListView_GetItemText( g_hCutList, nResult, 2, buffer, 10 );
								g_rtCutRect.top	= atoi( buffer );
								ListView_GetItemText( g_hCutList, nResult, 3, buffer, 10 );
								g_rtCutRect.right	= atoi( buffer );					
								ListView_GetItemText( g_hCutList, nResult, 4, buffer, 10 );
								g_rtCutRect.bottom	= atoi( buffer );	
				
								g_nSprIndex = nResult;
								g_nBoxState = CUT;							
								InvalidateRect( g_hWnd, NULL, FALSE );	
							}
						}
					}
				}
				break;
		case 1: // 스프라이트 리스트가 인덱스가 바뀌면 충돌좌표와 중심좌표가 바뀐다.
				if(hdr->hwndFrom == g_hCutList)
				{
					if(hdr->code == NM_CLICK)
					{ 
						nResult = ListView_GetNextItem( g_hCutList, -1, LVNI_ALL | LVNI_SELECTED );			
						if( nResult != -1)
						{
							g_nSprIndex = nResult;
							// 중심좌표 설정
							ptCenterXY = g_Sprite.GetCenterPos(g_nSprIndex);
							SetDlgItemInt( g_hMenuWnd, IDC_EDIT3, ptCenterXY.x, FALSE );
							SetDlgItemInt( g_hMenuWnd, IDC_EDIT4, ptCenterXY.y, FALSE );
							//충돌좌표 설정
							ListView_DeleteAllItems(g_hCollisionList); 
							nCount = g_Sprite.GetCollisionCount(g_nSprIndex);
							for( i = 0 ; i < nCount ; i++ )
							{
								AddListData(g_hCollisionList, g_Sprite.GetCollisionRect(g_nSprIndex, i));										
							}

							// Note: XOR 펜 옵션 때문에 						
							SetRect(&g_rtMouseXY, -1, -1, -1, -1); //클리핑시킴							
						}
					}
				}

				if( hdr->hwndFrom == g_hCollisionList )
				{
					if( hdr->code == NM_CLICK )
					{
						nia = (LPNMITEMACTIVATE)lParam;	
						g_nCollisionListIndex = nia->iItem;	
						g_bIsBoxDraw = TRUE;												
					}
				}

				InvalidateRect( g_hWnd, NULL, FALSE );
				break;
		case 2:
				if(hdr->hwndFrom == g_hAniTimeList)
				{
					if(hdr->code == NM_CLICK)
					{ 
						nResult = ListView_GetNextItem( g_hAniTimeList, -1, LVNI_ALL | LVNI_SELECTED );			
						if( nResult != -1)
						{
							g_nAniSprIndex = nResult;
							SetDlgItemInt( g_hMenuWnd, IDC_EDIT5, g_Sprite.GetAniTime(g_nAniSprIndex), FALSE );
						}
					}
				}else if(hdr->hwndFrom == g_hAniPartList){
					if(hdr->code == NM_CLICK)
					{ 
						nResult = ListView_GetNextItem( g_hAniPartList, -1, LVNI_ALL | LVNI_SELECTED );			
						if( nResult != -1)
						{
							g_nAniPartListIndex = nResult;		
							ListView_GetItemText( g_hAniPartList, g_nAniPartListIndex, 1, buffer, 10 );
							SetDlgItemText(hDlg, IDC_EDIT6, buffer);
							g_nAniSprIndex = atoi(buffer);  // 첫 번째 스프라이트를 보여 준다.

							ListView_GetItemText( g_hAniPartList, g_nAniPartListIndex, 2, buffer, 10 );
							SetDlgItemText(hDlg, IDC_EDIT7, buffer);						
						}
					}
				}
				InvalidateRect( g_hWnd, NULL, FALSE );
				break;
		}
		
		return (INT_PTR)TRUE;

	case WM_COMMAND: 
			switch( LOWORD(wParam) )
			{
			case IDC_RADIO1: // 자르기 모드, 이전에 설정해 둔 형태로 출력 되어야 한다.
				// 스크롤 상태만 설정하면 된다.
				g_nCurrentMode = 0;
				szBmpSize = g_Sprite.GetImageSize();
				ScrollProcess( g_hWnd, szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);		
				EnableCutCtrl(hDlg, TRUE);	 // 자르기 툴 활성화	
				EnablePosCtrl(hDlg, FALSE);	 // 좌표 설정 컨트롤 비활성화			
				EnableAniCtrl(hDlg, FALSE); // 에니메이션 설정 컨트롤 비활성화	
				InvalidateRect(g_hWnd, NULL, FALSE);
				break;

			case IDC_RADIO2: // 좌표 설정 모드 
				// 자르기 모드의 리스트 컨트롤에 값일 있을 때만 동작한다.
				nCount = ListView_GetItemCount(g_hCutList);		
				if( nCount > 0 )
				{					
					// 좌표 설정 툴 모드 외에는 모두 비활성 시킨다.					
					g_nCurrentMode = 1;

					szBmpSize.cx = g_Sprite.GetSprHeight(g_nSprIndex);
					szBmpSize.cy = g_Sprite.GetSprWidth(g_nSprIndex);
					ScrollProcess( g_hWnd, szBmpSize.cx, szBmpSize.cy);					

					// 초기 셋팅
					SetDlgItemInt(hDlg, IDC_EDIT3, g_Sprite.GetCenterPos(g_nSprIndex).x, FALSE);
					SetDlgItemInt(hDlg, IDC_EDIT4, g_Sprite.GetCenterPos(g_nSprIndex).y, FALSE);

					EnableCutCtrl(hDlg, TRUE);
					EnablePosCtrl(hDlg, TRUE);	 
					EnableAniCtrl(hDlg, FALSE); // 에니메이션 설정 컨트롤 비활성화	

					CheckDlgButton(g_hMenuWnd, IDC_RADIO4, BST_CHECKED); // 중심좌표 설정 라디오버튼
					CheckDlgButton(g_hMenuWnd, IDC_RADIO5, BST_UNCHECKED); // 중심좌표 설정 라디오버튼
					SetCursor(g_hCrossCursor); //기본이 중심좌표 설정이므로
					InvalidateRect(g_hWnd, NULL, FALSE);
				}else{ // 스프라이트가 없으므로 이전 모드를 다시 설정하도록 한다.
					
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 자르기 모드
					CheckDlgButton(g_hMenuWnd, IDC_RADIO2, BST_UNCHECKED); // 좌표 모드
					CheckDlgButton(g_hMenuWnd, IDC_RADIO3, BST_UNCHECKED); // 에니 모드					
				}
				break;

			case IDC_RADIO3: // 에니메이션 모드
				nCount = ListView_GetItemCount(g_hCutList);		
				if( nCount > 0 )
				{		
					g_nCurrentMode = 2;				
					EnableCutCtrl(hDlg, FALSE); //자르기 컨트롤 비활성화
					EnablePosCtrl(hDlg, FALSE);	// 좌표 설정 컨트롤 비활성화		
					EnableAniCtrl(hDlg, TRUE);  // 에니메이션 설정 컨트롤 비활성화

					ListView_DeleteAllItems(g_hAniTimeList);
					ITEM.mask = LVIF_TEXT;
					ITEM.state = 0;
					ITEM.stateMask = 0;
				
					nCount = g_Sprite.GetSprCount();
					for(i = 0 ; i < nCount ; i++)
						AddAniTimeList(g_hAniTimeList, g_Sprite.GetAniTime(i));					
				
					g_nAniSprIndex = 0;
					InvalidateRect(g_hWnd, NULL, FALSE);
				}else{
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 자르기 모드
					CheckDlgButton(g_hMenuWnd, IDC_RADIO2, BST_UNCHECKED); // 좌표 모드
					CheckDlgButton(g_hMenuWnd, IDC_RADIO3, BST_UNCHECKED); // 에니 모드
				}
				break;

			case IDC_BUTTON2: // 확대 버튼
				if(g_Sprite.GetSrcImageDC() != NULL )
				{
					switch(g_nCurrentMode)
					{
					case 0: // 자르기 확대
						g_nExpansion++;		
						szBmpSize = g_Sprite.GetImageSize();
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);	
						break;
					case 1: // 좌표 설정 확대
						g_nRate++;
						szBmpSize.cx = g_Sprite.GetSprWidth(g_nSprIndex);
						szBmpSize.cy = g_Sprite.GetSprHeight(g_nSprIndex);
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nRate, szBmpSize.cy * g_nRate);
						break;
					case 2: // 에니메이션 확대
						g_nAniRate++;
						szBmpSize.cx = g_Sprite.GetSprWidth(g_nAniSprIndex);
						szBmpSize.cy = g_Sprite.GetSprHeight(g_nAniSprIndex);
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nAniRate, szBmpSize.cy * g_nAniRate);
						break;
					}								
					InvalidateRect(g_hWnd, NULL, FALSE);
				}else{
					MessageBox(g_hWnd, "이미지가 없습니다", "오류", MB_OK);
				}
				return (INT_PTR)TRUE;

			case IDC_BUTTON3: // 축소 버튼
				if(g_Sprite.GetSrcImageDC() == NULL )
				{
				   MessageBox(g_hWnd, "이미지가 없습니다", "오류", MB_OK);
				   break;
				}

				switch(g_nCurrentMode)
				{
				case 0:
						if( g_nExpansion - 1 < 1 )
							g_nExpansion = 1;
						else
							g_nExpansion--;

						szBmpSize = g_Sprite.GetImageSize();
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);
						InvalidateRect(g_hWnd, 0, FALSE);
						break;
				case 1:
						if( g_nRate - 1 < 1 )
							g_nRate = 1;
						else
							g_nRate--;
						
						InvalidateRect(g_hWnd, 0, FALSE);						
						break;
				case 2:
						if( g_nAniRate - 1 < 1 )
							g_nAniRate = 1;
						else
							g_nAniRate--;			

						InvalidateRect(g_hWnd, 0, FALSE);	
						break;
				}
				return (INT_PTR)TRUE;

			case IDC_BUTTON4: // 투명값 얻기 버튼
				if(g_Sprite.GetSrcImageDC() == NULL )
				{
				   MessageBox(g_hWnd, "이미지가 없습니다", "오류", MB_OK);
				   break;
				}

				g_bIsTransColorChoice = TRUE;
				g_nBoxState = NONE;		
				InvalidateRect(g_hWnd, 0, FALSE);
				return (INT_PTR)TRUE;

			case IDC_BUTTON5:  // 자른 좌표 등록 버튼				
				AddListData(g_hCutList, g_rtCutRect);							
				g_Sprite.AddCutRect(g_rtCutRect);
				if(g_nSprIndex == -1)
					g_nSprIndex = 0;

				return (INT_PTR)TRUE;

			case IDC_BUTTON6: // 스프라이트 리스트 항목 삽입
				if( g_nSprIndex == -1 )
					MessageBox( hDlg, "삽입할 항목을 먼저 선택해 주세요", "주의", MB_OK );
				else
				{
					InsertListData(g_hCutList, g_nSprIndex, g_rtSprRect);						
					g_Sprite.InsertCutRect(g_nSprIndex, g_rtSprRect);
				}
					
				return (INT_PTR)TRUE;

			case IDC_BUTTON7: // 스프라이트 리스트 항목 삭제	
				if( g_Sprite.GetSprCount() <= 0 )
					MessageBox( hDlg, "삭제할 항목을 먼저 선택해 주세요", "주의", MB_OK );
				else
				{				
					g_Sprite.DeleteCutRect(g_nSprIndex);
					ListView_DeleteItem( g_hCutList, g_nSprIndex );					
					nCount =  ListView_GetItemCount( g_hCutList );
					for( i = g_nSprIndex ; i < nCount ; i++ )
					{
						sprintf( buffer, "%d", i );
						ListView_SetItemText( g_hCutList, i, 0, buffer );
					}
				}

				g_nBoxState = NONE;
				InvalidateRect(g_hWnd, 0, FALSE);
				return (INT_PTR)TRUE;
			//-------------------- 좌표 설정 메뉴 부분 ----------------------------
			case IDC_BUTTON10: // 중심좌표 적용 버튼
				ptCenterXY.x = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
				ptCenterXY.y = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
				g_Sprite.SetCenterPos(g_nSprIndex, ptCenterXY);
				InvalidateRect(g_hWnd, 0, FALSE);
				return (INT_PTR)TRUE;
			case IDC_BUTTON11: // 충돌 좌표 등록
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED && g_nSprIndex >= 0 )
				{										
					AddListData(g_hCollisionList, g_rtMouseXY);		

					// Note: XOR 펜 옵션 때문에 						
					SetRect(&g_rtMouseXY, -1, -1, -1, -1); //클리핑시킴
					InvalidateRect( g_hWnd, NULL, FALSE );
				}
				return (INT_PTR)TRUE;
			case IDC_RADIO4:
				SetCursor(g_hCrossCursor);
				InvalidateRect( g_hWnd, NULL, FALSE );
				return (INT_PTR)TRUE;

			case IDC_RADIO5: //충돌 좌표 선택
				SetCursor(g_hNormalCursor);
				InvalidateRect( g_hWnd, NULL, FALSE );
				return (INT_PTR)TRUE;

			case IDC_BUTTON12: // 삭제 부분
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED )
				{	//리스트에 내용이 없으면 -1을 리턴한다.				
					nResult = ListView_GetNextItem( g_hCollisionList, -1, LVNI_ALL | LVNI_SELECTED );				

					if( nResult == -1 )
						MessageBox( hDlg, "삭제할 항목을 먼저 선택해 주세요", "주의", MB_OK );
					else
					{								
						ListView_DeleteItem(g_hCollisionList, nResult);
						nCount = ListView_GetItemCount(g_hCollisionList);						
						
						for( i = nResult ; i < nCount ; i++ ) // 삭제후에 순번을 새로 고침
						{
							sprintf(buffer, "%d", i);
							ListView_SetItemText(g_hCollisionList, i, 0, buffer); 			
						}
						
						InvalidateRect( g_hWnd, NULL, FALSE );
					}
				}
				return (INT_PTR)TRUE;

			case IDC_BUTTON18: // 충돌 좌표 적용 부분
				nCount = ListView_GetItemCount(g_hCollisionList);
				if( nCount > 0 && g_nSprIndex != -1)
				{
					g_Sprite.CreateCollisionRect(g_nSprIndex, nCount);					
					for(i = 0 ; i < nCount ; i++)
					{
						rect = GetListData(g_hCollisionList, i);
						g_Sprite.SetCollisionRect(g_nSprIndex, i, rect);											
					}
				}
				
				return (INT_PTR)TRUE;

			case IDC_BUTTON13: // 에니 타임 적용 버튼
				nCount = ListView_GetItemCount(g_hAniTimeList);
				if( nCount > 0 )
				{					
					dwAniTime = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
					sprintf(buffer, "%d", dwAniTime);					
					ListView_SetItemText( g_hAniTimeList, g_nAniSprIndex, 1, buffer );
					g_Sprite.SetAniTime(g_nAniSprIndex, dwAniTime);
				}

				return (INT_PTR)TRUE;
			case IDC_BUTTON14: // 등록
				nCount = ListView_GetItemCount(g_hAniPartList);
				nIndex0 = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
				nIndex1 = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);
				InsertAniPartList(g_hAniPartList, nCount, nIndex0, nIndex1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON15: // 삽입
				nIndex0 = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
				nIndex1 = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);
				InsertAniPartList(g_hAniPartList, g_nAniPartListIndex, nIndex0, nIndex1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON17: // 삭제
				ListView_DeleteItem( g_hAniPartList, g_nAniSprIndex );					
				nCount =  ListView_GetItemCount( g_hAniPartList );
				for( i = g_nAniSprIndex ; i < nCount ; i++ )
				{
					sprintf( buffer, "%d", i );
					ListView_SetItemText( g_hAniPartList, i, 0, buffer );
				}

				return (INT_PTR)TRUE;

			case IDC_BUTTON19: // 플레이
				g_dwOldTime = GetTickCount();
				
				// AniPartList에 있는 에니메이션 구간과 시간을 가져올 것
				ListView_GetItemText(g_hAniPartList, g_nAniPartListIndex, 1, buffer, 10 );
				g_sAniPartRange.nIndex0 = atoi( buffer );
				ListView_GetItemText(g_hAniPartList, g_nAniPartListIndex, 2, buffer, 10 );
				g_sAniPartRange.nIndex1 = atoi( buffer );
				
				// 에니메이션을 하기 위한 첫 번째 인덱스를 설정
				ListView_GetItemText( g_hAniTimeList, g_sAniPartRange.nIndex0, 1, buffer, 10 );
				g_dwAniTime = atoi(buffer);			
				g_nAniSprIndex = g_sAniPartRange.nIndex0;	
								
				SetTimer(g_hWnd, 1, 16, NULL);
				InvalidateRect(g_hWnd, NULL, FALSE);
				return (INT_PTR)TRUE;

			case IDC_BUTTON20: // 정지
				KillTimer(g_hWnd, 1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON16: // 수정
				nIndex0 = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
				nIndex1 = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);					
				sprintf(buffer, "%d", nIndex0);					
				ListView_SetItemText( g_hAniPartList, g_nAniPartListIndex, 1, buffer );
				sprintf(buffer, "%d", nIndex1);					
				ListView_SetItemText( g_hAniPartList, g_nAniPartListIndex, 2, buffer );
				return (INT_PTR)TRUE;
			}		
	
		break;
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
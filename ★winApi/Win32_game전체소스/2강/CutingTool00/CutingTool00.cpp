// CutingTool00.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "CutingTool00.h"
#include <CommDlg.h>
#include <commctrl.h>
#include "CutImage.h"
#include <stdio.h>

#define CLIENT_WIDTH  800
#define CLIENT_HEIGHT 600

#define MAX_LOADSTRING 100

enum BOX_STATE { DRAG, CUT, NONE };

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.
HWND g_hWnd, g_hMenuWnd, g_hCutPosList;
SIZE g_szMainWnd;
HDC g_hMemDC;
BOX_STATE g_nBoxState = NONE;
RECT g_rtCutRect;

CCutImage g_CutImage;
int g_nExpansion = 1;
BOOL g_bIsTransColorChoice = FALSE;
HCURSOR g_hTransparentCursor, g_hCrossCursor;
int g_nSprIndex = 0;

int g_xMinScroll, g_xMaxScroll, g_yMinScroll, g_yMaxScroll;  
int g_xCurrentScroll, g_yCurrentScroll;
SIZE g_szWndSize; // 스크롤바에 의해 적용될 윈도우의 크기
SIZE g_szOrginMainWndize;  // 초기화한 후에 변경하면 안된다. 클라이언트 영역이 800x600일 때 윈도우 크기이다.
BOOL g_bIsVScrollBar, g_bIsHScrollBar;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MenuDlg(HWND, UINT, WPARAM, LPARAM);
void ScrollProcess( int , int );

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
	LoadString(hInstance, IDC_CUTINGTOOL00, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CUTINGTOOL00));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CUTINGTOOL00));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CUTINGTOOL00);
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
   g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
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
int FileOpenDilaog(HWND hWnd, char *strFilePath, char* strFileName, char* strFilter, char *strDefExt)
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
	ofn.lpstrDefExt = strDefExt;

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
	ofn.lpstrDefExt = "cut";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //선택이 안된 경우
}

void Box( HDC hMemDC, RECT rtBox )
{			
	HBRUSH OldBrush, NullBrush;	

	NullBrush = (HBRUSH)GetStockObject( NULL_BRUSH );
	OldBrush  = (HBRUSH)SelectObject( hMemDC, NullBrush );	
	Rectangle( hMemDC, rtBox.left, rtBox.top, 
		       rtBox.right + 1 , rtBox.bottom + 1 );
	SelectObject( hMemDC, OldBrush );	 
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rtWnd = { 0, 0, 800, 600 }, rtDlg, rect = { 0, };	
	static SIZE szDlgSize;	
	static char strFilePath[MAX_PATH], strFileName[100];
	SIZE szBitmapSize;
	static int nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY;
	char buffer[100];	
	static char strFilter[] = "자른 파일(*.cut)\0*.cut\0";
	int nCount;

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

		g_hTransparentCursor = LoadCursor( NULL, IDC_HAND ); // hInst가 아닌 NULL로 채워야 한다.
		g_hCrossCursor		 = LoadCursor( NULL, IDC_ARROW );

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
		else
			SetCursor( g_hCrossCursor );
		break;

	case WM_LBUTTONDOWN:
		if( g_bIsTransColorChoice )
		{
			g_CutImage.GetTransColor(LOWORD(lParam) / g_nExpansion, HIWORD(lParam) / g_nExpansion);
			g_bIsTransColorChoice = FALSE;

			SetDlgItemInt(g_hMenuWnd, IDC_EDIT2, g_CutImage.GetTransRed(), FALSE);
			SetDlgItemInt(g_hMenuWnd, IDC_EDIT3, g_CutImage.GetTransGreen(), FALSE);
			SetDlgItemInt(g_hMenuWnd, IDC_EDIT4, g_CutImage.GetTransBlue(), FALSE);
		}else{			
			nOldMouseX = nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; // 매크로 GET_X_LPARAM(), GET_Y_LPARAM()
			nOldMouseY = nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;	
			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT5, nOldMouseX, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT6, nOldMouseY, FALSE );			

			InvalidateRect( hWnd, NULL, FALSE );
		}
		break;

	case WM_MOUSEMOVE : 					
		if( MK_LBUTTON & wParam ) // 마우스가 드래그 상태
		{			
			g_nBoxState = DRAG;
			// 출력하려는 원본의 이미지 위치로 설정
			nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; 
			nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;				
			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT7, nNewMouseX, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT8, nNewMouseY, FALSE );		
			InvalidateRect( hWnd, NULL, FALSE );			
		}
		break;	

	case WM_LBUTTONUP:	// 최적의 영역 설정
		if( g_nBoxState == DRAG )
		{
			SetRect(&rect, nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY);
			g_rtCutRect = g_CutImage.ScanBoxRect(rect);
			g_nBoxState = CUT;

			SetDlgItemInt( g_hMenuWnd, IDC_EDIT5, g_rtCutRect.left, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT6, g_rtCutRect.top, FALSE );	
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT7, g_rtCutRect.right, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT8, g_rtCutRect.bottom, FALSE );	
			InvalidateRect(hWnd, 0, FALSE);
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
			SetScrollPos(hWnd, SB_VERT, 
				          g_yCurrentScroll, TRUE);
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
			
			if( FileOpenDilaog( hWnd, strFilePath, strFileName, strFilter, "cut" ) != -1 )
			{
				g_CutImage.LoadCutInfo(hWnd, strFilePath);

				// 읽은 데이터를 컨트롤에 설정하는 부분
				SetDlgItemText( g_hMenuWnd, IDC_EDIT1, g_CutImage.GetBmpFileName() );									
				SetDlgItemInt( g_hMenuWnd, IDC_EDIT2, g_CutImage.GetTransRed(), FALSE );								
				SetDlgItemInt( g_hMenuWnd, IDC_EDIT3, g_CutImage.GetTransGreen(), FALSE );								
				SetDlgItemInt( g_hMenuWnd, IDC_EDIT4, g_CutImage.GetTransBlue(), FALSE );
				g_nBoxState = NONE;

				ListView_DeleteAllItems(g_hCutPosList);
				nCount = g_CutImage.GetSprCount();

				for( int i = 0 ; i < nCount ; i++ )
				{
					LVITEM ITEM; 
					ITEM.mask = LVIF_TEXT;
					ITEM.state = 0;
					ITEM.stateMask = 0;
					ITEM.iSubItem = 0;		 
					ITEM.iItem = i; // Note: 추가 아이템 등록 인덱스 

					sprintf( buffer, "%d", i );
					ITEM.pszText = buffer;
					ListView_InsertItem( g_hCutPosList, &ITEM);	
					rect = g_CutImage.GetSprRect(i);
					sprintf( buffer, "%d", rect.left );
					ListView_SetItemText( g_hCutPosList, i, 1, buffer );

					sprintf( buffer, "%d", rect.top );
					ListView_SetItemText( g_hCutPosList, i, 2, buffer );

					sprintf( buffer, "%d", rect.right );
					ListView_SetItemText( g_hCutPosList, i, 3, buffer );

					sprintf( buffer, "%d", rect.bottom );
					ListView_SetItemText( g_hCutPosList, i, 4, buffer );		
				}		

				SIZE szImageSize = g_CutImage.GetImageSize();
				// Note: 원본 이미지를 다룰 g_hMemDC 생성과 복사 부분
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(g_hWnd, szImageSize); // 메모리DC 생성

				ScrollProcess(szImageSize.cx, szImageSize.cy);	
				g_nExpansion = 1;
				g_xCurrentScroll = 0;
				g_yCurrentScroll = 0;		

				InvalidateRect( hWnd, NULL, TRUE );					
			}
			break;

		case ID_32772: // 파일 저장
			if( FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter ) != -1 )
			{	// 저장파일 형식이 한 가지이므로 파일 선택 인덱스를 조사할 필요가 없다.				
				nCount = ListView_GetItemCount(g_hCutPosList);
				g_CutImage.SetSprCount(nCount);
				g_CutImage.CreateCutRect();
				
				for( int i = 0 ; i < nCount ; i++ )
				{
					ListView_GetItemText( g_hCutPosList, i, 1, buffer, 10 );
					rect.left = atoi( buffer );
					ListView_GetItemText( g_hCutPosList, i, 2, buffer, 10 );
					rect.top	= atoi( buffer );
					ListView_GetItemText( g_hCutPosList, i, 3, buffer, 10 );
					rect.right	= atoi( buffer );						
					ListView_GetItemText( g_hCutPosList, i, 4, buffer, 10 );
					rect.bottom	= atoi( buffer );				
					g_CutImage.SetSprRect(i, rect);
				}

				g_CutImage.SaveCutInfo(strFilePath);
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

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		if( g_CutImage.GetSrcImageDC() != NULL )
		{
			szBitmapSize = g_CutImage.GetImageSize();
			BitBlt(g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, g_CutImage.GetSrcImageDC(), 0, 0, SRCCOPY);

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

			StretchBlt( hdc, -g_xCurrentScroll, -g_yCurrentScroll, 
				szBitmapSize.cx * g_nExpansion, szBitmapSize.cy * g_nExpansion,
				g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, SRCCOPY );			
		}
		
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		if(g_hMemDC != NULL)
			DeleteDC(g_hMemDC);

		DestroyWindow(g_hMenuWnd);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void ScrollProcess( int nImageWidth, int nImageHeight )
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
			ShowScrollBar(g_hWnd, SB_HORZ, TRUE);
			SetScrollRange(g_hWnd, SB_HORZ, g_xMinScroll, 
				           g_xMaxScroll, FALSE); 
			SetScrollPos(g_hWnd, SB_HORZ, 0, FALSE);
		}else{ // 스크롤바에 맞춰 윈도우 생성 및 스크롤바 설정			
			g_szWndSize.cy = g_szOrginMainWndize.cy + 17;		
					
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_HORZ, TRUE);
			SetScrollRange(g_hWnd, SB_HORZ, g_xMinScroll, 
				            g_xMaxScroll, FALSE); // 밑에서 InvalidateRect 하므로	
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
			g_bIsHScrollBar = TRUE;
		}					
	}else{ // 이미지가 클리이언트 영역보다 적은 경우
		if( g_bIsHScrollBar ) // 이전에 스크롤바가 있었다면 비활성으로, 윈도우 크기 조정
		{			
			ShowScrollBar(g_hWnd, SB_HORZ, FALSE); // 스크롤바 숨기기
			g_bIsHScrollBar = FALSE;
			g_szWndSize.cy = g_szOrginMainWndize.cy;
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
		}											
	}					

	g_yCurrentScroll = 0;
	if( nImageHeight > CLIENT_HEIGHT )
	{
		if( g_bIsVScrollBar )
		{
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_VERT, TRUE);
			SetScrollRange(g_hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); 
			SetScrollPos(g_hWnd, SB_VERT, 0, FALSE);
		}else{
			GetWindowRect(g_hWnd, &rect); // 높이가 달라지면 
			g_szWndSize.cx = rect.right - rect.left + 17;				
					
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_VERT, TRUE);
			SetScrollRange(g_hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); // 밑에서 InvalidateRect 하므로	
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
			g_bIsVScrollBar = TRUE;
		}
	}else{
		if(g_bIsVScrollBar)
		{
			ShowScrollBar(g_hWnd, SB_VERT, FALSE);
			g_bIsVScrollBar = FALSE;
			g_szWndSize.cx = g_szOrginMainWndize.cx;
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // 크기와 위치 재조정
		}
	}			
}

// 메뉴 대화상자 입니다.
INT_PTR CALLBACK MenuDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static char strFilePath[MAX_PATH];
    static char strFileName[100];
	LVCOLUMN COL;
	LVITEM ITEM; 
	int idx, nCount, i;
	char buffer[100];
	SIZE szBmpSize;	

	switch (message)
	{
	case WM_INITDIALOG:
		g_hCutPosList = GetDlgItem( hDlg, IDC_LIST1 );
		ListView_SetExtendedListViewStyle( g_hCutPosList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt  = LVCFMT_CENTER;

		// Note: 기초 상태 리스트 박스 셋팅
		COL.cx = 40;
		COL.pszText = "순서";
		COL.iSubItem = 0;
		SendMessage( g_hCutPosList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

		COL.cx = 50;
		COL.pszText = "X0";
		COL.iSubItem = 1;
		SendMessage( g_hCutPosList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );                  
        
		COL.cx = 50;
		COL.pszText = "Y0";                    
		COL.iSubItem = 2;
		SendMessage( g_hCutPosList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL );				

		COL.cx = 50;
		COL.pszText = "X1";                    
		COL.iSubItem = 3;
		SendMessage( g_hCutPosList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL );

		COL.cx = 50;
		COL.pszText = "Y1";                    
		COL.iSubItem = 4;
		SendMessage( g_hCutPosList, LVM_INSERTCOLUMN, 4, (LPARAM)&COL );
		return (INT_PTR)TRUE;

	case WM_NOTIFY: // 리스트 뷰가 선택되면 
		nCount =  ListView_GetItemCount( g_hCutPosList );
		if( nCount > 0 )
		{
			g_nSprIndex = ListView_GetNextItem( g_hCutPosList, -1, LVNI_ALL | LVNI_SELECTED );
			if( g_nSprIndex != -1)
			{
				ListView_GetItemText( g_hCutPosList, g_nSprIndex, 1, buffer, 10 );
				g_rtCutRect.left = atoi( buffer );
				ListView_GetItemText( g_hCutPosList, g_nSprIndex, 2, buffer, 10 );
				g_rtCutRect.top	= atoi( buffer );
				ListView_GetItemText( g_hCutPosList, g_nSprIndex, 3, buffer, 10 );
				g_rtCutRect.right	= atoi( buffer );					
				ListView_GetItemText( g_hCutPosList, g_nSprIndex, 4, buffer, 10 );
				g_rtCutRect.bottom	= atoi( buffer );	
				
				g_nBoxState = CUT;							
				InvalidateRect( g_hWnd, NULL, FALSE );	
			}
		}
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1: // 이미지 읽기 버튼
			if( FileOpenDilaog(hDlg, strFilePath, strFileName, "비트맵(*.bmp)\0*.bmp\0", "bmp") != -1 )
			{
				SetDlgItemText(hDlg, IDC_EDIT1, strFileName);		
				g_CutImage.LoadBmpImage(g_hWnd, strFileName); 
				szBmpSize = g_CutImage.GetImageSize();
				
				// Note: 원본 이미지를 다룰 g_hMemDC 생성과 복사 부분
				if(g_hMemDC != NULL)
					delete g_hMemDC;

				g_hMemDC = CreateMemDC(g_hWnd, szBmpSize); // 메모리DC 생성
				ScrollProcess(szBmpSize.cx, szBmpSize.cy);	
				g_nExpansion = 1;
				g_xCurrentScroll = 0;
				g_yCurrentScroll = 0;				
			}

			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // 확대 버튼
			g_nExpansion++;		
			szBmpSize = g_CutImage.GetImageSize();
			ScrollProcess(szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);				
			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON3: // 축소 버튼
			if( g_nExpansion - 1 < 1 )
				g_nExpansion = 1;
			else
				g_nExpansion--;

			szBmpSize = g_CutImage.GetImageSize();
			ScrollProcess(szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);
			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON4: // 투명색상 얻기 버튼
			g_bIsTransColorChoice = TRUE;
			g_nBoxState = NONE;		
			InvalidateRect(g_hWnd, 0, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON5:  // 자른 좌표 등록 버튼
			ITEM.mask = LVIF_TEXT;
			ITEM.state = 0;
			ITEM.stateMask = 0;
			ITEM.iSubItem = 0;		 

			idx = ListView_GetItemCount( g_hCutPosList );  
			ITEM.iItem = idx; // Note: 추가 아이템 등록 인덱스 

			sprintf( buffer, "%d", idx );
			ITEM.pszText = buffer;
			ListView_InsertItem( g_hCutPosList, &ITEM);	
			
			GetDlgItemText( hDlg, IDC_EDIT5, buffer, 10 );
			ListView_SetItemText( g_hCutPosList, idx, 1, buffer );

			GetDlgItemText( hDlg, IDC_EDIT6, buffer, 10 );
			ListView_SetItemText( g_hCutPosList, idx, 2, buffer );

			GetDlgItemText( hDlg, IDC_EDIT7, buffer, 10 );
			ListView_SetItemText( g_hCutPosList, idx, 3, buffer );

			GetDlgItemText( hDlg, IDC_EDIT8, buffer, 10 );
			ListView_SetItemText( g_hCutPosList, idx, 4, buffer );	
			
			return (INT_PTR)TRUE;

		case IDC_BUTTON6:  // 좌표 삭제 버튼
			// Note: GetNextItem()은 선택된 항목을 찾아 주는 함수이다. 
			idx = ListView_GetNextItem( g_hCutPosList, -1, LVNI_ALL | LVNI_SELECTED );

			if( idx == -1 )
				MessageBox( hDlg, "삭제할 항목을 먼저 선택해 주세요", "주의", MB_OK );
			else
			{
				ListView_DeleteItem( g_hCutPosList, idx );
				nCount =  ListView_GetItemCount( g_hCutPosList );
				for( i = idx ; i < nCount ; i++ )
				{
					sprintf( buffer, "%d", i );
					ListView_SetItemText( g_hCutPosList, i, 0, buffer );
				}
			}

			g_nBoxState = NONE;
			InvalidateRect(g_hWnd, 0, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON7:  // 좌표 삽입 버튼
			idx = ListView_GetNextItem( g_hCutPosList, -1, LVNI_ALL | LVNI_SELECTED );

			if( idx == -1 )
				MessageBox( hDlg, "삭제할 항목을 먼저 선택해 주세요", "주의", MB_OK );
			else
			{
				ITEM.mask = LVIF_TEXT;
				ITEM.state = 0;
				ITEM.stateMask = 0;
				ITEM.iSubItem = 0;		 
				ITEM.iItem = idx; // Note: 추가 아이템 등록 인덱스 

				sprintf( buffer, "%d", idx );
				ITEM.pszText = buffer;
				ListView_InsertItem( g_hCutPosList, &ITEM);	
			
				GetDlgItemText( hDlg, IDC_EDIT5, buffer, 10 );
				ListView_SetItemText( g_hCutPosList, idx, 1, buffer );

				GetDlgItemText( hDlg, IDC_EDIT6, buffer, 10 );
				ListView_SetItemText( g_hCutPosList, idx, 2, buffer );

				GetDlgItemText( hDlg, IDC_EDIT7, buffer, 10 );
				ListView_SetItemText( g_hCutPosList, idx, 3, buffer );

				GetDlgItemText( hDlg, IDC_EDIT8, buffer, 10 );
				ListView_SetItemText( g_hCutPosList, idx, 4, buffer );	

				nCount =  ListView_GetItemCount( g_hCutPosList );
				for( i = idx + 1 ; i < nCount ; i++ )
				{
					sprintf( buffer, "%d", i );
					ListView_SetItemText( g_hCutPosList, i, 0, buffer );
				}
			}
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

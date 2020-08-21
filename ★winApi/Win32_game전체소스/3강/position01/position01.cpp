// position01.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "position01.h"
#include <CommDlg.h>
#include <commctrl.h>
#include "Position.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

SIZE g_szWndSize; // 스크롤바에 의해 적용될 윈도우의 크기
SIZE g_szOrginMainWndize;  // 초기화 후에 변경하면 안된다. 클라이언트 영역이 800x600일 때 윈도우 크기이다.
HWND g_hWnd = NULL, g_hMenuWnd = NULL;     
CPosition g_PositionObj;
int g_nCutIndex = -1;
char *g_strListMenu[] = {"순서", "x0", "y0", "x1", "y1" };
HWND g_CutListCtrl = NULL;
HWND g_hCollisionListCtrl = NULL;
int g_nCollisionIndex = -1;
int g_nRate = 1;
RECT g_rtMouseXY;
BOOL g_bIsBoxDraw;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MenuDlg(HWND, UINT, WPARAM, LPARAM);
void				SetListData( HWND, RECT );
RECT				GetListData( HWND, int );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_POSITION01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}	

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POSITION01));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);	
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POSITION01);
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
   RECT rect = { 0, 0, 800, 600};

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
   g_szWndSize.cx = rect.right - rect.left;
   g_szWndSize.cy = rect.bottom - rect.top ;		
   
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0,  g_szWndSize.cx, g_szWndSize.cy, NULL, NULL, hInstance, NULL);

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
	ofn.lpstrDefExt = "pos";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //선택이 안된 경우
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	RECT rect, rtDlg;	
	static SIZE szDlgSize;	
	static int nOldMouseX, nOldMouseY, nNewMouseX, nNewMouseY;		
	OPENFILENAME ofn;
	static char strFilePath[MAX_PATH], strFileExtension[10], strFileName[100];		
	HBITMAP hBitmap;
	POINT ptPoint;
	int nCount, nWidth, nHeight;
	HDC hMemDC;
	int i, nResult;
	static char *strFilter[2] = { "자른파일(*.cut)\0*.cut\0좌표파일(*.pos)\0*.pos\0\0",
								"좌표파일(*.pos)\0*.pos\0" };

	switch (message)
	{
	case WM_CREATE:
		g_hMenuWnd = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG1), 
			                       hWnd, MenuDlg); 			
		GetWindowRect(g_hMenuWnd, &rtDlg);		
		szDlgSize.cx = rtDlg.right - rtDlg.left;
		szDlgSize.cy = rtDlg.bottom - rtDlg.top;		
		GetWindowRect(hWnd, &rect); 
		MoveWindow(g_hMenuWnd, rect.right, rect.top, szDlgSize.cx, szDlgSize.cy, TRUE);			
		break;

	case WM_SIZE:
		GetWindowRect(hWnd, &rect);
		MoveWindow(hWnd, rect.left, rect.top, g_szWndSize.cx, g_szWndSize.cy, TRUE);
		break;

	case WM_MOVE:
		GetWindowRect(hWnd, &rect);				
		MoveWindow(g_hMenuWnd, rect.right, rect.top, szDlgSize.cx, szDlgSize.cy, TRUE);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case ID_32771: // 파일 열기
			 nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter[0]);
			 switch(nResult)
			 {
			 case 1: // sprite가 로딩되면 pos도 같이 생성한다.
					g_PositionObj.LoadCutInfo(hWnd, strFilePath);			
					g_PositionObj.CreatePosInfo();
					SetWindowText(hWnd, strFileName);					

					// Note: 컨트롤과 인덱스 초기화
					g_nCutIndex = 0;
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT7, g_nCutIndex , TRUE);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT1, 0, FALSE);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT2, 0, FALSE);						

					ListView_DeleteAllItems(g_CutListCtrl);
					ListView_DeleteAllItems(g_hCollisionListCtrl);

					// Note: 리스트 컨트롤 데이터 등록  
					nCount = g_PositionObj.GetSpriteCount();						
					for(int i = 0 ; i <  nCount ; i++ )
						SetListData(g_CutListCtrl, g_PositionObj.GetSprRect(i));	

					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // 중심좌표 설정						
					InvalidateRect(hWnd, NULL, FALSE); // 배경지우지 않고 출력한다. 
					break;
				case 2:					
					g_PositionObj.LoadPosInfo(strFilePath);						
								
					// Note: 충돌 좌표를 리스트 뷰에 초기 설정
					ListView_DeleteAllItems( g_hCollisionListCtrl );
					nCount = g_PositionObj.GetCollisionCount(g_nCutIndex);
					for(int i = 0 ; i < nCount ; i++ )
						SetListData( g_hCollisionListCtrl, g_PositionObj.GetCollisionRect(g_nCutIndex, i));							
					// 중심 좌표 설정
					ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT1, ptPoint.x, FALSE); 
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT2, ptPoint.y, FALSE);						
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED);
					break;
			 }
			 
			 break;

		case ID_32772: // 파일 저장
			if( FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter[1] ) != -1 )
			{   // Note: 저장할 파일이 pos 한 가지이므로 인덱스를 조사할 필요 없음
				g_PositionObj.SavePosInfo(strFilePath);
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

	case WM_MOUSEMOVE:		
		if( MK_LBUTTON & wParam ) // 마우스가 드래그 상태
		{	// 충돌 좌표를 출력하는 모드이면
			if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED )
			{
				nWidth = g_PositionObj.GetSprWidth(g_nCutIndex); 
				nHeight = g_PositionObj.GetSprHeight(g_nCutIndex);
				SetRect(&rect, 0, 0, nWidth, nHeight);	

				ptPoint.x = LOWORD(lParam) / g_nRate;
				ptPoint.y = HIWORD(lParam) / g_nRate;
				if(PtInRect(&rect, ptPoint))
				{
					g_rtMouseXY.right = ptPoint.x;
					g_rtMouseXY.bottom = ptPoint.y;

					SetDlgItemInt(g_hMenuWnd, IDC_EDIT5, g_rtMouseXY.right, FALSE );
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT6, g_rtMouseXY.bottom, FALSE );
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
		}
		break;

	case WM_RBUTTONDOWN: // 선택된 충돌좌표의 마스크 해제
		if(g_bIsBoxDraw)
		{
			g_bIsBoxDraw = FALSE; 
			InvalidateRect( hWnd, NULL, FALSE );
		}
		break;

	case WM_LBUTTONDOWN:
		// note: 중심 좌표 설정
		if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO1) == BST_CHECKED )
		{		
			nWidth = g_PositionObj.GetSprWidth(g_nCutIndex); 
			nHeight = g_PositionObj.GetSprHeight(g_nCutIndex);
			SetRect(&rect, 0, 0, nWidth, nHeight);		

			ptPoint.x = LOWORD(lParam) / g_nRate;
			ptPoint.y = HIWORD(lParam) / g_nRate;
				
			if(PtInRect(&rect, ptPoint))
			{
				g_PositionObj.SetCenterPos(g_nCutIndex, ptPoint);				
				SetDlgItemInt( g_hMenuWnd, IDC_EDIT1, ptPoint.x, FALSE );
				SetDlgItemInt( g_hMenuWnd, IDC_EDIT2, ptPoint.y, FALSE );				
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		else if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED )
		{
			nWidth = g_PositionObj.GetSprWidth(g_nCutIndex); 
			nHeight = g_PositionObj.GetSprHeight(g_nCutIndex);
			SetRect(&rect, 0, 0, nWidth, nHeight);		
			
			g_bIsBoxDraw = FALSE;
			ptPoint.x = LOWORD(lParam) / g_nRate;
			ptPoint.y = HIWORD(lParam) / g_nRate;

			if(PtInRect(&rect, ptPoint))
			{
				g_rtMouseXY.left = g_rtMouseXY.right = ptPoint.x; 
				g_rtMouseXY.top = g_rtMouseXY.bottom = ptPoint.y;
			
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT3, g_rtMouseXY.left, FALSE );
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT4, g_rtMouseXY.top, FALSE );
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT5, g_rtMouseXY.right, FALSE );
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT6, g_rtMouseXY.bottom, FALSE );
				InvalidateRect( hWnd, NULL, FALSE );
			}
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.

		if( g_nCutIndex != -1 )
		{			
			nWidth = g_PositionObj.GetSprWidth(g_nCutIndex);
			nHeight = g_PositionObj.GetSprHeight(g_nCutIndex);

			hMemDC = CreateCompatibleDC( hdc );
			hBitmap = CreateCompatibleBitmap( hdc, nWidth, nHeight ); 			 
			SelectObject( hMemDC, (HBITMAP)hBitmap );	// 모든 색상값이 0으로 설정된다.		
			DeleteObject( hBitmap );

			// 투명색상을 빼고 메모리DC로 복사한다.
			rect = g_PositionObj.GetSprRect(g_nCutIndex);
			TransparentBlt( hMemDC, 0, 0, nWidth, nHeight, g_PositionObj.GetSrcImageDC(), rect.left, rect.top,
				nWidth, nHeight, g_PositionObj.GetTransColor() );		

			if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO1) == BST_CHECKED)
			{					
				ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
				
				SetROP2( hMemDC, R2_NOTXORPEN);
				MoveToEx( hMemDC, ptPoint.x - 2, ptPoint.y, NULL ); // 가로
				LineTo( hMemDC,  ptPoint.x + 3, ptPoint.y );
				MoveToEx( hMemDC,  ptPoint.x, ptPoint.y- 2, NULL ); // 세로 상단 
				LineTo( hMemDC, ptPoint.x, ptPoint.y + 3 );							
			}
			else if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED )
			{					
				SetROP2( hMemDC, R2_NOTXORPEN);
				Rectangle(hMemDC, g_rtMouseXY.left, g_rtMouseXY.top, g_rtMouseXY.right, g_rtMouseXY.bottom);

				SetROP2( hMemDC, R2_NOTXORPEN);
				nCount = ListView_GetItemCount( g_hCollisionListCtrl ); 				
				for(i = 0 ; i < nCount ; i++)
				{
					rect = GetListData(g_hCollisionListCtrl, i);					
					Rectangle(hMemDC, rect.left, rect.top, rect.right, rect.bottom);						
				}

				// Note: 선택된 충돌좌표를 마스크하는 부분
				if(g_bIsBoxDraw)
				{
					SetROP2( hMemDC, R2_NOTMASKPEN);
					rect = GetListData(g_hCollisionListCtrl, g_nCollisionIndex);					
					Rectangle(hMemDC, rect.left, rect.top, rect.right, rect.bottom);
				}
			}

			StretchBlt(hdc, 0, 0, nWidth*g_nRate, nHeight*g_nRate, hMemDC, 0, 0, nWidth, nHeight, SRCCOPY);					
		}
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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


INT_PTR CALLBACK MenuDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{	
	int nCount, i, nIndex;
	LVCOLUMN lvColumn;
	LPNMHDR hdr;			
	LPNMITEMACTIVATE nia;	
	char string[100];
	POINT ptPoint;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		g_CutListCtrl = GetDlgItem(hDlg, IDC_LIST1);
		g_hCollisionListCtrl = GetDlgItem(hDlg, IDC_LIST2);
		ListView_SetExtendedListViewStyle( g_CutListCtrl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyle( g_hCollisionListCtrl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		nCount = sizeof(g_strListMenu)/sizeof(char *);
		lvColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		for(i = 0 ; i < nCount; i++)
		{
			lvColumn.cx = 50;
			lvColumn.pszText = g_strListMenu[i];
			ListView_InsertColumn(g_CutListCtrl, i, &lvColumn);
			ListView_InsertColumn(g_hCollisionListCtrl, i, &lvColumn);
		}			
		return (INT_PTR)TRUE;

	case WM_NOTIFY:
			hdr = (LPNMHDR)lParam;				
			if( hdr->hwndFrom == g_CutListCtrl )
			{
				if( hdr->code == NM_CLICK )
				{
					if(g_PositionObj.GetPosInfo() == NULL ) // 좌표 정보가 없는 경우는 리턴한다.
					{
						nia = (LPNMITEMACTIVATE)lParam;	// 선택된 인덱스	
						g_nCutIndex = nia->iItem;  // 인덱스만 넘긴다.
						SetDlgItemInt(hDlg, IDC_EDIT7, g_nCutIndex , FALSE);
						InvalidateRect( g_hWnd, NULL, FALSE ); // 윈도우 뷰의 화면을 갱신함.
						return (INT_PTR)TRUE;
					}
					else
					{ // 기본적으로 중심좌표는 0, 0 이고 충돌좌표만 체크해서 처리한다.
						nia = (LPNMITEMACTIVATE)lParam;	// 선택된 인덱스	
						
						if( nia->iItem != g_nCutIndex ) // 기존 스프라이트의 인덱스와 선택된 인덱스 비교
						{						
							// Note: 현재 리스트 컨트롤 안의 내용이 바뀌기 전에 모든 충돌좌표를 저장한다.
							nCount = ListView_GetItemCount( g_hCollisionListCtrl );
							if( nCount > 0 )
							{
								g_PositionObj.CreateCollisionRect(g_nCutIndex, nCount);
								for(i = 0 ; i < nCount ; i++)
									g_PositionObj.SetCollisionRect(g_nCutIndex, i, GetListData( g_hCollisionListCtrl, i ) );							
							}

							// Note: 현재의 데이터를 저장한 후에 인덱스를 바꾼다.
							g_nCutIndex = nia->iItem;
							SetDlgItemInt(hDlg, IDC_EDIT7, g_nCutIndex , FALSE);
						
							// Note: 중심좌표 설정
							ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
							SetDlgItemInt(hDlg, IDC_EDIT1, ptPoint.x, FALSE);
							SetDlgItemInt(hDlg, IDC_EDIT2, ptPoint.y, FALSE);
						
							// Note: 충돌 좌표의 리스트 컨트롤을 새로 셋업, 0개이면 반복문 실행하지 않음
							ListView_DeleteAllItems( g_hCollisionListCtrl ); 
							nCount = g_PositionObj.GetCollisionCount(g_nCutIndex);
							for( i = 0 ; i < nCount ; i++ )
								SetListData( g_hCollisionListCtrl, g_PositionObj.GetCollisionRect(g_nCutIndex, i));					

							InvalidateRect( g_hWnd, NULL, TRUE ); // 윈도우 뷰의 화면을 갱신함.					
						}	
					}
				}
			}

			// Note: 충돌 좌표 리스트 뷰의 항목이 클릭되면 클릭된 좌표를 화면에 출력
			if( hdr->hwndFrom == g_hCollisionListCtrl )
			{
				if( hdr->code == NM_CLICK )
				{
					nia = (LPNMITEMACTIVATE)lParam;	
					g_nCollisionIndex = nia->iItem;	
					g_bIsBoxDraw = TRUE;
					InvalidateRect( g_hWnd, NULL, FALSE );							
				}
			}
			return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1: // 확대
			g_nRate++;
			InvalidateRect(g_hWnd, NULL, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // 축소
			if( g_nRate - 1 > 0 )
			{	
				g_nRate--;
				InvalidateRect(g_hWnd, NULL, TRUE);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON5: // 적용
			ptPoint.x = GetDlgItemInt(hDlg, IDC_EDIT1, 0, FALSE); 
			ptPoint.y = GetDlgItemInt(hDlg, IDC_EDIT2, 0, FALSE);
			g_PositionObj.SetCenterPos(g_nCutIndex, ptPoint);
			InvalidateRect(g_hWnd, NULL, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON6: // 충돌좌표 등록 버튼		
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED && (g_nCutIndex != -1))
				{					
					SetListData(g_hCollisionListCtrl, g_rtMouseXY);		

					// Note: XOR 펜 옵션 때문에 						
					SetRect(&g_rtMouseXY, -1, -1, -1, -1); //클리핑시킴
					InvalidateRect( g_hWnd, NULL, FALSE );
				}
				break;

		case IDC_BUTTON7: // 충돌 좌표 삭제 버튼
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED && (g_nCutIndex != -1))
				{
					nIndex = ListView_GetNextItem( g_hCollisionListCtrl, -1, LVNI_ALL | LVNI_SELECTED );				

					if( nIndex == -1 )
						MessageBox( hDlg, "삭제할 항목을 먼저 선택해 주세요", "주의", MB_OK );
					else
					{								
						ListView_DeleteItem( g_hCollisionListCtrl, nIndex );
						nCount = ListView_GetItemCount( g_hCollisionListCtrl );						
						
						for( i = nIndex ; i < nCount ; i++ ) // 삭제후에 순번을 새로 고침
						{
							sprintf( string, "%d", i );
							ListView_SetItemText( g_hCollisionListCtrl, i, 0, string ); 			
						}
						
						InvalidateRect( g_hWnd, NULL, FALSE );
					}
				}
				break;

		case IDC_BUTTON8: // 충돌 좌표 적용 버튼
			nCount = ListView_GetItemCount( g_hCollisionListCtrl );
			if( nCount > 0 )
			{
				g_PositionObj.CreateCollisionRect(g_nCutIndex, nCount);
				for(i = 0 ; i < nCount ; i++)
					g_PositionObj.SetCollisionRect(g_nCutIndex, i, GetListData( g_hCollisionListCtrl, i ) );							
			}
			break;

		case IDC_RADIO1:
			if(HIWORD(wParam) == BN_CLICKED)
				InvalidateRect(g_hWnd, 0, FALSE);
			return (INT_PTR)TRUE;

		case IDC_RADIO2:
			if(HIWORD(wParam) == BN_CLICKED)
				InvalidateRect(g_hWnd, 0, FALSE);
			return (INT_PTR)TRUE;		
		}	
		break;
	}
	return (INT_PTR)FALSE;
}

void SetListData( HWND hList, RECT rect )
{
	LVITEM ITEM; 
	int idx;
	char buffer[100];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		 

	idx = ListView_GetItemCount( hList ); //하나 많은 카운트를 돌려주기에 이를 이용 
	ITEM.iItem = idx; // Note: 추가 아이템 등록 인덱스 

	sprintf( buffer, "%d", idx );
	ITEM.pszText = buffer;
	ListView_InsertItem( hList, &ITEM);
	
	sprintf( buffer, "%d", rect.left );
	ListView_SetItemText( hList, idx, 1, buffer );

	sprintf( buffer, "%d", rect.top );
	ListView_SetItemText( hList, idx, 2, buffer );

	sprintf( buffer, "%d", rect.right );
	ListView_SetItemText( hList, idx, 3, buffer );

	sprintf( buffer, "%d", rect.bottom );
	ListView_SetItemText( hList, idx, 4, buffer );
}

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
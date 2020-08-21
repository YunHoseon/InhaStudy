// AniTool01.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
/*
에니메이션 툴을 만들 때 참고할 사항

1. 에니메이션 툴의 가장 중요한 사항은 로딩된 스프라이트를 연속적으로 
   일정한 시간 간격으로 출력하는 것이다.
   이를 위해 타이머를 사용하는 방법과 게임 루프를 돌리는 방법이 있지만
   출력에 큰 차이가 없으므로 가장 쉽게 설정할 수 있는 타이머를 이용한다.
   1000 밀리세컨드가 1초이므로 1000 / 60 으로 하면 60 프레임일 때 1 프레임당
   시간 간격이 나오므로 이를 활용한다. 16으로 설정
   타이머를 설정할 때 알아야 하는 것은 타이머의 시간을 16이하로 설정해도 
   타이머 메시지가 여기에 맞춰서 발생하는 것은 아니다.
   즉 타이머 메시지는 한계가 있으며 현재 16을 맞춰도 실제 FPS를 체크해 보면
   약 34 ~ 38 정도가 나온다. 
   30 FPS 이상만 나오면 에니메이션 시간을 맞추는 것은 문제가 없으므로 이 방법을
   사용한다.

2. 이전 툴에서 만든 소스의 내용을 사용하라.
   이미 작성된 윈도우 품 프로그래밍의 소스를 잘 활용하면 시간과 노력을 줄일 수 있다.

3. 에니메이션에 필요한 데이터는 에니메이션 시간 간격에 대한 DWORD 변수 하나이다.
   그러므로 여기서는 클래스를 만들 이유가 전혀 없고 Sprite 클래스를 만들 때에
   통합되도록 한다.

4. 이 툴까지 완성을 했으면 어느 정도 Win32 API 윈도우 프로그래밍에 대해서 감을 잡았을 
   것이다. 그리고 C++의 기본은 학습하였을 것이므로 이쯤에서 MFC를 공부해 보는 것도 
   괜찮을 것 같다고 생각한다.

5. 모든 것이 처음부터 완벽하게 될려면 각고의 노력이 필요함을 생각하고 처음부터 너무 큰
   계획과 목표보다는 한 단계씩 계획과 목표를 높여 간다는 생각으로 도전해 보는 것은
   어떨까 생각합니다. Good Bye!~~ ^^V
*/

#include "stdafx.h"
#include "AniTool01.h"
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
HWND g_SprListCtrl = NULL;
int g_nSprIndex = -1, g_nSize = 1;

DWORD *g_pAniTime, g_dwAniTime, g_dwOldTime;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MenuDlg(HWND, UINT, WPARAM, LPARAM);


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
	LoadString(hInstance, IDC_ANITOOL01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANITOOL01));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANITOOL01));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ANITOOL01);
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
   
   g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0,  g_szWndSize.cx, g_szWndSize.cy, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
	ofn.lpstrDefExt = "ani";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //선택이 안된 경우
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect, rtDlg;	
	LVITEM ITEM;
	int nCount, nWidth, nHeight, nX, nY, nResult;	
	FILE *fp;	
	HBITMAP hBitmap;	
	POINT ptCenter;
	DWORD dwCurTime;
	
	static SIZE szDlgSize;		
	static char strFilePath[MAX_PATH], strFileExtension[10], strFileName[100], string[100];	
	static char *strFilter[2] = { "자른파일(*.cut)\0*.cut\0좌표파일(*.pos)\0*.pos\0에니파일(*.ani)\0*.ani\0",
								"에니파일(*.ani)\0*.ani\0" };
	static HDC hBackBuffer;	// 백버퍼 DC

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

		hdc = GetDC( hWnd );
		hBackBuffer = CreateCompatibleDC( hdc );
		hBitmap = CreateCompatibleBitmap( hdc, 800, 600 );
		SelectObject( hBackBuffer, (HBITMAP)hBitmap );		 
		DeleteObject( hBitmap );
		ReleaseDC( hWnd, hdc );	
		break;

	case WM_SIZE:
		GetWindowRect(hWnd, &rect);
		MoveWindow(hWnd, rect.left, rect.top, g_szWndSize.cx, g_szWndSize.cy, TRUE);
		break;

	case WM_MOVE:
		GetWindowRect(hWnd, &rect);				
		MoveWindow(g_hMenuWnd, rect.right, rect.top, szDlgSize.cx, szDlgSize.cy, TRUE);
		break;

	case WM_TIMER:
		dwCurTime = GetTickCount();		
		if( dwCurTime - g_dwOldTime >= g_dwAniTime )
		{
			g_dwOldTime = dwCurTime;
			g_nSprIndex = ++g_nSprIndex % g_PositionObj.GetSprCount();
			ListView_GetItemText( g_SprListCtrl, g_nSprIndex, 1, string, 10 );
			g_dwAniTime =  (DWORD)atoi( string ); 
		}

		InvalidateRect( hWnd, NULL, FALSE );
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case ID_32771: // 열기
			ZeroMemory(strFilePath, sizeof(strFileName));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter[0]);			
			switch(nResult)
			{
			case 1: 
					g_PositionObj.LoadCutInfo(hWnd, strFilePath);			
					g_PositionObj.CreatePosInfo();
					ListView_DeleteAllItems(g_SprListCtrl);

					// 순번 등록 부분
					ITEM.mask = LVIF_TEXT;
					ITEM.state = 0;
					ITEM.stateMask = 0;
					ITEM.iSubItem = 0;
					nCount = g_PositionObj.GetSprCount();
					for(int i = 0 ; i < nCount ; i++ )
					{
						ITEM.iItem = i; // Note: 추가 아이템 등록 인덱스 
						sprintf( string, "%d", i );
						ITEM.pszText = string;
						ListView_InsertItem( g_SprListCtrl, &ITEM);
					}

					g_nSprIndex = 0; // 스프라이트 초기 인덱스 설정
					break;
			case 2 :
					g_PositionObj.LoadPosInfo(strFilePath);							
					break;
			 case 3: 
					fp = fopen(strFilePath, "r");
					nCount = g_PositionObj.GetSprCount();
					if(g_pAniTime != NULL)
						delete [] g_pAniTime;
					g_pAniTime = new DWORD[nCount];
					for(int i = 0 ; i < nCount ; i++ )
						fscanf(fp, "%d\n", &g_pAniTime[i]);
					fclose(fp);

					for(int i = 0 ; i < nCount ; i++ )
					{
						sprintf( string, "%d", (int)g_pAniTime[i] );
						ListView_SetItemText( g_SprListCtrl, i, 1, string );	
					}	
					break;
			}

			InvalidateRect( hWnd, NULL, FALSE );
			break;

		case ID_32772: // ani 파일 저장
			ZeroMemory(strFilePath, sizeof(strFileName));
			ZeroMemory(strFileName, sizeof(strFileName));
			if( FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter[1] ) != -1 )
			{ 			
				nCount = g_PositionObj.GetSprCount();
				fp = fopen( strFilePath, "wt" ); 

				for(int i = 0 ; i < nCount ; i++ )
				{
					ListView_GetItemText( g_SprListCtrl, i, 1, string, 10 );					
					fprintf( fp, "%d\n", atoi( string ) );
				}
				fclose( fp );
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
		// TODO: 여기에 그리기 코드를 추가합니다.
		PatBlt( hBackBuffer, 0, 0, 800, 600, BLACKNESS ); // 배경 지우기

		if( g_nSprIndex != -1 )
		{	
			if(g_PositionObj.GetSprCount() > 0 ) // 스프라이트 로딩된 것임
			{
				nWidth = g_PositionObj.GetSprWidth(g_nSprIndex);
				nHeight = g_PositionObj.GetSprHeight(g_nSprIndex);
				rect = g_PositionObj.GetSprRect(g_nSprIndex);
				
				if(g_PositionObj.GetPosInfo() != NULL)
				{
					ptCenter = g_PositionObj.GetSpriteCenterPos(g_nSprIndex);
					nX = 400 - ptCenter.x*g_nSize;
					nY = 300 - ptCenter.y*g_nSize;
				}else{
					ptCenter.x = ptCenter.y = 0;
				}			
			
				TransparentBlt( hBackBuffer, nX, nY, nWidth * g_nSize, nHeight * g_nSize, g_PositionObj.GetSrcImageDC(), rect.left, rect.top,
								nWidth, nHeight, g_PositionObj.GetTransColor()); 	
			}						

			SetBkColor(hBackBuffer, RGB(0,0,0));
			SetTextColor(hBackBuffer, RGB(10, 255, 10));
			sprintf(string, "에니 인덱스: %3d", g_nSprIndex);
			TextOut(hBackBuffer, 600, 10, string, strlen(string));
		}
		

		SelectObject(hBackBuffer, GetStockObject(DC_PEN)); // 운영체제의 기본 펜을 셋팅해서 사용할 수 있다.
	    SetDCPenColor(hBackBuffer, RGB(250, 0, 0));
		MoveToEx(hBackBuffer, 400, 0, NULL);
		LineTo(hBackBuffer, 400, 599);
		MoveToEx(hBackBuffer, 0, 300, NULL);
		LineTo(hBackBuffer, 799, 300);

		BitBlt( hdc, 0, 0, 800, 600, hBackBuffer, 0, 0, SRCCOPY);
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
INT_PTR CALLBACK MenuDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LVCOLUMN lvColumn;
	LPNMHDR hdr;			
	LPNMITEMACTIVATE nia;	
	char string[100];

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		g_SprListCtrl = GetDlgItem(hDlg, IDC_LIST1);
		ListView_SetExtendedListViewStyle( g_SprListCtrl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
				
		lvColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		lvColumn.cx = 50;
		lvColumn.pszText = "순서";
		ListView_InsertColumn(g_SprListCtrl, 0, &lvColumn);

		lvColumn.cx = 150;
		lvColumn.pszText = "에니메이션 시간";
		ListView_InsertColumn(g_SprListCtrl, 1, &lvColumn);
		return (INT_PTR)TRUE;

	case WM_NOTIFY: // 리스트 뷰가 선택되면				
		hdr = (LPNMHDR)lParam;
		if(hdr->hwndFrom == g_SprListCtrl)
		{
			if(hdr->code == NM_CLICK)
			{
				nia = (LPNMITEMACTIVATE)lParam;	// 선택된 인덱스
				if( nia->iItem < 0 || nia->iItem >= g_PositionObj.GetSprCount())
					return TRUE;
				
				if(nia->iItem != g_nSprIndex)
				{					
					g_nSprIndex = nia->iItem;
					ListView_GetItemText( g_SprListCtrl, g_nSprIndex, 1, string, 10 );
					SetDlgItemText( hDlg, IDC_EDIT1, string );
					InvalidateRect( g_hWnd, NULL, FALSE );						
				}
			}
		}
		return TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_BUTTON1: // 적용
			GetDlgItemText(hDlg,IDC_EDIT1, string, 10); 
			ListView_SetItemText( g_SprListCtrl, g_nSprIndex, 1, string );							
			SetDlgItemInt( hDlg, IDC_EDIT1, 0, FALSE); //에디트 박스안의 데이터 삭제
			break;
		case IDC_BUTTON2: // 플레이어 버튼
			g_dwOldTime = GetTickCount();
			SetTimer(g_hWnd, 1, 16, NULL);
			// 리스트 컨트로에 있는 초기 에니메이션 시간 가져오는 부분
			ListView_GetItemText( g_SprListCtrl, 0, 1, string, 10 );
			g_dwAniTime = atoi(string);			
			g_nSprIndex = 0;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON3: // 정지 버튼			
			KillTimer(g_hWnd, 1);
			g_nSprIndex = 0;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON4: // 확대 버튼
			g_nSize++;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON5: // 축소 버튼			
			g_nSize--;
			if( g_nSize < 1 )
				g_nSize = 1;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		}
		
		return (INT_PTR)TRUE;
		
	}

	return (INT_PTR)FALSE;
}


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
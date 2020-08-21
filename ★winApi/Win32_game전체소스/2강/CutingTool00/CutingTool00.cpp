// CutingTool00.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.
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
SIZE g_szWndSize; // ��ũ�ѹٿ� ���� ����� �������� ũ��
SIZE g_szOrginMainWndize;  // �ʱ�ȭ�� �Ŀ� �����ϸ� �ȵȴ�. Ŭ���̾�Ʈ ������ 800x600�� �� ������ ũ���̴�.
BOOL g_bIsVScrollBar, g_bIsHScrollBar;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CUTINGTOOL00, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CUTINGTOOL00));

	// �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;      
   
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.  
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
int FileOpenDilaog(HWND hWnd, char *strFilePath, char* strFileName, char* strFilter, char *strDefExt)
{
	OPENFILENAME ofn;
	char strFileTitle[MAX_PATH] = {0,};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = "���� ������ ������ �ּ���";
	ofn.lpstrFileTitle = strFileName; // global, static ���� ���
	ofn.lpstrFile = strFilePath; // global, static ����
	ofn.lpstrFilter = strFilter;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrDefExt = strDefExt;

	if( GetOpenFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //������ �ȵ� ���
}

int FileSaveDilaog(HWND hWnd, char *strFilePath, char* strFileName, char* strFilter)
{
	OPENFILENAME ofn;
	char strFileTitle[MAX_PATH] = {0,};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrTitle = "������ ������ ������ �ּ���";
	ofn.lpstrFileTitle = strFileName; // global, static ���� ���
	ofn.lpstrFile = strFilePath; // global, static ����
	ofn.lpstrFilter = strFilter;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrDefExt = "cut";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //������ �ȵ� ���
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
	static char strFilter[] = "�ڸ� ����(*.cut)\0*.cut\0";
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

		g_hTransparentCursor = LoadCursor( NULL, IDC_HAND ); // hInst�� �ƴ� NULL�� ä���� �Ѵ�.
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
			nOldMouseX = nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; // ��ũ�� GET_X_LPARAM(), GET_Y_LPARAM()
			nOldMouseY = nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;	
			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT5, nOldMouseX, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT6, nOldMouseY, FALSE );			

			InvalidateRect( hWnd, NULL, FALSE );
		}
		break;

	case WM_MOUSEMOVE : 					
		if( MK_LBUTTON & wParam ) // ���콺�� �巡�� ����
		{			
			g_nBoxState = DRAG;
			// ����Ϸ��� ������ �̹��� ��ġ�� ����
			nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; 
			nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;				
			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT7, nNewMouseX, FALSE );			
			SetDlgItemInt( g_hMenuWnd, IDC_EDIT8, nNewMouseY, FALSE );		
			InvalidateRect( hWnd, NULL, FALSE );			
		}
		break;	

	case WM_LBUTTONUP:	// ������ ���� ����
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

	case WM_HSCROLL: // LOWORD(wParam) ���� ����, HIWORD(wParam)�� ��ġ
		if(LOWORD(wParam) == SB_THUMBTRACK) // ��ũ�ѹ��� ���� ��ġ, ��ũ�� �ڽ��� ���� ���´�.
		{			
			g_xCurrentScroll = HIWORD(wParam);			
			SetScrollPos(hWnd, SB_HORZ, g_xCurrentScroll, TRUE);
		}
		
		InvalidateRect(hWnd, 0, FALSE);
		break;

	case WM_VSCROLL: // LOWORD(wParam) ���� ����, HIWORD(wParam)�� ��ġ
		if(LOWORD(wParam) == SB_THUMBTRACK) // ��ũ�� �ڽ� �̵��� ���� �޽���
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
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case ID_32771: // ���� �б�
			
			if( FileOpenDilaog( hWnd, strFilePath, strFileName, strFilter, "cut" ) != -1 )
			{
				g_CutImage.LoadCutInfo(hWnd, strFilePath);

				// ���� �����͸� ��Ʈ�ѿ� �����ϴ� �κ�
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
					ITEM.iItem = i; // Note: �߰� ������ ��� �ε��� 

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
				// Note: ���� �̹����� �ٷ� g_hMemDC ������ ���� �κ�
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(g_hWnd, szImageSize); // �޸�DC ����

				ScrollProcess(szImageSize.cx, szImageSize.cy);	
				g_nExpansion = 1;
				g_xCurrentScroll = 0;
				g_yCurrentScroll = 0;		

				InvalidateRect( hWnd, NULL, TRUE );					
			}
			break;

		case ID_32772: // ���� ����
			if( FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter ) != -1 )
			{	// �������� ������ �� �����̹Ƿ� ���� ���� �ε����� ������ �ʿ䰡 ����.				
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

			// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.		
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
	// ���� ���� ũ�Ⱑ �̹����� ũ�⿡ ���� ��ũ�ѹٰ� �������̴�.
	g_xCurrentScroll = 0;
	if( nImageWidth > CLIENT_WIDTH ) 
	{
		if( g_bIsHScrollBar )
		{ // ��ũ�ѹ� �缳��
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_HORZ, TRUE);
			SetScrollRange(g_hWnd, SB_HORZ, g_xMinScroll, 
				           g_xMaxScroll, FALSE); 
			SetScrollPos(g_hWnd, SB_HORZ, 0, FALSE);
		}else{ // ��ũ�ѹٿ� ���� ������ ���� �� ��ũ�ѹ� ����			
			g_szWndSize.cy = g_szOrginMainWndize.cy + 17;		
					
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_HORZ, TRUE);
			SetScrollRange(g_hWnd, SB_HORZ, g_xMinScroll, 
				            g_xMaxScroll, FALSE); // �ؿ��� InvalidateRect �ϹǷ�	
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
			g_bIsHScrollBar = TRUE;
		}					
	}else{ // �̹����� Ŭ���̾�Ʈ �������� ���� ���
		if( g_bIsHScrollBar ) // ������ ��ũ�ѹٰ� �־��ٸ� ��Ȱ������, ������ ũ�� ����
		{			
			ShowScrollBar(g_hWnd, SB_HORZ, FALSE); // ��ũ�ѹ� �����
			g_bIsHScrollBar = FALSE;
			g_szWndSize.cy = g_szOrginMainWndize.cy;
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
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
			GetWindowRect(g_hWnd, &rect); // ���̰� �޶����� 
			g_szWndSize.cx = rect.right - rect.left + 17;				
					
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(g_hWnd, SB_VERT, TRUE);
			SetScrollRange(g_hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); // �ؿ��� InvalidateRect �ϹǷ�	
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
			g_bIsVScrollBar = TRUE;
		}
	}else{
		if(g_bIsVScrollBar)
		{
			ShowScrollBar(g_hWnd, SB_VERT, FALSE);
			g_bIsVScrollBar = FALSE;
			g_szWndSize.cx = g_szOrginMainWndize.cx;
			SendMessage(g_hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
		}
	}			
}

// �޴� ��ȭ���� �Դϴ�.
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

		// Note: ���� ���� ����Ʈ �ڽ� ����
		COL.cx = 40;
		COL.pszText = "����";
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

	case WM_NOTIFY: // ����Ʈ �䰡 ���õǸ� 
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
		case IDC_BUTTON1: // �̹��� �б� ��ư
			if( FileOpenDilaog(hDlg, strFilePath, strFileName, "��Ʈ��(*.bmp)\0*.bmp\0", "bmp") != -1 )
			{
				SetDlgItemText(hDlg, IDC_EDIT1, strFileName);		
				g_CutImage.LoadBmpImage(g_hWnd, strFileName); 
				szBmpSize = g_CutImage.GetImageSize();
				
				// Note: ���� �̹����� �ٷ� g_hMemDC ������ ���� �κ�
				if(g_hMemDC != NULL)
					delete g_hMemDC;

				g_hMemDC = CreateMemDC(g_hWnd, szBmpSize); // �޸�DC ����
				ScrollProcess(szBmpSize.cx, szBmpSize.cy);	
				g_nExpansion = 1;
				g_xCurrentScroll = 0;
				g_yCurrentScroll = 0;				
			}

			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // Ȯ�� ��ư
			g_nExpansion++;		
			szBmpSize = g_CutImage.GetImageSize();
			ScrollProcess(szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);				
			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON3: // ��� ��ư
			if( g_nExpansion - 1 < 1 )
				g_nExpansion = 1;
			else
				g_nExpansion--;

			szBmpSize = g_CutImage.GetImageSize();
			ScrollProcess(szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);
			InvalidateRect(g_hWnd, 0, TRUE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON4: // ������� ��� ��ư
			g_bIsTransColorChoice = TRUE;
			g_nBoxState = NONE;		
			InvalidateRect(g_hWnd, 0, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON5:  // �ڸ� ��ǥ ��� ��ư
			ITEM.mask = LVIF_TEXT;
			ITEM.state = 0;
			ITEM.stateMask = 0;
			ITEM.iSubItem = 0;		 

			idx = ListView_GetItemCount( g_hCutPosList );  
			ITEM.iItem = idx; // Note: �߰� ������ ��� �ε��� 

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

		case IDC_BUTTON6:  // ��ǥ ���� ��ư
			// Note: GetNextItem()�� ���õ� �׸��� ã�� �ִ� �Լ��̴�. 
			idx = ListView_GetNextItem( g_hCutPosList, -1, LVNI_ALL | LVNI_SELECTED );

			if( idx == -1 )
				MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
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

		case IDC_BUTTON7:  // ��ǥ ���� ��ư
			idx = ListView_GetNextItem( g_hCutPosList, -1, LVNI_ALL | LVNI_SELECTED );

			if( idx == -1 )
				MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
			else
			{
				ITEM.mask = LVIF_TEXT;
				ITEM.state = 0;
				ITEM.stateMask = 0;
				ITEM.iSubItem = 0;		 
				ITEM.iItem = idx; // Note: �߰� ������ ��� �ε��� 

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

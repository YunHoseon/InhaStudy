// SpriteTool00.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.
char *g_strListMenu[] = {"����", "x0", "y0", "x1", "y1" };
SIZE g_szWndSize; // ��ũ�ѹٿ� ���� ����� �������� ũ��
SIZE g_szOrginMainWndize;  // �ʱ�ȭ �Ŀ� �����ϸ� �ȵȴ�. Ŭ���̾�Ʈ ������ 800x600�� �� ������ ũ���̴�.
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
int g_nRate = 1; // ��ǥ�������� ����ϴ� Ȯ����� ����
int g_nCollisionListIndex = 0; //�浹��ǥ ����Ʈ �ε���
int g_nAniSprIndex = 0; //���ϸ��̼� ����Ʈ ��Ʈ�� ���� �ε���
int g_nAniRate = 1; //���ϸ��̼� ��忡�� Ȯ�� �� ��� 
int g_nAniPartListIndex = -1;
DWORD g_dwOldTime = 0, g_dwAniTime;
RANGE g_sAniPartRange;

HDC g_hMemDC;
CSprite g_Sprite;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

// Note: ����Ʈ ��Ʈ���� �����ϴ� �Լ��� �׸��� 4���� ��츸 ���
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

// Note: �޸� DC�� �����ϴ� �Լ�
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
	ofn.lpstrTitle = "���� ������ ������ �ּ���";
	ofn.lpstrFileTitle = strFileName; // global, static ���� ���
	ofn.lpstrFile = strFilePath; // global, static ����
	ofn.lpstrFilter = strFilter;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;	

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
	ofn.lpstrDefExt = "spr";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //������ �ȵ� ���
}

// Note: ��ũ�� �������� ��ũ�ѹٸ� Ȱ�� �Ǵ� ��Ȱ����Ű�� �Լ�
void ScrollProcess(HWND hWnd, int nImageWidth, int nImageHeight )
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
			ShowScrollBar(hWnd, SB_HORZ, TRUE);
			SetScrollRange(hWnd, SB_HORZ, g_xMinScroll, 
				           g_xMaxScroll, FALSE); 
			SetScrollPos(hWnd, SB_HORZ, 0, FALSE);
		}else{ // ��ũ�ѹٿ� ���� ������ ���� �� ��ũ�ѹ� ����			
			g_szWndSize.cy = g_szOrginMainWndize.cy + 17;		
					
			g_xMaxScroll = nImageWidth - CLIENT_WIDTH;
			g_xMinScroll = 0;
			ShowScrollBar(hWnd, SB_HORZ, TRUE);
			SetScrollRange(hWnd, SB_HORZ, g_xMinScroll, 
				            g_xMaxScroll, FALSE); // �ؿ��� InvalidateRect �ϹǷ�	
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
			g_bIsHScrollBar = TRUE;
		}					
	}else{ // �̹����� Ŭ���̾�Ʈ �������� ���� ���
		if( g_bIsHScrollBar ) // ������ ��ũ�ѹٰ� �־��ٸ� ��Ȱ������, ������ ũ�� ����
		{			
			ShowScrollBar(hWnd, SB_HORZ, FALSE); // ��ũ�ѹ� �����
			g_bIsHScrollBar = FALSE;
			g_szWndSize.cy = g_szOrginMainWndize.cy;
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
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
			GetWindowRect(hWnd, &rect); // ���̰� �޶����� 
			g_szWndSize.cx = rect.right - rect.left + 17;				
					
			g_yMaxScroll = nImageHeight - CLIENT_HEIGHT;
			g_yMinScroll = 0;
			ShowScrollBar(hWnd, SB_VERT, TRUE);
			SetScrollRange(hWnd, SB_VERT, g_yMinScroll, g_yMaxScroll, FALSE); // �ؿ��� InvalidateRect �ϹǷ�	
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
			g_bIsVScrollBar = TRUE;
		}
	}else{
		if(g_bIsVScrollBar)
		{
			ShowScrollBar(hWnd, SB_VERT, FALSE);
			g_bIsVScrollBar = FALSE;
			g_szWndSize.cx = g_szOrginMainWndize.cx;
			SendMessage(hWnd, WM_MOVE, 0, 0 ); // ũ��� ��ġ ������
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

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SPRITETOOL00, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPRITETOOL00));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPRITETOOL00));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SPRITETOOL00);
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// Note: ���� Ÿ�ӿ� �ð��� �߰��ϴ� �Լ�
void AddAniTimeList(HWND hList, DWORD nAniTime)
{
	char string[100];
	LVITEM ITEM; 
	int nIndex = ListView_GetItemCount(hList);

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;	
	ITEM.iItem = nIndex; // Note: �߰� ������ ��� �ε��� 
	ITEM.iSubItem = 0;
	sprintf(string, "%d", nIndex );
	ITEM.pszText = string;
	ListView_InsertItem( g_hAniTimeList, &ITEM); // �������					
	sprintf( string, "%d", g_Sprite.GetAniTime(nIndex) );
	ListView_SetItemText( g_hAniTimeList, nIndex, 1, string ); // ����Ÿ�ӵ��	
}

// Note: ������ �ε����� ������ �����ϴ� �Լ�
void InsertListData( HWND hList, int nIndex, RECT rect )
{
	LVITEM ITEM; 
	char buffer[100];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nIndex; // Note: �߰� ������ ��� �ε��� 

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

// Note: ����Ʈ�� ���� �߰��ϴ� �Լ�
void AddListData( HWND hList, RECT rect )
{
	LVITEM ITEM; 
	char buffer[100];
	int nIndex = ListView_GetItemCount( hList );

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nIndex; // Note: �߰� ������ ��� �ε��� 

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

// Note: �ִ� ���� ����Ʈ�� �׸��� �����ϴ� �Լ�
void InsertAniPartList(HWND hList, int nPartIndex, int nIndex0, int nIndex1)
{
	LVITEM ITEM; 
	char buffer[100];

	ITEM.mask = LVIF_TEXT;
	ITEM.state = 0;
	ITEM.stateMask = 0;
	ITEM.iSubItem = 0;		
	ITEM.iItem = nPartIndex; // Note: �߰� ������ ��� �ε��� 

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

// Note: �ڸ��� ����Ʈ ��Ʈ�� �ʱ�ȭ
void InitListType0(HWND hList)
{
	LVCOLUMN COL;

	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: ���� ���� ����Ʈ �ڽ� ����
	COL.cx = 40;
	COL.pszText = "����";
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

// Note: ���� Ÿ�� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void InitAniTimeListType(HWND hList)
{
	LVCOLUMN COL;
	
	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: ���� ���� ����Ʈ �ڽ� ����
	COL.cx = 40;
	COL.pszText = "����";
	COL.iSubItem = 0;
	SendMessage( hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

	COL.cx = 100;
	COL.pszText = "time";
	COL.iSubItem = 1;
	SendMessage( hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );   
}

// Note: ���� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void InitAniPartListType(HWND hList)
{
	LVCOLUMN COL;

	ListView_SetExtendedListViewStyle( hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt  = LVCFMT_CENTER;

	// Note: ���� ���� ����Ʈ �ڽ� ����
	COL.cx = 40;
	COL.pszText = "����";
	COL.iSubItem = 0;
	SendMessage( hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL ); 

	COL.cx = 100;
	COL.pszText = "���� Index0";
	COL.iSubItem = 1;
	SendMessage( hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL );   

	COL.cx = 100;
	COL.pszText = "���� Index1";
	COL.iSubItem = 2;
	SendMessage( hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL );   
}

// Note: �ڸ��� ���� ��Ʈ���� Ȱ�� �� ��Ȱ�� ��Ŵ
void EnableCutCtrl(HWND hDlg, BOOL bEnable)
{
	Button_Enable( GetDlgItem(hDlg, IDC_BUTTON4), bEnable);
	ListBox_Enable(GetDlgItem(hDlg, IDC_LIST2), bEnable);
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON5), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON6), bEnable);	
	Button_Enable(GetDlgItem(hDlg, IDC_BUTTON7), bEnable);	
}


// Note: ��ǥ ���� ��Ʈ���� Ȱ�� �� ��Ȱ�� ��Ŵ
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

// Note: ���ϸ��̼� ���� ��Ʈ���� Ȱ�� �� ��Ȱ�� ��Ŵ
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
	static char *strFilter = "��Ʈ��(*.bmp)\0*.bmp\0��������Ʈ(*.spr)\0*.spr\0";
	static char *strFilter2 = "��������Ʈ(*.spr)\0*.spr\0";
	
	static HDC hBackBuffer;	// ����� DC
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

		// �ڸ��� ��� �ʱ�ȭ �κ�	
		g_nCurrentMode = 0;
		CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �ڸ��� ���
		sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
		SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);	
		g_hTransparentCursor = LoadCursor( NULL, IDC_HAND ); // hInst�� �ƴ� NULL�� ä���� �Ѵ�.
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
				g_Sprite.GetTransColor(LOWORD(lParam) / g_nExpansion, HIWORD(lParam) / g_nExpansion); // Ȯ����Ҹ� ���� ��ǥ�� ȯ���Ͽ� �Է�
				g_bIsTransColorChoice = FALSE;

				sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);			
			}else{			
				nOldMouseX = nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; // ��ũ�� GET_X_LPARAM(), GET_Y_LPARAM()
				nOldMouseY = nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;		
				InvalidateRect( hWnd, NULL, FALSE );
			}
		}else if(g_nCurrentMode == 1){
			if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO4) == BST_CHECKED ) // �߽���ǥ
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
		if( MK_LBUTTON & wParam ) // ���콺�� �巡�� ����
		{			
			if(g_nCurrentMode == 0 ) //�ڸ��� ���
			{
				g_nBoxState = DRAG;
				// ����Ϸ��� ������ �̹��� ��ġ�� ����
				nNewMouseX = (LOWORD(lParam) + g_xCurrentScroll) / g_nExpansion; 
				nNewMouseY = (HIWORD(lParam) + g_yCurrentScroll) / g_nExpansion;							
				InvalidateRect( hWnd, NULL, FALSE );
			}else if(g_nCurrentMode == 1){ // ��ǥ ���� ��� 
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

	case WM_LBUTTONUP:	// ������ ���� ����
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
			SetScrollPos(hWnd, SB_VERT, g_yCurrentScroll, TRUE);
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
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter);	
			switch(nResult)
			{
			case 1: // ��Ʈ�� �б�		
				g_Sprite.Release();
				g_Sprite.Init();

				g_Sprite.LoadBmpImage(hWnd, strFilePath, strFileName);
			
				// Note: ���� �̹����� �ٷ� g_hMemDC ������ ���� �κ�
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(hWnd, g_Sprite.GetImageSize()); // �޸�DC ����

				// ��Ʈ�� ���� �κ�
				// Note: ����Ʈ ��Ʈ�� ���� ����� 
				ListView_DeleteAllItems(g_hCutList);
				ListView_DeleteAllItems(g_hCollisionList);
				ListView_DeleteAllItems(g_hAniTimeList);
				ListView_DeleteAllItems(g_hAniPartList);

				g_nSprIndex = -1;
				SetDlgItemText(g_hMenuWnd, IDC_EDIT1, g_Sprite.GetBmpFileName());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, ""); 
				CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �ڸ��� ���
				EnableCutCtrl(g_hMenuWnd, TRUE);
				EnablePosCtrl(g_hMenuWnd, FALSE);
				EnableAniCtrl(g_hMenuWnd, FALSE);
				ScrollProcess(hWnd, g_Sprite.GetImageSize().cx, g_Sprite.GetImageSize().cy);
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			case 2: // ��������Ʈ �б�
				g_Sprite.Load(hWnd, strFilePath);
				g_Sprite.LoadBmpImage(hWnd);
				// Note: ���� �̹����� �ٷ� g_hMemDC ������ ���� �κ�
				if(g_hMemDC != NULL)
					DeleteDC(g_hMemDC);

				g_hMemDC = CreateMemDC(hWnd, g_Sprite.GetImageSize()); // �޸�DC ����						

				// ��Ʈ�� ���� �κ�
				// Note: ����Ʈ ��Ʈ�� ���� ����� 
				ListView_DeleteAllItems(g_hCutList);
				ListView_DeleteAllItems(g_hCollisionList);
				ListView_DeleteAllItems(g_hAniTimeList);
				ListView_DeleteAllItems(g_hAniPartList);

				// Note:  �̹��� ���ϸ� ����
				SetDlgItemText(g_hMenuWnd, IDC_EDIT1, g_Sprite.GetBmpFileName());

				// Note: ������� ����
				sprintf(string, "R: %-3d   G: %-3d   B: %-3d", g_Sprite.GetTransRed(),  g_Sprite.GetTransGreen(), g_Sprite.GetTransBlue());
				SetDlgItemText(g_hMenuWnd, IDC_EDIT2, string);

				// Note: ��������Ʈ ����
				nCount = g_Sprite.GetSprCount();

				for(i = 0; i < nCount ; i++)
				{	// Note: ��������Ʈ ��ǥ ����
					AddListData(g_hCutList, g_Sprite.GetSprRect(i));
					//Note: ���� Ÿ�� ���� ==> ��������Ʈ�� ���� ������ �����Ƿ� 
					AddAniTimeList(g_hAniTimeList, g_Sprite.GetAniTime(i));	
				}

				// Note: ���� ��������Ʈ �߽���ǥ ����
				ptPoint = g_Sprite.GetCenterPos(0);
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT3, ptPoint.x, FALSE);
				SetDlgItemInt(g_hMenuWnd, IDC_EDIT4, ptPoint.y, FALSE);

				// Note: ���� �浹 ��ǥ ����						
				for(i = 0; i < g_Sprite.GetCollisionCount(0) ; i++)
					AddListData(g_hCollisionList, g_Sprite.GetCollisionRect(0, i));						
				
				//Note: ���� ���� ����
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
				SetWindowText(hWnd, strFileName); // ������ Ÿ��Ʋ �ٿ� ��������Ʈ ���ϸ� ���
				CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �ڸ��� ���
				EnableCutCtrl(g_hMenuWnd, TRUE);
				EnablePosCtrl(g_hMenuWnd, FALSE);
				EnableAniCtrl(g_hMenuWnd, FALSE);
				InvalidateRect(hWnd, 0, FALSE);
				break;			
			}

			break;

		case ID_32772: // ���� ����
			ZeroMemory(strFilePath, sizeof(strFilePath));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter2);	
			if(nResult != -1)
			{
				//���ϸ��̼� ���� ���� �� ��
				nCount = g_Sprite.GetSprCount();
				for(int i = 0; i < nCount ; i++)
				{
					ListView_GetItemText( g_hAniTimeList, i, 1, string, 10 );					
					g_Sprite.SetAniTime(i, atoi(string));
				}
				
				// ���ϸ��̼� ���� ���� ���� �� ��
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
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
		PatBlt( hBackBuffer, 0, 0, 800, 600, BLACKNESS ); // ��� �����

		switch(g_nCurrentMode)
		{
		case 0: // �ڸ��� ���
				if( g_Sprite.GetSrcImageDC() != NULL )
				{
					szBitmapSize = g_Sprite.GetImageSize();
					BitBlt(g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, g_Sprite.GetSrcImageDC(), 0, 0, SRCCOPY);

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

					StretchBlt( hBackBuffer, -g_xCurrentScroll, -g_yCurrentScroll, 
						szBitmapSize.cx * g_nExpansion, szBitmapSize.cy * g_nExpansion,
						g_hMemDC, 0, 0, szBitmapSize.cx, szBitmapSize.cy, SRCCOPY );			
				}

			break;
		case 1: // ��ǥ ���� ��� 
			if(g_Sprite.GetSprCount() > 0 )
			{
				nWidth = g_Sprite.GetSprWidth(g_nSprIndex);
				nHeight = g_Sprite.GetSprHeight(g_nSprIndex);

				if(hPosMemDC != NULL)
					DeleteDC(hPosMemDC);
				hPosMemDC = CreateCompatibleDC( hdc );
				hBitmap = CreateCompatibleBitmap( hdc, nWidth, nHeight ); 			 
				SelectObject( hPosMemDC, (HBITMAP)hBitmap );	// ��� ������ 0���� �����ȴ�.		
				DeleteObject( hBitmap );

				// ��������� ���� �޸�DC�� �����Ѵ�.
				rect = g_Sprite.GetSprRect(g_nSprIndex);
				TransparentBlt( hPosMemDC, 0, 0, nWidth, nHeight, g_Sprite.GetSrcImageDC(), rect.left, rect.top,
					nWidth, nHeight, g_Sprite.GetTransColor() );		

				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO4) == BST_CHECKED) // �߽���ǥ
				{					
					ptPoint = g_Sprite.GetCenterPos(g_nSprIndex);
				
					SetROP2( hPosMemDC, R2_NOTXORPEN);
					MoveToEx( hPosMemDC, 0, ptPoint.y, NULL ); // ����
					LineTo( hPosMemDC, rect.right, ptPoint.y );

					MoveToEx( hPosMemDC,  ptPoint.x, 0, NULL ); // ���� ��� 
					LineTo( hPosMemDC, ptPoint.x, rect.bottom);							
				}
				else if( IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED ) //�浹��ǥ
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

					// Note: ���õ� �浹��ǥ�� ����ũ�ϴ� �κ�
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

		case 2: // ���ϸ��̼� ��� 
			nCount = ListView_GetItemCount(g_hAniTimeList);
			if(nCount > 0 ) // ��������Ʈ �ε��� ����
			{
				nWidth = g_Sprite.GetSprWidth(g_nAniSprIndex);
				nHeight = g_Sprite.GetSprHeight(g_nAniSprIndex);
				rect = g_Sprite.GetSprRect(g_nAniSprIndex);
				
				ptPoint = g_Sprite.GetCenterPos(g_nAniSprIndex);
				nX = 400 - ptPoint.x*g_nAniRate;
				nY = 400 - ptPoint.y*g_nAniRate;			

				hAniMemDC = CreateCompatibleDC( hdc );
				hBitmap = CreateCompatibleBitmap( hdc, nWidth*g_nAniRate, nHeight*g_nAniRate ); //Ȯ������� �޸�DC ����			 
				SelectObject( hAniMemDC, (HBITMAP)hBitmap );	// ��� ������ 0���� �����ȴ�.		
				DeleteObject( hBitmap );

				TransparentBlt( hAniMemDC, 0, 0, nWidth*g_nAniRate, nHeight*g_nAniRate, g_Sprite.GetSrcImageDC(), 
					            rect.left, rect.top, nWidth, nHeight, g_Sprite.GetTransColor()); 
				BitBlt(hBackBuffer, nX, nY, nWidth*g_nAniRate, nHeight*g_nAniRate, hAniMemDC, 0, 0, SRCCOPY);
				DeleteDC(hAniMemDC);
			}						

			SetBkColor(hBackBuffer, RGB(0,0,0));
			SetTextColor(hBackBuffer, RGB(10, 255, 10));
			sprintf(string, "���� �ε���: %3d", g_nAniSprIndex);
			TextOut(hBackBuffer, 600, 10, string, strlen(string));
		
			SelectObject(hBackBuffer, GetStockObject(DC_PEN)); // �ü���� �⺻ ���� �����ؼ� ����� �� �ִ�.
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

		if(hPosMemDC != NULL) //���� �����̴�.
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
		InitListType0(g_hCutList); // �ڸ��� ����Ʈ ��Ʈ�� �ʱ�ȭ
		InitListType0(g_hCollisionList); // �ڸ��� ����Ʈ ��Ʈ�� �ʱ�ȭ
		InitAniTimeListType(g_hAniTimeList);
		InitAniPartListType(g_hAniPartList);
		
		EnablePosCtrl(hDlg, FALSE);	 // ��ǥ ���� ��Ʈ�� ��Ȱ��ȭ			
		EnableAniCtrl(hDlg, FALSE); // ���ϸ��̼� ���� ��Ʈ�� ��Ȱ��ȭ
		return (INT_PTR)TRUE;

	case WM_NOTIFY: // ����Ʈ �䰡 ���õǸ� 
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
		case 1: // ��������Ʈ ����Ʈ�� �ε����� �ٲ�� �浹��ǥ�� �߽���ǥ�� �ٲ��.
				if(hdr->hwndFrom == g_hCutList)
				{
					if(hdr->code == NM_CLICK)
					{ 
						nResult = ListView_GetNextItem( g_hCutList, -1, LVNI_ALL | LVNI_SELECTED );			
						if( nResult != -1)
						{
							g_nSprIndex = nResult;
							// �߽���ǥ ����
							ptCenterXY = g_Sprite.GetCenterPos(g_nSprIndex);
							SetDlgItemInt( g_hMenuWnd, IDC_EDIT3, ptCenterXY.x, FALSE );
							SetDlgItemInt( g_hMenuWnd, IDC_EDIT4, ptCenterXY.y, FALSE );
							//�浹��ǥ ����
							ListView_DeleteAllItems(g_hCollisionList); 
							nCount = g_Sprite.GetCollisionCount(g_nSprIndex);
							for( i = 0 ; i < nCount ; i++ )
							{
								AddListData(g_hCollisionList, g_Sprite.GetCollisionRect(g_nSprIndex, i));										
							}

							// Note: XOR �� �ɼ� ������ 						
							SetRect(&g_rtMouseXY, -1, -1, -1, -1); //Ŭ���ν�Ŵ							
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
							g_nAniSprIndex = atoi(buffer);  // ù ��° ��������Ʈ�� ���� �ش�.

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
			case IDC_RADIO1: // �ڸ��� ���, ������ ������ �� ���·� ��� �Ǿ�� �Ѵ�.
				// ��ũ�� ���¸� �����ϸ� �ȴ�.
				g_nCurrentMode = 0;
				szBmpSize = g_Sprite.GetImageSize();
				ScrollProcess( g_hWnd, szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);		
				EnableCutCtrl(hDlg, TRUE);	 // �ڸ��� �� Ȱ��ȭ	
				EnablePosCtrl(hDlg, FALSE);	 // ��ǥ ���� ��Ʈ�� ��Ȱ��ȭ			
				EnableAniCtrl(hDlg, FALSE); // ���ϸ��̼� ���� ��Ʈ�� ��Ȱ��ȭ	
				InvalidateRect(g_hWnd, NULL, FALSE);
				break;

			case IDC_RADIO2: // ��ǥ ���� ��� 
				// �ڸ��� ����� ����Ʈ ��Ʈ�ѿ� ���� ���� ���� �����Ѵ�.
				nCount = ListView_GetItemCount(g_hCutList);		
				if( nCount > 0 )
				{					
					// ��ǥ ���� �� ��� �ܿ��� ��� ��Ȱ�� ��Ų��.					
					g_nCurrentMode = 1;

					szBmpSize.cx = g_Sprite.GetSprHeight(g_nSprIndex);
					szBmpSize.cy = g_Sprite.GetSprWidth(g_nSprIndex);
					ScrollProcess( g_hWnd, szBmpSize.cx, szBmpSize.cy);					

					// �ʱ� ����
					SetDlgItemInt(hDlg, IDC_EDIT3, g_Sprite.GetCenterPos(g_nSprIndex).x, FALSE);
					SetDlgItemInt(hDlg, IDC_EDIT4, g_Sprite.GetCenterPos(g_nSprIndex).y, FALSE);

					EnableCutCtrl(hDlg, TRUE);
					EnablePosCtrl(hDlg, TRUE);	 
					EnableAniCtrl(hDlg, FALSE); // ���ϸ��̼� ���� ��Ʈ�� ��Ȱ��ȭ	

					CheckDlgButton(g_hMenuWnd, IDC_RADIO4, BST_CHECKED); // �߽���ǥ ���� ������ư
					CheckDlgButton(g_hMenuWnd, IDC_RADIO5, BST_UNCHECKED); // �߽���ǥ ���� ������ư
					SetCursor(g_hCrossCursor); //�⺻�� �߽���ǥ �����̹Ƿ�
					InvalidateRect(g_hWnd, NULL, FALSE);
				}else{ // ��������Ʈ�� �����Ƿ� ���� ��带 �ٽ� �����ϵ��� �Ѵ�.
					
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �ڸ��� ���
					CheckDlgButton(g_hMenuWnd, IDC_RADIO2, BST_UNCHECKED); // ��ǥ ���
					CheckDlgButton(g_hMenuWnd, IDC_RADIO3, BST_UNCHECKED); // ���� ���					
				}
				break;

			case IDC_RADIO3: // ���ϸ��̼� ���
				nCount = ListView_GetItemCount(g_hCutList);		
				if( nCount > 0 )
				{		
					g_nCurrentMode = 2;				
					EnableCutCtrl(hDlg, FALSE); //�ڸ��� ��Ʈ�� ��Ȱ��ȭ
					EnablePosCtrl(hDlg, FALSE);	// ��ǥ ���� ��Ʈ�� ��Ȱ��ȭ		
					EnableAniCtrl(hDlg, TRUE);  // ���ϸ��̼� ���� ��Ʈ�� ��Ȱ��ȭ

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
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �ڸ��� ���
					CheckDlgButton(g_hMenuWnd, IDC_RADIO2, BST_UNCHECKED); // ��ǥ ���
					CheckDlgButton(g_hMenuWnd, IDC_RADIO3, BST_UNCHECKED); // ���� ���
				}
				break;

			case IDC_BUTTON2: // Ȯ�� ��ư
				if(g_Sprite.GetSrcImageDC() != NULL )
				{
					switch(g_nCurrentMode)
					{
					case 0: // �ڸ��� Ȯ��
						g_nExpansion++;		
						szBmpSize = g_Sprite.GetImageSize();
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nExpansion, szBmpSize.cy * g_nExpansion);	
						break;
					case 1: // ��ǥ ���� Ȯ��
						g_nRate++;
						szBmpSize.cx = g_Sprite.GetSprWidth(g_nSprIndex);
						szBmpSize.cy = g_Sprite.GetSprHeight(g_nSprIndex);
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nRate, szBmpSize.cy * g_nRate);
						break;
					case 2: // ���ϸ��̼� Ȯ��
						g_nAniRate++;
						szBmpSize.cx = g_Sprite.GetSprWidth(g_nAniSprIndex);
						szBmpSize.cy = g_Sprite.GetSprHeight(g_nAniSprIndex);
						ScrollProcess(g_hWnd, szBmpSize.cx * g_nAniRate, szBmpSize.cy * g_nAniRate);
						break;
					}								
					InvalidateRect(g_hWnd, NULL, FALSE);
				}else{
					MessageBox(g_hWnd, "�̹����� �����ϴ�", "����", MB_OK);
				}
				return (INT_PTR)TRUE;

			case IDC_BUTTON3: // ��� ��ư
				if(g_Sprite.GetSrcImageDC() == NULL )
				{
				   MessageBox(g_hWnd, "�̹����� �����ϴ�", "����", MB_OK);
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

			case IDC_BUTTON4: // ���� ��� ��ư
				if(g_Sprite.GetSrcImageDC() == NULL )
				{
				   MessageBox(g_hWnd, "�̹����� �����ϴ�", "����", MB_OK);
				   break;
				}

				g_bIsTransColorChoice = TRUE;
				g_nBoxState = NONE;		
				InvalidateRect(g_hWnd, 0, FALSE);
				return (INT_PTR)TRUE;

			case IDC_BUTTON5:  // �ڸ� ��ǥ ��� ��ư				
				AddListData(g_hCutList, g_rtCutRect);							
				g_Sprite.AddCutRect(g_rtCutRect);
				if(g_nSprIndex == -1)
					g_nSprIndex = 0;

				return (INT_PTR)TRUE;

			case IDC_BUTTON6: // ��������Ʈ ����Ʈ �׸� ����
				if( g_nSprIndex == -1 )
					MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
				else
				{
					InsertListData(g_hCutList, g_nSprIndex, g_rtSprRect);						
					g_Sprite.InsertCutRect(g_nSprIndex, g_rtSprRect);
				}
					
				return (INT_PTR)TRUE;

			case IDC_BUTTON7: // ��������Ʈ ����Ʈ �׸� ����	
				if( g_Sprite.GetSprCount() <= 0 )
					MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
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
			//-------------------- ��ǥ ���� �޴� �κ� ----------------------------
			case IDC_BUTTON10: // �߽���ǥ ���� ��ư
				ptCenterXY.x = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
				ptCenterXY.y = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
				g_Sprite.SetCenterPos(g_nSprIndex, ptCenterXY);
				InvalidateRect(g_hWnd, 0, FALSE);
				return (INT_PTR)TRUE;
			case IDC_BUTTON11: // �浹 ��ǥ ���
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO5) == BST_CHECKED && g_nSprIndex >= 0 )
				{										
					AddListData(g_hCollisionList, g_rtMouseXY);		

					// Note: XOR �� �ɼ� ������ 						
					SetRect(&g_rtMouseXY, -1, -1, -1, -1); //Ŭ���ν�Ŵ
					InvalidateRect( g_hWnd, NULL, FALSE );
				}
				return (INT_PTR)TRUE;
			case IDC_RADIO4:
				SetCursor(g_hCrossCursor);
				InvalidateRect( g_hWnd, NULL, FALSE );
				return (INT_PTR)TRUE;

			case IDC_RADIO5: //�浹 ��ǥ ����
				SetCursor(g_hNormalCursor);
				InvalidateRect( g_hWnd, NULL, FALSE );
				return (INT_PTR)TRUE;

			case IDC_BUTTON12: // ���� �κ�
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED )
				{	//����Ʈ�� ������ ������ -1�� �����Ѵ�.				
					nResult = ListView_GetNextItem( g_hCollisionList, -1, LVNI_ALL | LVNI_SELECTED );				

					if( nResult == -1 )
						MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
					else
					{								
						ListView_DeleteItem(g_hCollisionList, nResult);
						nCount = ListView_GetItemCount(g_hCollisionList);						
						
						for( i = nResult ; i < nCount ; i++ ) // �����Ŀ� ������ ���� ��ħ
						{
							sprintf(buffer, "%d", i);
							ListView_SetItemText(g_hCollisionList, i, 0, buffer); 			
						}
						
						InvalidateRect( g_hWnd, NULL, FALSE );
					}
				}
				return (INT_PTR)TRUE;

			case IDC_BUTTON18: // �浹 ��ǥ ���� �κ�
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

			case IDC_BUTTON13: // ���� Ÿ�� ���� ��ư
				nCount = ListView_GetItemCount(g_hAniTimeList);
				if( nCount > 0 )
				{					
					dwAniTime = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
					sprintf(buffer, "%d", dwAniTime);					
					ListView_SetItemText( g_hAniTimeList, g_nAniSprIndex, 1, buffer );
					g_Sprite.SetAniTime(g_nAniSprIndex, dwAniTime);
				}

				return (INT_PTR)TRUE;
			case IDC_BUTTON14: // ���
				nCount = ListView_GetItemCount(g_hAniPartList);
				nIndex0 = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
				nIndex1 = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);
				InsertAniPartList(g_hAniPartList, nCount, nIndex0, nIndex1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON15: // ����
				nIndex0 = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
				nIndex1 = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);
				InsertAniPartList(g_hAniPartList, g_nAniPartListIndex, nIndex0, nIndex1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON17: // ����
				ListView_DeleteItem( g_hAniPartList, g_nAniSprIndex );					
				nCount =  ListView_GetItemCount( g_hAniPartList );
				for( i = g_nAniSprIndex ; i < nCount ; i++ )
				{
					sprintf( buffer, "%d", i );
					ListView_SetItemText( g_hAniPartList, i, 0, buffer );
				}

				return (INT_PTR)TRUE;

			case IDC_BUTTON19: // �÷���
				g_dwOldTime = GetTickCount();
				
				// AniPartList�� �ִ� ���ϸ��̼� ������ �ð��� ������ ��
				ListView_GetItemText(g_hAniPartList, g_nAniPartListIndex, 1, buffer, 10 );
				g_sAniPartRange.nIndex0 = atoi( buffer );
				ListView_GetItemText(g_hAniPartList, g_nAniPartListIndex, 2, buffer, 10 );
				g_sAniPartRange.nIndex1 = atoi( buffer );
				
				// ���ϸ��̼��� �ϱ� ���� ù ��° �ε����� ����
				ListView_GetItemText( g_hAniTimeList, g_sAniPartRange.nIndex0, 1, buffer, 10 );
				g_dwAniTime = atoi(buffer);			
				g_nAniSprIndex = g_sAniPartRange.nIndex0;	
								
				SetTimer(g_hWnd, 1, 16, NULL);
				InvalidateRect(g_hWnd, NULL, FALSE);
				return (INT_PTR)TRUE;

			case IDC_BUTTON20: // ����
				KillTimer(g_hWnd, 1);
				return (INT_PTR)TRUE;

			case IDC_BUTTON16: // ����
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
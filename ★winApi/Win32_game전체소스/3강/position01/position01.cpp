// position01.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
#include "stdafx.h"
#include "position01.h"
#include <CommDlg.h>
#include <commctrl.h>
#include "Position.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

SIZE g_szWndSize; // ��ũ�ѹٿ� ���� ����� �������� ũ��
SIZE g_szOrginMainWndize;  // �ʱ�ȭ �Ŀ� �����ϸ� �ȵȴ�. Ŭ���̾�Ʈ ������ 800x600�� �� ������ ũ���̴�.
HWND g_hWnd = NULL, g_hMenuWnd = NULL;     
CPosition g_PositionObj;
int g_nCutIndex = -1;
char *g_strListMenu[] = {"����", "x0", "y0", "x1", "y1" };
HWND g_CutListCtrl = NULL;
HWND g_hCollisionListCtrl = NULL;
int g_nCollisionIndex = -1;
int g_nRate = 1;
RECT g_rtMouseXY;
BOOL g_bIsBoxDraw;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_POSITION01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}	

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POSITION01));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);	
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POSITION01);
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
   RECT rect = { 0, 0, 800, 600};

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//


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
	ofn.lpstrDefExt = "pos";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //������ �ȵ� ���
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
	static char *strFilter[2] = { "�ڸ�����(*.cut)\0*.cut\0��ǥ����(*.pos)\0*.pos\0\0",
								"��ǥ����(*.pos)\0*.pos\0" };

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
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case ID_32771: // ���� ����
			 nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter[0]);
			 switch(nResult)
			 {
			 case 1: // sprite�� �ε��Ǹ� pos�� ���� �����Ѵ�.
					g_PositionObj.LoadCutInfo(hWnd, strFilePath);			
					g_PositionObj.CreatePosInfo();
					SetWindowText(hWnd, strFileName);					

					// Note: ��Ʈ�Ѱ� �ε��� �ʱ�ȭ
					g_nCutIndex = 0;
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT7, g_nCutIndex , TRUE);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT1, 0, FALSE);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT2, 0, FALSE);						

					ListView_DeleteAllItems(g_CutListCtrl);
					ListView_DeleteAllItems(g_hCollisionListCtrl);

					// Note: ����Ʈ ��Ʈ�� ������ ���  
					nCount = g_PositionObj.GetSpriteCount();						
					for(int i = 0 ; i <  nCount ; i++ )
						SetListData(g_CutListCtrl, g_PositionObj.GetSprRect(i));	

					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED); // �߽���ǥ ����						
					InvalidateRect(hWnd, NULL, FALSE); // ��������� �ʰ� ����Ѵ�. 
					break;
				case 2:					
					g_PositionObj.LoadPosInfo(strFilePath);						
								
					// Note: �浹 ��ǥ�� ����Ʈ �信 �ʱ� ����
					ListView_DeleteAllItems( g_hCollisionListCtrl );
					nCount = g_PositionObj.GetCollisionCount(g_nCutIndex);
					for(int i = 0 ; i < nCount ; i++ )
						SetListData( g_hCollisionListCtrl, g_PositionObj.GetCollisionRect(g_nCutIndex, i));							
					// �߽� ��ǥ ����
					ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT1, ptPoint.x, FALSE); 
					SetDlgItemInt(g_hMenuWnd, IDC_EDIT2, ptPoint.y, FALSE);						
					CheckDlgButton(g_hMenuWnd, IDC_RADIO1, BST_CHECKED);
					break;
			 }
			 
			 break;

		case ID_32772: // ���� ����
			if( FileSaveDilaog(hWnd, strFilePath, strFileName, strFilter[1] ) != -1 )
			{   // Note: ������ ������ pos �� �����̹Ƿ� �ε����� ������ �ʿ� ����
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
		if( MK_LBUTTON & wParam ) // ���콺�� �巡�� ����
		{	// �浹 ��ǥ�� ����ϴ� ����̸�
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

	case WM_RBUTTONDOWN: // ���õ� �浹��ǥ�� ����ũ ����
		if(g_bIsBoxDraw)
		{
			g_bIsBoxDraw = FALSE; 
			InvalidateRect( hWnd, NULL, FALSE );
		}
		break;

	case WM_LBUTTONDOWN:
		// note: �߽� ��ǥ ����
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
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

		if( g_nCutIndex != -1 )
		{			
			nWidth = g_PositionObj.GetSprWidth(g_nCutIndex);
			nHeight = g_PositionObj.GetSprHeight(g_nCutIndex);

			hMemDC = CreateCompatibleDC( hdc );
			hBitmap = CreateCompatibleBitmap( hdc, nWidth, nHeight ); 			 
			SelectObject( hMemDC, (HBITMAP)hBitmap );	// ��� ������ 0���� �����ȴ�.		
			DeleteObject( hBitmap );

			// ��������� ���� �޸�DC�� �����Ѵ�.
			rect = g_PositionObj.GetSprRect(g_nCutIndex);
			TransparentBlt( hMemDC, 0, 0, nWidth, nHeight, g_PositionObj.GetSrcImageDC(), rect.left, rect.top,
				nWidth, nHeight, g_PositionObj.GetTransColor() );		

			if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO1) == BST_CHECKED)
			{					
				ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
				
				SetROP2( hMemDC, R2_NOTXORPEN);
				MoveToEx( hMemDC, ptPoint.x - 2, ptPoint.y, NULL ); // ����
				LineTo( hMemDC,  ptPoint.x + 3, ptPoint.y );
				MoveToEx( hMemDC,  ptPoint.x, ptPoint.y- 2, NULL ); // ���� ��� 
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

				// Note: ���õ� �浹��ǥ�� ����ũ�ϴ� �κ�
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
					if(g_PositionObj.GetPosInfo() == NULL ) // ��ǥ ������ ���� ���� �����Ѵ�.
					{
						nia = (LPNMITEMACTIVATE)lParam;	// ���õ� �ε���	
						g_nCutIndex = nia->iItem;  // �ε����� �ѱ��.
						SetDlgItemInt(hDlg, IDC_EDIT7, g_nCutIndex , FALSE);
						InvalidateRect( g_hWnd, NULL, FALSE ); // ������ ���� ȭ���� ������.
						return (INT_PTR)TRUE;
					}
					else
					{ // �⺻������ �߽���ǥ�� 0, 0 �̰� �浹��ǥ�� üũ�ؼ� ó���Ѵ�.
						nia = (LPNMITEMACTIVATE)lParam;	// ���õ� �ε���	
						
						if( nia->iItem != g_nCutIndex ) // ���� ��������Ʈ�� �ε����� ���õ� �ε��� ��
						{						
							// Note: ���� ����Ʈ ��Ʈ�� ���� ������ �ٲ�� ���� ��� �浹��ǥ�� �����Ѵ�.
							nCount = ListView_GetItemCount( g_hCollisionListCtrl );
							if( nCount > 0 )
							{
								g_PositionObj.CreateCollisionRect(g_nCutIndex, nCount);
								for(i = 0 ; i < nCount ; i++)
									g_PositionObj.SetCollisionRect(g_nCutIndex, i, GetListData( g_hCollisionListCtrl, i ) );							
							}

							// Note: ������ �����͸� ������ �Ŀ� �ε����� �ٲ۴�.
							g_nCutIndex = nia->iItem;
							SetDlgItemInt(hDlg, IDC_EDIT7, g_nCutIndex , FALSE);
						
							// Note: �߽���ǥ ����
							ptPoint = g_PositionObj.GetSpriteCenterPos(g_nCutIndex);
							SetDlgItemInt(hDlg, IDC_EDIT1, ptPoint.x, FALSE);
							SetDlgItemInt(hDlg, IDC_EDIT2, ptPoint.y, FALSE);
						
							// Note: �浹 ��ǥ�� ����Ʈ ��Ʈ���� ���� �¾�, 0���̸� �ݺ��� �������� ����
							ListView_DeleteAllItems( g_hCollisionListCtrl ); 
							nCount = g_PositionObj.GetCollisionCount(g_nCutIndex);
							for( i = 0 ; i < nCount ; i++ )
								SetListData( g_hCollisionListCtrl, g_PositionObj.GetCollisionRect(g_nCutIndex, i));					

							InvalidateRect( g_hWnd, NULL, TRUE ); // ������ ���� ȭ���� ������.					
						}	
					}
				}
			}

			// Note: �浹 ��ǥ ����Ʈ ���� �׸��� Ŭ���Ǹ� Ŭ���� ��ǥ�� ȭ�鿡 ���
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
		case IDC_BUTTON1: // Ȯ��
			g_nRate++;
			InvalidateRect(g_hWnd, NULL, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON2: // ���
			if( g_nRate - 1 > 0 )
			{	
				g_nRate--;
				InvalidateRect(g_hWnd, NULL, TRUE);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON5: // ����
			ptPoint.x = GetDlgItemInt(hDlg, IDC_EDIT1, 0, FALSE); 
			ptPoint.y = GetDlgItemInt(hDlg, IDC_EDIT2, 0, FALSE);
			g_PositionObj.SetCenterPos(g_nCutIndex, ptPoint);
			InvalidateRect(g_hWnd, NULL, FALSE);
			return (INT_PTR)TRUE;

		case IDC_BUTTON6: // �浹��ǥ ��� ��ư		
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED && (g_nCutIndex != -1))
				{					
					SetListData(g_hCollisionListCtrl, g_rtMouseXY);		

					// Note: XOR �� �ɼ� ������ 						
					SetRect(&g_rtMouseXY, -1, -1, -1, -1); //Ŭ���ν�Ŵ
					InvalidateRect( g_hWnd, NULL, FALSE );
				}
				break;

		case IDC_BUTTON7: // �浹 ��ǥ ���� ��ư
				if(IsDlgButtonChecked(g_hMenuWnd, IDC_RADIO2) == BST_CHECKED && (g_nCutIndex != -1))
				{
					nIndex = ListView_GetNextItem( g_hCollisionListCtrl, -1, LVNI_ALL | LVNI_SELECTED );				

					if( nIndex == -1 )
						MessageBox( hDlg, "������ �׸��� ���� ������ �ּ���", "����", MB_OK );
					else
					{								
						ListView_DeleteItem( g_hCollisionListCtrl, nIndex );
						nCount = ListView_GetItemCount( g_hCollisionListCtrl );						
						
						for( i = nIndex ; i < nCount ; i++ ) // �����Ŀ� ������ ���� ��ħ
						{
							sprintf( string, "%d", i );
							ListView_SetItemText( g_hCollisionListCtrl, i, 0, string ); 			
						}
						
						InvalidateRect( g_hWnd, NULL, FALSE );
					}
				}
				break;

		case IDC_BUTTON8: // �浹 ��ǥ ���� ��ư
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

	idx = ListView_GetItemCount( hList ); //�ϳ� ���� ī��Ʈ�� �����ֱ⿡ �̸� �̿� 
	ITEM.iItem = idx; // Note: �߰� ������ ��� �ε��� 

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
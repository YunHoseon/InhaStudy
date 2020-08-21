// AniTool01.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
/*
���ϸ��̼� ���� ���� �� ������ ����

1. ���ϸ��̼� ���� ���� �߿��� ������ �ε��� ��������Ʈ�� ���������� 
   ������ �ð� �������� ����ϴ� ���̴�.
   �̸� ���� Ÿ�̸Ӹ� ����ϴ� ����� ���� ������ ������ ����� ������
   ��¿� ū ���̰� �����Ƿ� ���� ���� ������ �� �ִ� Ÿ�̸Ӹ� �̿��Ѵ�.
   1000 �и������尡 1���̹Ƿ� 1000 / 60 ���� �ϸ� 60 �������� �� 1 �����Ӵ�
   �ð� ������ �����Ƿ� �̸� Ȱ���Ѵ�. 16���� ����
   Ÿ�̸Ӹ� ������ �� �˾ƾ� �ϴ� ���� Ÿ�̸��� �ð��� 16���Ϸ� �����ص� 
   Ÿ�̸� �޽����� ���⿡ ���缭 �߻��ϴ� ���� �ƴϴ�.
   �� Ÿ�̸� �޽����� �Ѱ谡 ������ ���� 16�� ���絵 ���� FPS�� üũ�� ����
   �� 34 ~ 38 ������ ���´�. 
   30 FPS �̻� ������ ���ϸ��̼� �ð��� ���ߴ� ���� ������ �����Ƿ� �� �����
   ����Ѵ�.

2. ���� ������ ���� �ҽ��� ������ ����϶�.
   �̹� �ۼ��� ������ ǰ ���α׷����� �ҽ��� �� Ȱ���ϸ� �ð��� ����� ���� �� �ִ�.

3. ���ϸ��̼ǿ� �ʿ��� �����ʹ� ���ϸ��̼� �ð� ���ݿ� ���� DWORD ���� �ϳ��̴�.
   �׷��Ƿ� ���⼭�� Ŭ������ ���� ������ ���� ���� Sprite Ŭ������ ���� ����
   ���յǵ��� �Ѵ�.

4. �� ������ �ϼ��� ������ ��� ���� Win32 API ������ ���α׷��ֿ� ���ؼ� ���� ����� 
   ���̴�. �׸��� C++�� �⺻�� �н��Ͽ��� ���̹Ƿ� ���뿡�� MFC�� ������ ���� �͵� 
   ������ �� ���ٰ� �����Ѵ�.

5. ��� ���� ó������ �Ϻ��ϰ� �ɷ��� ������ ����� �ʿ����� �����ϰ� ó������ �ʹ� ū
   ��ȹ�� ��ǥ���ٴ� �� �ܰ辿 ��ȹ�� ��ǥ�� ���� ���ٴ� �������� ������ ���� ����
   ��� �����մϴ�. Good Bye!~~ ^^V
*/

#include "stdafx.h"
#include "AniTool01.h"
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
HWND g_SprListCtrl = NULL;
int g_nSprIndex = -1, g_nSize = 1;

DWORD *g_pAniTime, g_dwAniTime, g_dwOldTime;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ANITOOL01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANITOOL01));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANITOOL01));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ANITOOL01);
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
	ofn.lpstrDefExt = "ani";

	if( GetSaveFileName(&ofn) != 0 )
	{
		return ofn.nFilterIndex;
	}

	return -1; //������ �ȵ� ���
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
	static char *strFilter[2] = { "�ڸ�����(*.cut)\0*.cut\0��ǥ����(*.pos)\0*.pos\0��������(*.ani)\0*.ani\0",
								"��������(*.ani)\0*.ani\0" };
	static HDC hBackBuffer;	// ����� DC

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
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case ID_32771: // ����
			ZeroMemory(strFilePath, sizeof(strFileName));
			ZeroMemory(strFileName, sizeof(strFileName));
			nResult = FileOpenDilaog(hWnd, strFilePath, strFileName, strFilter[0]);			
			switch(nResult)
			{
			case 1: 
					g_PositionObj.LoadCutInfo(hWnd, strFilePath);			
					g_PositionObj.CreatePosInfo();
					ListView_DeleteAllItems(g_SprListCtrl);

					// ���� ��� �κ�
					ITEM.mask = LVIF_TEXT;
					ITEM.state = 0;
					ITEM.stateMask = 0;
					ITEM.iSubItem = 0;
					nCount = g_PositionObj.GetSprCount();
					for(int i = 0 ; i < nCount ; i++ )
					{
						ITEM.iItem = i; // Note: �߰� ������ ��� �ε��� 
						sprintf( string, "%d", i );
						ITEM.pszText = string;
						ListView_InsertItem( g_SprListCtrl, &ITEM);
					}

					g_nSprIndex = 0; // ��������Ʈ �ʱ� �ε��� ����
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

		case ID_32772: // ani ���� ����
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
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
		PatBlt( hBackBuffer, 0, 0, 800, 600, BLACKNESS ); // ��� �����

		if( g_nSprIndex != -1 )
		{	
			if(g_PositionObj.GetSprCount() > 0 ) // ��������Ʈ �ε��� ����
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
			sprintf(string, "���� �ε���: %3d", g_nSprIndex);
			TextOut(hBackBuffer, 600, 10, string, strlen(string));
		}
		

		SelectObject(hBackBuffer, GetStockObject(DC_PEN)); // �ü���� �⺻ ���� �����ؼ� ����� �� �ִ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
		lvColumn.pszText = "����";
		ListView_InsertColumn(g_SprListCtrl, 0, &lvColumn);

		lvColumn.cx = 150;
		lvColumn.pszText = "���ϸ��̼� �ð�";
		ListView_InsertColumn(g_SprListCtrl, 1, &lvColumn);
		return (INT_PTR)TRUE;

	case WM_NOTIFY: // ����Ʈ �䰡 ���õǸ�				
		hdr = (LPNMHDR)lParam;
		if(hdr->hwndFrom == g_SprListCtrl)
		{
			if(hdr->code == NM_CLICK)
			{
				nia = (LPNMITEMACTIVATE)lParam;	// ���õ� �ε���
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
		case IDC_BUTTON1: // ����
			GetDlgItemText(hDlg,IDC_EDIT1, string, 10); 
			ListView_SetItemText( g_SprListCtrl, g_nSprIndex, 1, string );							
			SetDlgItemInt( hDlg, IDC_EDIT1, 0, FALSE); //����Ʈ �ڽ����� ������ ����
			break;
		case IDC_BUTTON2: // �÷��̾� ��ư
			g_dwOldTime = GetTickCount();
			SetTimer(g_hWnd, 1, 16, NULL);
			// ����Ʈ ��Ʈ�ο� �ִ� �ʱ� ���ϸ��̼� �ð� �������� �κ�
			ListView_GetItemText( g_SprListCtrl, 0, 1, string, 10 );
			g_dwAniTime = atoi(string);			
			g_nSprIndex = 0;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON3: // ���� ��ư			
			KillTimer(g_hWnd, 1);
			g_nSprIndex = 0;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON4: // Ȯ�� ��ư
			g_nSize++;
			InvalidateRect(g_hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON5: // ��� ��ư			
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
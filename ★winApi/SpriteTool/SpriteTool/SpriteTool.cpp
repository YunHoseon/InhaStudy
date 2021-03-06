// SpriteTool.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SpriteTool.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	BottomWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MenuDlg(HWND, UINT, WPARAM, LPARAM);

HWND g_hWnd, g_hMenuWnd, g_hBottomWnd, g_hDlgWnd;
SIZE g_szMainWnd, g_szBottomWndSize, g_szMenuDlgSize;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPRITETOOL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPRITETOOL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPRITETOOL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPWSTR)MAKEINTRESOURCE(IDC_SPRITETOOL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

	wcex.lpszMenuName = NULL;
	wcex.lpfnWndProc = BottomWndProc;
	wcex.lpszClassName = L"BottomWnd";
	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd;
   
   g_hBottomWnd = g_hWnd = hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rtWnd = { 0, 0, 800, 600 }, rtDlg = {800, 0, 1200, 800 };
	static SIZE szWndSize, szDlgSize;
	OPENFILENAME ofn;
	static char strFileTitle[256], strFileExtension[10], strFile[256];

    switch (message)
    {
	case WM_CREATE:
		g_hMenuWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CUT_IMAGE), hWnd, MenuDlg);
		AdjustWindowRect(&rtWnd, WS_OVERLAPPEDWINDOW, TRUE);
		GetWindowRect(g_hMenuWnd, &rtDlg);
		szWndSize.cx = rtWnd.right - rtWnd.left;
		szWndSize.cy = rtWnd.bottom - rtWnd.top;
		szDlgSize.cx = rtDlg.right - rtDlg.left + 1;
		szDlgSize.cy = rtDlg.bottom - rtDlg.top + 1;
		MoveWindow(hWnd, 10, 10, szWndSize.cx, szWndSize.cy, TRUE);
		MoveWindow(g_hMenuWnd, 10 + szWndSize.cx, 10, szDlgSize.cx, szDlgSize.cy, TRUE);
		break;
	case WM_SIZE:
		GetWindowRect(hWnd, &rtWnd);
		MoveWindow(hWnd, rtWnd.left, rtWnd.top, szWndSize.cx, szWndSize.cy, TRUE);
		break;
	case WM_MOVE:
		GetWindowRect(hWnd, &rtWnd);
		MoveWindow(hWnd, rtWnd.left, rtWnd.top, szWndSize.cx, szWndSize.cy, TRUE);
		MoveWindow(g_hMenuWnd, rtWnd.right, rtWnd.top, szDlgSize.cx, szDlgSize.cy, TRUE);
		break;
    case WM_COMMAND:
        {
            wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_FILE_OPEN:
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrTitle = "파일을 선택해주세요";
				ofn.lpstrFileTitle = strFileTitle;
				ofn.lpstrFile = strFile;
				ofn.lpstrFilter = "임시파일(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0";
				ofn.nMaxFile = 256;
				ofn.nMaxFileTitle = 256;

				if (GetOpenFileName(&ofn) != 0)
				{
					switch (ofn.nFilterIndex)
					{
					case 1:
						MessageBox(0, strFile, "임시 파일", MB_OK);
						break;
					case 2:
						MessageBox(0, strFile, "모든 파일", MB_OK);
						break;
					default:
						break;
					}
				}
				break;

			case ID_FILE_SAVE:
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrTitle = "저장할 파일을 선택해주세요";
				ofn.lpstrFileTitle = strFileTitle;
				ofn.lpstrFile = strFile;
				ofn.lpstrFilter = "임시파일(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0";
				ofn.nMaxFile = 256;
				ofn.nMaxFileTitle = 256;

				if (GetSaveFileName(&ofn) != 0)
				{
					switch (ofn.nFilterIndex)
					{
					case 1:
						MessageBox(0, strFile, "임시 파일", MB_OK);
						break;
					case 2:
						MessageBox(0, strFile, "모든 파일", MB_OK);
						break;
					default:
						break;
					}
				}
				break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DestroyWindow(g_hMenuWnd);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}*/
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK BottomWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	SIZE szWindowSize, szMainWndSize;

	switch (message)
	{
	case WM_CREATE:
		g_hDlgWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SPRITETOOL_DIALOG), hWnd, MenuDlg);
		szWindowSize.cx = GetSystemMetrics(SM_CXSCREEN);
		szWindowSize.cy = GetSystemMetrics(SM_CYSCREEN);

		szMainWndSize.cx = szWindowSize.cx * 0.75f;
		szMainWndSize.cy = (szWindowSize.cy - 30) * 0.7f;
		g_szBottomWndSize.cx = szMainWndSize.cx;
		g_szBottomWndSize.cy = (szWindowSize.cy - 30) - szMainWndSize.cx;
		g_szMenuDlgSize.cx = szWindowSize.cx - szMainWndSize.cx;
		g_szMenuDlgSize.cy = (szWindowSize.cy - 30);
		MoveWindow(hWnd, 0, 0, szMainWndSize.cx, szMainWndSize.cy, TRUE);
		g_hBottomWnd = CreateWindow("BottomWnd", "뷰2", WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_VISIBLE,
			0, szMainWndSize.cy, g_szBottomWndSize.cx, g_szBottomWndSize.cy, hWnd, NULL, hInst, NULL);
		MoveWindow(g_hDlgWnd, szMainWndSize.cx, 0, g_szMenuDlgSize.cx, g_szMenuDlgSize.cy, TRUE);
		break;
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		DestroyWindow(g_hMenuWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
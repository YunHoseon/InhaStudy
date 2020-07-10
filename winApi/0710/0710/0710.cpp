// 0710.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0710.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawGrid(HDC hdc, int startX, int startY, int endX, int endY, int gap)
{
	for (int i = 0; i < endX / gap - 1; i++)
	{
		MoveToEx(hdc, startX + gap*i, startY, NULL);
		LineTo(hdc, startX + gap*i, endY);
	}
	 
	for (int i = 0; i < endY / gap - 1; i++)
	{
		MoveToEx(hdc, startX, startY + gap*i, NULL);
		LineTo(hdc, endX , startY + gap*i);
	}
}

void DrawCircle(HDC hdc, int centerX, int centerY, int r)
{
	Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void DrawFlower(HDC hdc, int centerX, int centerY, int r, int num)
{
	double angle = 360 / num;
	int r2 = 0;

	r2 = r * sin(angle / 2) / (1 - (sin(angle / 2)));

	/*for (int i = 0; i < num; i++)
	{
		
	}*/
}

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
    LoadStringW(hInstance, IDC_MY0710, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0710));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0710));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground =  CreateSolidBrush(RGB(150, 200, 150));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0710);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR str[100];
	static int count, yPos;
	static SIZE size;

    switch (message)
    {
	case WM_CREATE:
		count = 0;
		yPos = 0;
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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

	case WM_CHAR:
	{
		//HDC hdc = GetDC(hWnd);
		//TextOut(hdc, 100, 100, _T("키 눌림 확인"), 7);

		if (wParam == VK_BACK && count > 0)
		{
			count--;
			yPos -= 20;
		}
		else if (wParam == VK_RETURN)
		{
			count = 0;
			yPos = yPos + 20;
		}
		else
			str[count++] = wParam;

		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);

		//ReleaseDC(hWnd, hdc);
	}
		break;
	case WM_KEYDOWN:
		
		break;
	case WM_KEYUP:
		break;

    case WM_PAINT:
        {	
			// TODO: Add any drawing code that uses hdc here...
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			
			//WCHAR str[15] = L"임우재 Babo";
			//RECT rc;
			//rc.left = 100;
			//rc.top = 100;
			//rc.right = 400;
			//rc.bottom = 400;
			//
			//SetTextColor(hdc, RGB(200, 100, 150));
			//
			////TextOut(hdc, 300, 300, str, _tcslen(str));
			//DrawText(hdc, str, _tcsclen(str), &rc, DT_RIGHT | DT_TOP);

			RECT rcs[2];

			TCHAR str2[32] = _T("ID : 임우재바보");
			TextOut(hdc, 10, 10, str2, _tcslen(str2));

			TCHAR str3[32] = _T("GOLD : 5252");
			TextOut(hdc, 450, 10, str3, _tcslen(str3));

			RECT rc;
			rc.left = 50;
			rc.right = 400;
			rc.top = yPos;
			rc.bottom = 300 + yPos;

			
			GetTextExtentPoint(hdc, str, _tcsclen(str), &size);
			TextOut(hdc, 0, yPos, str, _tcslen(str));
			//DrawText(hdc, str, _tcsclen(str), &rc, DT_LEFT | DT_TOP);
			SetCaretPos(size.cx, yPos);

			//DrawGrid(hdc, 100, 100, 450, 450, 50);
			DrawCircle(hdc, 250, 250, 50);
			DrawFlower(hdc, 250, 250, 50, 12);

			//MoveToEx(hdc, 100, 100, NULL);
			//LineTo(hdc, 200, 200);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
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

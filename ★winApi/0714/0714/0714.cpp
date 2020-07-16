// 0714.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0714.h"
#include <string>
#include "Shape.h"

#define PI 3.141592

using namespace std;

POINT starPoint[10];

void DrawCircle(HDC hdc, int centerX, int centerY, int r)
{
	Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void DrawStar(HDC hdc, int x, int y, int r)
{
	MoveToEx(hdc, x, y, NULL);

	for (int i = 0; i < 9; i += 2)
	{
		starPoint[i].x = x + (r * sin(72 * (i/2) * PI / 180));
		starPoint[i].y = y - (r * cos(72 * (i/2) * PI / 180));
		SetPixel(hdc, starPoint[i].x, starPoint[i].y, (0,0,0));
	}

	float a = starPoint[0].y - starPoint[4].y;
	float b = -(starPoint[0].x - starPoint[4].x);
	float c = starPoint[2].y - starPoint[8].y;
	float d = -(starPoint[2].x - starPoint[8].x);
	float e = a * starPoint[0].x + b * starPoint[0].y;
	float f = c * starPoint[2].x + d * starPoint[2].y;

	starPoint[1].x = (e*d - b*f) / (a*d - b*c); 
	starPoint[1].y = (a*f - e*c) / (a*d - b*c);

	double r2 = pow(pow(x - starPoint[1].x, 2) + pow(y - starPoint[1].y, 2), 0.5);

	for (int i = 3; i < 10; i += 2)
	{
		starPoint[i].x = x + (r2 * sin((72 * (i/2)+36) * PI / 180));
		starPoint[i].y = y - (r2 * cos((72 * (i/2)+36) * PI / 180));
		SetPixel(hdc, starPoint[i].x, starPoint[i].y, (0, 0, 0));
	}

	Polygon(hdc, starPoint, 10);
}

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
    LoadStringW(hInstance, IDC_MY0714, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0714));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0714));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0714);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
	POINT point[5] = { {55, 51} , {51, 65}, {60, 57}, {50, 57}, {59, 65} };
	static int keyboard = 0;
	static int x = 50, y = 50;
	static RECT rectRange;

	static int mx = 50 , my = 50;

    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &rectRange);

		SetTimer(hWnd, 1, 70, NULL);
		//SetTimer(hWnd, 2, 70, NULL);

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

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			keyboard = 1;
			y -= 20;
			if (y - 20 < rectRange.top)
				y += 20;
			break;

		case VK_LEFT:
			keyboard = 2;
			x -= 20;
			if (x - 20 < rectRange.left)
				x += 20;
			break;

		case VK_RIGHT:
			keyboard = 3;
			x += 20;
			if (x + 20 > rectRange.right)
				x -= 20;
			break;

		case VK_DOWN:
			keyboard = 4;
			y += 20;
			if (y + 20 > rectRange.bottom)
				y -= 20;
			break;

		default:
			break;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_KEYUP:
		/*InvalidateRgn(hWnd, NULL, TRUE);
		keyboard = 0;*/
		break;

	case WM_SIZE:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		break;
	}

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (mx > x)
			{
				x += 10;
				if (x > mx)
					x = mx;
			}
			else if (mx < x)
			{
				x -= 10;
				if (x < mx)
					x = mx;
			}

			if (my > y)
			{
				y += 7;
				if (y > my)
					y = my;
			}
			else if (my < y)
			{
				y -= 7;
				if (y < my)
					y = my;
			}

			break;
		/*case 2:
			y += 5;
			if (y + 20 > rectRange.bottom)
				y -= 5;
			break;*/
		}

		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;
		
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			/*RECT rt[4];
			rt[0] = { 200, 0, 300, 100 };
			rt[1] = { 100, 100, 200, 200 };
			rt[2] = { 400, 100, 300, 200 };
			rt[3] = { 200, 200, 300, 300 };

			TCHAR str[32] = _T("우재바보");

			DrawText(hdc, str, _tcslen(str), &rt, DT_SINGLELINE | DT_TOP | DT_LEFT);
			DrawText(hdc, str, _tcslen(str), &rt, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hdc, str, _tcslen(str), &rt, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);

			Polygon(hdc, point, 5);*/

			/*HPEN hPen, oldPen, hPen2;
			hPen = CreatePen(PS_SOLID, 1, RGB(150, 200, 150));
			hPen2 = CreatePen(PS_DOT, 1, RGB(150, 150, 200));

			oldPen = (HPEN)SelectObject(hdc, hPen);
			SelectObject(hdc, hPen2);

			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(RGB(250, 250, 100));

			SelectObject(hdc, hBrush);
			DrawStar(hdc, 200, 200, 50);

			//oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

			SelectObject(hdc, hPen);
			for (int i = 0; i < 5; i++)
				DrawStar(hdc, 300 + (i * 20), 300 + (i * 20), 100 + (i * 20));

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			DeleteObject(hPen2);*/

			/*Rectangle(hdc, 200, 0, 300, 100);
			Rectangle(hdc, 100, 100, 200, 200);
			Rectangle(hdc, 400, 100, 300, 200);
			Rectangle(hdc, 200, 200, 300, 300);

			DrawText(hdc, _T("위쪽"), _tcslen(_T("위쪽")), &rt[0], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hdc, _T("왼쪽"), _tcslen(_T("왼쪽")), &rt[1], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hdc, _T("오른쪽"), _tcslen(_T("오른쪽")), &rt[2], DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DrawText(hdc, _T("아래쪽"), _tcslen(_T("아래쪽")), &rt[3], DT_SINGLELINE | DT_VCENTER | DT_CENTER);

			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(RGB(150, 200, 250));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			if (keyboard == 1)				
				Rectangle(hdc, 200, 0, 300, 100);
			else if(keyboard == 2)
				Rectangle(hdc, 100, 100, 200, 200);
			else if (keyboard == 3)
				Rectangle(hdc, 400, 100, 300, 200);
			else if (keyboard == 4)
				Rectangle(hdc, 200, 200, 300, 300);

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);*/

			HBRUSH hBrush;
			hBrush = CreateSolidBrush(RGB(250, 210, 200));
			SelectObject(hdc, hBrush);

			//DrawCircle(hdc, x, y, 30);
			DrawStar(hdc, x, y, 30);
			
			DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		//KillTimer(hWnd, 1);
		//KillTimer(hWnd, 2);
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

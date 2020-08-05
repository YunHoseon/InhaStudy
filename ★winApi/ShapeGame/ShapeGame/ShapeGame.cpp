// ShapeGame.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "ShapeGame.h"

using namespace std;

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

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHAPEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHAPEGAME));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHAPEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SHAPEGAME);
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
	static vector<CShape*> cShapes;
	static RECT rectRange;

    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &rectRange);
		SetTimer(hWnd, 1, 70, NULL);
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

	case WM_TIMER:
	{
		int randNum = 0;

		switch (wParam)
		{
		case 1:
			for (CShape *cRect : cShapes)
			{
				for (int i = 0; i < cRect->vertexNum; i++)		//도형 회전
				{
					float xTmp = cRect->points[i].x - cRect->x;
					float yTmp = cRect->points[i].y - cRect->y;

					cRect->points[i].x = cos(20 * PI / 180) * xTmp - sin(20 * PI / 180) * yTmp + cRect->x;
					cRect->points[i].y = sin(20 * PI / 180) * xTmp + cos(20 * PI / 180) * yTmp + cRect->y;
				}

	/*			for (CShape *cRect : cShapes)
				{
					for (int i = 0; i < cRect->vertexNum; i++)
					{
						cRect->points[i].x = cos(30 * PI / 180) * (float)(cRect->points[i].x - cRect->x) - sin(30 * PI / 180) * (float)(cRect->points[i].y - cRect->y) + cRect->x;
						cRect->points[i].y = sin(30 * PI / 180) * (float)(cRect->points[i].x - cRect->x) + cos(30 * PI / 180) * (float)(cRect->points[i].y - cRect->y) + cRect->y;
					}
				}*/

				cRect->x += cRect->GetSpeed() * cRect->moveToX;
				cRect->y += cRect->GetSpeed() * cRect->moveToY;

				for (int i = 0; i < cRect->vertexNum; i++)	//도형 이동
				{
					cRect->points[i].x += cRect->GetSpeed() * cRect->moveToX;
					cRect->points[i].y += cRect->GetSpeed() * cRect->moveToY;
				}

				for (int i = 0; i < cRect->vertexNum; i++)		//벽에 막히게
				{
					if (cRect->points[i].y + (cRect->size * 0.5) <= rectRange.top + cRect->size)
						cRect->SetmoveToY(1);

					if (cRect->points[i].y + (cRect->size * 0.5) >= rectRange.bottom)
						cRect->SetmoveToY(-1);

					if (cRect->points[i].x + (cRect->size * 0.5) <= rectRange.left + cRect->size)
						cRect->SetmoveToX(1);

					if (cRect->points[i].x + (cRect->size * 0.5) >= rectRange.right)
						cRect->SetmoveToX(-1);
				}
			}

			//for (CShape *cRect : cShapes)
			//{
			//
			//}

			break;

		default:
			break;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
	}

		break;

	case WM_LBUTTONDOWN:
	{
		srand(time(NULL));
		int mx = LOWORD(lParam), my = HIWORD(lParam);
		CRectangle *cRect = new CRectangle(mx, my);

		cShapes.push_back(cRect);

		InvalidateRgn(hWnd, NULL, TRUE);
	}
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			
			for (CShape *cRect : cShapes)
				cRect->DrawShape(hdc);
			
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
		KillTimer(hWnd, 1);
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

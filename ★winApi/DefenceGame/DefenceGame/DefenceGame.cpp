#include "stdafx.h"
#include "DefenceGame.h"

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
    LoadStringW(hInstance, IDC_DEFENCEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENCEGAME));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFENCEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 497, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush;
	static RECT rectRange;					//윈도우 창 사각형
	SIZE crSize;							//글자 크기 측정(캐럿)

	static TCHAR playerID[9];				//아이디
	static int charNum;						//글자 수

	static int mx;							//마우스 x좌표
	static int my;							//마우스 y좌표

	bool col = false;

    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &rectRange);	//윈도우 창 크기 저장
		CreateCaret(hWnd, NULL, 5, 15);		//캐럿 생성

		charNum = 0;
		gameState = START;
		break;

    case WM_COMMAND:
        {
            //int wmId = LOWORD(wParam);
            // Parse the menu selections:
            /*switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }*/
        }
        break;

	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			for (CObjects *blocks : objects)
			{
				if (blocks->objType == type_Enemy)
				{
					blocks->center.y += 5;							//적 아래로 이동

					for (int i = 0; i < blocks->vertexNum; i++)
					{
						blocks->points[i].y += 5;

						/*if (blocks->points[i].y >= 500)
						{
							objects.pop_back();
							delete blocks;
						}*/
					}
						
					for (int i = 0; i < blocks->vertexNum; i++)		//적 회전
					{
						float xTmp = blocks->points[i].x - blocks->center.x;
						float yTmp = blocks->points[i].y - blocks->center.y;

						blocks->points[i].x = cos(20 * PI / 180) * xTmp - sin(20 * PI / 180) * yTmp + blocks->center.x;
						blocks->points[i].y = sin(20 * PI / 180) * xTmp + cos(20 * PI / 180) * yTmp + blocks->center.y;
					}
				}
			}

			for (int i = 0; i < objects.size(); i++)	//충돌 처리
			{
				for (int j = 0; j < objects.size(); j++)
				{
					if (objects[j]->objType == type_Enemy && objects[i]->objType == type_Block)
					{
						int dir = pow(pow(objects[i]->center.x - objects[j]->center.x, 2) + pow(objects[i]->center.y - objects[j]->center.y, 2), 0.5);

						if (dir <= objects[j]->size + objects[i]->size)		//충돌 했을 때
							col = true;
					}
				}
			}
			break;

		case 2:
			srand(time(NULL));
			int randNum = rand() % 6;

			EnemyObj *enemeis = new EnemyObj(40 + (randNum * 80), 100);
			objects.push_back(enemeis);
			break;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
	}
		break;

	case WM_CHAR:
		if(gameState == START)
			GameStartMenu(hWnd, wParam, &charNum, player.GetID());
		break;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(RGB(250, 200, 200));

			switch (gameState)
			{
			case START:
			{
				RECT rc_title = { 100, 200, 400, 300 };
				DrawText(hdc, _T("인베이더 L"), _tcslen(_T("인베이더 L")), &rc_title, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				RECT rc_ID = { 150, 350, 400, 400 };
				DrawText(hdc, _T("ID"), _tcslen(_T("ID")), &rc_ID, DT_SINGLELINE | DT_LEFT);

				Rectangle(hdc, 180, 345, 350, 375);
				SetCaretPos(185, 350);
				TextOut(hdc, 185, 350, player.GetID(), _tcslen(player.GetID()));
			}
				break;

			case INGAME:
			{
				RECT rc_ID = { 10, 10, 100, 40 };
				DrawText(hdc, player.GetID(), _tcslen(player.GetID()), &rc_ID, DT_SINGLELINE | DT_LEFT);

				RECT rc_Score = { 300, 10, 450, 50 };
				DrawText(hdc, to_wstring(player.GetScore()).c_str(), _tcslen(to_wstring(player.GetScore()).c_str()), &rc_Score, DT_SINGLELINE | DT_RIGHT);

				TextOut(hdc, 185, 350, to_wstring(mx).c_str(), _tcslen(to_wstring(mx).c_str()));

				for (CObjects *blocks : objects)
				{
					if (blocks->objType == type_Block)
						blocks->DrawObj(hdc);
						
					if (blocks->objType == type_Enemy)
						blocks->DrawObj(hdc);
				}
			}
				break;

			case END:
				break;

			default:
				break;
			}

			DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
		DestroyCaret();
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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

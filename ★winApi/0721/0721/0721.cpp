// 0721.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0721.h"

#pragma comment(lib, "msimg32.lib")		//투명색 지정하기 위해

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

HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hTransparentImage;
BITMAP bitTransparent;

//HBITMAP hAniImage;
//BITMAP bitAni;
//const int Sprite_Size_X = 57;
//const int Sprite_Size_Y = 52;
//int run_Frame_max = 0;
//int run_Frame_min = 0;
//int cur_Frame = run_Frame_min;

HBITMAP hAniImage;	//
BITMAP bitAni;
const int Sprite_Size_X = 32;
const int Sprite_Size_Y = 32;
int run_Frame_max = 0;
int run_Frame_min = 0;
int cur_Frame = run_Frame_min;
int dir = 0;
int ax = 300, ay = 100;

bool sizeChanged = false;

RECT rectView;
void DrawRectText(HDC hdc);

HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);

void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdateFrame(HWND hWnd); 

void DrawRect(HDC hdc, int centerX, int centerY, int r)
{
	Rectangle(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void DrawCircle(HDC hdc, int centerX, int centerY, int r)
{
	Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

POINT starPoint[10];
void DrawStar(HDC hdc, int x, int y, int r)
{
	MoveToEx(hdc, x, y, NULL);

	for (int i = 0; i < 9; i += 2)
	{
		starPoint[i].x = x + (r * sin(72 * (i / 2) * PI / 180));
		starPoint[i].y = y - (r * cos(72 * (i / 2) * PI / 180));
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
		starPoint[i].x = x + (r2 * sin((72 * (i / 2) + 36) * PI / 180));
		starPoint[i].y = y - (r2 * cos((72 * (i / 2) + 36) * PI / 180));
	}

	Polygon(hdc, starPoint, 10);
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	UpdateFrame(hWnd);
	//InvalidateRgn(hWnd, NULL, FALSE);
}

TCHAR sKeyState[128];

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)	//
{
	if (GetKeyState('A') & 0x8000)
	{
		dir = 1;

		if (GetKeyState('S') & 0x8000)
		{
			dir = 4;
			ay += 10;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			dir = 6;
			ay -= 10;
		}
		ax -= 10;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		dir = 0;

		if (GetKeyState('D') & 0x8000)
		{
			dir = 5;
			ax += 10;
		}
		ay += 10;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		dir = 2;

		if (GetKeyState('W') & 0x8000)
		{
			dir = 7;
			ay -= 10;
		}
		ax += 10;
	}
	else if (GetKeyState('W') & 0x8000)
	{
		dir = 3;

		if (GetKeyState('A') & 0x8000)
		{
			dir = 6;
			ax -= 10;
		}
		ay -= 10;
	}
	else
	{
		wsprintf(sKeyState, TEXT(""));
	}
}

/* DialogBox */

BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR word[256];

	/* CheckBox */
	static int Check[3], Radio;
	TCHAR hobby[][30] = { _T("독서"), _T("음악감상"), _T("게임") };
	TCHAR sex[][30] = { _T("여자"), _T("남자") };
	TCHAR output[200];

	static HWND hCombo;
	static int selection;
	TCHAR name[20];

	switch (iMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hButton;
		/*hButton = GetDlgItem(hDlg, ID_BUTTON_PRINT);
		EnableWindow(hButton, FALSE);*/

		CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE);
		hCombo = GetDlgItem(hDlg, IDC_COMBO_LIST);

	}
		SetWindowPos(hDlg, HWND_TOP, (rectView.left + (rectView.right - rectView.left) / 2) - 400, (rectView.top + (rectView.bottom - rectView.top)/ 2) - 300, 800, 600, NULL);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;*/
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_PRINT:
		{
			HDC hdc = GetDC(hDlg);
			TextOut(hdc, 10, 10, _T("Hello Dialog"), 12);
			ReleaseDC(hDlg, hdc);
		}
		break;

		case ID_BUTTON_COPY:
			GetDlgItemText(hDlg, IDC_EDIT_INPUT, word, 256);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, word);
			break;

		case ID_BUTTON_DELETE:
			SetDlgItemText(hDlg, IDC_EDIT_INPUT, _T(""));
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, _T(""));
			break;

		case ID_BUTTON_END:
			EndDialog(hDlg, 0);
			break;

		case IDC_CHECK_READING:
			Check[0] = 1 - Check[0];
			break;

		case IDC_CHECK_MUSIC:
			Check[1] = 1 - Check[1];
			break;

		case IDC_CHECK_GAME:
			Check[2] = 1 - Check[2];
			break;

		case IDC_RADIO_FEMALE:
			Radio = 0;
			break;

		case IDC_RADIO_MALE:
			Radio = 1;
			break;

		case IDC_BUTTON_OUTPUT:
			_stprintf_s(output, _T("선택한 취미는 %s %s %s 입니다.\r\n 선택한 성별은 %s입니다."), 
				Check[0] ? hobby[0] : _T(""),
				Check[1] ? hobby[1] : _T(""), 
				Check[2] ? hobby[2] : _T(""), 
				sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_SAMPLE, output);
			break;

		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name);
			return 0;

		case IDC_BUTTON_DELETE:
			SendMessage(hCombo, CB_DELETESTRING, selection, 0);
			return 0;

		case IDC_COMBO_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			break;
		}
	}
	return false;
 }

 /* split window */
#define IDC_CHILD_BTN			100
#define IDC_CHILD_BTN_CIRCLE	101
#define IDC_CHILD_BTN_RECT		102
#define IDC_CHILD_BTN_STAR		103

 HWND childHwnd[3];

 enum Shape { EMPTY, CIRCLE, RECTANGLE, STAR };
 enum Shape shape = EMPTY;
 static int mx, my;

 LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
 {
	 HWND hButton;
	 HDC hdc = GetDC(childHwnd[0]);

	 switch (iMsg)
	 {
	 case WM_CREATE:
		 /*hButton[0] = CreateWindow(_T("button"), _T("확인"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			 200, 10, 100, 25, hWnd, (HMENU)IDC_CHILD_BTN, hInst, NULL);*/
		 break;

		 //case WM_COMMAND:
			// switch (LOWORD(wParam))
			// {
			//	 /*case IDC_CHILD_BTN:
			//	 {
			//		 HDC hdc = GetDC(hWnd);
			//		 TextOut(hdc, 0, 10, _T("Child2"), 6);
			//		 ReleaseDC(hWnd, hdc);
			//		 return 0;
			//	 }
			//	 break;*/
			// }
			// break;

	 case WM_PAINT:
		 switch (shape)
		 {
		 case CIRCLE:
			 DrawCircle(hdc, mx, my, 50);
			 break;

		 case RECTANGLE:
			 DrawRect(hdc, mx, my, 50);
			 break;

		 case STAR:
			 DrawStar(hdc, mx, my, 50);
			 break;

		 default:
			 break;
		 }
		 break;

	 case WM_LBUTTONDOWN:
		 mx = LOWORD(lParam);
		 my = HIWORD(lParam);
		 InvalidateRect(hWnd, NULL, FALSE);
		 break;

	 case WM_DESTROY:
		 break;

	 }
	 ReleaseDC(hWnd, hdc);
	 return DefWindowProc(hWnd, iMsg, wParam, lParam);
 }

 LRESULT CALLBACK ChildWndProc2(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
 {
	 HDC hdc = GetDC(childHwnd[1]);

	 switch (iMsg)
	 {
	 case WM_PAINT:
	 {
		 PAINTSTRUCT ps;
		 HDC hdc = BeginPaint(hWnd, &ps);

		 switch (shape)
		 {
		 case CIRCLE:
			 DrawCircle(hdc, 100, 100, 80);
			 break;

		 case RECTANGLE:
			 DrawRect(hdc, 100, 100, 80);
			 break;

		 case STAR:
			 DrawStar(hdc, 100, 100, 80);
			 break;
		 }
		 EndPaint(hWnd, &ps);
	 }
		break;
	 }
	 ReleaseDC(childHwnd[1], hdc);
	 return DefWindowProc(hWnd, iMsg, wParam, lParam);
 }

 LRESULT CALLBACK ChildWndProc3(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
 {
	 HWND hButton[3];

	 switch (iMsg)
	 {
	 case WM_CREATE:
		 hButton[0] = CreateWindow(_T("button"), _T("원"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			 200, 40, 100, 25, hWnd, (HMENU)IDC_CHILD_BTN_CIRCLE, hInst, NULL);
		 hButton[1] = CreateWindow(_T("button"), _T("사각형"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			 200, 70, 100, 25, hWnd, (HMENU)IDC_CHILD_BTN_RECT, hInst, NULL);
		 hButton[2] = CreateWindow(_T("button"), _T("별"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			 200, 100, 100, 25, hWnd, (HMENU)IDC_CHILD_BTN_STAR, hInst, NULL);
		 break;

	 case WM_COMMAND:

		 switch (LOWORD(wParam))
		 {
		 case IDC_CHILD_BTN_CIRCLE:
			 shape = CIRCLE;
			 break;

		 case IDC_CHILD_BTN_RECT:
			 shape = RECTANGLE;
			 break;

		 case IDC_CHILD_BTN_STAR:
			 shape = STAR;
			 break;
		 }
		 InvalidateRect(childHwnd[1], NULL, TRUE);
		 break;

	 }
	 return DefWindowProc(hWnd, iMsg, wParam, lParam);
 }

void OutFromFile(TCHAR filename[], HWND hWnd)
{
	FILE *fptr;
	HDC hdc;
	int line;
	TCHAR buffer[500];
	line = 0;
	hdc = GetDC(hWnd);

#ifdef _UNICODE
	_tfopen_s(&fptr, filename, _T("r, ccs = UNICODE"));
#else
	_tfopen_s(&fptr, filename, _T("r"));
#endif // _UNICODE
	while (_fgetts(buffer, 100, fptr) != NULL)
	{
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
			buffer[_tcslen(buffer) - 1] = NULL;

		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}

	fclose(fptr);
	ReleaseDC(hWnd, hdc);
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
    LoadStringW(hInstance, IDC_MY0721, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0721));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0721));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0721);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	//wcex.lpfnWndProc = ChildWndProc;
	//wcex.lpszMenuName = NULL;
	//wcex.lpszClassName = _T("Child1");
	//RegisterClassExW(&wcex);

	//wcex.lpfnWndProc = ChildWndProc2;
	//wcex.lpszMenuName = NULL;
	//wcex.lpszClassName = _T("Child2");
	//RegisterClassExW(&wcex);

	//wcex.lpfnWndProc = ChildWndProc3;
	//wcex.lpszMenuName = NULL;
	//wcex.lpszClassName = _T("Child3");
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1100, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

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
	//static int mx, my;
	//static int shape = 0;

	OPENFILENAME ofn;
	TCHAR str[100], lpstrFile[100] = _T("");
	TCHAR filter[] = _T("Every File(*.*) \0*.*\0TextFile\0*.txt;*.doc\0");

	OPENFILENAME sfn;

	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	int i;

	static HMENU hMenu, hSubMenu;

    switch (message)
    {
	case WM_CREATE:
		/*hMenu = GetMenu(hWnd);
		hSubMenu = GetSubMenu(hMenu, 2);
		EnableMenuItem(hSubMenu, ID_DRAW_CIRCLE, MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_DRAW_RECT, MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_DRAW_STAR, MF_GRAYED);*/

		CreateBitmap();
		
		SetTimer(hWnd, 123, 100, AniProc);	//
		SetTimer(hWnd, 111, 100, KeyStateProc);

		//GetClientRect(hWnd, &rectView);
		GetClientRect(hWnd, &rectView);
		childHwnd[0] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child1"), NULL, WS_CHILD | WS_VISIBLE, 0, 0, 
			rectView.right/2, rectView.bottom / 2 + 1,  hWnd, NULL, hInst, NULL);

		childHwnd[1] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child2"), NULL, WS_CHILD | WS_VISIBLE, 0,
			rectView.bottom/2+1, rectView.right/2, rectView.bottom / 2-1, hWnd, NULL, hInst, NULL); 

		childHwnd[2] = CreateWindowExW(WS_EX_CLIENTEDGE, _T("Child3"), _T("우재바보"), WS_CHILD | WS_VISIBLE, rectView.right/2 + 1,
			rectView.top, rectView.right/2, rectView.bottom, hWnd, NULL, hInst, NULL);
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
           /* case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

			case ID_DRAW_CIRCLE:
				MessageBox(NULL, L"Circle", L"Draw", MB_OK);
				shape = 1;
				break;
			case ID_DRAW_RECT:
				MessageBox(NULL, L"Rectangle", L"Draw", MB_OK);
				shape = 2;
				break;
			case ID_DRAW_STAR:
				MessageBox(NULL, L"Star", L"Draw", MB_OK);
				shape = 3;
				break;

			case ID_FILEOPEN:
				memset(&ofn, 0, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFilter = filter;
				ofn.lpstrFile = lpstrFile;
				ofn.nMaxFile = 100;
				ofn.lpstrInitialDir = _T(".");

				if (GetOpenFileName(&ofn) != 0)
				{
					_stprintf_s(str, _T("%s 파일을 열겠습니까?"), ofn.lpstrFile);
					MessageBox(hWnd, str, _T("열기 선택"), MB_OK);

					OutFromFile(ofn.lpstrFile, hWnd);
				}
				break;

			case ID_FILESAVE:
				memset(&sfn, 0, sizeof(OPENFILENAME));
				sfn.lStructSize = sizeof(OPENFILENAME);
				sfn.hwndOwner = hWnd;
				sfn.lpstrFilter = filter;
				sfn.lpstrFile = lpstrFile;
				sfn.nMaxFile = 100;
				sfn.lpstrInitialDir = _T(".");

				if (GetSaveFileName(&sfn) != 0)
				{
					_stprintf_s(str, _T("%s 파일을 저장하겠습니까?"), sfn.lpstrFile);
					MessageBox(hWnd, str, _T("저장하기 선택"), MB_OK);

				}
				break;

			case ID_CHANGE_COLOR:

				for (i = 0; i < 16; i++)
					tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);

				memset(&COLOR, 0, sizeof(CHOOSECOLOR));
				COLOR.lStructSize = sizeof(CHOOSECOLOR);
				COLOR.hwndOwner = hWnd;
				COLOR.lpCustColors = tmp;
				COLOR.Flags = CC_FULLOPEN;

				if (ChooseColor(&COLOR) != 0)
				{
					color = COLOR.rgbResult;
					InvalidateRgn(hWnd, NULL, TRUE);
				}
				break;*/

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break; 

	//case WM_TIMER:
	//	UpdateFrame(hWnd);
	//	InvalidateRgn(hWnd, NULL, FALSE);
	//	break;

	case WM_RBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg6_1Proc);
		break;

	case WM_SIZE:
		//GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectView);
		sizeChanged = true;
		break;

	case WM_MOVE:
		GetWindowRect(hWnd, &rectView);
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			//DrawBitmap(hWnd, hdc);
			//DrawBitmapDoubleBuffering(hWnd, hdc);
			//DrawRectText(hdc);

			/*hBrush = CreateSolidBrush(color);
			OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			switch (shape)
			{
			case 1:
				DrawCircle(hdc, mx, my, 30);
				break;
			case 2:
				DrawRect(hdc, mx, my, 30);
				break;
			case 3:
				DrawStar(hdc, mx, my, 30);
				break;

			default:
				break;
			}

			SelectObject(hdc, OldBrush);
			DeleteObject(hBrush);*/
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DeleteBitmap();
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

void DrawRectText(HDC hdc)
{
	static int xPos = 0;
	static int speed = 10;
	TCHAR strTest[] = _T("\\(^▽^)/");
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, xPos, 10, strTest, _tcslen(strTest));

	//TextOut(hdc, 100, 10, sKeyState, _tcslen(sKeyState));
	
	if (xPos >= rectView.right - (rectView.right % speed) || xPos < 0)
	{
		speed *= -1;
	}
	xPos += speed;
}

void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

	if (sizeChanged)
	{
		DeleteObject(hDoubleBufferImage);
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		sizeChanged = false;
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);
	
	{
		hMemDC2 = CreateCompatibleDC(hMemDC);	//이미지 찢어짐 방지
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hMemDC2);
	}

	{
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		BitBlt(hMemDC, 100, 100, bx, by, hMemDC2, 0, 0, SRCCOPY);
		TransparentBlt(hMemDC, 200, 100, bx, by, hMemDC2,
			0, 0, bx, by, RGB(255, 0, 255));
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hMemDC2);
	}

	{
		hMemDC2 = CreateCompatibleDC(hMemDC);	//
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
		bx = bitAni.bmWidth / 6;
		by = bitAni.bmHeight / 8;

		int xStart = cur_Frame * bx;
		int yStart = 0 + by * dir;

		TransparentBlt(hMemDC, ax, ay, bx * 2, by * 2, hMemDC2,
			xStart, yStart, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hMemDC2);
	}

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
		hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);

	DeleteDC(hMemDC);
}

void CreateBitmap()
{
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\fom.bmp"), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}
	
	{
		hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("images\\sigong.bmp"), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
	}

	{
		hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images\\character.bmp"), IMAGE_BITMAP,	//
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hAniImage, sizeof(BITMAP), &bitAni);
		run_Frame_max = bitAni.bmWidth / Sprite_Size_X - 1;
		run_Frame_min = 0;
		cur_Frame = run_Frame_min;
	}
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	
	{
		hMemDC = CreateCompatibleDC(hdc);	//이미지 찢어짐 방지
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hOldBitmap);
	}

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTransparentImage);
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hdc, 200, 100, bx, by, hMemDC,
			0, 0, bx, by, RGB(255, 0, 255));
		SelectObject(hMemDC, hOldBitmap);
	}

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
		bx = bitAni.bmWidth / 16;
		by = bitAni.bmHeight / 2;

		int xStart = cur_Frame * bx;
		int yStart = 0;

		TransparentBlt(hdc, 300, 100, bx, by, hMemDC,
			xStart, yStart, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
	}
	DeleteDC(hMemDC);
}

void DeleteBitmap()
{
	DeleteObject(hBackImage);
	DeleteObject(hTransparentImage);
	DeleteObject(hAniImage);
}

void UpdateFrame(HWND hWnd)	//
{
	cur_Frame++;

	if (cur_Frame > run_Frame_max)
		cur_Frame = run_Frame_min;
}

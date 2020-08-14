// 0813Omok.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0813Omok.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC	WM_USER + 2
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

extern Bitmap bitmap;
extern Map map;

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
    LoadStringW(hInstance, IDC_MY0813OMOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0813OMOK));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0813OMOK));
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
      CW_USEDEFAULT, 0, 1010, 770, nullptr, nullptr, hInstance, nullptr);

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
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA wsadata;
	static SOCKET s;
	static TCHAR tcMessage[200];
	static TCHAR szbuffer[100];
	static TCHAR str[100];
	static SOCKADDR_IN addr = { 0 };
	int msgLen;
	static char buffer[100];
	static int count;

	static int mx, my;
	static vector<TCHAR*> messages;

    switch (message)
    {
	case WM_CREATE:
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
		{
			MessageBox(NULL, _T("socket failed"), _T("Error"), MB_OK);
			return 0;
		}
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("connect failed"), _T("Error"), MB_OK);
			return 0;
		}
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

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

		//case WM_MOUSEMOVE:
		//	mx = LOWORD(lParam);
		//	my = HIWORD(lParam);
		//	InvalidateRgn(hWnd, NULL, TRUE);
		//	break;

		case WM_LBUTTONDOWN:
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			map.LocationStone(mx, my);
			InvalidateRgn(hWnd, NULL, TRUE);
			break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			Rectangle(hdc, 750, 675, 980, 700);
			map.DrawMap(hdc);

			if (_tcscmp(tcMessage, _T("")))
			{
				for (int i = 0; i < messages.size();i++)
					TextOut(hdc, 760, 30 * i, messages[i], (int)_tcslen(messages[i]));
			}
			TextOut(hdc, 760, 680, str, _tcslen(str));

			/*RECT rc_Score = { 300, 10, 450, 50 };
			DrawText(hdc, to_wstring(mx).c_str(), _tcslen(to_wstring(mx).c_str()), &rc_Score, DT_SINGLELINE | DT_RIGHT);
			RECT rc_Score2 = { 300, 10, 500, 50 };
			DrawText(hdc, to_wstring(my).c_str(), _tcslen(to_wstring(my).c_str()), &rc_Score2, DT_SINGLELINE | DT_RIGHT);*/

			map.DrawStone(hdc, mx, my);
			
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_ASYNC:
		switch (lParam)
		{
		case FD_READ:
		{
			msgLen = recv(s, buffer, 100, 0);
			buffer[msgLen] = NULL;

			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, strlen(buffer), szbuffer, 100);

			TCHAR *tmpBuffer = new TCHAR[_tcslen(szbuffer)];
			wsprintf(tmpBuffer, L"%s", szbuffer);
			messages.push_back(tmpBuffer);
			memset(szbuffer, 0, sizeof(szbuffer));
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), tcMessage, msgLen);
			tcMessage[msgLen] = NULL;
#else
			strcpy_s(msg, buffer);

#endif
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
		default:
			break;
		}
		break;

	case WM_CHAR:
	{
		if (wParam == VK_RETURN)
			if (s == INVALID_SOCKET)
				return 0;
			else
			{
#ifdef _UNICODE
				msgLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msgLen, NULL, NULL);

				TCHAR *tmpBuffer2 = new TCHAR[_tcslen(str)];
				wsprintf(tmpBuffer2, L"%s", str);
				messages.push_back(tmpBuffer2);
#else
				strcpy_s(buffer, str);
				msgLen = strlen(buffer);

#endif
				send(s, (LPSTR)buffer, strlen(buffer) + 1, 0);
				memset(buffer, 0, sizeof(buffer));
				count = 0;
				return 0;
			}
		if (wParam == VK_BACK && count > 0)
		{
			count--;
		}
		else
		{
			str[count++] = wParam;
		}

		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);
	}
	return 0;

    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
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

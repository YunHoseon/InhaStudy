// 0813Omok_Server.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0813Omok_Server.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define WM_ASYNC	WM_USER + 2
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
    LoadStringW(hInstance, IDC_MY0813OMOK_SERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0813OMOK_SERVER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0813OMOK_SERVER));
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
      CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

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
	static WSADATA wsadata;
	static SOCKET s;
	static vector<SOCKET> vecCs;
	static TCHAR tcMessage[200];	//유니코드 문자열용 저장소
	static char buffer[100];		//클라이언트 데이터를 읽기위한 임시저장소
	static TCHAR szbuffer[100];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static TCHAR str[100];			//접속 메시지
	static int count;
	int size, msgLen;

	static vector<TCHAR*> messages;

    switch (message)
    {
	case WM_CREATE:
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
		{
			MessageBox(NULL, _T("binding failed"), _T("Error"), MB_OK);
			return 0;
		}

		if (listen(s, 5) == -1)	//SOCKET_ERROR
		{
			MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
			return 0;
		}
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);
		break;

	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
		{
			size = sizeof(c_addr);
			SOCKET cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			vecCs.push_back(cs);

			WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

			TCHAR *log = new TCHAR[32];
			wsprintf(log, L"%d 님이 접속했습니다.", cs);
			messages.push_back(log);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;

		case FD_READ:
		{
			msgLen = recv(wParam, buffer, 100, 0);
			buffer[msgLen] = NULL;

			for (int i = 0; i < vecCs.size(); i++)
				send(vecCs[i], buffer, strlen(buffer), 0);
		}
		break;

		case FD_CLOSE:
		{
			closesocket(wParam);
			TCHAR *log = new TCHAR[32];
			wsprintf(log, L"%d 님이 나갔습니다.", wParam);
			messages.push_back(log);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;

		default:
			break;
		}
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			for (int i = 0; i < messages.size(); i++)
				TextOut(hdc, 20, i * 30, messages[i], _tcslen(messages[i]));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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

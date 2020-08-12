// 0812WinServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0812WinServer.h"
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

int WinServer();

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
    LoadStringW(hInstance, IDC_MY0812WINSERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0812WINSERVER));

	//return WinServer();

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0812WINSERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0812WINSERVER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WSADATA wsadata;
	static SOCKET s, cs;
	static TCHAR tcMessage[200];
	static char buffer[100];
	static TCHAR szbuffer[100];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static TCHAR str[100];
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
		else
		{
			MessageBox(NULL, _T("binding success"), _T("Success"), MB_OK);
		}

		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);

		if (listen(s, 5) == -1)	//SOCKET_ERROR
		{
			MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
			return 0;
		}
		break;

	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ);
			break;
		case FD_READ:
		{
			msgLen = recv(cs, buffer, 100, 0);
			buffer[msgLen] = NULL;

			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, strlen(buffer), szbuffer, 100);

			TCHAR *tmpBuffer = new TCHAR[_tcslen(szbuffer)];
			wsprintf(tmpBuffer,L"%s", szbuffer);
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

			if (_tcscmp(tcMessage, _T("")))
			{
				for (int i = 0; i < messages.size();i++)
				{
					TextOut(hdc, 20, 30 * i, messages[i], (int)_tcslen(messages[i]));
				}
			}
				
			TextOut(hdc, 20, 500, str, _tcslen(str));
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_CHAR:
		if (wParam == VK_RETURN)
			if (cs == INVALID_SOCKET)
			{
				return 0;
			}
			else
			{
#ifdef _UNICODE
				msgLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msgLen, NULL, NULL);

				TCHAR *tmpBuffer2 = new TCHAR[_tcslen(str)];
				wsprintf(tmpBuffer2, L"%s", str);
				messages.push_back(tmpBuffer2);
#else
				strcpy_s(msg, buffer);

#endif
				send(cs, (LPSTR)buffer, strlen(buffer) + 1, 0);
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
		return 0;

	/*case WM_KEYDOWN:
		if (cs == INVALID_SOCKET)
			break;
		send(cs, "반가워 Client!", 15, 0);
		break;*/
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

int WinServer()
{
	WSADATA wsadata;
	SOCKET s;
	TCHAR message[300];
	SOCKADDR_IN addr = { 0 };

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
	else
	{
		MessageBox(NULL, _T("binding success"), _T("Success"), MB_OK);
	}

	if (listen(s, 5) == -1)	//SOCKET_ERROR
	{
		MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
		return 0;
	}
	else
	{
		MessageBox(NULL, _T("listen success"), _T("Success"), MB_OK);
	}
		
	do
	{
		SOCKADDR_IN c_addr;
		char buffer[100];
#ifdef _UNICODE
		TCHAR wbuffer[100];
#endif // _UNICODE
		int msgLen;
		int size = sizeof(c_addr);
		SOCKET cs = accept(s, (LPSOCKADDR)&c_addr, &size);
		msgLen = recv(cs, buffer, 100, 0);
		buffer[msgLen] = NULL;

#ifdef _UNICODE
		msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), wbuffer, msgLen);
		wbuffer[msgLen] = NULL;
		_stprintf_s(message, _T("클라이언트 메시지 : %s, 서버를 종료하시겠습니까?"), wbuffer);
#else
		_stprintf_s(message, _T("클라이언트 메시지 : %s, 서버를 종료하시겠습니까?"), buffer);
#endif
	} while (MessageBox(NULL, message, _T("Server Message"), MB_YESNO) == IDNO);
	
	closesocket(s);
	WSACleanup();

	return 0;
}

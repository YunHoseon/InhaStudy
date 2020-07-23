#include "stdafx.h"
#include "DefenceGame.h"

#define MAX_LOADSTRING 100
const int FILESIZE = 1024;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

typedef struct PLAYERDATA
{
	int score;
	TCHAR id[9];
};

vector<PLAYERDATA> datas;

bool Compare(PLAYERDATA a, PLAYERDATA b)
{
	return a.score > b.score;
}

void SaveFile()
{
	ofstream fp;

	PLAYERDATA* playerData = new PLAYERDATA;
	fp.open("data.dat", ios_base::out | ios_base::binary | ios_base::app);

	if (fp.is_open())									//파일이 열렸을 때
	{
		wcscpy(playerData->id, player.GetID());
		playerData->score = player.GetScore();

		fp.write((char*)playerData, sizeof(PLAYERDATA));
		
		fp.close();
	}

	delete playerData;
}

void LoadFile() 
{
	ifstream fp;

	PLAYERDATA* playerData = new PLAYERDATA;

	fp.open("data.dat", ios_base::in | ios_base::binary);
	
	while(!fp.eof())
	{
 		fp.read((char*)playerData, sizeof(PLAYERDATA));
		datas.push_back(*playerData);		//(벡터)데이터 컨테이너에 저장
	}
	datas.pop_back();

	sort(datas.begin(), datas.end(), Compare);

	delete playerData;
}

void DeleteObjects()
{
	BlockObj *bObj;
	EnemyObj *eObj;
	BulletObj *blObj;

	while (blockList.size() > 0)
	{
		bObj = blockList.back();
		blockList.pop_back();
		delete bObj;
	}

	while (enemyList.size() > 0)
	{
		eObj = enemyList.back();
		enemyList.pop_back();
		delete eObj;
	}

	while (bulletList.size() > 0)
	{
		blObj = bulletList.back();
		bulletList.pop_back();
		delete blObj;
	}
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

	float xTmp = playerObj.points[1].x - playerObj.center.x;	//회전 연산
	float yTmp = playerObj.points[1].y - playerObj.center.y;

	static int mx;							//마우스 좌표
	static int my;

    switch (message)
    {
	case WM_CREATE:
		GetClientRect(hWnd, &rectRange);	//윈도우 창 크기 저장
		CreateCaret(hWnd, NULL, 5, 15);		//캐럿 생성

		charNum = 0;
		gameState = START;
		break;

	case WM_KEYDOWN:
		if (gameState == INGAME)
		{
			switch (wParam)
			{
			case 97:
			case VK_LEFT:
				playerObj.points[1].x = cos(-(10 * PI / 180)) * xTmp - sin(-(10 * PI / 180)) * yTmp + playerObj.center.x;
				playerObj.points[1].y = sin(-(10 * PI / 180)) * xTmp + cos(-(10 * PI / 180)) * yTmp + playerObj.center.y;
				break;

			case 100:
			case VK_RIGHT:
				playerObj.points[1].x = cos(10 * PI / 180) * xTmp - sin(10 * PI / 180) * yTmp + playerObj.center.x;
				playerObj.points[1].y = sin(10 * PI / 180) * xTmp + cos(10 * PI / 180) * yTmp + playerObj.center.y;
				break;

			case VK_SPACE:
			{
				BulletObj *bullets = new BulletObj(playerObj.points[1].x, playerObj.points[1].y);	//총알 생성
				bulletList.push_back(bullets);

				bullets->bx = playerObj.center.x - playerObj.points[1].x;
				bullets->by = playerObj.center.y - playerObj.points[1].y;
			}
				break;

			default:
				break;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
		}
			break;

	case WM_CHAR:
		if (gameState == START)
		{
			GameStartMenu(hWnd, wParam, &charNum, player.GetID());
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (gameState == END)
		{
			if ((mx >= 300 && mx <= 450) && (my >= 600 && my <= 650))		//종료 버튼
				PostQuitMessage(0);
			else if ((mx >= 50 && mx <= 200) && (my >= 600 && my <= 650))	//다시 시작 버튼
			{
				player.SetScore(0);
				playerObj.points[1].x = playerObj.center.x;
				playerObj.points[1].y = playerObj.center.y - (playerObj.size + 20);

				gameState = INGAME;
				CreateObjects();

				SetTimer(hWnd, 1, 70, NULL);
				SetTimer(hWnd, 2, 1000, NULL);

				InvalidateRgn(hWnd, NULL, TRUE);
			}
		}
		break;

	case WM_TIMER:
	{
		list<EnemyObj*>::iterator iter = enemyList.begin();
		list<BlockObj*>::iterator iter2 = blockList.begin();
		list<BulletObj*>::iterator iter3 = bulletList.begin();

		switch (wParam)
		{
		case 1:
		{
			cObject->Collision();								//적&블록 충돌

			for (iter = enemyList.begin(); iter != enemyList.end();)
			{
				(*iter)->center.y += 5;							//적 아래로 이동

				for (int i = 0; i < (*iter)->vertexNum; i++)	//적 회전
				{
					(*iter)->points[i].y += 5;					//꼭짓점들도 이동

					float xTmp = (*iter)->points[i].x - (*iter)->center.x;
					float yTmp = (*iter)->points[i].y - (*iter)->center.y;

					(*iter)->points[i].x = cos(20 * PI / 180) * xTmp - sin(20 * PI / 180) * yTmp + (*iter)->center.x;
					(*iter)->points[i].y = sin(20 * PI / 180) * xTmp + cos(20 * PI / 180) * yTmp + (*iter)->center.y;
				}

				if ((*iter)->center.y >= rectRange.bottom)
					iter = enemyList.erase(iter);				//범위 벗어나면 삭제
				else
					iter++;
			}

			for (iter3 = bulletList.begin(); iter3 != bulletList.end();)	//총알 움직임
			{
				(*iter3)->center.x -= (*iter3)->bx / 2;
				(*iter3)->center.y -= (*iter3)->by / 2;
				iter3++;
			}

			if (blockList.size() == 0)							//블록이 모두 없어지면 게임 오버
			{
				SaveFile();
				gameState = END;

				KillTimer(hWnd, 2);
				KillTimer(hWnd, 1);
			}
		}
			break;

		case 2:
			srand(time(NULL));
			int randNum = rand() % 6 + 1;

			for (int i = 1; i < randNum; i++)
			{
				int randNum2 = rand() % 6;
				EnemyObj *enemeis = new EnemyObj(40 + (randNum2 * 80), 100);		//적 생성
				enemyList.push_back(enemeis);
			}
			
			break;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
	}
		break;

	/*case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRgn(hWnd, NULL, TRUE);
		break;*/

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
				playerObj.DrawObj(hdc);

				RECT rc_ID = { 10, 10, 100, 40 };
				DrawText(hdc, player.GetID(), _tcslen(player.GetID()), &rc_ID, DT_SINGLELINE | DT_LEFT);

				RECT rc_Score = { 300, 10, 450, 50 };
				DrawText(hdc, to_wstring(player.GetScore()).c_str(), _tcslen(to_wstring(player.GetScore()).c_str()), &rc_Score, DT_SINGLELINE | DT_RIGHT);

				for (EnemyObj *it_enemies : enemyList)
					it_enemies->DrawObj(hdc);

				for (BlockObj *it_blocks : blockList)
					it_blocks->DrawObj(hdc);

				for (BulletObj *it_bullets : bulletList)
					it_bullets->DrawObj(hdc);
			}
				break;

			case END:
			{
				DeleteObjects();
				LoadFile();

				RECT rc_Rank = { 200, 100, 300, 200 };
				DrawText(hdc, _T("RANK"), _tcslen(_T("RANK")), &rc_Rank, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				RECT rc_Result[5];

				for (int i = 0; i < 5 && i < datas.size(); i++)					//랭킹 출력
				{
					rc_Result[i] = { 150, 200 + (i*50), 350, 300 + (i * 50) };

					DrawText(hdc, datas[i].id, _tcslen(datas[i].id), &rc_Result[i], DT_SINGLELINE | DT_LEFT);
					DrawText(hdc, to_wstring(datas[i].score).c_str(), _tcslen(to_wstring(datas[i].score).c_str()), &rc_Result[i], DT_SINGLELINE | DT_RIGHT);
				}
				
				Rectangle(hdc, 50, 600, 200, 650);
				Rectangle(hdc, 300, 600, 450, 650);

				RECT rc_Restart = { 50, 600, 200, 650 };
				DrawText(hdc, _T("다시하기"), _tcslen(_T("다시하기")), &rc_Restart, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				RECT rc_Quit = { 300, 600, 450, 650 };
				DrawText(hdc, _T("종료"), _tcslen(_T("종료")), &rc_Quit, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
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

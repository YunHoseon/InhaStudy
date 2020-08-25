#include "stdafx.h"
#include "StartScene.h"

extern Singleton *singleton;

StartScene::StartScene()
{
	startGame = false;

	startBtn = { 280, 250, 320, 270 };
	loadBtn = { 280, 280, 320, 300 };
	quitBtn = { 280, 310, 320, 330 };
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
}

void StartScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	static int mx, my;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (mx > startBtn.left && mx < startBtn.right &&
			my > startBtn.top && my < startBtn.bottom)
		{
			startGame = true;
			singleton->sceneManager->SceneChange(GameState::INGAME);

		}
		else if (mx > loadBtn.left && mx < loadBtn.right &&
			my > loadBtn.top && my < loadBtn.bottom)
		{

		}
		else if (mx > quitBtn.left && mx < quitBtn.right &&
			my > quitBtn.top && my < quitBtn.bottom)
			PostQuitMessage(0);
		break;
	default:
		break;
	}
}

void StartScene::Render(HWND hWnd, HDC hdc)
{
	Rectangle(hdc, 280, 250, 320, 270);
	DrawText(hdc, _T("START"), _tcslen(_T("START")), &startBtn, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 280, 280, 320, 300);
	DrawText(hdc, _T("LOAD"), _tcslen(_T("LOAD")), &loadBtn, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	Rectangle(hdc, 280, 310, 320, 330);
	DrawText(hdc, _T("QUIT"), _tcslen(_T("QUIT")), &quitBtn, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void StartScene::Free(HWND hWnd)
{
	startGame = false;
}

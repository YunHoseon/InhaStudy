#include "stdafx.h"
#include "StartScene.h"

extern Singleton *singleton;

StartScene::StartScene()
{
	startGame = false;

	drawTitle = { 290, 150, 500, 180 };
	drawStartBtn = { 150, 430, 300, 500 };
	drawQuitBtn = { 490, 430, 640, 500 };
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
	startGame = false;
}

void StartScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	static int mx, my;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (mx > drawStartBtn.left && mx < drawStartBtn.right &&
			my > drawStartBtn.top && my < drawStartBtn.bottom)
		{
			startGame = true;
			singleton->sceneManager->SceneChange(GameState::INGAME);

		}
		else if (mx > drawQuitBtn.left && mx < drawQuitBtn.right &&
			my > drawQuitBtn.top && my < drawQuitBtn.bottom)
		{
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
}

void StartScene::Render(HWND hWnd, HDC hdc)
{
	DrawText(hdc, _T("¶¥µû¸Ô±â"), _tcslen(_T("¶¥µû¸Ô±â")), &drawTitle, DT_SINGLELINE | DT_CENTER);

	Rectangle(hdc, 150, 430, 300, 500);
	DrawText(hdc, _T("START"), _tcslen(_T("START")), &drawStartBtn, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	Rectangle(hdc, 490, 430, 640, 500);
	DrawText(hdc, _T("QUIT"), _tcslen(_T("QUIT")), &drawQuitBtn, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void StartScene::Free()
{
	startGame = false;
}

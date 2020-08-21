#pragma once
#include "Sprite.h"
#include "GameFrame.h"
enum BUTTON_STATE { BUTTON_DOWN, BUTTON_UP, BUTTON_NORMAL, BUTTON_DELAY };

class CButtonUI : protected CSprite
{
private:
public:
	// Note: 버튼 속성
	int m_nX, m_nY;
	RECT m_rtRect;
	BOOL m_bIsClicked;	
	int m_nIndex;
	BUTTON_STATE m_nButtonState;

public:
	BOOL IsClicked();	
	void Init(HWND hWnd, char *filename, int nX, int nY);
	void Render(HDC hBackBuffer);
	void Update(MOUSE_STATE nMouseState, POINT ptMouse);
	void Release();
public:
	CButtonUI(void);
	~CButtonUI(void);
};


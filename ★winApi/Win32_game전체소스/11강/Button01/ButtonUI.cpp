#include "StdAfx.h"
#include "ButtonUI.h"

CButtonUI::CButtonUI(void)
{
	m_bIsClicked = FALSE; 
	m_nIndex = 0;
	m_nButtonState = BUTTON_NORMAL;
}

CButtonUI::~CButtonUI(void)
{
}

BOOL CButtonUI::IsClicked()
{
	return m_bIsClicked;
}

void CButtonUI::Init(HWND hWnd, char *filename, int nX, int nY)
{
	m_nIndex = 0;
	Load(hWnd, filename);
	m_nX = nX; // ÁÂÇ¥´Â °íÁ¤
	m_nY = nY;
	SetRect(&m_rtRect, m_nX, m_nY, m_nX + GetSprWidth(m_nIndex) - 1, m_nY + GetSprHeight(m_nIndex) - 1);
}

void CButtonUI::Render(HDC hBackBuffer)
{
	int nWidth = GetSprWidth(m_nIndex);
	int nHeight = GetSprHeight(m_nIndex);
	RECT rect = GetSprRect(m_nIndex);
	HDC hSprMemDC = GetSrcImageDC();	
	TransparentBlt( hBackBuffer, m_nX, m_nY, nWidth, nHeight, hSprMemDC, 
					            rect.left, rect.top, nWidth, nHeight, GetTransColor()); 
}

void CButtonUI::Update(MOUSE_STATE nMouseState, POINT ptMouse)
{			
	if(PtInRect(&m_rtRect, ptMouse))
	{		
		switch(m_nButtonState)
		{
		case BUTTON_NORMAL:
			if(nMouseState == MOUSE_DOWN)
			{
				m_nButtonState = BUTTON_DOWN;
				m_nIndex = 1;
				m_bIsClicked = FALSE;
			}else{
				m_bIsClicked = FALSE;
			}
			break;
		case BUTTON_DOWN:
			if(nMouseState == MOUSE_UP)
			{
				m_nButtonState = BUTTON_UP;
				m_nIndex = 0;
				m_bIsClicked = FALSE;
			}
			break;
		case BUTTON_UP:			
			m_nButtonState = BUTTON_DELAY;					
			break;
		case BUTTON_DELAY:
			Sleep(200);
			m_bIsClicked = TRUE;			
			m_nButtonState = BUTTON_NORMAL;		
			break;
		}
	}else{		
		m_nIndex = 0;
		m_bIsClicked = FALSE;
		m_nButtonState = BUTTON_NORMAL;	
	}
}

void CButtonUI::Release()
{
	CSprite::Release();
}
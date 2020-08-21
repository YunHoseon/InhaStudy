#include "StdAfx.h"
#include "GameFrame.h"
/*----------------------------------------------------------------
2015년 5월 29일 
- 가장 기본적인 형태로 하고 콜백함수를 이용하여 내부에서 돌리도록 한다.
  되도록 DX에서 사용하는 방법을 사용할 것.
----------------------------------------------------------------*/

CGameFrame::CGameFrame(void)
{
	m_bIsFullMode = TRUE; // 기본이 풀모드
	m_nFPSCount = 0;
	m_nFPS = 0;
}


CGameFrame::~CGameFrame(void)
{
}

void CGameFrame::FullScreenModeChange()		
{							
	DEVMODE sDevMode ;			
	sDevMode.dmSize	= sizeof(DEVMODE);	
	sDevMode.dmPelsWidth    = m_nWidth;			
	sDevMode.dmPelsHeight   = m_nHeight;			
	sDevMode.dmFields       = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&sDevMode, CDS_FULLSCREEN);
}

void CGameFrame::ChangeScreenMode(BOOL bIsFullMode)
{
	RECT rect;	
	m_bIsFullMode = bIsFullMode;
	DEVMODE sDevMode;
	if(bIsFullMode)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP );
		SetWindowPos(m_hWnd, 0, 0, 0, m_nWidth, m_nHeight, SWP_SHOWWINDOW );
		FullScreenModeChange();
	}else{			
		SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW );		

		// 윈도우 크기 설정
		SetRect( &rect, 0, 0, m_nWidth, m_nHeight );
		AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, FALSE );
		SetWindowPos( m_hWnd, 0, 100, 100, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
	}
}


void CGameFrame::Init(HWND hWnd, int nWidth, int nHeight, BOOL bIsFullMode)
{	
	HBITMAP hBitmap;
	HDC hdc;
	RECT rect;

	m_hWnd = hWnd;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_bIsFullMode = bIsFullMode;

	hdc = GetDC(m_hWnd);
	m_hBackBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, m_nWidth, m_nHeight);
	SelectObject(m_hBackBuffer, (HBITMAP)hBitmap);	
	DeleteObject(hBitmap);
	ReleaseDC(m_hWnd, hdc);

	ChangeScreenMode(bIsFullMode);

	SceneInit();

	m_dwOldTIme = m_dwOldFPSTime = GetTickCount();	 // 추가된 부분
}

void CGameFrame::Update()
{
	m_dwCurTime = GetTickCount();
	m_dwElapsedTime = m_dwCurTime - m_dwOldTIme; // <-- 추가된 부분
	m_dwOldTIme = m_dwCurTime;	// <-- 추가된 부분

	if(m_dwCurTime - m_dwOldFPSTime >= 1000)
	{
		m_dwOldFPSTime = m_dwCurTime;
		m_nFPS = m_nFPSCount;
		m_nFPSCount = 0;		
	}else{
		m_nFPSCount++;
	}
	
	SceneUpdate();
}

void CGameFrame::Render()
{
	HDC hdc = GetDC(m_hWnd);
	PatBlt(m_hBackBuffer, 0, 0, m_nWidth, m_nHeight, BLACKNESS);
	// 렌더링 이미지 출력

	SceneRender();

	BitBlt(hdc, 0, 0, m_nWidth, m_nHeight, m_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void CGameFrame::Release()
{
	DeleteDC(m_hBackBuffer);

	SceneRelease();
}





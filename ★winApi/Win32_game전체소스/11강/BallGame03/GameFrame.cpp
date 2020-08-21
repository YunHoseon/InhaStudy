#include "StdAfx.h"
#include "GameFrame.h"
/*----------------------------------------------------------------
2015�� 5�� 29�� 
- ���� �⺻���� ���·� �ϰ� �ݹ��Լ��� �̿��Ͽ� ���ο��� �������� �Ѵ�.
  �ǵ��� DX���� ����ϴ� ����� ����� ��.
----------------------------------------------------------------*/

CGameFrame::CGameFrame(void)
{
	m_bIsFullMode = TRUE; // �⺻�� Ǯ���
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

		// ������ ũ�� ����
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

	m_dwOldTIme = m_dwOldFPSTime = GetTickCount();	 // �߰��� �κ�
}

void CGameFrame::Update()
{
	m_dwCurTime = GetTickCount();
	m_dwElapsedTime = m_dwCurTime - m_dwOldTIme; // <-- �߰��� �κ�
	m_dwOldTIme = m_dwCurTime;	// <-- �߰��� �κ�

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
	// ������ �̹��� ���

	SceneRender();

	BitBlt(hdc, 0, 0, m_nWidth, m_nHeight, m_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void CGameFrame::Release()
{
	DeleteDC(m_hBackBuffer);

	SceneRelease();
}





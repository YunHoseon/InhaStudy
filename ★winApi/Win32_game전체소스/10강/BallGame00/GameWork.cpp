#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// 추상 클래스의 함수를 하위에서 구현함으로써 이 클래스 안에서 프로그래밍만 할 수 있게 
// 되었다. 실제 WinMain()에는 상위 클래스의 내용이 호출 되지만 실제 게임등이 실행되는 곳은
// 바로 이 클래스 부분이다.


CGameWork::CGameWork(void)
{
	m_nStageNumber = 0;
	m_hBackGroundDC = NULL;
}

CGameWork::~CGameWork(void)
{
}


HDC CGameWork::CreateBmpDC(char *filename)
{
	HBITMAP hBitmap;
	HDC hdc = GetDC( m_hWnd );
	HDC hMemDC = CreateCompatibleDC( hdc );	
	hBitmap = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );	
	
	SelectObject( hMemDC, hBitmap );
	DeleteObject( hBitmap );	
	ReleaseDC( m_hWnd, hdc );
	return hMemDC;
}

void CGameWork::SceneInit()
{	
	char *strBackGroundImage[] = {"ground1_r.bmp", "ground2_r.bmp", "ground3_r.bmp", "ground4_r.bmp" };
	if(m_hBackGroundDC != NULL)
		DeleteDC(m_hBackGroundDC);
	m_hBackGroundDC = CreateBmpDC(strBackGroundImage[m_nStageNumber]);	

	// Note: 골대 
	m_GoalDaeSpr.Load(m_hWnd, "goalpost_r.spr");
	m_GoalDaePat.Load("goal1.pat");
	m_GoalDae.Init(&m_GoalDaeSpr, &m_GoalDaePat);	
}

void CGameWork::SceneUpdate()
{
	m_GoalDae.Update(m_dwCurTime, m_dwElapsedTime);
}

void CGameWork::SceneRender()
{
	char string[100];
	//------------------ 렌더링 시작 ----------------------
	BitBlt(m_hBackBuffer, 0, 0, 600, 600, m_hBackGroundDC, 0, 0, SRCCOPY);	
	m_GoalDae.Render(m_hBackBuffer);

	//------------------ 렌더링 끝 -------------------------
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	if(m_hBackGroundDC != NULL)
		DeleteDC(m_hBackGroundDC);

	m_GoalDaeSpr.Release();	
}
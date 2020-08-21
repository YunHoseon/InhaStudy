#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// 추상 클래스의 함수를 하위에서 구현함으로써 이 클래스 안에서 프로그래밍만 할 수 있게 
// 되었다. 실제 WinMain()에는 상위 클래스의 내용이 호출 되지만 실제 게임등이 실행되는 곳은
// 바로 이 클래스 부분이다.

CGameWork::CGameWork(void)
{
}

CGameWork::~CGameWork(void)
{
}

void CGameWork::SceneInit()
{	
	m_ButtonUI[0].Init(m_hWnd, "start_button.spr", 100, 100);
	m_ButtonUI[1].Init(m_hWnd, "end_button.spr", 100, 170);
}

void CGameWork::SceneUpdate()
{
	for(int i = 0; i < 2; i++)
		m_ButtonUI[i].Update(m_nMouseState, m_ptMouseClick);	
}

void CGameWork::SceneRender()
{
	static int nCount = 0;
	static int val = 0;
	char string[100];
	//------------------------- Render 시작 ---------------------------------

	for(int i = 0; i < 2; i++)
		m_ButtonUI[i].Render(m_hBackBuffer);		
	//------------------------- Render 끝   ---------------------------------
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	for(int i = 0; i < 2; i++)
		m_ButtonUI[i].Release();
}
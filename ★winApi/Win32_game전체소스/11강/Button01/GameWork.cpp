#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// �߻� Ŭ������ �Լ��� �������� ���������ν� �� Ŭ���� �ȿ��� ���α׷��ָ� �� �� �ְ� 
// �Ǿ���. ���� WinMain()���� ���� Ŭ������ ������ ȣ�� ������ ���� ���ӵ��� ����Ǵ� ����
// �ٷ� �� Ŭ���� �κ��̴�.

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
	//------------------------- Render ���� ---------------------------------

	for(int i = 0; i < 2; i++)
		m_ButtonUI[i].Render(m_hBackBuffer);		
	//------------------------- Render ��   ---------------------------------
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
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
}

void CGameWork::SceneUpdate()
{
	
}

void CGameWork::SceneRender()
{
	char string[100];
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
}
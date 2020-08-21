#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// �߻� Ŭ������ �Լ��� �������� ���������ν� �� Ŭ���� �ȿ��� ���α׷��ָ� �� �� �ְ� 
// �Ǿ���. ���� WinMain()���� ���� Ŭ������ ������ ȣ�� ������ ���� ���ӵ��� ����Ǵ� ����
// �ٷ� �� Ŭ���� �κ��̴�.

#define GAP 17

CGameWork::CGameWork(void)
{
}

CGameWork::~CGameWork(void)
{
}

void CGameWork::SceneInit()
{	
	m_PlayerSprite.Load(m_hWnd, "player.spr");
	m_Player.Init(&m_PlayerSprite, 170, 400);
	m_BallSprite.Load(m_hWnd, "ball.spr");
	m_Ball.Init(&m_BallSprite,  170 - GAP, 400, 0.3f);
}

void CGameWork::SceneUpdate()
{
	if(GetAsyncKeyState(VK_RIGHT) < 0 )
	{
		m_Player.Move(VK_RIGHT);		
	}
	else if(GetAsyncKeyState(VK_LEFT) < 0)
	{
		m_Player.Move(VK_LEFT);
		
	}else if(GetAsyncKeyState(VK_SPACE) < 0) // ���� �ƹ����ۿ����� �����ϵ��� ��
	{
		if( m_Player.Shoot() == TRUE && m_Ball.GetState() != BALL_SHOOT ) // �����ۿ� ���� �ʱ�ȭ		
			m_Ball.Shooting(m_Player.GetX(), m_Player.GetY() - GAP);
	}

	m_Player.Update(m_dwCurTime, m_dwElapsedTime);
	// Note: ���ΰ��� ���¿� ���� ���� ������ �����Ƿ�
	switch(m_Player.GetState())
	{
	case PLAYER_LEFT:		
		m_Ball.LeftMove(m_Player.GetX() - GAP, m_Player.GetY());		
		break;
	case PLAYER_RIGHT:
		m_Ball.RightMove( m_Player.GetX() + GAP, m_Player.GetY());			
		break;
	case PLAYER_READY: // 0.5�� ���� ���� ���� ���·� �ִ´�.
		if( m_Player.GetPreAction() == PLAYER_LEFT )	
			m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
		else if( m_Player.GetPreAction() == PLAYER_RIGHT )	
			m_Ball.Stop(m_Player.GetX() + GAP, m_Player.GetY());
		break;
	case PLAYER_IDLE:
		if(m_Ball.GetState() != BALL_SHOOT)
			m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
		break;
	}

	m_Ball.Update(m_dwCurTime, m_dwElapsedTime);
}

void CGameWork::SceneRender()
{
	char string[100];
	//--------------------- Render Start---------------------------//

	m_Player.Render(m_hBackBuffer);
	m_Ball.Render(m_hBackBuffer);
	//--------------------- Render End ----------------------------//
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	m_PlayerSprite.Release();
	m_BallSprite.Release();
}
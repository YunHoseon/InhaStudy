#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// 추상 클래스의 함수를 하위에서 구현함으로써 이 클래스 안에서 프로그래밍만 할 수 있게 
// 되었다. 실제 WinMain()에는 상위 클래스의 내용이 호출 되지만 실제 게임등이 실행되는 곳은
// 바로 이 클래스 부분이다.

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
		
	}else if(GetAsyncKeyState(VK_SPACE) < 0) // 슛은 아무동작에서도 가능하도록 함
	{
		if( m_Player.Shoot() == TRUE && m_Ball.GetState() != BALL_SHOOT ) // 슛동작에 대한 초기화		
			m_Ball.Shooting(m_Player.GetX(), m_Player.GetY() - GAP);
	}

	m_Player.Update(m_dwCurTime, m_dwElapsedTime);
	// Note: 주인공의 상태에 따라 볼이 영향을 받으므로
	switch(m_Player.GetState())
	{
	case PLAYER_LEFT:		
		m_Ball.LeftMove(m_Player.GetX() - GAP, m_Player.GetY());		
		break;
	case PLAYER_RIGHT:
		m_Ball.RightMove( m_Player.GetX() + GAP, m_Player.GetY());			
		break;
	case PLAYER_READY: // 0.5초 정도 공이 정지 상태로 있는다.
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
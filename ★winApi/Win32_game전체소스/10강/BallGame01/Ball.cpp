#include "StdAfx.h"
#include "Ball.h"

#define LIMIT_Y 0


CBall::CBall(void)
{	
}


CBall::~CBall(void)
{
}


// Note: 공을 가진다. 주인공이 공은 다양하게 가질 수 있다.
void CBall::Init(CSprite *pSprite, int nX, int nY, float fVelocity)
{
	m_pSprite = pSprite;
	m_fX = nX;
	m_fY = nY;
	m_fVelocity = fVelocity;

	m_nPreBallState = m_nBallState = BALL_STOP;
	m_nAniSprIndex = 0;	
	m_dwOldAniTime = GetTickCount(); 
}

void CBall::LeftMove(int nX, int nY)
{
	m_nBallState = BALL_LEFT;
	m_fX = nX;
	m_fY = nY;
	if(m_nPreBallState != m_nBallState)
	{
		m_nPreBallState = m_nBallState;
		m_AniRange = m_pSprite->GetAniRange(BALL_LEFT);
		m_nAniSprIndex = m_AniRange.nIndex0;
	}
}

void CBall::RightMove(int nX, int nY)
{
	m_nBallState = BALL_RIGHT;
	m_fX = nX;
	m_fY = nY;
	if(m_nPreBallState != m_nBallState)
	{
		m_nPreBallState = m_nBallState;
		m_AniRange = m_pSprite->GetAniRange(BALL_RIGHT);
		m_nAniSprIndex = m_AniRange.nIndex0;
	}
}

void CBall::Shooting(int nX, int nY)
{	
	m_fX = nX;
	m_fY = nY;	
	m_nPreBallState = m_nBallState;
	m_nBallState = BALL_SHOOT;
	m_AniRange = m_pSprite->GetAniRange(BALL_RIGHT); // 슛 상태일 떄는 슛팅으로 
	m_nAniSprIndex = m_AniRange.nIndex0;	
}

void CBall::Stop(int nX, int nY)
{
	m_nBallState = BALL_STOP;
	m_fX = nX;
	m_fY = nY;	
	m_nAniSprIndex = 0;
}

int CBall::GetX()
{
	return (int)m_fX;
}

int CBall::GetY()
{
	return (int)m_fY;
}

BALL_STATE CBall::GetState()
{
	return m_nBallState;
}

void CBall::SetXY(int nX, int nY)
{
	m_fX = nX;
	m_fY = nY;
}

void CBall::Update(DWORD dwCurTime, DWORD dwElapsedTime)
{
	DWORD dwAniElapsedTime, dwAniTime;

	switch(m_nBallState)
	{
	case BALL_SHOOT:		
		m_fY -= m_fVelocity * dwElapsedTime; // s = v*(t1-t0);				
		if( m_fY < LIMIT_Y )
		{
			m_nBallState = BALL_STOP;			
			break;
		}
	case BALL_LEFT:
	case BALL_RIGHT:
		// BALL_SHOOT, BALL_LEFT, BALL_RIGHT 까지 볼에 대한 에니메이션 
		dwAniElapsedTime = dwCurTime - m_dwOldAniTime;
		dwAniTime = m_pSprite->GetAniTime(m_nAniSprIndex);	
		if( dwAniElapsedTime >= dwAniTime )
		{
			m_dwOldAniTime = dwCurTime;
			m_nAniSprIndex++;
			if(m_nAniSprIndex > m_AniRange.nIndex1)
				m_nAniSprIndex = m_AniRange.nIndex0;						
		}
		break;		
	}
}


void CBall::Render(HDC hBackBuffer)
{
	int nWidth = m_pSprite->GetSprWidth(m_nAniSprIndex);
	int nHeight = m_pSprite->GetSprHeight(m_nAniSprIndex);
	RECT rect = m_pSprite->GetSprRect(m_nAniSprIndex);
	HDC hSprMemDC = m_pSprite->GetSrcImageDC();
	POINT ptCenterPos = m_pSprite->GetCenterPos(m_nAniSprIndex);
	TransparentBlt( hBackBuffer, m_fX - ptCenterPos.x, m_fY - ptCenterPos.y, nWidth, nHeight, hSprMemDC, 
					            rect.left, rect.top, nWidth, nHeight, m_pSprite->GetTransColor()); 
}
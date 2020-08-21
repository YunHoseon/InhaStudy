#include "StdAfx.h"
#include "GoalDae.h"



CGoalDae::CGoalDae(void)
{
}


CGoalDae::~CGoalDae(void)
{
}


void CGoalDae::Init(CSprite *pSprite, CPattern *pPattern)
{
	m_pSprite = pSprite;
	m_pPattern = pPattern;
	m_fX = pPattern->GetInitXY().x;
	m_fY = pPattern->GetInitXY().y;
}

void CGoalDae::Update(DWORD dwCurTime, DWORD dwElapsedTime)
{
	float fDistance;	
	POINT ptPoint;
	static DWORD dwStopElapsedTime = 0;
	static int nMovePathIndex = 0;
	MOVE_INFO sMoveInfo;
	static float fAddDistance; // 누적 거리

	sMoveInfo = m_pPattern->GetMoveInfo(nMovePathIndex);	
	if(sMoveInfo.nDirection == STOP)
	{
		dwStopElapsedTime += dwElapsedTime; // 한 프레임당 걸린 시간을 누적
		if(dwStopElapsedTime >= sMoveInfo.dwDelayTime) // STOP 상태에서 이동경로가 바뀌는 조건
		{
			dwStopElapsedTime = 0;
			nMovePathIndex = ++nMovePathIndex % m_pPattern->GetMoveCount();
			if(nMovePathIndex == 0) // 다음 이동에 대한 초기화
			{ 
				ptPoint = m_pPattern->GetInitXY();
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
			}				
		}
	}else{		
		if(m_fX == sMoveInfo.nDestX && m_fY == sMoveInfo.nDestY)
		{
			if( nMovePathIndex + 1 == m_pPattern->GetMoveCount() )
			{
				ptPoint = m_pPattern->GetInitXY(); // 초기값 셋팅
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
				nMovePathIndex = 0;
			}else{
				nMovePathIndex++;					
			}		
		}else{
			fDistance = sMoveInfo.fVelocity * dwElapsedTime; // s = v*(t1-t0);				
			fAddDistance += fDistance;	
			if( (int)fAddDistance >= sMoveInfo.nAllDistance ) // 거리로 다음 이동경로를 결정
			{
				m_fX = sMoveInfo.nDestX;
				m_fY = sMoveInfo.nDestY;
				fAddDistance = 0.0f;
			}else{
				switch(sMoveInfo.nDirection)
				{			
				case RIGHT:
					m_fX += fDistance;
					break;			
				case LEFT:						
					m_fX -= fDistance;														
					break;								
				}			
			}
		}
	}
}

void CGoalDae::Render(HDC hBackBuffer)	
{
	HDC hSprMemDC = m_pSprite->GetSrcImageDC();
	RECT rect = m_pSprite->GetSprRect(0);
	int nWidth = m_pSprite->GetSprWidth(0);
	int nHeight = m_pSprite->GetSprHeight(0);
	TransparentBlt( hBackBuffer, m_fX, m_fY, nWidth, nHeight, hSprMemDC, 
					            rect.left, rect.top, nWidth, nHeight, m_pSprite->GetTransColor()); 
}

RECT CGoalDae::GetRect()
{
	RECT rect;
	rect.left = m_fX;
	rect.top = m_fY;
	rect.right = m_fX + m_pSprite->GetSprWidth(0) - 1;
	rect.bottom = m_fY + m_pSprite->GetSprHeight(0) - 1;	
	return rect;
}

// 게임 화면에서 충돌좌표
RECT CGoalDae::GetCollisionRect()
{
	RECT rect, rtCollision;
	rtCollision = m_pSprite->GetCollisionRect(0, 0);
	rect.left = m_fX + rtCollision.left;
	rect.top = m_fY + rtCollision.top;
	rect.right = rect.left + (rtCollision.right - rtCollision.left);
	rect.bottom = rect.top + (rtCollision.bottom - rtCollision.top);
	return rect;
}
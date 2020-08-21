#include "StdAfx.h"
#include "Enemy.h"
/*-----------------------------------------------------------------------------
이 클래스의 목적은 CSprite와 CPattern으로 부터 최종 출력하기 위한 좌표 m_ptXY와 
출력할 스프라이트의 인덱스를 구하는 것이다.
또한 CSprite의 멤버변수와 CPattern의 멤버변수를 이용하여 캐릭터 클래스를 구성하는 
것이 중요하다.
-------------------------------------------------------------------------------*/

CEnemy::CEnemy(void)
{
}


CEnemy::~CEnemy(void)
{	
}

// 현재 캐릭터 에니메이션이 4방향에 대한 부분밖에 없으므로 
// 8방향을 4방향의 에니메이션으로 설정하는 함수이다.
MOVE_MOTION CEnemy::GetAniDirectionIndex(DIRECTION nDirection)
{
	switch(nDirection)
	{
	case TOP:
		 return M_TOP;
	case RIGHT_TOP:
	case RIGHT:
	case RIGHT_DOWN:
		 return M_RIGHT;
	case DOWN:
		 return M_DOWN;
	case LEFT_DOWN:
	case LEFT:
	case LEFT_TOP:
		 return M_LEFT;
	case STOP:
		 return M_STOP;
	}

	return M_TOP; // 의미없음
}

void CEnemy::Init(CSprite *pSprite, CPattern *pPattern) 
{
	POINT ptPoint;
	m_pSprite = pSprite;	
	m_dwOldAniTime = GetTickCount();	
	m_pPattern = pPattern;
	m_nMovePathIndex = 0;
	m_fAddDistance = 0.0f;
	ptPoint = pPattern->GetInitXY();
	m_fX = ptPoint.x;
	m_fY = ptPoint.y;
	m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);		
	
	m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // 패턴에서 얻어지는 에니메이션 5 방향에 대한 에니 범위 인덱스( 0 ~ 4),  고정	
	m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
	m_nAniSprIndex = m_AniRange.nIndex0;	
}

// Note: m_nAniSprIndex는 패턴의 이동경로가 바뀔 때 최초 결정되고 m_ANiRangeIndex에 의해 그 범위가 결정된다.
// Update() 함수의 최종목적은 출력 좌표(m_ptXY)와 출력할 스프라이트 인덱스(m_nAniSprIndex)를 구하는 것이다.
void CEnemy::Update(DWORD dwCurTime, DWORD dwElapsedTime)
{
	float fDistance;	
	POINT ptPoint;

	m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);	
	if(m_sMoveInfo.nDirection == STOP)
	{
		m_dwStopElapsedTime += dwElapsedTime; // 한 프레임당 걸린 시간을 누적
		if(m_dwStopElapsedTime >= m_sMoveInfo.dwDelayTime) // STOP 상태에서 이동경로가 바뀌는 조건
		{
			m_dwStopElapsedTime = 0;
			m_nMovePathIndex = ++m_nMovePathIndex % m_pPattern->GetMoveCount();
			if(m_nMovePathIndex == 0) // 다음 이동에 대한 초기화
			{ 
				ptPoint = m_pPattern->GetInitXY();
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
			}			

			////// 방향이 바뀔때 이동 에니메이션도 바뀐다.
			m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);
			m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // 패턴에서 얻어지는 에니메이션 5 방향에 대한 에니 범위 인덱스( 0 ~ 4),  고정	
			m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = dwCurTime;
		}
	}else{		
		if(m_fX == m_sMoveInfo.nDestX && m_fY == m_sMoveInfo.nDestY)
		{
			if(m_nMovePathIndex + 1 == m_pPattern->GetMoveCount() )
			{
				ptPoint = m_pPattern->GetInitXY(); // 초기값 셋팅
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
				m_nMovePathIndex = 0;
			}else{
				m_nMovePathIndex++;					
			}

			//////// 방향이 바뀔때 이동 에니메이션도 바뀐다.
			m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);
			m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // 패턴에서 얻어지는 에니메이션 5 방향에 대한 에니 범위 인덱스( 0 ~ 4),  고정	
			m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = dwCurTime;
		}else{
			fDistance = m_sMoveInfo.fVelocity * dwElapsedTime; // s = v*(t1-t0);				
			m_fAddDistance += fDistance;	
			if( (int)m_fAddDistance >= m_sMoveInfo.nAllDistance ) // 거리로 다음 이동경로를 결정
			{
				m_fX = m_sMoveInfo.nDestX;
				m_fY = m_sMoveInfo.nDestY;
				m_fAddDistance = 0.0f;						
			}else{
				switch(m_sMoveInfo.nDirection)
				{
				case TOP:
					m_fY -= fDistance;
					break;
				case RIGHT_TOP:
					m_fX += fDistance;
					m_fY -= fDistance;
					break;
				case RIGHT:
					m_fX += fDistance;
					break;
				case RIGHT_DOWN:
					m_fX += fDistance;
					m_fY += fDistance;
					break;
				case DOWN:					
					m_fY += fDistance;							
					break;	
				case LEFT_DOWN:
					m_fX -= fDistance;
					m_fY += fDistance;
					break;
				case LEFT:						
					m_fX -= fDistance;														
					break;
				case LEFT_TOP:						
					m_fX -= fDistance;
					m_fY -= fDistance;
					break;						
				}			
			}
		}
	}

	//Note 에니메이션은 5방향 범위에 대한 에니메이션만 해주면 된다.
	//     에니메이션은 반복만 할 뿐 실제 에니메이션 범위를 바꾸는 것은 패턴에서 한다.
	DWORD dwAniElapsedTime = dwCurTime - m_dwOldAniTime;
	DWORD dwAniTime = m_pSprite->GetAniTime(m_nAniSprIndex);	
	if( dwAniElapsedTime >= dwAniTime )
	{
		m_dwOldAniTime = dwCurTime;
		m_nAniSprIndex++;
		if(m_nAniSprIndex > m_AniRange.nIndex1)
			m_nAniSprIndex = m_AniRange.nIndex0;		
	}	
}

void CEnemy::Render(HDC hBackBuffer)
{	
	int nWidth = m_pSprite->GetSprWidth(m_nAniSprIndex);
	int nHeight = m_pSprite->GetSprHeight(m_nAniSprIndex);
	RECT rect = m_pSprite->GetSprRect(m_nAniSprIndex);
	HDC hSprMemDC = m_pSprite->GetSrcImageDC();
	POINT ptCenterPos = m_pSprite->GetCenterPos(m_nAniSprIndex);
	TransparentBlt( hBackBuffer, m_fX - ptCenterPos.x, m_fY - ptCenterPos.y, nWidth, nHeight, hSprMemDC, 
					            rect.left, rect.top, nWidth, nHeight, m_pSprite->GetTransColor()); 	
}

// 현재 스프라이트의 출력 좌표
RECT CEnemy::GetRect(){
	RECT rect;
	int nWidth = m_pSprite->GetSprWidth(m_nAniSprIndex);
	int nHeight = m_pSprite->GetSprHeight(m_nAniSprIndex);
	POINT ptCenterPos = m_pSprite->GetCenterPos(m_nAniSprIndex);
	rect.left = m_fX - ptCenterPos.x;
	rect.top = m_fY - ptCenterPos.y;
	rect.right = rect.left + nWidth - 1;
	rect.bottom = rect.top + nHeight - 1;
	return rect;
}


BOOL CEnemy::IsSprCollsion(RECT rect){
	RECT rtRect1, rtRect2, rtRect, rtTemp;
	int nCount = m_pSprite->GetCollisionCount(m_nAniSprIndex);
	rtRect1 = GetRect(); // 실제 출력 좌표
	for(int i = 0 ; i < nCount ; i++)
	{
		rtRect = m_pSprite->GetCollisionRect(m_nAniSprIndex, i); // 스프라이트로부터 충돌좌표 가져오기
		rtRect2.left = rtRect1.left + rtRect.left; // 실제 출력좌표로 변환
		rtRect2.top = rtRect1.top + rtRect.top;
		rtRect2.right = rtRect2.left + (rtRect.right - rtRect.left) - 1;
		rtRect2.bottom = rtRect2.top + (rtRect.bottom - rtRect.top) - 1;
		if( IntersectRect(&rtTemp, &rect, &rtRect2) != 0) // 충돌
			return TRUE;
	}
	return FALSE;
}
#include "StdAfx.h"
#include "Player.h"


CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}


void CPlayer::Init(CSprite *pSprite, int nX, int nY)
{
	m_pSprite = pSprite;		
	m_fX = nX;
	m_fY = nY;
	m_nPreAction = m_nAction = PLAYER_IDLE;
	m_AniRange = m_pSprite->GetAniRange(m_nAction);
	m_nAniSprIndex = m_AniRange.nIndex0;
	m_dwOldAniTime = GetTickCount();
	m_dwStopElapsedTime = 0; // 아이들일 때 정지시간을 누적하는 변수
	m_fVelocity = 0.03f;	
}

void CPlayer::Update(DWORD dwCurTime, DWORD dwElapsedTime )
{
	float fDistance;	
	DWORD dwAniElapsedTime, dwAniTime;
	
	switch(m_nAction)
	{
	case PLAYER_LEFT:		
		if( m_nPreAction != m_nAction){ // 서로 다른 동작에서 이동하지 못하도록 하기 위해 		{
			m_nPreAction = m_nAction;
			break;
		}

		fDistance = m_fVelocity * dwElapsedTime; // s = v*(t1-t0);		
		m_fX -= fDistance;				
		
		dwAniElapsedTime = dwCurTime - m_dwOldAniTime;
		dwAniTime = m_pSprite->GetAniTime(m_nAniSprIndex);	
		if( dwAniElapsedTime >= dwAniTime )
		{
			m_dwOldAniTime = dwCurTime;
			m_nAniSprIndex++;
			if(m_nAniSprIndex > m_AniRange.nIndex1)
			{ // Note: 마지막 인덱스를 유지하면서 REDAY 상태로 들오간다.
				m_nAniSprIndex = m_AniRange.nIndex1;		
				m_nPreAction = m_nAction;
				m_nAction = PLAYER_READY;
				m_dwStopElapsedTime = 0;
			}
		}
		break;
	case PLAYER_RIGHT:
		if( m_nPreAction != m_nAction){ // 서로 다른 동작에서 이동하지 못하도록 하기 위해 		{
			m_nPreAction = m_nAction;
			break;
		}
			
		fDistance = m_fVelocity * dwElapsedTime; // s = v*(t1-t0);		
		m_fX += fDistance;			

		dwAniElapsedTime = dwCurTime - m_dwOldAniTime;
		dwAniTime = m_pSprite->GetAniTime(m_nAniSprIndex);	
		if( dwAniElapsedTime >= dwAniTime )
		{
			m_dwOldAniTime = dwCurTime;
			m_nAniSprIndex++;
			if(m_nAniSprIndex > m_AniRange.nIndex1)
			{ // Note: 마지막 인덱스를 유지하면서 REDAY 상태로 들오간다.
				m_nAniSprIndex = m_AniRange.nIndex1;	
				m_nPreAction = m_nAction;
				m_nAction = PLAYER_READY;
				m_dwStopElapsedTime = 0;
			}
		}
		break;	
	case PLAYER_READY: // 아이들로 넘어가기 위해 0.5초간 마지막 스프라이트 인덱스 유지하기 위한 상태
		m_dwStopElapsedTime += dwElapsedTime;
		if(m_dwStopElapsedTime >= 500) // READY 상태에서 0.5초 후에는 IDLE 상태로 들어간다.
		{
			m_dwStopElapsedTime = 0;
			m_nPreAction = m_nAction;
			m_nAction = PLAYER_IDLE;
			m_AniRange = m_pSprite->GetAniRange(m_nAction);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = dwCurTime;
		}
		break;

	case PLAYER_IDLE: // 아이들은 계속 에니메이션만 반복
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

	case PLAYER_SHOOT:
		dwAniElapsedTime = dwCurTime - m_dwOldAniTime;
		dwAniTime = m_pSprite->GetAniTime(m_nAniSprIndex);	
		if( dwAniElapsedTime >= dwAniTime )
		{
			m_dwOldAniTime = dwCurTime;
			m_nAniSprIndex++;
			if(m_nAniSprIndex > m_AniRange.nIndex1)
			{
				m_nPreAction = m_nAction;
				m_nAction = PLAYER_IDLE; 
				m_AniRange = m_pSprite->GetAniRange(m_nAction);
				m_nAniSprIndex = m_AniRange.nIndex0;
				m_dwOldAniTime = dwCurTime;
			}
		}
		break;
	}	
}

void CPlayer::Render(HDC hBackBuffer)
{
	int nWidth = m_pSprite->GetSprWidth(m_nAniSprIndex);
	int nHeight = m_pSprite->GetSprHeight(m_nAniSprIndex);
	RECT rect = m_pSprite->GetSprRect(m_nAniSprIndex);
	HDC hSprMemDC = m_pSprite->GetSrcImageDC();
	POINT ptCenterPos = m_pSprite->GetCenterPos(m_nAniSprIndex);
	TransparentBlt( hBackBuffer, m_fX - ptCenterPos.x, m_fY - ptCenterPos.y, nWidth, nHeight, hSprMemDC, 
					            rect.left, rect.top, nWidth, nHeight, m_pSprite->GetTransColor()); 
}

void CPlayer::Move(int nKey)
{
	// Note: 캐릭터 행동 상태와 키 눌림에 따라 반응
	switch(m_nAction)
	{
	case PLAYER_READY:
	case PLAYER_IDLE:
			if( nKey == VK_LEFT )
			{
				m_nPreAction = m_nAction;
				m_nAction = PLAYER_LEFT;
			}
			else if( nKey == VK_RIGHT)
			{
				m_nPreAction = m_nAction;
				m_nAction = PLAYER_RIGHT;
			}

			m_AniRange = m_pSprite->GetAniRange(m_nAction);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = GetTickCount();
			break;
	case PLAYER_RIGHT:
			if(nKey == VK_LEFT)
			{
				if(m_nAniSprIndex == m_AniRange.nIndex1)
				{
					m_nPreAction = m_nAction;
					m_nAction = PLAYER_LEFT;
					m_AniRange = m_pSprite->GetAniRange(m_nAction);
					m_nAniSprIndex = m_AniRange.nIndex0;
					m_dwOldAniTime = GetTickCount();
				}
			}
			break;		
	case PLAYER_LEFT:
			if(nKey == VK_RIGHT)
			{
				if(m_nAniSprIndex == m_AniRange.nIndex1)
				{
					m_nPreAction = m_nAction;
					m_nAction = PLAYER_RIGHT;
					m_AniRange = m_pSprite->GetAniRange(m_nAction);
					m_nAniSprIndex = m_AniRange.nIndex0;
					m_dwOldAniTime = GetTickCount();
				}	
			}
			break;
	}
}

// Note: 슛동작은 상태와 상관없이 동작하도록 한다.
BOOL CPlayer::Shoot()
{
	if(m_nAction != PLAYER_SHOOT)
	{
		m_nAction = PLAYER_SHOOT;
		m_AniRange = m_pSprite->GetAniRange(m_nAction);
		m_nAniSprIndex = m_AniRange.nIndex0;
		m_dwOldAniTime = GetTickCount();
		return TRUE;
	}

	return FALSE;
}
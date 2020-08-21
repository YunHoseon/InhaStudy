#include "StdAfx.h"
#include "Enemy.h"
/*-----------------------------------------------------------------------------
�� Ŭ������ ������ CSprite�� CPattern���� ���� ���� ����ϱ� ���� ��ǥ m_ptXY�� 
����� ��������Ʈ�� �ε����� ���ϴ� ���̴�.
���� CSprite�� ��������� CPattern�� ��������� �̿��Ͽ� ĳ���� Ŭ������ �����ϴ� 
���� �߿��ϴ�.
-------------------------------------------------------------------------------*/

CEnemy::CEnemy(void)
{
}


CEnemy::~CEnemy(void)
{	
}

// ���� ĳ���� ���ϸ��̼��� 4���⿡ ���� �κйۿ� �����Ƿ� 
// 8������ 4������ ���ϸ��̼����� �����ϴ� �Լ��̴�.
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

	return M_TOP; // �ǹ̾���
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
	
	m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // ���Ͽ��� ������� ���ϸ��̼� 5 ���⿡ ���� ���� ���� �ε���( 0 ~ 4),  ����	
	m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
	m_nAniSprIndex = m_AniRange.nIndex0;	
}

// Note: m_nAniSprIndex�� ������ �̵���ΰ� �ٲ� �� ���� �����ǰ� m_ANiRangeIndex�� ���� �� ������ �����ȴ�.
// Update() �Լ��� ���������� ��� ��ǥ(m_ptXY)�� ����� ��������Ʈ �ε���(m_nAniSprIndex)�� ���ϴ� ���̴�.
void CEnemy::Update(DWORD dwCurTime, DWORD dwElapsedTime)
{
	float fDistance;	
	POINT ptPoint;

	m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);	
	if(m_sMoveInfo.nDirection == STOP)
	{
		m_dwStopElapsedTime += dwElapsedTime; // �� �����Ӵ� �ɸ� �ð��� ����
		if(m_dwStopElapsedTime >= m_sMoveInfo.dwDelayTime) // STOP ���¿��� �̵���ΰ� �ٲ�� ����
		{
			m_dwStopElapsedTime = 0;
			m_nMovePathIndex = ++m_nMovePathIndex % m_pPattern->GetMoveCount();
			if(m_nMovePathIndex == 0) // ���� �̵��� ���� �ʱ�ȭ
			{ 
				ptPoint = m_pPattern->GetInitXY();
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
			}			

			////// ������ �ٲ� �̵� ���ϸ��̼ǵ� �ٲ��.
			m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);
			m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // ���Ͽ��� ������� ���ϸ��̼� 5 ���⿡ ���� ���� ���� �ε���( 0 ~ 4),  ����	
			m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = dwCurTime;
		}
	}else{		
		if(m_fX == m_sMoveInfo.nDestX && m_fY == m_sMoveInfo.nDestY)
		{
			if(m_nMovePathIndex + 1 == m_pPattern->GetMoveCount() )
			{
				ptPoint = m_pPattern->GetInitXY(); // �ʱⰪ ����
				m_fX = ptPoint.x;
				m_fY = ptPoint.y;
				m_nMovePathIndex = 0;
			}else{
				m_nMovePathIndex++;					
			}

			//////// ������ �ٲ� �̵� ���ϸ��̼ǵ� �ٲ��.
			m_sMoveInfo = m_pPattern->GetMoveInfo(m_nMovePathIndex);
			m_nAniRangeIndex = GetAniDirectionIndex(m_sMoveInfo.nDirection); // ���Ͽ��� ������� ���ϸ��̼� 5 ���⿡ ���� ���� ���� �ε���( 0 ~ 4),  ����	
			m_AniRange = m_pSprite->GetAniRange(m_nAniRangeIndex);
			m_nAniSprIndex = m_AniRange.nIndex0;
			m_dwOldAniTime = dwCurTime;
		}else{
			fDistance = m_sMoveInfo.fVelocity * dwElapsedTime; // s = v*(t1-t0);				
			m_fAddDistance += fDistance;	
			if( (int)m_fAddDistance >= m_sMoveInfo.nAllDistance ) // �Ÿ��� ���� �̵���θ� ����
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

	//Note ���ϸ��̼��� 5���� ������ ���� ���ϸ��̼Ǹ� ���ָ� �ȴ�.
	//     ���ϸ��̼��� �ݺ��� �� �� ���� ���ϸ��̼� ������ �ٲٴ� ���� ���Ͽ��� �Ѵ�.
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

// ���� ��������Ʈ�� ��� ��ǥ
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
	rtRect1 = GetRect(); // ���� ��� ��ǥ
	for(int i = 0 ; i < nCount ; i++)
	{
		rtRect = m_pSprite->GetCollisionRect(m_nAniSprIndex, i); // ��������Ʈ�κ��� �浹��ǥ ��������
		rtRect2.left = rtRect1.left + rtRect.left; // ���� �����ǥ�� ��ȯ
		rtRect2.top = rtRect1.top + rtRect.top;
		rtRect2.right = rtRect2.left + (rtRect.right - rtRect.left) - 1;
		rtRect2.bottom = rtRect2.top + (rtRect.bottom - rtRect.top) - 1;
		if( IntersectRect(&rtTemp, &rect, &rtRect2) != 0) // �浹
			return TRUE;
	}
	return FALSE;
}
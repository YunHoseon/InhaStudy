#pragma once
#include "Sprite.h"
enum ACTION { PLAYER_RIGHT, PLAYER_LEFT, PLAYER_IDLE, PLAYER_SHOOT, PLAYER_FAILED, PLAYER_READY };

class CPlayer 
{
private:
	CSprite *m_pSprite;
	float m_fX, m_fY;
	DWORD m_dwStopElapsedTime; // 아이들일 때 정지시간을 누적하는 변수	
	float m_fVelocity;
	ACTION m_nAction, m_nPreAction;	
	
	int m_nAniSprIndex; // 출력할 스프라이트의 인덱스	
	int m_nAniRangeIndex; // 에니메이션 범위 인덱스
	RANGE m_AniRange;     // 에니메이션 시작 인덱스와 끝 인덱스
	DWORD m_dwOldAniTime; // 이전 에니메이션 시각
public:
	void Init(CSprite *pSprite, int nX, int nY, float fMoveVelocity);
	void Update(DWORD dwCurTime, DWORD dwElapsedTime );
	void Render(HDC hBackBuffer);
	void Move(int nKey);
	BOOL Shoot();	
	ACTION GetState() { return m_nAction; }
	int GetX() { return (int)m_fX; }
	int GetY() { return (int)m_fY; }	
	ACTION GetPreAction() { return m_nPreAction; }
public:
	CPlayer(void);
	~CPlayer(void);
};


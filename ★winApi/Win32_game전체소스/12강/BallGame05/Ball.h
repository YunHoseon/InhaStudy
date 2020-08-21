#pragma once
#include "Sprite.h"
#include "Player.h"

enum BALL_STATE { BALL_RIGHT, BALL_LEFT, BALL_SHOOT, BALL_STOP };
class CBall
{
private:
	int m_fX, m_fY;
	BALL_STATE m_nBallState, m_nPreBallState;
	float m_fVelocity;

	CSprite *m_pSprite;	
	int m_nAniSprIndex; // 애니메이션할 스프라이트의 인덱스	
	int m_nAniRangeIndex; // 에니메이션 범위 인덱스
	RANGE m_AniRange;     // 에니메이션 시작 인덱스와 끝 인덱스
	DWORD m_dwOldAniTime; // 스프라이트의 에니메이션 경과시간을 측정하기 위해서

public:	
	void Init(CSprite *pSprite, int nX, int nY, float fVelocity);
	void SetState(BALL_STATE nState);
	void SetXY(int nX, int nY);
	void Update(DWORD dwCurTime, DWORD dwElapsedTime);
	void Render(HDC hBackBuffer);
	void Shooting(int nX, int nY);
	void LeftMove(int nX, int nY);
	void RightMove(int nX, int nY);
	int  GetX();
	int	 GetY();
	RECT GetRect(); // 실제 출력 좌표
	BALL_STATE GetState();
	void Stop(int nX, int nY);
public:
	CBall(void);
	~CBall(void);
};


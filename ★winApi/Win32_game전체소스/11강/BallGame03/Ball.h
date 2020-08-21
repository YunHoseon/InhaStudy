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
	int m_nAniSprIndex; // �ִϸ��̼��� ��������Ʈ�� �ε���	
	int m_nAniRangeIndex; // ���ϸ��̼� ���� �ε���
	RANGE m_AniRange;     // ���ϸ��̼� ���� �ε����� �� �ε���
	DWORD m_dwOldAniTime; // ��������Ʈ�� ���ϸ��̼� ����ð��� �����ϱ� ���ؼ�

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
	RECT GetRect(); // ���� ��� ��ǥ
	BALL_STATE GetState();
	void Stop(int nX, int nY);
public:
	CBall(void);
	~CBall(void);
};


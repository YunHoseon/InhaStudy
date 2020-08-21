#pragma once
#include "Sprite.h"
enum ACTION { PLAYER_RIGHT, PLAYER_LEFT, PLAYER_IDLE, PLAYER_SHOOT, PLAYER_FAILED, PLAYER_READY };

class CPlayer 
{
private:
	CSprite *m_pSprite;
	float m_fX, m_fY;
	DWORD m_dwStopElapsedTime; // ���̵��� �� �����ð��� �����ϴ� ����	
	float m_fVelocity;
	ACTION m_nAction, m_nPreAction;	
	
	int m_nAniSprIndex; // ����� ��������Ʈ�� �ε���	
	int m_nAniRangeIndex; // ���ϸ��̼� ���� �ε���
	RANGE m_AniRange;     // ���ϸ��̼� ���� �ε����� �� �ε���
	DWORD m_dwOldAniTime; // ���� ���ϸ��̼� �ð�
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


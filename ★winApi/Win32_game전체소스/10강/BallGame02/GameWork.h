#pragma once
#include "GameFrame.h"
#include "Sprite.h"
#include "Player.h"
#include "Ball.h"
#include "ENEMY_INFO.h"
#include "Enemy.h"
#include "GoalDae.h"

class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

	// Note: 1 �ܰ� => ���� ��� ���
	HDC m_hBackGroundDC;
	int m_nStageNumber;
	HDC CreateBmpDC(char *filename);
	CSprite m_GoalDaeSpr;
	CPattern m_GoalDaePat;
	CGoalDae m_GoalDae;

	// Note: 2 �ܰ� => ���ΰ��� ��
	CSprite m_PlayerSprite, m_BallSprite;
	CPlayer m_Player;	
	CBall m_Ball;

	// Note:L 3 �ܰ� => �� ���� ����, ĳ���� �� �ҽ� ���
	CSprite m_pEnemySpr[8]; // ��ĳ���� ��������Ʈ , 8���� �����Ͽ� ���
	CEnemy *m_pEnemy;
	ENEMY_INFO *m_pEnemyInfo; // new�� delete�� ����ؼ� �����ڿ� �Ҹ��ڸ� ����ϱ� ���� �����ͷ� ����
	CPattern *m_pPattern;

public:
	CGameWork(void);
	~CGameWork(void);
};


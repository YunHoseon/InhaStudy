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

	// Note: 1 단계 => 배경과 골대 출력
	HDC m_hBackGroundDC;
	int m_nStageNumber;
	HDC CreateBmpDC(char *filename);
	CSprite m_GoalDaeSpr;
	CPattern m_GoalDaePat;
	CGoalDae m_GoalDae;

	// Note: 2 단계 => 주인공과 공
	CSprite m_PlayerSprite, m_BallSprite;
	CPlayer m_Player;	
	CBall m_Ball;

	// Note:L 3 단계 => 몹 패턴 적용, 캐릭터 툴 소스 사용
	CSprite m_pEnemySpr[8]; // 적캐릭터 스프라이트 , 8개로 고정하여 사용
	CEnemy *m_pEnemy;
	ENEMY_INFO *m_pEnemyInfo; // new와 delete를 사용해서 생성자와 소멸자를 사용하기 위해 포인터로 선언
	CPattern *m_pPattern;

public:
	CGameWork(void);
	~CGameWork(void);
};


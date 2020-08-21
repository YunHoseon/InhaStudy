#pragma once
#include "GameFrame.h"
#include "Sprite.h"
#include "Player.h"
#include "Ball.h"
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
public:
	CGameWork(void);
	~CGameWork(void);
};


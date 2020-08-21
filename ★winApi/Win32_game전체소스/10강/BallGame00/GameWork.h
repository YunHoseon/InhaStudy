#pragma once
#include "GameFrame.h"
#include "Sprite.h"
#include "GoalDae.h"


class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

	// Note: ���� ��� ���
	HDC m_hBackGroundDC;
	int m_nStageNumber;
	HDC CreateBmpDC(char *filename);

    CSprite m_GoalDaeSpr;
	CPattern m_GoalDaePat;
	CGoalDae m_GoalDae;

public:
	CGameWork(void);
	~CGameWork(void);
};


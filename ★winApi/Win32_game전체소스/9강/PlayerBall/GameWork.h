#pragma once
#include "GameFrame.h"
#include "Player.h"
#include "Ball.h"

class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

	CSprite m_PlayerSprite;
	CPlayer m_Player;
	
	CSprite m_BallSprite;
	CBall m_Ball;
public:
	CGameWork(void);
	~CGameWork(void);
};


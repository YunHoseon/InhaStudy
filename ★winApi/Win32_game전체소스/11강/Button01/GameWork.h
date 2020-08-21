#pragma once
#include "GameFrame.h"
#include "ButtonUI.h"

class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

	CButtonUI m_ButtonUI[2];
	
public:
	CGameWork(void);
	~CGameWork(void);
};


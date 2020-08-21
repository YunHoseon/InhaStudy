#pragma once
#include "GameFrame.h"

class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

public:
	CGameWork(void);
	~CGameWork(void);
};


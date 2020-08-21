#pragma once
#include "GameFrame.h"
#include <fmod.hpp>


class CGameWork : public CGameFrame
{
private:	
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

	void SoundInit();
	void SoundUpdate();
	void SoundRelease();


	FMOD::System     *m_pSystem;
    FMOD::Sound      *m_pSound1, *m_pBGMSound2;
	FMOD::Channel    *m_pBGMChannel;

public:
	CGameWork(void);
	~CGameWork(void);
};




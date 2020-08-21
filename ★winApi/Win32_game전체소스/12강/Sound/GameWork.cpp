#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// �߻� Ŭ������ �Լ��� �������� ���������ν� �� Ŭ���� �ȿ��� ���α׷��ָ� �� �� �ְ� 
// �Ǿ���. ���� WinMain()���� ���� Ŭ������ ������ ȣ�� ������ ���� ���ӵ��� ����Ǵ� ����
// �ٷ� �� Ŭ���� �κ��̴�.


CGameWork::CGameWork(void)
{
}

CGameWork::~CGameWork(void)
{
}

void CGameWork::SceneInit()
{	
	SoundInit();
}

void CGameWork::SceneUpdate()
{
	SoundUpdate();
}

void CGameWork::SceneRender()
{
	char string[100];
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	SoundRelease();
}

void CGameWork::SoundInit()
{
	 FMOD::System_Create(&m_pSystem);
	 m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);
	 m_pSystem->createSound("ubs.wav", FMOD_DEFAULT, 0, &m_pSound1);
	 m_pSystem->createStream("run.wav", FMOD_LOOP_NORMAL, 0, &m_pBGMSound2);
	 m_pSystem->playSound(m_pBGMSound2, 0, false, &m_pBGMChannel);	 
}


void CGameWork::SoundUpdate()
{	
	 FMOD::Channel *channel1 = 0;
	 if( GetAsyncKeyState('1') < 0 )
	 {
		 m_pSystem->playSound(m_pSound1, 0, false, &channel1);
		 channel1->setVolume(0.1f);
	 }

	 m_pSystem->update();
}

void CGameWork::SoundRelease()
{
	 m_pSound1->release();
	 m_pBGMSound2->release();

	 m_pSystem->close();
	 m_pSystem->release();
}
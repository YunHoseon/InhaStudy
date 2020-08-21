#pragma once
#include "GameFrame.h"
#include "Sprite.h"
#include "Player.h"
#include "Ball.h"
#include "ENEMY_INFO.h"
#include "Enemy.h"
#include "GoalDae.h"
#include "ButtonUI.h"
#include "StageInfo.h"
#include <fmod.hpp>

enum GAME_STATE {GAME_INIT, GAME_LOADING, GAME_READY, GAME_RUN, GAME_STOP, GAME_SUCCESS, GAME_FAILED, GAME_RESULT, GAME_END }; 

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

	// Note: 4 단계 ( 게임 흐름 만들기)
	GAME_STATE m_nGameState;
	CSprite m_StageCountSpr; // 스테이지 숫자 스프라이트
	CButtonUI m_ButtonUI[5]; // 0: start, 1:end 2 :yes, 3:no, 4: end
	HDC m_hMainDC, m_hLoadingDC, m_hLoadingBallDC, m_hLoadingBarDC, m_hReadyDC, m_hLastScoreDC, m_hPlayInfoDC, m_hGoalEffectDC, m_hSuccessDC, m_hFailedDC, m_hResultDC;
	int m_nLoadingBarCount, m_nLoadingBallX, m_nLoadingBarX;
	DWORD m_dwOldTime, m_dwGameStartTime, m_dwOldEffectTime;
	int m_nEffectCount;
	BOOL m_bGoalEffect, m_bEffectBlink;

	CStageInfo m_StageInfo;
	CSprite m_PlayScoreText1, m_PlayScoreText2, m_ResultText, m_GoalEffect;
	int m_nTotalScore, m_nScore, m_nGoal, m_nMin, m_nSec;

	void ScorePrint(int nX, int nY, CSprite *pSprite, int nNum, int nGap);
	void ScorePrintEx(int nX, int nY, CSprite *pSprite, int nNum, int nGap);
	void ResultScorePrint(int nY, CSprite *pSprite, int nNum, int nGap);

	// Note: 사운드 처리 FMOD
	FMOD::System     *m_pSystem;
    FMOD::Sound      *m_pSound[9], *m_pBGMSound, *m_pInitSound, *m_pFailedSound;
	FMOD::Channel    *m_pBGMChannel, *m_pInitChannel, *m_pLoadingChannel, *m_pFailedChannel; // Loop 채널

public:
	CGameWork(void);
	~CGameWork(void);
};


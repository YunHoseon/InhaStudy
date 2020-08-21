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

	// Note: 4 �ܰ� ( ���� �帧 �����)
	GAME_STATE m_nGameState;
	CSprite m_StageCountSpr; // �������� ���� ��������Ʈ
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

	// Note: ���� ó�� FMOD
	FMOD::System     *m_pSystem;
    FMOD::Sound      *m_pSound[9], *m_pBGMSound, *m_pInitSound, *m_pFailedSound;
	FMOD::Channel    *m_pBGMChannel, *m_pInitChannel, *m_pLoadingChannel, *m_pFailedChannel; // Loop ä��

public:
	CGameWork(void);
	~CGameWork(void);
};


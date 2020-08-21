#include "StdAfx.h"
#include "GameWork.h"
#include <stdio.h>

// �߻� Ŭ������ �Լ��� �������� ���������ν� �� Ŭ���� �ȿ��� ���α׷��ָ� �� �� �ְ� 
// �Ǿ���. ���� WinMain()���� ���� Ŭ������ ������ ȣ�� ������ ���� ���ӵ��� ����Ǵ� ����
// �ٷ� �� Ŭ���� �κ��̴�.
#define GAP 17

CGameWork::CGameWork(void)
{
	m_nStageNumber = 0;
	m_hBackGroundDC = NULL;
	m_pEnemyInfo = NULL;
	m_pPattern = NULL;
	m_nTotalScore = 0;
	m_pBGMSound = NULL;
}

CGameWork::~CGameWork(void)
{
}


HDC CGameWork::CreateBmpDC(char *filename)
{
	HBITMAP hBitmap;
	HDC hdc = GetDC( m_hWnd );
	HDC hMemDC = CreateCompatibleDC( hdc );	
	hBitmap = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	
	SelectObject( hMemDC, hBitmap );
	DeleteObject( hBitmap );	
	ReleaseDC( m_hWnd, hdc );
	return hMemDC;
}


void CGameWork::SceneInit()
{	
	char *strEnemySprFileName[] = {"enemy1_r.spr", "enemy2_r.spr", "enemy3_r.spr", "enemy4_r.spr", 
									"enemy5_r.spr", "enemy6_r.spr", "enemy7_r.spr", "enemy8_r.spr" };
	char *strBackGroundImage[] = {"ground1_r.bmp", "ground2_r.bmp", "ground3_r.bmp", "ground4_r.bmp" };
	char *strStageInfo[] = {"test1.stg", "test2.stg", "test3.stg", "test4.stg" };
	char *strSoundFileName[] = {"creadit.wav", "ready.wav", "shoot.wav", "ubs.wav", "wow.wav", "goal1.wav", "play_shoot.wav", "logo.wav", "fail.wav" };
	FMOD::Channel  *m_pChannel1;

	switch(m_nGameState)
	{
	case GAME_INIT: // Note: �ѹ� �ε��ؼ� ��� ����ϴ� �� ���ַ� �ڵ�
		// �ʱ�ȭ �κ�
		m_hMainDC = CreateBmpDC("main2.bmp");
		m_ButtonUI[0].Init(m_hWnd, "start_button.spr", 569, 375);
		m_ButtonUI[1].Init(m_hWnd, "exit_button.spr", 569, 440);
		m_ButtonUI[2].Init(m_hWnd, "yes_button.spr", 233, 321);
		m_ButtonUI[3].Init(m_hWnd, "no_button.spr", 403, 321);
		m_ButtonUI[4].Init(m_hWnd, "end_button.spr", 322, 389);
		
		// �ε� �κ�
		m_hLoadingDC = CreateBmpDC("loading_r.bmp");
		m_hLoadingBallDC = CreateBmpDC("loading_ball.bmp");
		m_hLoadingBarDC = CreateBmpDC("loading_bar.bmp");		

		// ���� �κ�
		m_hReadyDC = CreateBmpDC("stage.bmp");
		m_StageCountSpr.Load(m_hWnd, "stage_count.spr");		

		// Note: ���� �÷��̾�, ���� �����̹Ƿ�
		m_GoalDaeSpr.Load(m_hWnd, "goalpost_r.spr");
		m_GoalDaePat.Load("goal1.pat");
		m_GoalDae.Init(&m_GoalDaeSpr, &m_GoalDaePat);	

		m_PlayerSprite.Load(m_hWnd, "player.spr");
		m_Player.Init(&m_PlayerSprite, 300, 500, 0.09f);
		m_BallSprite.Load(m_hWnd, "ball_r.spr");
		m_Ball.Init(&m_BallSprite, 300 - GAP, 500, 0.3f);

		for(int i = 0 ; i < 8; i++)
			m_pEnemySpr[i].Load(m_hWnd, strEnemySprFileName[i]);

		m_hPlayInfoDC = CreateBmpDC("play_info.bmp");
		m_PlayScoreText1.Load(m_hWnd, "total_stage_text.spr");
		m_PlayScoreText2.Load(m_hWnd, "score_time_goal_text.spr");

		// Note: �������� ���� ���� ��
		m_hSuccessDC = CreateBmpDC("success.bmp");
		m_hFailedDC = CreateBmpDC("retry_r.bmp");

		// Note: ���� ���� �ε�
		m_hResultDC = CreateBmpDC("last_score.bmp");
		m_ResultText.Load(m_hWnd, "last_score_count.spr");

		// Note: ���� ȿ�� ����Ʈ �ε�
		m_GoalEffect.Load(m_hWnd, "goal_effect.spr");
		m_nEffectCount = m_nTotalScore = 0;
		m_bGoalEffect = FALSE;
		m_bEffectBlink = TRUE;

		// Note: ���� ���� �� �ε�
		 FMOD::System_Create(&m_pSystem);
		 m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);
		 // Note: ȿ�� �� ����
		 for(int i = 0 ; i < 9 ; i++ )
			m_pSystem->createSound( strSoundFileName[i], FMOD_DEFAULT, 0, &m_pSound[i]);
		
		 m_pSystem->createStream("init1.wav", FMOD_LOOP_NORMAL, 0, &m_pInitSound);		
		 m_pSystem->playSound( m_pInitSound, 0, false, &m_pInitChannel);
		 break;

	case GAME_LOADING:		
		m_nLoadingBarCount = 0;
		m_nLoadingBallX = 20;
		m_nLoadingBarX = 26;
		m_dwOldTime = m_dwCurTime;		

		// Note: ------------------- ������ �ε� -----------------------------
		if(m_hBackGroundDC != NULL)
			DeleteDC(m_hBackGroundDC);
		m_hBackGroundDC = CreateBmpDC(strBackGroundImage[m_nStageNumber % 4]);	// 4�� �ۿ� �����Ƿ�

		m_StageInfo.Load(strStageInfo[m_nStageNumber]);
	
		// Note: ��ĳ���Ϳ� ������ ������ ����
		delete m_pEnemyInfo; // �Ҹ��� ȣ�� 
		m_pEnemyInfo = new ENEMY_INFO(); // ������ ȣ�� �� �ʱ�ȭ			
		m_pEnemyInfo->Load(m_StageInfo.m_strEnemyTeamName);

		//Note: ��ĳ���� ����
		delete [] m_pEnemy;
		m_pEnemy = new CEnemy[m_pEnemyInfo->nEnemyCount];
	
		// Note: �� ���� ����
		delete [] m_pPattern;
		m_pPattern = new CPattern[m_pEnemyInfo->nPatCount];
		for(int i = 0 ; i < m_pEnemyInfo->nPatCount ; i++)
			m_pPattern[i].Load(m_pEnemyInfo->strPatFileName[i]);

		// Note: ���ϰ� ��������Ʈ�� ��ĳ���Ϳ� ����
		int nSprIndex, nPatIndex;
		for(int i =0 ; i < m_pEnemyInfo->nEnemyCount ; i++)
		{
			nSprIndex = m_pEnemyInfo->pEnemyIndex[i].nSprIndex;
			nPatIndex = m_pEnemyInfo->pEnemyIndex[i].nPatIndex;
			m_pEnemy[i].Init(&m_pEnemySpr[nSprIndex], &m_pPattern[nPatIndex]);
		}

		if(m_pBGMSound != NULL)
			m_pBGMSound->release();
		m_pSystem->createStream(m_StageInfo.m_strBackgroundSoundName, FMOD_LOOP_NORMAL, 0, &m_pBGMSound);
		m_pSystem->createStream("fail.wav", FMOD_LOOP_NORMAL, 0, &m_pFailedSound);		
		break;
		
	case GAME_READY:
		m_dwOldTime = m_dwCurTime;	
		m_pSystem->playSound(m_pSound[1], 0, false, &m_pChannel1); // ready ����	
		break;
	case GAME_RUN:
		m_nScore = 0;
		m_nGoal = m_StageInfo.m_nGoalCount;
		m_nMin = m_StageInfo.m_nLimitedTime / 60000;
		m_nSec = (m_StageInfo.m_nLimitedTime / 1000 ) % 60;	
		m_dwGameStartTime = m_dwCurTime;	
		m_bGoalEffect = FALSE;
		m_bEffectBlink = TRUE;
		break;	

	case GAME_STOP: // GAME_RUN���� GAME_SUCCESS�� �Ѿ� ���� ���� ȿ���� ����� ����ϱ� ���� �� �ܰ�
		m_dwOldTime = m_dwCurTime;	
		break;

	case GAME_SUCCESS:				
		m_nTotalScore += m_nScore; // ���� ����
		m_dwOldTime = m_dwCurTime;	
		m_pBGMChannel->stop();
		m_pSystem->playSound(m_pSound[7], 0, false, &m_pChannel1);
		break;

	case GAME_FAILED:
		m_pBGMChannel->stop();
		m_pSystem->playSound(m_pFailedSound, 0, false, &m_pFailedChannel); // ���� ����	
		m_nScore = 0;
		break;
	}
}

void CGameWork::SceneUpdate()
{
	BOOL bCollision = FALSE;
	FMOD::Channel  *m_pChannel1;	

	switch(m_nGameState)
	{
	case GAME_INIT:
		for(int i = 0; i < 2; i++)
		{
			m_ButtonUI[i].Update(m_nMouseState, m_ptMouseClick);			
			if(m_ButtonUI[i].IsClicked() == TRUE)
			{
				// ��ư ���� ����
				m_pInitChannel->stop();
				m_pSystem->playSound(m_pSound[0], 0, false, &m_pChannel1);
				if( i == 0 ) //start ��ư Ŭ��
				{
					m_nGameState = GAME_LOADING;
					SceneInit();									
				}else{
					SendMessage(m_hWnd, WM_DESTROY, 0, 0);
					return;
				}
			}
		}
		break;

	case GAME_LOADING:		
		if( m_nLoadingBarCount == 50)
		{
			m_nGameState = GAME_READY;
			m_pLoadingChannel->stop();
			SceneInit();								
		}else if(m_dwCurTime - m_dwOldTime >= 150)	{
			m_dwOldTime = m_dwCurTime;
			m_nLoadingBarCount++;
		}
		break;
		
	case GAME_READY:
		if(m_dwCurTime - m_dwOldTime > 2000)
		{
			m_nGameState = GAME_RUN;
			SceneInit();		
			m_pSystem->playSound(m_pBGMSound, 0, false, &m_pBGMChannel); // ���� ��� ����
		}
		break;

	case GAME_RUN:
		// Note: ���� �켱 ������ ���� ���� ���ѽð��� ������ ���̴�.
		if(m_dwCurTime - m_dwGameStartTime >= m_StageInfo.m_nLimitedTime)
		{ 
			if(m_nGoal > 0 )
			{ // �̼� ����
			  m_nGameState = GAME_FAILED;
			  SceneInit();
			  return ;
			}
		}else{
			DWORD dwRemindTime = m_StageInfo.m_nLimitedTime - (m_dwCurTime - m_dwGameStartTime);
			m_nMin = dwRemindTime / 60000;
			m_nSec =  (dwRemindTime / 1000 ) % 60;			
		}

		if(GetAsyncKeyState(VK_RIGHT) < 0 )
		{
			m_Player.Move(VK_RIGHT);		
		}
		else if(GetAsyncKeyState(VK_LEFT) < 0)
		{
			m_Player.Move(VK_LEFT);
			
		}else if(GetAsyncKeyState(VK_SPACE) < 0) // ���� �ƹ����ۿ����� �����ϵ��� ��
		{
			if(m_Ball.GetState() != BALL_SHOOT && m_Player.Shoot() == TRUE) // �����ۿ� ���� �ʱ�ȭ		
			{
				m_Ball.Shooting(m_Player.GetX(), m_Player.GetY() - GAP);
				m_pSystem->playSound(m_pSound[6], 0, false, &m_pChannel1); // �� ����
				m_pSystem->playSound(m_pSound[2], 0, false, &m_pChannel1); // �� ����	
			}
		}

		m_Player.Update(m_dwCurTime, m_dwElapsedTime);

		// Note: ���ΰ��� ���¿� ���� ���� ������ �����Ƿ�
		switch(m_Player.GetState())
		{
		case PLAYER_LEFT:		
			if(m_Ball.GetState() != BALL_SHOOT) 
				m_Ball.LeftMove(m_Player.GetX() - GAP, m_Player.GetY());		
			break;
		case PLAYER_RIGHT:
			if(m_Ball.GetState() != BALL_SHOOT)
				m_Ball.RightMove( m_Player.GetX() + GAP, m_Player.GetY());			
			break;
		case PLAYER_READY: // 0.5�� ���� ���� ���� ���·� �ִ´�.
			if( m_Ball.GetState() != BALL_SHOOT )
			{
				if( m_Player.GetPreAction() == PLAYER_LEFT  )	
					m_Ball.Stop( m_Player.GetX() - GAP, m_Player.GetY());
				else if( m_Player.GetPreAction() == PLAYER_RIGHT )	
					m_Ball.Stop(m_Player.GetX() + GAP, m_Player.GetY());
			}
			break;
		case PLAYER_IDLE:
			if(m_Ball.GetState() != BALL_SHOOT)
				m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
			break;
		}

		m_Ball.Update(m_dwCurTime, m_dwElapsedTime);	

		for(int i = 0; i < m_pEnemyInfo->nEnemyCount ; i++)
			m_pEnemy[i].Update(m_dwCurTime, m_dwElapsedTime);

		// Note: �浹 üũ
		//       ���� ��ĳ���� �浹 üũ 
		RECT rtBallRect, rtRect, rtTemp;
		rtBallRect = m_Ball.GetRect();

		for(int i = 0 ; i < m_pEnemyInfo->nEnemyCount ; i++)
		{
			// Note: 1 �� �浹 ����, ��������Ʈ ��ǥ�θ�
			rtRect = m_pEnemy[i].GetRect();
			if( IntersectRect(&rtTemp, &rtBallRect, &rtRect) != 0 ) // 1�� �浹
			{  // 2�� �浹 üũ
				if( m_pEnemy[i].IsSprCollsion(rtBallRect) == TRUE)
				{
					m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
					bCollision = TRUE;
					m_pSystem->playSound(m_pSound[3], 0, false, &m_pChannel1); // ���� ���� �浹 ���� ����
					break; // �� �Ѱ��� �浹�̹Ƿ� ������ �ݺ����� ������ �ϹǷ�....
				}
			}
		}
		
		m_GoalDae.Update(m_dwCurTime, m_dwElapsedTime);

		// ���� ��� �浹 üũ
		if(bCollision == FALSE)
		{   
			rtRect = m_GoalDae.GetCollisionRect();
			if(IntersectRect(&rtTemp, &rtBallRect, &rtRect) != 0 )
			{  // �����̹Ƿ� �������� ����
				// Note: ���� ����Ʈ ����
				m_pSystem->playSound(m_pSound[5], 0, false, &m_pChannel1); // ���� ���� ���
				m_bGoalEffect = TRUE;
				m_dwOldEffectTime = m_dwCurTime;
				m_nEffectCount = 0;
				m_bEffectBlink = TRUE;			

				m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
				bCollision = TRUE;
				--m_nGoal;
				m_nScore += 10;  // �� ��� 10���� ����
				if( m_nGoal == 0 )
				{  // �̼� ����
					 m_nGameState = GAME_STOP;					
					 SceneInit();
					 return ; // ������Ʈ �Լ� ����
				}				
			}
		}

		// ���� ���߼� �浹 üũ
		if(bCollision == FALSE)
		{
			if( rtBallRect.top <= 30 )
			{
				m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
				bCollision = TRUE;
				m_pSystem->playSound(m_pSound[4], 0, false, &m_pChannel1); // ���� ���� �浹 ���� ����
			}
		}	

		// Note: Effect �� ���� ó�� ����
		if( m_bGoalEffect )
		{
			if(m_nEffectCount == 7)
			{
				m_bGoalEffect = FALSE;				
				break;
			}
			
			if(m_dwCurTime - m_dwOldEffectTime >= 500)
			{
				m_dwOldEffectTime = m_dwCurTime;
				m_nEffectCount++;				
				m_bEffectBlink = !m_bEffectBlink;
			}
		}
		break;	

	case GAME_STOP: // ��ǥ���� ä���� �� ����Ǵ� �κ��̴�.
		if(m_dwCurTime - m_dwOldTime >= 3000)
		{			
			m_nGameState = GAME_SUCCESS;
			SceneInit();	
		}else if( m_bGoalEffect ){ // Note: Effect �� ���� ó�� ����
			if(m_nEffectCount == 7)
			{
				m_bGoalEffect = FALSE;				
				break;
			}
			
			if(m_dwCurTime - m_dwOldEffectTime >= 500)
			{
				m_dwOldEffectTime = m_dwCurTime;
				m_nEffectCount++;				
				m_bEffectBlink = !m_bEffectBlink;
			}
		}
		break;

	case GAME_SUCCESS: // 5�� ���� ��� ����� �Ŀ� ���� ���������� �ε�
		if( m_dwCurTime - m_dwOldTime >= 5100 )
		{
			++m_nStageNumber;
			m_nGameState = GAME_LOADING;
			SceneInit();
		}
		break;

	case GAME_FAILED: // ���콺 ó�� �κ�
		for(int i = 2 ; i < 4 ; i++)
		{
			m_ButtonUI[i].Update(m_nMouseState, m_ptMouseClick);
			if(m_ButtonUI[i].IsClicked() == TRUE)
			{
				if( i == 2 ){ // �ٽ� ����, ready��
					m_pFailedChannel->stop();
					m_pSystem->playSound(m_pSound[0], 0, false, &m_pChannel1);  // ��ư �Ҹ�
					m_nGameState = GAME_READY;
					SceneInit();					
				} else if( i == 3 ){ // ���� ����, ���� ��� �� �����Ŵ
					m_nGameState = GAME_RESULT;
					m_pFailedChannel->stop();
					m_pSystem->playSound(m_pSound[0], 0, false, &m_pChannel1);  // ��ư �Ҹ�
					return ;
				}
			}
		}
		break;

	case GAME_RESULT:
		m_ButtonUI[4].Update(m_nMouseState, m_ptMouseClick);
		if(m_ButtonUI[4].IsClicked() == TRUE)
		{
			m_pSystem->playSound(m_pSound[0], 0, false, &m_pChannel1);  // ��ư �Ҹ�
			Sleep(400); // ���� ��� ������ 
			m_nGameState = GAME_END;
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		}
		break;
	}	

	m_pSystem->update(); 
}

void CGameWork::ScorePrint(int nX, int nY, CSprite *pSprite, int nNum, int nGap)
{
	char string[100], strTemp[2] = {0,};
	int nCount, nIndex, nWidth, nHeight;
	HDC hSpriteDC;
	RECT rect;

	sprintf(string, "%d", nNum);
	nCount = strlen(string);
	hSpriteDC = pSprite->GetSrcImageDC();			
	for(int i = 0; i < nCount ; i++)
	{		
		strTemp[0] = string[i];  // ���� ���ڿ� ��ȯ
		nIndex = atoi(strTemp);  
		nWidth = pSprite->GetSprWidth(nIndex);
		nHeight = pSprite->GetSprHeight(nIndex);
		rect = pSprite->GetSprRect(nIndex); // �ڸ� ��ǥ
		BitBlt(m_hBackBuffer, nX, nY, nWidth, nHeight, hSpriteDC, rect.left, rect.top, SRCCOPY);
		nX += nWidth + nGap; 
	}
}

// �� �ڸ� ���� �� �ڸ� ���� ó���ϴ� �Լ�
void CGameWork::ScorePrintEx(int nX, int nY, CSprite *pSprite, int nNum, int nGap)
{
	char string[100], strTemp[2] = {0,};
	int nCount, nIndex, nWidth, nHeight;
	HDC hSpriteDC;
	RECT rect;

	if(nNum <= 9)
	   sprintf(string, "%02d", nNum);
	else
	   sprintf(string, "%d", nNum);

	nCount = strlen(string);
	hSpriteDC = pSprite->GetSrcImageDC();			
	for(int i = 0; i < nCount ; i++)
	{		
		strTemp[0] = string[i];  // ���� ���ڿ� ��ȯ
		nIndex = atoi(strTemp);  
		nWidth = pSprite->GetSprWidth(nIndex);
		nHeight = pSprite->GetSprHeight(nIndex);
		rect = pSprite->GetSprRect(nIndex); // �ڸ� ��ǥ
		BitBlt(m_hBackBuffer, nX, nY, nWidth, nHeight, hSpriteDC, rect.left, rect.top, SRCCOPY);
		nX += nWidth + nGap; 
	}
}


// ��� ������ ����ϴ� �κ�, �߰� �����Ѵ�.
void CGameWork::ResultScorePrint(int nY, CSprite *pSprite, int nNum, int nGap)
{
	char string[100], strTemp[2] = {0,};
	int nCount, nIndex, nWidth, nHeight, nX, nTextLength = 0; // ���ڿ� ����
	HDC hSpriteDC;
	RECT rect;

	sprintf(string, "%d", nNum);
	nCount = strlen(string);
	// Note: ����� ��ü ���ڿ��� ���̸� ���
	for(int i = 0 ; i < nCount ; i++)
	{   
		strTemp[0] = string[i];  
		nIndex = atoi(strTemp);  
		nWidth = pSprite->GetSprWidth(nIndex);
		nTextLength += nWidth + nGap;
	}
	
	hSpriteDC = pSprite->GetSrcImageDC();			
	nX = (799 - nTextLength - 1) / 2; // ���� 800�� ��, ���ڿ� ������ ��
	for(int i = 0; i < nCount ; i++)
	{		
		strTemp[0] = string[i];  // ���� ���ڿ� ��ȯ
		nIndex = atoi(strTemp);  
		nWidth = pSprite->GetSprWidth(nIndex);
		nHeight = pSprite->GetSprHeight(nIndex);
		rect = pSprite->GetSprRect(nIndex); // �ڸ� ��ǥ
		BitBlt(m_hBackBuffer, nX, nY, nWidth, nHeight, hSpriteDC, rect.left, rect.top, SRCCOPY);
		nX += nWidth + nGap; 
	}
}



void CGameWork::SceneRender()
{
	char string[100], strTemp[2]= {0,};
	HDC hSpriteDC;
	int nCount, nX, nWidth, nHeight, nIndex;
	RECT rect;	
	
	//------------------ ������ ���� ----------------------
	switch(m_nGameState)
	{
	case GAME_INIT:
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hMainDC, 0, 0, SRCCOPY); // ���� ȭ�� ���
		for(int i = 0; i < 2; i++) // start, exit ��ư ���
			m_ButtonUI[i].Render(m_hBackBuffer);
		break;

	case GAME_LOADING:		
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hLoadingDC, 0, 0, SRCCOPY);
		BitBlt(m_hBackBuffer, m_nLoadingBallX + 9*m_nLoadingBarCount - 1, 441, 61, 60, m_hLoadingBallDC, 0, 0, SRCCOPY);

		for(int i = 0 ; i < m_nLoadingBarCount ; i++) // 9, 43
		{
			BitBlt(m_hBackBuffer, m_nLoadingBarX + 9*i - 1, 450, 9, 43, m_hLoadingBarDC, 0, 0, SRCCOPY);			
		}
		break;
		
	case GAME_READY:
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hReadyDC, 0, 0, SRCCOPY);				
		sprintf(string, "%d", m_nStageNumber + 1);
		nCount = strlen(string);
		hSpriteDC = m_StageCountSpr.GetSrcImageDC();			
		for(int i = 0, nX = 542 ; i < nCount ; i++)
		{		
			strTemp[0] = string[i];  // ���� ���ڿ� ��ȯ
			nIndex = atoi(strTemp);  
			nWidth = m_StageCountSpr.GetSprWidth(nIndex);
			nHeight = m_StageCountSpr.GetSprHeight(nIndex);
			rect = m_StageCountSpr.GetSprRect(nIndex); // �ڸ� ��ǥ
			BitBlt(m_hBackBuffer, nX, 260, nWidth, nHeight, hSpriteDC, rect.left, rect.top, SRCCOPY);
			nX += nWidth + 10; 
		}
		break;
	
	case GAME_STOP:	
	case GAME_RUN:	
		BitBlt(m_hBackBuffer, 0, 0, 600, 600, m_hBackGroundDC, 0, 0, SRCCOPY);	
		// Note: ���� �������̽� �κ�
		BitBlt(m_hBackBuffer, 600, 0, 200, 243, m_hPlayInfoDC, 0, 0, SRCCOPY);				
		ScorePrint(690, 22, &m_PlayScoreText1, m_nTotalScore, 3); // ���� ���
		ScorePrint(690, 53, &m_PlayScoreText1, m_nStageNumber + 1, 3); // �������� ���
		ScorePrint(707, 139, &m_PlayScoreText2, m_nScore, 3); // ���� ���
		ScorePrintEx(707, 175, &m_PlayScoreText2, m_nMin, 3); // �� ���
		rect = m_PlayScoreText2.GetSprRect(10);
		nWidth = m_PlayScoreText2.GetSprWidth(10);
		nHeight = m_PlayScoreText2.GetSprHeight(10);
		BitBlt(m_hBackBuffer, 735, 178, nWidth, nHeight, m_PlayScoreText2.GetSrcImageDC(), rect.left, rect.top, SRCCOPY); 
		ScorePrintEx(743, 175, &m_PlayScoreText2, m_nSec, 3); // �� ���		
		ScorePrint(707, 212, &m_PlayScoreText2, m_nGoal, 3); // ��ǥ���μ� ���
		// Note: ��� �κ�
		m_GoalDae.Render(m_hBackBuffer);
		// Note: ��ĳ���� ���
		for(int i = 0 ; i < m_pEnemyInfo->nEnemyCount ; i++)
			m_pEnemy[i].Render(m_hBackBuffer);

		// Note: ���� ����Ʈ ���
		if( m_bGoalEffect )
		{
			if( m_bEffectBlink ) // ����Ʈ ���
			{
				nWidth = m_GoalEffect.GetSprWidth(0);
				nHeight = m_GoalEffect.GetSprHeight(0);
				rect = m_GoalEffect.GetSprRect(0);
				TransparentBlt(m_hBackBuffer, 200, 170, nWidth, nHeight, m_GoalEffect.GetSrcImageDC(),  
											  rect.left, rect.top, nWidth, nHeight, m_GoalEffect.GetTransColor());
			}
		}

		// Note: ���ΰ��� �� ���
		m_Player.Render(m_hBackBuffer);
		m_Ball.Render(m_hBackBuffer);
		break;

	case GAME_SUCCESS:		
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hSuccessDC, 0, 0, SRCCOPY);		
		break;

	case GAME_FAILED:	
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hFailedDC, 0, 0, SRCCOPY);
		for(int i = 2 ; i < 4 ; i++)
			m_ButtonUI[i].Render(m_hBackBuffer);
		break;

	case GAME_RESULT:		
		BitBlt(m_hBackBuffer, 0, 0, 800, 600, m_hResultDC, 0, 0, SRCCOPY);		 
		ResultScorePrint(231, &m_ResultText, m_nTotalScore, 9); // ���� ���
		m_ButtonUI[4].Render(m_hBackBuffer);
		break;
	}
	
	
	//------------------ ������ �� -------------------------
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	// Note: �޸� DC ����  
	DeleteDC(m_hMainDC);
	DeleteDC(m_hLoadingDC);
	DeleteDC(m_hLoadingBallDC);
	DeleteDC(m_hLoadingBarDC);
	DeleteDC(m_hReadyDC);
	DeleteDC(m_hLastScoreDC);
	DeleteDC(m_hPlayInfoDC);
	DeleteDC(m_hGoalEffectDC);
	DeleteDC(m_hSuccessDC);
	DeleteDC(m_hFailedDC);
	DeleteDC(m_hResultDC);

	if(m_hBackGroundDC != NULL)
		DeleteDC(m_hBackGroundDC);

	// Note: ���� ����
	for(int i = 0 ; i < 9 ; i++)
		m_pSound[i]->release();
	m_pFailedSound->release();
	m_pBGMSound->release();
	m_pInitSound->release();
	m_pSystem->close();
	m_pSystem->release();

	m_GoalDaeSpr.Release();
	m_PlayerSprite.Release();
	m_BallSprite.Release();
	m_PlayScoreText1.Release();
	m_PlayScoreText2.Release();
	m_ResultText.Release();
	m_StageCountSpr.Release();	

	for(int i = 0 ; i < 8 ; i++)
		m_pEnemySpr[i].Release();
	
	delete m_pEnemyInfo;
	delete [] m_pEnemy;
	delete [] m_pPattern;
}
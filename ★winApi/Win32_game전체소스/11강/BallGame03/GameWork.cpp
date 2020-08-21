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

	if(m_hBackGroundDC != NULL)
		DeleteDC(m_hBackGroundDC);
	m_hBackGroundDC = CreateBmpDC(strBackGroundImage[m_nStageNumber]);	
	// Note: ��� 
	m_GoalDaeSpr.Load(m_hWnd, "goalpost_r.spr");
	m_GoalDaePat.Load("goal1.pat");
	m_GoalDae.Init(&m_GoalDaeSpr, &m_GoalDaePat);	

	m_PlayerSprite.Load(m_hWnd, "player.spr");
	m_Player.Init(&m_PlayerSprite, 300, 500, 0.07f);
	m_BallSprite.Load(m_hWnd, "ball_r.spr");
	m_Ball.Init(&m_BallSprite, 300 - GAP, 500, 0.3f);

	for(int i = 0 ; i < 8; i++)
		m_pEnemySpr[i].Load(m_hWnd, strEnemySprFileName[i]);
	
	// Note: ��ĳ���Ϳ� ������ ������ ����
	delete m_pEnemyInfo; // �Ҹ��� ȣ�� 
	m_pEnemyInfo = new ENEMY_INFO(); // ������ ȣ�� �� �ʱ�ȭ			
	m_pEnemyInfo->Load("test.mob");

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
}

void CGameWork::SceneUpdate()
{
	BOOL bCollision = FALSE;

	if(GetAsyncKeyState(VK_RIGHT) < 0 )
	{
		m_Player.Move(VK_RIGHT);		
	}
	else if(GetAsyncKeyState(VK_LEFT) < 0)
	{
		m_Player.Move(VK_LEFT);
		
	}else if(GetAsyncKeyState(VK_SPACE) < 0) // ���� �ƹ����ۿ����� �����ϵ��� ��
	{
		if( m_Player.Shoot() == TRUE && m_Ball.GetState() != BALL_SHOOT ) // �����ۿ� ���� �ʱ�ȭ		
			m_Ball.Shooting(m_Player.GetX(), m_Player.GetY() - GAP);
	}

	m_Player.Update(m_dwCurTime, m_dwElapsedTime);

	// Note: ���ΰ��� ���¿� ���� ���� ������ �����Ƿ�
	switch(m_Player.GetState())
	{
	case PLAYER_LEFT:		
		m_Ball.LeftMove(m_Player.GetX() - GAP, m_Player.GetY());		
		break;
	case PLAYER_RIGHT:
		m_Ball.RightMove( m_Player.GetX() + GAP, m_Player.GetY());			
		break;
	case PLAYER_READY: // 0.5�� ���� ���� ���� ���·� �ִ´�.
		if( m_Player.GetPreAction() == PLAYER_LEFT )	
			m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
		else if( m_Player.GetPreAction() == PLAYER_RIGHT )	
			m_Ball.Stop(m_Player.GetX() + GAP, m_Player.GetY());
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
			m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
			bCollision = TRUE;
		}
	}

	// ���� ���߼� �浹 üũ
	if(bCollision == FALSE)
	{
		if( rtBallRect.top <= 30 )
		{
			m_Ball.Stop(m_Player.GetX() - GAP, m_Player.GetY());
			bCollision = TRUE;
		}
	}	
}

void CGameWork::SceneRender()
{
	char string[100];
	//------------------ ������ ���� ----------------------
	BitBlt(m_hBackBuffer, 0, 0, 600, 600, m_hBackGroundDC, 0, 0, SRCCOPY);	
	
	m_GoalDae.Render(m_hBackBuffer);

	// Note: ��ĳ���� ���
	for(int i = 0 ; i < m_pEnemyInfo->nEnemyCount ; i++)
		m_pEnemy[i].Render(m_hBackBuffer);

	// ���ΰ��� �� ���
	m_Player.Render(m_hBackBuffer);
	m_Ball.Render(m_hBackBuffer);
	
	//------------------ ������ �� -------------------------
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS); 
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));
}

void CGameWork::SceneRelease()
{
	if(m_hBackGroundDC != NULL)
		DeleteDC(m_hBackGroundDC);

	m_GoalDaeSpr.Release();
	m_PlayerSprite.Release();
	m_BallSprite.Release();
	

	for(int i = 0 ; i < 8 ; i++)
		m_pEnemySpr[i].Release();
	
	delete m_pEnemyInfo;
	delete [] m_pEnemy;
	delete [] m_pPattern;
}
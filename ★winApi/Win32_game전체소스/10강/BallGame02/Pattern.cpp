#include "StdAfx.h"
#include "Pattern.h"
#include <stdio.h>


CPattern::CPattern(void)
{
	m_pMoveInfo = NULL;
	m_nMoveCount = 0;
}


CPattern::~CPattern(void)
{
	delete [] m_pMoveInfo;
}


BOOL CPattern::Load(char *filename)
{
	FILE *fp;

	fp = fopen(filename, "rt");
	fscanf(fp, "move count = %d\n", &m_nMoveCount);
	fscanf(fp, "x0 = %d y0 = %d\n", &m_nX0, &m_nY0);

	if(m_pMoveInfo != NULL)
		delete [] m_pMoveInfo;
				
	m_pMoveInfo = new MOVE_INFO[m_nMoveCount];		
	for(int i= 0 ; i < m_nMoveCount ; i++)
	{
			fscanf(fp, "dir=%d vel=%f dist=%d time=%d x=%d y=%d\n", &m_pMoveInfo[i].nDirection, 
			           &m_pMoveInfo[i].fVelocity,	&m_pMoveInfo[i].nAllDistance, 
			 		   &m_pMoveInfo[i].dwDelayTime, &m_pMoveInfo[i].nDestX,
					   &m_pMoveInfo[i].nDestY);
	}
	fclose(fp);

	return TRUE;
}

BOOL CPattern::Save(char *filename)
{
	FILE *fp;

	fp = fopen(filename, "wt");
	fprintf(fp, "move count = %d\n", m_nMoveCount);
	fprintf(fp, "x0 = %d y0 = %d\n", m_nX0, m_nY0);	
				
	for(int i= 0 ; i < m_nMoveCount ; i++)
	{
		fprintf(fp, "dir=%d vel=%f dist=%d time=%d x=%d y=%d\n", m_pMoveInfo[i].nDirection, 
			           m_pMoveInfo[i].fVelocity,	m_pMoveInfo[i].nAllDistance, 
			 		   m_pMoveInfo[i].dwDelayTime,  m_pMoveInfo[i].nDestX,
					   m_pMoveInfo[i].nDestY);
	}
	fclose(fp);
	return TRUE;
}

void CPattern::Release()
{
	if(m_nMoveCount > 0 )
		delete [] m_pMoveInfo;

	m_pMoveInfo = NULL;
}

MOVE_INFO CPattern::GetMoveInfo(int nIndex)
{
	return m_pMoveInfo[nIndex];
}

POINT CPattern::GetInitXY()
{
	POINT xy = { m_nX0, m_nY0 };
	return xy;
}

void CPattern::SetInitXY(POINT xy)
{
	m_nX0 = xy.x;
	m_nY0 = xy.y;
}
	
int  CPattern::GetMoveCount()
{
	return m_nMoveCount;
}

// Note: 이동 정보 개수가 셋팅되면 전체를 다시 생성해야 한다.
void CPattern::CreateMoveInfo(int nMoveCount)
{
	if(m_pMoveInfo != NULL)
		delete [] m_pMoveInfo;
				
	m_nMoveCount = nMoveCount;
	m_pMoveInfo = new MOVE_INFO[m_nMoveCount];
}

void CPattern::SetMoveInfo(int nIndex, MOVE_INFO sMoveInfo)
{
	m_pMoveInfo[nIndex] = sMoveInfo;
}


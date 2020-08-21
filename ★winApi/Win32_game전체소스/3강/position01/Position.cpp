#include "StdAfx.h"
#include "Position.h"
#include <stdio.h>

CPosition::CPosition(void)
{
	m_pPosInfo = NULL;
}

CPosition::~CPosition(void)
{
	ReleasePosInfo();
}

void CPosition::ReleasePosInfo()
{
	if( m_pPosInfo != NULL )
	{
		delete [] m_pPosInfo;		
		m_pPosInfo = NULL;
	}
}

BOOL CPosition::LoadPosInfo(char *strFileName) 
{
	FILE *fp;

	if(m_sCutInfo.pCutRect == NULL )
		return FALSE; // cut 파일이 로딩이 않된 것이다.	

	ReleasePosInfo();
	fp = fopen( strFileName, "rt" );
	m_pPosInfo = new POS_INFO[m_sCutInfo.nCount];
								
	for(int i = 0 ; i < m_sCutInfo.nCount ; i++ )
	{
		fscanf( fp, "중심좌표: %d %d\n", &m_pPosInfo[i].ptCenter.x, &m_pPosInfo[i].ptCenter.y );
		fscanf( fp, "충돌개수: %d\n", &m_pPosInfo[i].nCollisionCount );

		if( m_pPosInfo[i].nCollisionCount > 0 )
		{
			m_pPosInfo[i].pCollisionRect = new RECT[m_pPosInfo[i].nCollisionCount];
			for(int j = 0 ; j < m_pPosInfo[i].nCollisionCount ; j++ )
			{
				fscanf( fp, "충돌좌표: %d %d %d %d\n", &m_pPosInfo[i].pCollisionRect[j].left, &m_pPosInfo[i].pCollisionRect[j].top,
											&m_pPosInfo[i].pCollisionRect[j].right, &m_pPosInfo[i].pCollisionRect[j].bottom );
			}
		}
	}

	fclose( fp );

	return TRUE;
}

BOOL CPosition::SavePosInfo(char *strFileName)
{
	FILE *fp = fopen( strFileName, "wt" );
								
	for(int i = 0 ; i < m_sCutInfo.nCount ; i++ )
	{
		fprintf( fp, "중심좌표: %d %d\n", m_pPosInfo[i].ptCenter.x, m_pPosInfo[i].ptCenter.y );
		fprintf( fp, "충돌개수: %d\n", m_pPosInfo[i].nCollisionCount );

		if( m_pPosInfo[i].nCollisionCount > 0 )
		{			
			for(int j = 0 ; j < m_pPosInfo[i].nCollisionCount ; j++ )
			{
				fprintf( fp, "충돌좌표: %d %d %d %d\n", m_pPosInfo[i].pCollisionRect[j].left, m_pPosInfo[i].pCollisionRect[j].top,
											m_pPosInfo[i].pCollisionRect[j].right, m_pPosInfo[i].pCollisionRect[j].bottom );
			}
		}
	}

	fclose( fp );

	return TRUE;
}
	
BOOL CPosition::CreateCollisionRect(int nSprIndex, int nCount)
{
	if(m_pPosInfo[nSprIndex].pCollisionRect != NULL )
		delete [] m_pPosInfo[nSprIndex].pCollisionRect;

	m_pPosInfo[nSprIndex].pCollisionRect = new RECT[nCount];
	m_pPosInfo[nSprIndex].nCollisionCount = nCount;
	return TRUE;
}

void CPosition::SetCollisionRect(int nSprIndex, int nIndex, RECT rect)
{
	m_pPosInfo[nSprIndex].pCollisionRect[nIndex] = rect;
}

BOOL CPosition::CreatePosInfo()
{
	m_pPosInfo = new POS_INFO[m_sCutInfo.nCount];	
	return TRUE;
}
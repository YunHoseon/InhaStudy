#include "StdAfx.h"
#include <stdio.h>
#include "StageInfo.h"

CStageInfo::CStageInfo(void)
{
	Init();
}


CStageInfo::~CStageInfo(void)
{
}

void CStageInfo::Init()
{
	m_nLimitedTime = 0;
	m_nGoalCount = 0;
	ZeroMemory( m_strEnemyTeamName, sizeof(m_strEnemyTeamName));
	ZeroMemory( m_strBackgroundSoundName, sizeof(m_strBackgroundSoundName));
}

BOOL CStageInfo::Load(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "rt");

	Init(); //  초기화 
	fscanf(fp, "제한시간: %d\n", &m_nLimitedTime);
	fscanf(fp, "목표골인수: %d\n", &m_nGoalCount);
	fscanf(fp, "상대방 선수팀: %s\n", m_strEnemyTeamName);
	fscanf(fp, "배경 사운드: %s\n", m_strBackgroundSoundName);
	return TRUE;
}

BOOL CStageInfo::Save(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "wt");
	fprintf(fp, "제한시간: %d\n", m_nLimitedTime);
	fprintf(fp, "목표골인수: %d\n", m_nGoalCount);
	fprintf(fp, "상대방 선수팀: %s\n", m_strEnemyTeamName);
	fprintf(fp, "배경 사운드: %s\n", m_strBackgroundSoundName);
	fclose(fp);
	return TRUE;
}
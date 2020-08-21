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

	Init(); //  �ʱ�ȭ 
	fscanf(fp, "���ѽð�: %d\n", &m_nLimitedTime);
	fscanf(fp, "��ǥ���μ�: %d\n", &m_nGoalCount);
	fscanf(fp, "���� ������: %s\n", m_strEnemyTeamName);
	fscanf(fp, "��� ����: %s\n", m_strBackgroundSoundName);
	return TRUE;
}

BOOL CStageInfo::Save(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "wt");
	fprintf(fp, "���ѽð�: %d\n", m_nLimitedTime);
	fprintf(fp, "��ǥ���μ�: %d\n", m_nGoalCount);
	fprintf(fp, "���� ������: %s\n", m_strEnemyTeamName);
	fprintf(fp, "��� ����: %s\n", m_strBackgroundSoundName);
	fclose(fp);
	return TRUE;
}
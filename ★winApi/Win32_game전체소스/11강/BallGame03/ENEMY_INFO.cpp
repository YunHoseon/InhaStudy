#include "StdAfx.h"
#include "ENEMY_INFO.h"
#include <stdio.h>

ENEMY_INFO::ENEMY_INFO(void)
{
	strPatFileName = NULL;
	pEnemyIndex = NULL;
}

ENEMY_INFO::~ENEMY_INFO(void)
{
	if(strPatFileName != NULL)
			delete [] strPatFileName;
	if(pEnemyIndex != NULL)
		delete [] pEnemyIndex;
}

void ENEMY_INFO::Load(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "rt");
	fscanf(fp, "%d\n", &nPatCount);
	
	if(strPatFileName != NULL)
		delete [] strPatFileName;
	strPatFileName = new char[nPatCount][70];
	for(int i = 0 ; i < nPatCount ; i++)
		fscanf(fp, "%s\n", strPatFileName[i]);
	fscanf(fp, "%d\n", &nEnemyCount);
	if(pEnemyIndex != NULL)
		delete [] pEnemyIndex;
	pEnemyIndex = new ENEMY_INDEX[nEnemyCount];
	for(int i  = 0; i < nEnemyCount ; i++)
		fscanf(fp, "%d %d\n", &pEnemyIndex[i].nSprIndex, &pEnemyIndex[i].nPatIndex);
	fclose(fp);
}

void ENEMY_INFO::Save(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "wt");
	fprintf(fp, "%d\n", nPatCount);	 // ���� ����
	for(int i = 0 ; i < nPatCount ; i++)
		fprintf(fp, "%s\n", strPatFileName[i]);
	fprintf(fp, "%d\n", nEnemyCount); // �� ĳ���� ����	
	for(int i  = 0; i < nEnemyCount ; i++)
		fprintf(fp, "%d %d\n", pEnemyIndex[i].nSprIndex, pEnemyIndex[i].nPatIndex);
	fclose(fp);
}
#pragma once
#include <stdio.h>

struct ENEMY_INDEX {
		int nSprIndex;
		int nPatIndex;
};

struct ENEMY_INFO
{
	// ���� ����
	int nPatCount;
	char (*strPatFileName)[70]; 	

	// ���� ���� ��������Ʈ ����
	int nEnemyCount;
	ENEMY_INDEX *pEnemyIndex;

	void Load(char *filename);
	void Save(char *filename);

	ENEMY_INFO(){
		strPatFileName = NULL;
		pEnemyIndex = NULL;
	}

	~ENEMY_INFO(){
		if(strPatFileName != NULL)
			delete [] strPatFileName;
		if(pEnemyIndex != NULL)
			delete [] pEnemyIndex;
	}
	
	void Load(char *filename)
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

	void Save(char *filename)
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
};


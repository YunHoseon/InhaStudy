#pragma once

struct ENEMY_INDEX {
		int nSprIndex;
		int nPatIndex;
};

class ENEMY_INFO
{
public:
	// ���� ����
	int nPatCount;
	char (*strPatFileName)[70]; 	

	// ���� ���� ��������Ʈ ����
	int nEnemyCount;
	ENEMY_INDEX *pEnemyIndex;

	void Load(char *filename);
	void Save(char *filename);
public:
	ENEMY_INFO(void);
	~ENEMY_INFO(void);
};


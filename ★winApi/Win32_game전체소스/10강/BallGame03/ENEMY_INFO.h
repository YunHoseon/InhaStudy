#pragma once

struct ENEMY_INDEX {
		int nSprIndex;
		int nPatIndex;
};

class ENEMY_INFO
{
public:
	// 패턴 정보
	int nPatCount;
	char (*strPatFileName)[70]; 	

	// 상대방 선수 스프라이트 정보
	int nEnemyCount;
	ENEMY_INDEX *pEnemyIndex;

	void Load(char *filename);
	void Save(char *filename);
public:
	ENEMY_INFO(void);
	~ENEMY_INFO(void);
};


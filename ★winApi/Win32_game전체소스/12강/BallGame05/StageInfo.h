#pragma once

class CStageInfo
{
public: // ��� �����Ͱ� �����Ƿ� �Ӽ��� publlic���� �ؼ� �ٷ� ����� �� �ֵ��� ��
	unsigned int m_nLimitedTime; //���ѽð�, �и�������
	int m_nGoalCount;    // �� ����
	char m_strEnemyTeamName[100]; // ���� ������ ��
	char m_strBackgroundSoundName[100];

public:
	void Init();
	BOOL Load(char *filename);
	BOOL Save(char *filename);	
public:
	CStageInfo(void);
	~CStageInfo(void);
};


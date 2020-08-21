#pragma once

class CStageInfo
{
public: // 계산 데이터가 없으므로 속성을 publlic으로 해서 바로 사용할 수 있도록 함
	unsigned int m_nLimitedTime; //제한시간, 밀리세컨드
	int m_nGoalCount;    // 공 개수
	char m_strEnemyTeamName[100]; // 상대방 선수팀 명
	char m_strBackgroundSoundName[100];

public:
	void Init();
	BOOL Load(char *filename);
	BOOL Save(char *filename);	
public:
	CStageInfo(void);
	~CStageInfo(void);
};


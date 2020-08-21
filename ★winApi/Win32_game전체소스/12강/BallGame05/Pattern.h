#pragma once
enum DIRECTION { TOP, RIGHT_TOP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_TOP, STOP };

struct MOVE_INFO
{
	DIRECTION nDirection; // 방향
	float fVelocity; //이동 속도
	int nAllDistance; // 이동 전체 거리
	DWORD dwDelayTime; // STOP 대기시간
	int nDestX, nDestY; // 최종 좌표
};

class CPattern
{
private:
	int m_nMoveCount; // 이동 속성 개수
	int m_nX0, m_nY0; // 초기 위치	
	MOVE_INFO *m_pMoveInfo; // 이동 개수
public:
	BOOL Load(char *filename);
	BOOL Save(char *filename);
	void Release();
	MOVE_INFO GetMoveInfo(int nIndex);
	POINT GetInitXY();
	int  GetMoveCount();
	void CreateMoveInfo(int nMoveCount);
	void SetMoveInfo(int nIndex, MOVE_INFO sMoveInfo);
	void SetInitXY(POINT xy);
public:
	CPattern(void);
	~CPattern(void);
};


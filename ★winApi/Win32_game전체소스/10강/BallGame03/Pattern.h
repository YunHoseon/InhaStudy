#pragma once
enum DIRECTION { TOP, RIGHT_TOP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, LEFT_TOP, STOP };

struct MOVE_INFO
{
	DIRECTION nDirection; // ����
	float fVelocity; //�̵� �ӵ�
	int nAllDistance; // �̵� ��ü �Ÿ�
	DWORD dwDelayTime; // STOP ���ð�
	int nDestX, nDestY; // ���� ��ǥ
};

class CPattern
{
private:
	int m_nMoveCount; // �̵� �Ӽ� ����
	int m_nX0, m_nY0; // �ʱ� ��ġ	
	MOVE_INFO *m_pMoveInfo; // �̵� ����
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


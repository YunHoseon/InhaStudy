#pragma once
#include "Sprite.h"
#include "Pattern.h"

enum MOVE_MOTION { M_TOP, M_RIGHT, M_DOWN, M_LEFT, M_STOP }; // ������ 8���������� �̹����� 4������ ���ϸ��̼��� �ϹǷ� 

// ���� ������ ���� Ŭ�����̴�.
class CEnemy
{	
private:
	CSprite *m_pSprite;	// �ܺ��� ��������Ʈ �׷��� Ư�� ��������Ʈ�� ����
	int m_nAniSprIndex; // �ִϸ��̼��� ��������Ʈ�� �ε���	
	int m_nAniRangeIndex; // ���ϸ��̼� ���� �ε���
	RANGE m_AniRange;     // ���ϸ��̼� ���� �ε����� �� �ε���
	DWORD m_dwOldAniTime; // ��������Ʈ�� ���ϸ��̼� ����ð��� �����ϱ� ���ؼ�

	CPattern *m_pPattern; // m_nPatIndex�� ���� �׷쿡�� �������� ���� ������ 
	MOVE_INFO m_sMoveInfo;	// �̵���ο� ���� ����	
	int m_nMovePathIndex;  // ���� �̵���� �ε��� 

	float m_fX, m_fY;
	DWORD m_dwStopElapsedTime; // ���̵��� �� �����ð��� �����ϴ� ����
	float m_fAddDistance;  // �̵��� �Ÿ��� �����ϴ� ����
	MOVE_MOTION GetAniDirectionIndex(DIRECTION nDirection); // 8���⿡ ���� ���ϸ��̼��� �����¿�� �����ϴ� �Լ�
public:
	void Init(CSprite *pSprite, CPattern *pPattern); // ��������Ʈ�� ������ ������ �����ϴ� �Լ�
	void Update(DWORD dwCurTime, DWORD dwElapsedTime); // dwElapsedtime�� �� �����Ӵ� ����ð��̴�.
	void Render(HDC hBackBuffer);	
public:
	CEnemy(void);
	~CEnemy(void);	
};


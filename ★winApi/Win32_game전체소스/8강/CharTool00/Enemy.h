#pragma once
#include "Sprite.h"
#include "Pattern.h"

enum MOVE_MOTION { M_TOP, M_RIGHT, M_DOWN, M_LEFT, M_STOP }; // 방향은 8방향이지만 이미지가 4방향의 에니메이션을 하므로 

// 상대방 선수에 대한 클래스이다.
class CEnemy
{	
private:
	CSprite *m_pSprite;	// 외부의 스프라이트 그룹의 특정 스프라이트를 참조
	int m_nAniSprIndex; // 애니메이션할 스프라이트의 인덱스	
	int m_nAniRangeIndex; // 에니메이션 범위 인덱스
	RANGE m_AniRange;     // 에니메이션 시작 인덱스와 끝 인덱스
	DWORD m_dwOldAniTime; // 스프라이트의 에니메이션 경과시간을 측정하기 위해서

	CPattern *m_pPattern; // m_nPatIndex로 패턴 그룹에서 가져오는 패턴 포인터 
	MOVE_INFO m_sMoveInfo;	// 이동경로에 대한 정보	
	int m_nMovePathIndex;  // 현재 이동경로 인덱스 

	float m_fX, m_fY;
	DWORD m_dwStopElapsedTime; // 아이들일 때 정지시간을 누적하는 변수
	float m_fAddDistance;  // 이동한 거리를 누적하는 변수
	MOVE_MOTION GetAniDirectionIndex(DIRECTION nDirection); // 8방향에 대한 에니메이션인 상하좌우로 변경하는 함수
public:
	void Init(CSprite *pSprite, CPattern *pPattern); // 스프라이트와 패턴의 정보를 설정하는 함수
	void Update(DWORD dwCurTime, DWORD dwElapsedTime); // dwElapsedtime은 한 프레임당 경과시간이다.
	void Render(HDC hBackBuffer);	
public:
	CEnemy(void);
	~CEnemy(void);	
};


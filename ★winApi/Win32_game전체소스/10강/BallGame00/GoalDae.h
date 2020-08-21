#pragma once
#include "Sprite.h"
#include "Pattern.h"

class CGoalDae  
{
private:
	RECT m_rtGoalDae; // °ñ´ëÀÇ ½ÇÁ¦ Ãâ·Â ÁÂÇ¥
	CSprite *m_pSprite;
	CPattern *m_pPattern;
	float m_fX, m_fY;

public:
	void Init(CSprite *pSprite, CPattern *pPattern);
	void Update(DWORD dwCurTime, DWORD dwElapsedTime);
	void Render(HDC hBackBuffer);	
	RECT GetRect();
	RECT GetCollisionRect();

public:
	CGoalDae(void);
	~CGoalDae(void);
};


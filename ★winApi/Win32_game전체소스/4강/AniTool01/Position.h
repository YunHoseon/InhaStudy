#pragma once
#include <Windows.h>
#include "CutImage.h"

struct POS_INFO
{
	POINT ptCenter;
	int nCollisionCount;
	RECT *pCollisionRect;

	POS_INFO() { ptCenter.x = 0;
				 ptCenter.y = 0;
				 nCollisionCount = 0;
				 pCollisionRect = NULL;
	}

	~POS_INFO() {
		delete [] pCollisionRect;
	}
};

class CPosition : public CCutImage
{
private:	
	POS_INFO *m_pPosInfo;  // 스프라이트마다 이 부분이 있어야 한다.	

protected:
	void ReleasePosInfo();

public:	
	BOOL LoadPosInfo(char *strFileName); 
	BOOL SavePosInfo(char *strFileName);
	void SetCenterPos(int nSprIndex, POINT ptCenter) 
					   { m_pPosInfo[nSprIndex].ptCenter = ptCenter; }		
	int GetSpriteCount() { return m_sCutInfo.nCount; }
	char *GetSpriteFileName() { return m_sCutInfo.strBmpFileName; }
	POINT GetSpriteCenterPos(int nIndex) { return m_pPosInfo[nIndex].ptCenter; }
	int GetCollisionCount(int nIndex) { return m_pPosInfo[nIndex].nCollisionCount; }
	RECT GetCollisionRect(int nSprIndex, int nCollisionIndex) 
	                   { return m_pPosInfo[nSprIndex].pCollisionRect[nCollisionIndex]; }	
	BOOL CreateCollisionRect(int nSprIndex, int nCount);
	void SetCollisionRect(int nSprIndex, int nIndex, RECT rect);
	BOOL CreatePosInfo();
	POS_INFO *GetPosInfo() { return m_pPosInfo; }

public:
	CPosition(void);
	~CPosition(void);
};


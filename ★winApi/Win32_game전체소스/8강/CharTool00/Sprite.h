#pragma once
#include <vector>
using namespace std;


struct RANGE
{
	int nIndex0;
	int nIndex1;
};

struct SPRITE // Note: 하나인 것과 다수인 것 구분
{
	RECT rtCutRect;
	POINT ptCenterXY;
	DWORD dwAniTime;

	int nCollisionCount;
	RECT *pCollisionRect;	

	SPRITE()
	{
		pCollisionRect = NULL;		
		nCollisionCount = 0;		
	}

	~SPRITE()
	{ // 널 포인터는 delete를 해도 영향을 주지 않으므로 NULL 별도로 체크할 필요없다. ^^
		delete [] pCollisionRect;		
	}
};

class CSprite
{
private:	
	// Note: 하나인 것과 종속적인 것을 구분하면 된다.
	char m_strBmpFileName[50]; // 이미지 파일명
	DWORD m_dwTransparentColor; // 투명 컬러값
	int  m_nSprCount; // 자른 좌표 계수
	vector<SPRITE *> m_SpriteList; // 나중에 SPRITE *m_pSpriteList로 해주면 된다. (게임에서는)
	int m_nAniRangeCount; // 에니메이션 범위 개수
	RANGE *m_pAniRange;		

private:
	SIZE m_szBitmapSize; // 로딩된 이미지 싸이즈

	int ScanLeft(int x1, int y1, int x2, int y2 );
	int ScanTop(int x1, int y1, int x2, int y2 );
	int ScanRight(int x1, int y1, int x2, int y2 );
	int ScanBottom(int x1, int y1, int x2, int y2 );
public:
	HDC m_hSrcImageDC; // <-- 이게 가장 중요하다.

public:
	CSprite(void);
	~CSprite(void);

	void Load(HWND hWnd, char *pFileName);
	void Save(char *pFileName);
	void Release(); // 스프라이트에 대한 모든 사항 해제 함수
	void Init();    // 스프라이트에 대한 초기화 함수

	//------------------ 자르기에 관한 멤버 함수 ---------------------------------
	void LoadBmpImage(HWND hWnd, char *pFilePath, char *pFileName);
	void LoadBmpImage(HWND hWnd); // 파일명을 저장하고 있는 경우 사용
	RECT ScanBoxRect(RECT rtDrag);	
	void AddCutRect( RECT rect);
	void DeleteCutRect(int nIndex);
	void InsertCutRect(int nIndex, RECT rect);

	SIZE GetImageSize() { return m_szBitmapSize; }		
	DWORD GetTransColor(int nX, int nY);
	DWORD GetTransColor() { return m_dwTransparentColor; }
	int GetTransRed();
	int GetTransGreen();
	int GetTransBlue();
	int GetSprCount() { return m_nSprCount; }
	HDC GetSrcImageDC() { return m_hSrcImageDC; }	
	char *GetBmpFileName() { return m_strBmpFileName; }	
	RECT GetSprRect(int nSprIndex);
	int  GetSprWidth(int nSprIndex);
	int  GetSprHeight(int nSprIndex);
	SPRITE* GetSprite(int nSprIndex);
	
	void SetTransparentColor(DWORD dwColor) { m_dwTransparentColor = dwColor; }
	void SetSprCount(int nCount) { nCount = nCount; } 
	void SetSprRect(int nSprIndex, RECT rect);	
	void CreateCutRect();
	
	//---------------- 좌표 설정에 대한 멤버 함수 ------------------------------------			
	POINT GetCenterPos(int nSprIndex);
	int GetCollisionCount(int nIndex);
	RECT GetCollisionRect(int nSprIndex, int nCollisionIndex);	                 
	BOOL CreateCollisionRect(int nSprIndex, int nCount);
	void SetCollisionRect(int nSprIndex, int nIndex, RECT rect);
	void SetCenterPos(int nSprIndex, POINT ptCenter);

	//---------------- 에니메이션 멤버 함수 ------------------------------------------
	DWORD GetAniTime(int nSprIndex);
	RANGE GetAniRange(int nIndex);
	int GetAniRangeCount();
	void CreateAniRange(int nCount);
	void SetAniRange(int nIndex, int nIndex0, int nIndex1);	
	void SetAniTime(int nSprIndex, DWORD dwAniTime);
};


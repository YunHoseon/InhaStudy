#pragma once
#include <vector>
using namespace std;


struct RANGE
{
	int nIndex0;
	int nIndex1;
};

struct SPRITE // Note: �ϳ��� �Ͱ� �ټ��� �� ����
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
	{ // �� �����ʹ� delete�� �ص� ������ ���� �����Ƿ� NULL ������ üũ�� �ʿ����. ^^
		delete [] pCollisionRect;		
	}
};

class CSprite
{
private:	
	// Note: �ϳ��� �Ͱ� �������� ���� �����ϸ� �ȴ�.
	char m_strBmpFileName[50]; // �̹��� ���ϸ�
	DWORD m_dwTransparentColor; // ���� �÷���
	int  m_nSprCount; // �ڸ� ��ǥ ���
	vector<SPRITE *> m_SpriteList; // ���߿� SPRITE *m_pSpriteList�� ���ָ� �ȴ�. (���ӿ�����)
	int m_nAniRangeCount; // ���ϸ��̼� ���� ����
	RANGE *m_pAniRange;		

private:
	SIZE m_szBitmapSize; // �ε��� �̹��� ������

	int ScanLeft(int x1, int y1, int x2, int y2 );
	int ScanTop(int x1, int y1, int x2, int y2 );
	int ScanRight(int x1, int y1, int x2, int y2 );
	int ScanBottom(int x1, int y1, int x2, int y2 );
public:
	HDC m_hSrcImageDC; // <-- �̰� ���� �߿��ϴ�.

public:
	CSprite(void);
	~CSprite(void);

	void Load(HWND hWnd, char *pFileName);
	void Save(char *pFileName);
	void Release(); // ��������Ʈ�� ���� ��� ���� ���� �Լ�
	void Init();    // ��������Ʈ�� ���� �ʱ�ȭ �Լ�

	//------------------ �ڸ��⿡ ���� ��� �Լ� ---------------------------------
	void LoadBmpImage(HWND hWnd, char *pFilePath, char *pFileName);
	void LoadBmpImage(HWND hWnd); // ���ϸ��� �����ϰ� �ִ� ��� ���
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
	
	//---------------- ��ǥ ������ ���� ��� �Լ� ------------------------------------			
	POINT GetCenterPos(int nSprIndex);
	int GetCollisionCount(int nIndex);
	RECT GetCollisionRect(int nSprIndex, int nCollisionIndex);	                 
	BOOL CreateCollisionRect(int nSprIndex, int nCount);
	void SetCollisionRect(int nSprIndex, int nIndex, RECT rect);
	void SetCenterPos(int nSprIndex, POINT ptCenter);

	//---------------- ���ϸ��̼� ��� �Լ� ------------------------------------------
	DWORD GetAniTime(int nSprIndex);
	RANGE GetAniRange(int nIndex);
	int GetAniRangeCount();
	void CreateAniRange(int nCount);
	void SetAniRange(int nIndex, int nIndex0, int nIndex1);	
	void SetAniTime(int nSprIndex, DWORD dwAniTime);
};


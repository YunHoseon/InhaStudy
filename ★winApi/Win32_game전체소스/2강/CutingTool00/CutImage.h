#pragma once

struct CUT_INFO
{
	char strBmpFileName[50]; // 이미지 파일명
	DWORD dwTransparentColor; // 투명 컬러값
	int  nCount; // 자른 좌표 계수
	RECT *pCutRect;
};

class CCutImage
{
protected:
	HDC m_hSrcImageDC; 	
	CUT_INFO m_sCutInfo;
	BITMAP m_sBitmap;

private:
	int ScanLeft(int x1, int y1, int x2, int y2 );
	int ScanTop(int x1, int y1, int x2, int y2 );
	int ScanRight(int x1, int y1, int x2, int y2 );
	int ScanBottom(int x1, int y1, int x2, int y2 );	

public:
	CCutImage(void);
	~CCutImage(void);	

	void LoadBmpImage(HWND hWnd, char *filename);	
	BOOL LoadCutInfo(HWND hWnd, char *strFileName);
	RECT ScanBoxRect(RECT rtDrag);	
	void CreateCutRect();
	BOOL SaveCutInfo(char *strFileName);
	
	SIZE GetImageSize();		
	DWORD GetTransColor(int nX, int nY);
	DWORD GetTransColor() { return m_sCutInfo.dwTransparentColor; }
	int GetTransRed();
	int GetTransGreen();
	int GetTransBlue();
	int GetSprCount() { return m_sCutInfo.nCount; }
	HDC GetSrcImageDC() { return m_hSrcImageDC; }	
	char *GetBmpFileName() { return m_sCutInfo.strBmpFileName; }	
	RECT GetSprRect(int nIndex) { return m_sCutInfo.pCutRect[nIndex]; }
	int  GetSprWidth(int nIndex) { return m_sCutInfo.pCutRect[nIndex].right - m_sCutInfo.pCutRect[nIndex].left + 1; }
	int  GetSprHeight(int nIndex) { return m_sCutInfo.pCutRect[nIndex].bottom - m_sCutInfo.pCutRect[nIndex].top + 1; }

	void SetBmpFileName(char* strFileName);
	void SetTransparentColor(DWORD dwColor) { m_sCutInfo.dwTransparentColor = dwColor; }
	void SetSprCount(int nCount) { m_sCutInfo.nCount = nCount; } 	
	void SetSprRect(int nIndex, RECT rect);	
};


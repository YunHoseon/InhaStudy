#include "StdAfx.h"
#include "Sprite.h"
#include <stdio.h>


CSprite::CSprite(void)
{
	Init();
}

CSprite::~CSprite(void)
{
	Release();
}

void CSprite::Init()
{
	memset(m_strBmpFileName, 0, sizeof(m_strBmpFileName)); 
	m_dwTransparentColor = 0;
	m_nSprCount = m_nAniRangeCount = 0;
	m_nAniRangeCount = 0;
	m_hSrcImageDC = NULL;	
	m_pAniRange = NULL;
}

void CSprite::Release()
{
	int nCount;	
	
	nCount = m_SpriteList.size();
	for(int i = 0 ; i < nCount ; i++)
		delete m_SpriteList[i];
	m_SpriteList.clear();
	m_nAniRangeCount = 0;	
	delete [] m_pAniRange;
	m_pAniRange = NULL;

	DeleteDC(m_hSrcImageDC);
	m_hSrcImageDC = NULL;
}

// Note: 이미지 로딩 함수
void CSprite::LoadBmpImage(HWND hWnd, char *pFilePath, char *pFileName)
{
	HBITMAP hBitmap;
	BITMAP sBitmap;	
	
	HDC hdc = GetDC( hWnd );	

	if( m_hSrcImageDC != NULL )
		DeleteDC( m_hSrcImageDC );
								
	m_hSrcImageDC = CreateCompatibleDC( hdc );	
	hBitmap = (HBITMAP)LoadImage( NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	
	// Note: HBITMAP로 부터 비트맵 정보를 읽어 낸다. 
	GetObject( (HBITMAP)hBitmap, sizeof(BITMAP), &sBitmap );	
	SelectObject( m_hSrcImageDC, hBitmap );
	DeleteObject( hBitmap );	
	ReleaseDC( hWnd, hdc );

	m_szBitmapSize.cx = sBitmap.bmWidth;
	m_szBitmapSize.cy = sBitmap.bmHeight;
	memcpy(m_strBmpFileName, pFileName, strlen(pFileName));
}

void CSprite::LoadBmpImage(HWND hWnd)
{
	HBITMAP hBitmap;
	BITMAP sBitmap;	

	HDC hdc = GetDC( hWnd );

	if( m_hSrcImageDC != NULL )
		DeleteDC( m_hSrcImageDC );
								
	m_hSrcImageDC = CreateCompatibleDC( hdc );	
	hBitmap = (HBITMAP)LoadImage( NULL, m_strBmpFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	
	// Note: HBITMAP로 부터 비트맵 정보를 읽어 낸다. 
	GetObject( (HBITMAP)hBitmap, sizeof(BITMAP), &sBitmap );	
	SelectObject( m_hSrcImageDC, hBitmap );
	DeleteObject( hBitmap );	
	ReleaseDC( hWnd, hdc );

	m_szBitmapSize.cx = sBitmap.bmWidth;
	m_szBitmapSize.cy = sBitmap.bmHeight;	
}

DWORD CSprite::GetTransColor(int nX, int nY)
{
	m_dwTransparentColor = GetPixel(m_hSrcImageDC, nX, nY);
	return m_dwTransparentColor;
}

int CSprite::GetTransRed()
{
	return GetRValue(m_dwTransparentColor);
}

int CSprite::GetTransBlue()
{
	return GetBValue(m_dwTransparentColor);
}

int CSprite::GetTransGreen()
{
	return GetGValue(m_dwTransparentColor);
}

void CSprite::SetSprRect(int nSprIndex, RECT rect)
{
	m_SpriteList[nSprIndex]->rtCutRect = rect;
}


RECT CSprite::GetSprRect(int nSprIndex) 
{ 
	return m_SpriteList[nSprIndex]->rtCutRect; 
}

int CSprite::GetSprWidth(int nSprIndex) 
{ 
	return m_SpriteList[nSprIndex]->rtCutRect.right - m_SpriteList[nSprIndex]->rtCutRect.left + 1; 
}

int CSprite::GetSprHeight(int nSprIndex) 
{ 
	return m_SpriteList[nSprIndex]->rtCutRect.bottom - m_SpriteList[nSprIndex]->rtCutRect.top + 1; 
}

SPRITE* CSprite::GetSprite(int nSprIndex) 
{ 
	return m_SpriteList[nSprIndex]; 
}

// 스프라이트를 추가하는 부분 : 등록버튼 클릭시
void CSprite::AddCutRect(RECT rect)
{	
	SPRITE *pSprite = new SPRITE;
	ZeroMemory(pSprite, sizeof(SPRITE));
	pSprite->rtCutRect = rect;
	m_SpriteList.push_back(pSprite);
	m_nSprCount = m_SpriteList.size(); // <-- 중간에 바뀔 수 있다. 조금 위험성이 있다.
}

void CSprite::DeleteCutRect(int nIndex)
{
	SPRITE *pSprite = m_SpriteList[nIndex];	
	delete pSprite;	
	
	m_SpriteList.erase(m_SpriteList.begin() + nIndex);
	m_nSprCount = m_SpriteList.size();
}

void CSprite::InsertCutRect(int nIndex, RECT rect)
{
	SPRITE *pSprite = new SPRITE;
	pSprite->rtCutRect = rect;
	m_SpriteList.insert(m_SpriteList.begin() + nIndex, pSprite);
	m_nSprCount = m_SpriteList.size();
}

RECT CSprite::ScanBoxRect(RECT rtDrag)
{	
	RECT rect;
	rect.left = ScanLeft( rtDrag.left, rtDrag.top, rtDrag.right, rtDrag.bottom );
	rect.top = ScanTop( rtDrag.left, rtDrag.top, rtDrag.right, rtDrag.bottom );
	rect.right = ScanRight( rect.left, rect.top, rtDrag.right, rtDrag.bottom );
	rect.bottom = ScanBottom( rect.left, rect.top, rect.right, rtDrag.bottom );		
	return rect;
}

int CSprite::ScanLeft( int x1, int y1, int x2, int y2 )
{
	COLORREF Color, OldColor;
	
	OldColor = GetPixel( m_hSrcImageDC, x1, y1 );
	for( int i = x1 ; i <= x2 ; i++ )
	{		
		for( int j = y1 ; j <= y2 ; j++ )
		{
			Color = GetPixel( m_hSrcImageDC, i, j );
			if( Color != OldColor )
				return i;
		}
	}
	return -1;
}

int CSprite::ScanTop( int x1, int y1, int x2, int y2 )
{
	COLORREF Color, OldColor;

	OldColor = GetPixel( m_hSrcImageDC, x1, y1 );
	for( int i = y1 ; i <= y2 ; i++ )
	{		
		for( int j = x1 ; j <= x2 ; j++ )
		{
			Color = GetPixel( m_hSrcImageDC, j, i );
			if( Color != OldColor )
				return i;
		}
	}

	return -1;
}

int CSprite::ScanRight( int x1, int y1, int x2, int y2 )
{
	COLORREF Color, OldColor;

	OldColor = GetPixel( m_hSrcImageDC, x2, y1 );
	for( int i = x2 ; i >= x1 ; i-- )
	{	
		for( int j = y1 ; j <= y2 ; j++ )
		{
			Color = GetPixel( m_hSrcImageDC, i, j );
			if( Color != OldColor )
				return i;
		}
	}
	
	return -1;
}

int CSprite::ScanBottom( int x1, int y1, int x2, int y2 )
{
	COLORREF Color, OldColor;

	OldColor = GetPixel( m_hSrcImageDC, x1, y2 );
	for( int i = y2 ; i >= y1 ; i-- )
	{		
		for( int j = x1 ; j <= x2 ; j++ )
		{
			Color = GetPixel( m_hSrcImageDC, j, i );
			if( Color != OldColor )
				return i;
		}
	}

	return -1;
}

void CSprite::Load(HWND hWnd, char *pFileName)
{	
	RECT rect;
	POINT ptPoint;
	int nCount;

	// Note: 기존의 모든 데이터 제거
	Release();
	Init();

	FILE *fp = fopen(pFileName, "rt");
	fscanf(fp, "이미지 파일명:%s\n", m_strBmpFileName); // 이미지 파일명
	fscanf(fp, "투명색상:%d\n", &m_dwTransparentColor); // 투명색상 값
	fscanf(fp, "스프라이트 개수:%d\n", &m_nSprCount); // 스프라이트 전체 개수
	nCount = m_nSprCount;
	for(int i = 0 ; i < nCount ; i++)
	{				
		fscanf(fp, "스프라이트 좌표:%d %d %d %d\n", &rect.left, &rect.top, &rect.right, &rect.bottom);
		AddCutRect(rect);	
		fscanf(fp, "중심좌표:%d %d\n", &ptPoint.x, &ptPoint.y);
		SetCenterPos(i, ptPoint);
		fscanf(fp, "충돌개수:%d\n", &m_SpriteList[i]->nCollisionCount);
		CreateCollisionRect(i, m_SpriteList[i]->nCollisionCount); // 충돌메모리 생성

		for(int j = 0 ; j < m_SpriteList[i]->nCollisionCount ; j++)
		{			
			fscanf(fp, "%d %d %d %d\n", &rect.left, &rect.top, &rect.right, &rect.bottom);
			SetCollisionRect(i, j, rect);
		}
		fscanf(fp, "에니타임:%d\n", &m_SpriteList[i]->dwAniTime);
	}

	fscanf(fp, "에니구간 개수:%d\n", &m_nAniRangeCount);
	
	delete [] m_pAniRange;

	m_pAniRange = new RANGE[m_nAniRangeCount];	
	for(int m = 0 ; m < m_nAniRangeCount ; m++)
	{
		fscanf(fp, "%d %d\n", &m_pAniRange[m].nIndex0, 
							  &m_pAniRange[m].nIndex1);
	}	
	fclose(fp);	

	LoadBmpImage(hWnd); // 추가한 내용이다. 파일 정보를 전부 다 읽었으므로 
}

void CSprite::Save(char *pFileName)
{	
	RECT rect;

	FILE *fp = fopen(pFileName, "wt");
	fprintf(fp, "이미지 파일명:%s\n", m_strBmpFileName); // 이미지 파일명
	fprintf(fp, "투명색상:%d\n", m_dwTransparentColor); // 투명색상 값
	fprintf(fp, "스프라이트 개수:%d\n", m_nSprCount); // 스프라이트 전체 개수
	for(int i = 0 ; i < m_nSprCount ; i++)
	{		
		rect = m_SpriteList[i]->rtCutRect;
		fprintf(fp, "스프라이트 좌표:%d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
		fprintf(fp, "중심좌표:%d %d\n", m_SpriteList[i]->ptCenterXY.x, m_SpriteList[i]->ptCenterXY.y);
		fprintf(fp, "충돌개수:%d\n", m_SpriteList[i]->nCollisionCount);
		for(int j = 0 ; j < m_SpriteList[i]->nCollisionCount ; j++)
		{
			rect = m_SpriteList[i]->pCollisionRect[j];
			fprintf(fp, "%d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
		}
		fprintf(fp, "에니타임:%d\n", m_SpriteList[i]->dwAniTime);
	}

	fprintf(fp, "에니구간 개수:%d\n", m_nAniRangeCount);
	for(int m = 0 ; m < m_nAniRangeCount ; m++)
	{
		fprintf(fp, "%d %d\n", m_pAniRange[m].nIndex0, 
								m_pAniRange[m].nIndex1);
	}	
	fclose(fp);
}

//------------------ 좌표 설정에 관한 멤버 함수----------------------------
void CSprite::SetCenterPos(int nSprIndex, POINT ptCenter)
{ 
	m_SpriteList[nSprIndex]->ptCenterXY = ptCenter;
}		
	
POINT CSprite::GetCenterPos(int nSprIndex)
{ 
	return m_SpriteList[nSprIndex]->ptCenterXY; 
}

BOOL CSprite::CreateCollisionRect(int nSprIndex, int nCount)
{
	if( m_SpriteList[nSprIndex]->pCollisionRect != NULL )
		delete [] m_SpriteList[nSprIndex]->pCollisionRect;

	m_SpriteList[nSprIndex]->pCollisionRect = new RECT[nCount];
	m_SpriteList[nSprIndex]->nCollisionCount = nCount;
	return TRUE;
}

void CSprite::SetCollisionRect(int nSprIndex, int nIndex, RECT rect)
{
	m_SpriteList[nSprIndex]->pCollisionRect[nIndex] = rect;
}

int CSprite::GetCollisionCount(int nIndex) 
{
	return m_SpriteList[nIndex]->nCollisionCount; 
}

RECT CSprite::GetCollisionRect(int nSprIndex, int nCollisionIndex)
{ 
	return m_SpriteList[nSprIndex]->pCollisionRect[nCollisionIndex]; 
}	

void CSprite::CreateAniRange(int nCount)
{
	delete [] m_pAniRange;		

	m_pAniRange = new RANGE[nCount];
	m_nAniRangeCount = nCount;
}

void CSprite::SetAniRange(int nIndex, int nIndex0, int nIndex1)
{
	m_pAniRange[nIndex].nIndex0 = nIndex0;
	m_pAniRange[nIndex].nIndex1 = nIndex1;
}

RANGE CSprite::GetAniRange(int nIndex)
{	
	return m_pAniRange[nIndex];
}

int CSprite::GetAniRangeCount()
{
	return m_nAniRangeCount;
}

DWORD CSprite::GetAniTime(int nSprIndex)
{
	return m_SpriteList[nSprIndex]->dwAniTime;
}

void CSprite::SetAniTime(int nSprIndex, DWORD dwAniTime)
{
	m_SpriteList[nSprIndex]->dwAniTime = dwAniTime;
}


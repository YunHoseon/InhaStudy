#include "StdAfx.h"
#include "CutImage.h"
#include <stdio.h>

CCutImage::CCutImage(void)
{
	m_hSrcImageDC = NULL;		
	memset(&m_sCutInfo, 0, sizeof(CUT_INFO));
}

CCutImage::~CCutImage(void)
{		
	DeleteDC(m_hSrcImageDC);	
	if(m_sCutInfo.pCutRect != NULL) 
		delete [] m_sCutInfo.pCutRect;
}

void CCutImage::LoadBmpImage(HWND hWnd, char *filename)
{
	HBITMAP hBitmap;
	HDC hdc = GetDC( hWnd );

	if( m_hSrcImageDC != NULL )
		DeleteDC( m_hSrcImageDC );
								
	m_hSrcImageDC = CreateCompatibleDC( hdc );	
	hBitmap = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	
	// Note: HBITMAP로 부터 비트맵 정보를 읽어 낸다. 
	GetObject( (HBITMAP)hBitmap, sizeof(BITMAP), &m_sBitmap );	
	SelectObject( m_hSrcImageDC, hBitmap );
	DeleteObject( hBitmap );	
	ReleaseDC( hWnd, hdc );
}

SIZE CCutImage::GetImageSize()
{
	SIZE szBitmapSize;
	szBitmapSize.cx = m_sBitmap.bmWidth;
	szBitmapSize.cy = m_sBitmap.bmHeight;
	return szBitmapSize;
}

DWORD CCutImage::GetTransColor(int nX, int nY)
{
	m_sCutInfo.dwTransparentColor = GetPixel(m_hSrcImageDC, nX, nY);
	return m_sCutInfo.dwTransparentColor;
}

int CCutImage::GetTransRed()
{
	return GetRValue(m_sCutInfo.dwTransparentColor);
}

int CCutImage::GetTransBlue()
{
	return GetBValue(m_sCutInfo.dwTransparentColor);
}

int CCutImage::GetTransGreen()
{
	return GetGValue(m_sCutInfo.dwTransparentColor);
}

BOOL CCutImage::LoadCutInfo(HWND hWnd, char *strFileName)
{
	FILE *fp;
	fp = fopen( strFileName, "rt" );
	fscanf( fp, "%s\n", m_sCutInfo.strBmpFileName );
	fscanf( fp, "%d\n", &m_sCutInfo.dwTransparentColor );
	fscanf( fp, "%d\n", &m_sCutInfo.nCount );

	if( m_sCutInfo.pCutRect != NULL )
		delete [] m_sCutInfo.pCutRect;
	m_sCutInfo.pCutRect = new RECT[m_sCutInfo.nCount];

	for(int i = 0 ; i < m_sCutInfo.nCount ; i++ )
	{
		fscanf( fp, "%d %d %d %d\n", &m_sCutInfo.pCutRect[i].left, &m_sCutInfo.pCutRect[i].top, 
									 &m_sCutInfo.pCutRect[i].right, &m_sCutInfo.pCutRect[i].bottom );							
	}	
	fclose( fp );

	LoadBmpImage(hWnd, m_sCutInfo.strBmpFileName);
	return TRUE;
}

void CCutImage::SetBmpFileName(char* strFileName)
{
	memcpy(m_sCutInfo.strBmpFileName, strFileName, strlen(strFileName));
}

void CCutImage::CreateCutRect()
{
	if(m_sCutInfo.pCutRect != NULL)
		delete [] m_sCutInfo.pCutRect;

	m_sCutInfo.pCutRect = new RECT[m_sCutInfo.nCount];
}

void CCutImage::SetSprRect(int nIndex, RECT rect)
{
	m_sCutInfo.pCutRect[nIndex] = rect;
}


BOOL CCutImage::SaveCutInfo(char *strFileName)
{
	FILE *fp = fopen(strFileName, "wt");

	fprintf( fp, "%s\n", m_sCutInfo.strBmpFileName );
	fprintf( fp, "%d\n", m_sCutInfo.dwTransparentColor );
	fprintf( fp, "%d\n", m_sCutInfo.nCount );	

	for(int i = 0 ; i < m_sCutInfo.nCount ; i++ )
	{
		fprintf( fp, "%d %d %d %d\n", m_sCutInfo.pCutRect[i].left, m_sCutInfo.pCutRect[i].top, 
									 m_sCutInfo.pCutRect[i].right, m_sCutInfo.pCutRect[i].bottom );							
	}	

	fclose(fp);

	return TRUE;
}

RECT CCutImage::ScanBoxRect(RECT rtDrag)
{	
	RECT rect;
	rect.left = ScanLeft( rtDrag.left, rtDrag.top, rtDrag.right, rtDrag.bottom );
	rect.top = ScanTop( rtDrag.left, rtDrag.top, rtDrag.right, rtDrag.bottom );
	rect.right = ScanRight( rect.left, rect.top, rtDrag.right, rtDrag.bottom );
	rect.bottom = ScanBottom( rect.left, rect.top, rect.right, rtDrag.bottom );		
	return rect;
}

int CCutImage::ScanLeft( int x1, int y1, int x2, int y2 )
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

int CCutImage::ScanTop( int x1, int y1, int x2, int y2 )
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

int CCutImage::ScanRight( int x1, int y1, int x2, int y2 )
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

int CCutImage::ScanBottom( int x1, int y1, int x2, int y2 )
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
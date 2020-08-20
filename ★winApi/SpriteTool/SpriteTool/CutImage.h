#pragma once

struct CUT_INFO
{
	char strBmpFileName[50];
	DWORD dwTranparentColor;
	int nCount;
	RECT *pCutRect;
};

class CutImage
{
public:
	CutImage();
	~CutImage();
};


#pragma once

/*------------------------------------------------------------------
 �������� �ʿ�� �ϴ� ���� ���⼭ �� �־� �ָ� �ȴ�.
 �� ������ �ϰ� �Ǹ� �ϳ��� ���� Ʋ �ȿ��� ���α׷����� �� �� �ִ�.
------------------------------------------------------------------*/
class CGameFrame
{
protected:
	HWND m_hWnd;
	HDC	m_hBackBuffer;
	int m_nWidth, m_nHeight;
	BOOL m_bIsFullMode;
	int m_nFPS;
	DWORD m_dwOldFPSTime;
	DWORD m_dwCurTime;
	DWORD m_dwElapsedTime; // <-- �߰���

	virtual void SceneInit()=0;
	virtual void SceneUpdate()=0;
	virtual void SceneRender()=0;
	virtual void SceneRelease()=0;
	void ChangeScreenMode(BOOL bIsFullMode);

private:	
	DWORD m_dwOldTIme;  // <-- �߰���
	int m_nFPSCount;
	void FullScreenModeChange();

public:
	void Init(HWND hWnd, int nWidth, int nHeight, BOOL bIsFullMode);
	void Update();
	void Render();
	void Release();

public:
	CGameFrame(void);
	~CGameFrame(void);
};


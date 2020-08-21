#pragma once

/*------------------------------------------------------------------
 하위에서 필요로 하는 것은 여기서 다 넣어 주면 된다.
 팀 단위로 하게 되면 하나의 같은 틀 안에서 프로그래밍을 할 수 있다.
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

	virtual void SceneInit()=0;
	virtual void SceneUpdate()=0;
	virtual void SceneRender()=0;
	virtual void SceneRelease()=0;
	void ChangeScreenMode(BOOL bIsFullMode);

private:	
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


#pragma once
enum MOUSE_STATE { MOUSE_UP, MOUSE_DOWN, MOUSE_NONE };  
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

		// ���콺, Ű���� ó�� �κ�
	MOUSE_STATE m_nMouseState;
	POINT m_ptMouseClick;

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

	void MouseProcess(UINT message, LPARAM lParam); // ���콺 ó��

public:
	CGameFrame(void);
	~CGameFrame(void);
};


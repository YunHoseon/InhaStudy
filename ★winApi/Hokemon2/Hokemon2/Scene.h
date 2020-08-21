#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Render(HWND hWnd, HDC hdc) = 0;
	virtual void Free(HWND hWnd) = 0;
};
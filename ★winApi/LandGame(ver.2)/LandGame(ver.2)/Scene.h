#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Free() = 0;
};
#pragma once

class SceneManager;

class Singleton
{
	Singleton() {};

public:
	SceneManager *sceneManager;

	HDC hdc;
	HDC backHDC;
	RECT rectView;

	virtual ~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
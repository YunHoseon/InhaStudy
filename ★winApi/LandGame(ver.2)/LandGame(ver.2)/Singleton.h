#pragma once

class SceneManager;

class Singleton
{
	Singleton() {};

public:
	SceneManager *sceneManager;
	HDC hdc;
	HDC backHDC;

	~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
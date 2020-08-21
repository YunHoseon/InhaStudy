#pragma once

class SceneManager;

class Singleton
{
	Singleton() {};

public:
	SceneManager *sceneManager;
	virtual ~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
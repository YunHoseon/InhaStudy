#pragma once

class SceneManager;

class Singleton		//GameManager�� ����
{
	Singleton() { movable = true; };

public:
	SceneManager *sceneManager;
	RECT rectView;
	bool movable;

	virtual ~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
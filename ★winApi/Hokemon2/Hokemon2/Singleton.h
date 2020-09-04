#pragma once

class SceneManager;

class Singleton		//GameManager�� ����
{
	Singleton() 
	{
		movable = true;
		mapState = 1;
		isBattle = false;
	};

public:
	SceneManager *sceneManager;
	RECT rectView;
	bool movable;
	int mapState;	//1 = ����, 2 = ��
	bool isBattle;

	virtual ~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
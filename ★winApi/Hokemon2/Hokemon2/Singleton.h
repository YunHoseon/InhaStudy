#pragma once

class SceneManager;

class Singleton		//GameManager·Î Áþ±â
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
	int mapState;	//1 = ¸¶À», 2 = ½£
	bool isBattle;

	virtual ~Singleton() {};

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
#pragma once
class Singleton
{
	Singleton();
public:
	~Singleton();

	static Singleton *GetInstance()
	{
		static Singleton ins;
		return &ins;
	}
};
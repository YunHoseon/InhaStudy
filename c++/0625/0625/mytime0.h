#pragma once
#include <iostream>

class Time
{
	int hours;
	int minutes;

public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	//Time Sum(const Time &t) const;
	Time operator+(const Time &t) const;
	Time operator*(const int n) const;

	friend std::ostream & operator<<(std::ostream &os, const Time &t);
	void Show()const;
	~Time();
};

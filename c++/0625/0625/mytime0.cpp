#include "mytime0.h"

Time::Time() : hours(0), minutes(0) {};
Time::Time(int h, int m) : hours(h), minutes(m) {};

void Time::AddMin(int m)
{
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}

void Time::AddHr(int h)
{
	hours += h;
}

void Time::Reset(int h, int m)
{
	hours = h;
	minutes = m;
}

//Time Time::Sum(const Time & t) const
//{
//	Time sum;
//	sum.minutes = minutes + t.minutes;
//	sum.hours = hours + t.hours + sum.minutes / 60;
//	sum.minutes %= 60;
//	return sum;
//}

Time Time::operator+(const Time & t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

Time Time::operator*(const int n) const
{
	Time mul;
	mul.minutes = minutes * n;
	mul.hours = hours * n + mul.minutes / 60;
	mul.minutes %= 60;
	return mul;
}

void Time::Show() const
{
	std::cout << hours << "시간, " << minutes << "분";
}

Time::~Time()
{
}

std::ostream & operator<<(std::ostream & os, const Time & t)
{
	os << t.hours << "시간, " << t.minutes << "분";
	return os;
}

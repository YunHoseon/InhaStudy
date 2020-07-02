#pragma once
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

class Stopwatch
{
	clock_t startTime;
	clock_t endTime;

public:
	Stopwatch();
	void StartTimer();
	void StopTimer();
	clock_t getElapsedTime();
	~Stopwatch();

	clock_t GetStartTime() { return startTime; }
	clock_t GetEndTime() { return endTime; }
};


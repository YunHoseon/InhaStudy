#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	startTime = clock();
}

void Stopwatch::StartTimer()
{
	startTime = clock();
}

void Stopwatch::StopTimer()
{
	endTime = clock();
}

clock_t Stopwatch::getElapsedTime()
{
	return this->endTime - this->startTime;
}

Stopwatch::~Stopwatch()
{
}

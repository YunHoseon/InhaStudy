#include "stdafx.h"
#include "Hokemon.h"

Hokemon::Hokemon()	
{
	mExp = 0;
}

Hokemon::~Hokemon()
{
}

void Hokemon::StatusUp()
{
	SetMaxHp(GetMaxHp() + 1);
	SetmAtk(GetmAtk() + 1);
	SetmGrd(GetmGrd() + 1);
	SetmSpd(GetmSpd() + 1);
}

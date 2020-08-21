#include "stdafx.h"
#include "Hokemon.h"

Hokemon::Hokemon()	
{
	//파싱해서 포켓몬마다 다르게 설정하기
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

#include "stdafx.h"
#include "Hokemon.h"

Hokemon::Hokemon()	
{
	//�Ľ��ؼ� ���ϸ󸶴� �ٸ��� �����ϱ�
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

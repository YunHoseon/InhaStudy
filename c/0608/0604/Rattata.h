#pragma once
#include "Monster.h"

class Rattata :
	public Monster
{
public:

	Rattata()
	{
		/* Set Bulbasaur status */
		SetmNum(19);
		SetmName("����");

		SetmHp(10);
		SetMaxHp(10);
		SetmAtk(3);
		SetmGrd(2);
		SetmSpd(3);

		SetmType(normal);

		SetmLevel(3);
		SetmExp(0);

		/* Set Bulbasaur skill */
		SetsName("�����ġ��", 0);
		SetsType(normal, 0);
		SetsDamage(5, 0);
		Setpp(30, 0);
		SetMaxPp(30, 0);

		SetsName("��������", 1);
		SetsType(normal, 1);
		SetsDamage(0, 1);
		Setpp(20, 1);
		SetMaxPp(20, 1);
	}

	 /*void StatusUp()
	{
		SetMaxHp(GetMaxHp() + 1);
		SetmAtk(GetmAtk() + 1);
		SetmGrd(GetmGrd() + 1);
		SetmSpd(GetmSpd() + 2);
	}*/

	~Rattata()
	{
	}
};
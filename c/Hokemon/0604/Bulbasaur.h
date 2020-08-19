#pragma once
#include "Monster.h"

class Bulbasaur :
	public Monster
{
public:
	Bulbasaur()
	{
		/* Set Bulbasaur status */
		SetmNum(1);
		SetmName("ÀÌ»óÇØ¾¾");

		SetmHp(18);
		SetMaxHp(18);
		SetmAtk(3);
		SetmGrd(4);
		SetmSpd(2);

		SetmType(grass);

		SetmLevel(5);
		SetmExp(0);

		/* Set Bulbasaur skill */
		SetsName("¸öÅë¹ÚÄ¡±â", 0);
		SetsType(normal, 0);
		SetsDamage(5, 0);
		Setpp(30, 0);
		SetMaxPp(30, 0);

		SetsName("²¿¸®Èçµé±â", 1);
		SetsType(normal, 1);
		SetsDamage(0, 1);
		Setpp(20, 1);
		SetMaxPp(20, 1);
	}

	virtual void StatusUp()
	{
		SetMaxHp(GetMaxHp() + 1);
		SetmAtk(GetmAtk() + 1);
		SetmGrd(GetmGrd() + 2);
		SetmSpd(GetmSpd() + 1);
	}

	~Bulbasaur()
	{
	}
};
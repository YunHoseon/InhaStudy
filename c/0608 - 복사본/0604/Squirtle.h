#pragma once
#include "Monster.h"

class Squirtle :
	public Monster
{
public:

	Squirtle()
	{
		/* Set Squirtle status */
		SetmNum(1);
		SetmName("部何扁");

		SetmHp(15);
		SetMaxHp(15);
		SetmAtk(3);
		SetmGrd(4);
		SetmSpd(3);

		SetmType(water);

		SetmLevel(5);
		SetmExp(0);

		/* Set Squirtle skill */
		SetsName("个烹冠摹扁", 0);
		SetsType(normal, 0);
		SetsDamage(5, 0);
		Setpp(30, 0);
		SetMaxPp(30, 0);

		SetsName("部府如甸扁", 1);
		SetsType(normal, 1);
		SetsDamage(0, 1);
		Setpp(20, 1);
		SetMaxPp(20, 1);
	}

	/*virtual void StatusUp()
	{
		SetMaxHp(GetMaxHp() + 2);
		SetmAtk(GetmAtk() + 1);
		SetmGrd(GetmGrd() + 1);
		SetmSpd(GetmSpd() + 1);
	}*/

	~Squirtle()
	{
	}
};
#pragma once
#include "Monster.h"

class Charmander :
	public Monster
{
public:

	Charmander()
	{
		/* Set Charmander status */
		SetmNum(4);
		SetmName("파이리");

		SetmHp(13);
		SetMaxHp(13);
		SetmAtk(4);
		SetmGrd(2);
		SetmSpd(4);

		SetmType(fire);

		SetmLevel(5);
		SetmExp(0);

		/* Set Charmander skill */
		SetsName("할퀴기", 0);
		SetsType(normal, 0);
		SetsDamage(5, 0);
		Setpp(30, 0);
		SetMaxPp(30, 0);

		SetsName("울음소리", 1);
		SetsType(normal, 1);
		SetsDamage(0, 1);
		Setpp(20, 1);
		SetMaxPp(20, 1);
	}
	
	virtual void StatusUp()
	{
		SetMaxHp(GetMaxHp() + 1);
		SetmAtk(GetmAtk() + 2);
		SetmGrd(GetmGrd() + 1);
		SetmSpd(GetmSpd() + 1);
	}

	~Charmander()
	{
	}
};
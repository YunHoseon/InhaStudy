#pragma once
#include "Monster.h"
class Snorlax :
	public Monster
{
public:

	Snorlax()
	{
		/* Set Snorlax status */
		SetmNum(143);
		SetmName("잠만보");

		SetmHp(30);
		SetMaxHp(30);
		SetmAtk(8);
		SetmGrd(14);
		SetmSpd(5);

		SetmType(normal);

		SetmLevel(10);
		SetmExp(0);

		/* Set Snorlax skill */
		SetsName("몸통박치기", 0);
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

	~Snorlax()
	{
	}
};


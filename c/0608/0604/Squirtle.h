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
		SetmName("���α�");

		SetmHp(15);
		SetMaxHp(15);
		SetmAtk(3);
		SetmGrd(4);
		SetmSpd(3);

		SetmType(water);

		SetmLevel(5);
		SetmExp(0);

		/* Set Squirtle skill */
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


#pragma once
#include <stdio.h>
#include <string.h>

enum Type { normal, fire, water, grass };

typedef struct MonsterSkill
{
	char sName[32] = { NULL };
	unsigned int pp = 0;
	unsigned int MaxPp = 0;
	int sDamage = 0;
	enum Type sType = normal;
}MonsterSkill;

class Monster
{
private:
	unsigned int mNum = 0;
	char mName[16] = { NULL };

	int mHp = 0;
	int MaxHp = 0;
	unsigned int mAtk = 0;
	unsigned int mGrd = 0;
	unsigned int mSpd = 0;

	unsigned int mLevel = 0;
	unsigned int mExp = 0;

	enum Type mType = normal;

	MonsterSkill mskill[4];

public:

	/*Monster class getset*/

	unsigned int GetmNum() { return mNum; }
	void SetmNum(unsigned int _mNum) { mNum = _mNum; }

	char* GetmName() { return mName; }
	void SetmName(const char* _mName) { strcpy_s(mName, _mName); }

	int GetmHp() { return mHp; }
	void SetmHp(int _mHp) { mHp = _mHp; }

	int GetMaxHp() { return MaxHp; }
	void SetMaxHp(int _MaxHp) { MaxHp = _MaxHp; }

	unsigned int GetmAtk() { return mAtk; }
	void SetmAtk(unsigned int _mAtk) { mAtk = _mAtk; }

	unsigned int GetmGrd() { return mGrd; }
	void SetmGrd(unsigned int _mGrd) { mGrd = _mGrd; }

	unsigned int GetmSpd() { return mSpd; }
	void SetmSpd(unsigned int _mSpd) { mSpd = _mSpd; }

	enum Type GetmType() { return mType; }
	void SetmType(enum Type _mType) { mType = _mType; }

	unsigned int GetmLevel() { return mLevel; }
	void SetmLevel(const unsigned int _mLevel) { mLevel = _mLevel; }

	unsigned int GetmExp() { return mExp; }
	void SetmExp(unsigned int _mExp) { mExp = _mExp; }

	/*MonsterSkill struct getset*/

	char* GetsName(int skillNum) { return mskill[skillNum].sName; }
	void SetsName(const char* _sName, int skillNum) { strcpy_s(mskill[skillNum].sName, _sName); }

	unsigned int Getpp(int skillNum) { return mskill[skillNum].pp; }
	void Setpp(unsigned int _pp, int skillNum) { mskill[skillNum].pp = _pp; }

	unsigned int GetMaxPp(int skillNum) { return mskill[skillNum].MaxPp; }
	void SetMaxPp(unsigned int _MaxPp, int skillNum) { mskill[skillNum].MaxPp = _MaxPp; }

	int GetsDamage(int skillNum) { return mskill[skillNum].sDamage; }
	void SetsDamage(int _sDamage, int skillNum) { mskill[skillNum].sDamage = _sDamage; }

	enum Type GetsType(int skillNum) { return mskill[skillNum].sType; }
	void SetsType(enum Type _sType, int skillNum) { mskill[skillNum].sType = _sType; }

	virtual void StatusUp() 
	{
		SetMaxHp(GetMaxHp() + 1);
		SetmAtk(GetmAtk() + 1);
		SetmGrd(GetmGrd() + 1);
		SetmSpd(GetmSpd() + 1);
	}
};
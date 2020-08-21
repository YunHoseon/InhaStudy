#pragma once

enum Type { normal, fire, water, grass, elec };

typedef struct MonsterSkill
{
	char sName[32];
	unsigned int pp;
	unsigned int MaxPp;
	int sDamage;
	enum Type sType;
}MonsterSkill;

class Hokemon
{
private:
	unsigned int mNum;
	char mName[16];

	int mHp;
	int MaxHp;
	int mAtk;
	int mGrd;
	int mSpd;

	unsigned int mLevel;
	unsigned int mExp;

	enum Type mType;

	MonsterSkill mskill[4];

public:
	Hokemon();
	~Hokemon();

	void StatusUp();

	/*hokemon getter setter*/

	unsigned int GetmNum() { return mNum; }
	void SetmNum(unsigned int _mNum) { mNum = _mNum; }

	char* GetmName() { return mName; }
	void SetmName(const char* _mName) { strcpy_s(mName, _mName); }

	int GetmHp() { return mHp; }
	void SetmHp(int _mHp) { mHp = _mHp; }

	int GetMaxHp() { return MaxHp; }
	void SetMaxHp(int _MaxHp) { MaxHp = _MaxHp; }

	int GetmAtk() { return mAtk; }
	void SetmAtk(int _mAtk) { mAtk = _mAtk; }

	int GetmGrd() { return mGrd; }
	void SetmGrd(int _mGrd) { mGrd = _mGrd; }

	int GetmSpd() { return mSpd; }
	void SetmSpd(int _mSpd) { mSpd = _mSpd; }

	enum Type GetmType() { return mType; }
	void SetmType(enum Type _mType) { mType = _mType; }

	unsigned int GetmLevel() { return mLevel; }
	void SetmLevel(const unsigned int _mLevel) { mLevel = _mLevel; }

	unsigned int GetmExp() { return mExp; }
	void SetmExp(unsigned int _mExp) { mExp = _mExp; }

	/*skill getter setter*/

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
};
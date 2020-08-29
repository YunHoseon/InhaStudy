#pragma once

enum Type { normal, fire, water, grass, elec, poison };

class Hokemon
{
private:
	Hokemon_Data hData;

	unsigned int mLevel;
	unsigned int mExp;

	Skill_Data mSkill[4];

public:
	Hokemon();
	~Hokemon();

	void StatusUp();

	/*hokemon getter setter*/

	Hokemon_Data GetData() { return hData; }
	void SetData(Hokemon_Data _hData) { hData = _hData; }
	/*unsigned int GetmNum() { return mNum; }
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

	enum Type* GetmType(int _num) { return &mType[_num]; }
	void SetmType(enum Type* _mType, int _num) { mType[_num] = *_mType; }*/

	unsigned int GetmLevel() { return mLevel; }
	void SetmLevel(const unsigned int _mLevel) { mLevel = _mLevel; }

	unsigned int GetmExp() { return mExp; }
	void SetmExp(unsigned int _mExp) { mExp = _mExp; }

	/*skill getter setter*/

	Skill_Data* GetskillData() { return mSkill; }
	void SetskillData(Skill_Data _skillData, int _n) { mSkill[_n] = _skillData; }

	/*char* GetsName(int skillNum) { return mSkill[skillNum].sName; }
	void SetsName(const char* _sName, int skillNum) { strcpy_s(mSkill[skillNum].sName, _sName); }

	unsigned int Getpp(int skillNum) { return mSkill[skillNum].pp; }
	void Setpp(unsigned int _pp, int skillNum) { mSkill[skillNum].pp = _pp; }

	unsigned int GetMaxPp(int skillNum) { return mSkill[skillNum].MaxPp; }
	void SetMaxPp(unsigned int _MaxPp, int skillNum) { mSkill[skillNum].MaxPp = _MaxPp; }

	int GetsDamage(int skillNum) { return mSkill[skillNum].sDamage; }
	void SetsDamage(int _sDamage, int skillNum) { mSkill[skillNum].sDamage = _sDamage; }

	enum Type GetsType(int skillNum) { return mSkill[skillNum].sType; }
	void SetsType(enum Type _sType, int skillNum) { mSkill[skillNum].sType = _sType; }*/
};
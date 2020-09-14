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

	//unsigned int GetmNum() { return hData.hNum; }
	//void SetmNum(unsigned int _mNum) { hData.hNum = _mNum; }

	/*TCHAR* GetmName() { return hData.hName; }
	void SetmName(const TCHAR* _mName) 
	{
		USES_CONVERSION;
		_tcscpy(hData.hName, _mName); 
	}*/

	int GetmHp() { return hData.hHp; }
	void SetmHp(int _mHp) { hData.hHp = _mHp; }

	int GetMaxHp() { return hData.MaxHp; }
	void SetMaxHp(int _MaxHp) { hData.MaxHp = _MaxHp; }

	int GetmAtk() { return hData.hAtk; }
	void SetmAtk(int _mAtk) { hData.hAtk = _mAtk; }

	int GetmGrd() { return hData.hGrd; }
	void SetmGrd(int _mGrd) { hData.hGrd = _mGrd; }

	int GetmSpd() { return hData.hSpd; }
	void SetmSpd(int _mSpd) { hData.hSpd = _mSpd; }

	//enum Type* GetmType(int _num) { return &mType[_num]; }
	//void SetmType(enum Type* _mType, int _num) { mType[_num] = *_mType; }

	unsigned int GetmLevel() { return mLevel; }
	void SetmLevel(const unsigned int _mLevel) { mLevel = _mLevel; }

	unsigned int GetmExp() { return mExp; }
	void SetmExp(unsigned int _mExp) { mExp = _mExp; }

	/*skill getter setter*/

	Skill_Data* GetskillData(int _mNum) { return &mSkill[_mNum]; }
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
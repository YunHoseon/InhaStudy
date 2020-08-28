#pragma once

struct Hokemon_Data
{
	int hNum;
	char hName[16];
	int hHp;
	int MaxHp;
	int hAtk;
	int hGrd;
	int hSpd;
	int hNextEvol;
	int hType;
};

struct Skill_Data
{
	int id;
	int accuracy;
	char sName[32];
	int pp;
	int MaxPp;
	int sDamage;
	int sType;
};

class HokemonDB
{
public:
	std::map<int, Hokemon_Data> map_Hokemons;
	std::map<int, Skill_Data> map_Skills;

	HokemonDB();
	~HokemonDB();

	static HokemonDB *GetInstance()
	{
		static HokemonDB ins;
		return &ins;
	}
};


#pragma once

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


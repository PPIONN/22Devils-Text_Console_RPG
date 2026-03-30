#pragma once
#include"pokemon.h"
#include <cstdlib> // rand(), srand() 사용
#include <ctime>   // time() 사용
class gastly : public pokemon{
public:
	gastly(const int nowlevel, const std::string& name) { // 포켓몬이 만들어지면 스탯조정, 스킬조정
		newpokescale(nowlevel);
		updateSkills();
		setname(name);
	};

private:
	float hp = 10.0f;
	float attack = 5.0f;
	float defense = 5.0f;
	float specialAttack = 5.0f;
	float specialDefense = 5.0f;
	float speed = 5.0f;
	int level = 1;
	int exp = 19;

	float hpGrowth = 1.95f;
	float attackGrowth = 1.01f;
	float defenseGrowth = 0.91f;
	float specialAttackGrowth = 2.31f;
	float specialDefenseGrowth = 1.91f;
	float speedGrowth = 1.91;

	std::vector<Skill> const learnableSkills = {
		{ "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
		{ "Lick", "Ghost", "Physical", 20, 100, 30, 0 },
		{ "Spite", "Ghost", "Status", 0, 100, 10, 5 },
		{ "Mean Look", "Normal", "Status", 0, -1, 5, 8 },
		{ "Curse", "Unknown", "Status", 0, -1, 10, 12 },
		{ "Night Shade", "Ghost", "Special", 0, 100, 15, 15 },
		{ "Confuse Ray", "Ghost", "Status", 0, 100, 10, 19 },
		{ "Sucker Punch", "Dark", "Physical", 80, 100, 5, 22 },
		{ "Payback", "Dark", "Physical", 50, 100, 10, 26 },
		{ "Shadow Ball", "Ghost", "Special", 80, 100, 15, 29 },
		{ "Dream Eater", "Psychic", "Special", 100, 100, 15, 33 },
		{ "Dark Pulse", "Dark", "Special", 80, 100, 15, 36 },
		{ "Destiny Bond", "Ghost", "Status", 0, -1, 5, 40 },
		{ "Nightmare", "Ghost", "Status", 0, -1, 15, 43 } };
};

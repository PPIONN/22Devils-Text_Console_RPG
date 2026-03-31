#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H
#include "PokemonCore.h"

class Squirtle : public Pokemon {
public:
	Squirtle(Player* p) {
		owner = p; name = "꼬부기"; type = "Water"; level = p->playerlevel;
		hp = 44.0f; attack = 48.0f; defense = 65.0f; specialAttack = 50.0f; specialDefense = 64.0f; speed = 43.0f;
		hpGrowth = ((2 * 44 + 100) / 100.0f + 10); attackGrowth = ((2 * 48) / 100.0f + 5);
		defenseGrowth = ((2 * 65) / 100.0f + 5); specialAttackGrowth = ((2 * 50) / 100.0f + 5);
		specialDefenseGrowth = ((2 * 64) / 100.0f + 5); speedGrowth = ((2 * 43) / 100.0f + 5);
		newpokescale(level);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 1}, {"Water Gun", "Water", "Special", 40, 100, 25, 3},
			{"Bite", "Dark", "Physical", 60, 100, 25, 12}, {"Hydro Pump", "Water", "Special", 110, 80, 5, 33}
		};
		newpokeSkills();
	}
};

class Charmander : public Pokemon {
public:
	Charmander(Player* p) {
		owner = p; name = "파이리"; type = "Fire"; level = p->playerlevel;
		hp = 39.0f; attack = 52.0f; defense = 43.0f; specialAttack = 60.0f; specialDefense = 50.0f; speed = 65.0f;
		hpGrowth = ((2 * 39 + 100) / 100.0f + 10); attackGrowth = ((2 * 52) / 100.0f + 5);
		defenseGrowth = ((2 * 43) / 100.0f + 5); specialAttackGrowth = ((2 * 60) / 100.0f + 5);
		specialDefenseGrowth = ((2 * 50) / 100.0f + 5); speedGrowth = ((2 * 65) / 100.0f + 5);
		newpokescale(level);
		learnableSkills = {
			{"Scratch", "Normal", "Physical", 40, 100, 35, 1}, {"Ember", "Fire", "Special", 40, 100, 25, 4},
			{"Flamethrower", "Fire", "Special", 90, 100, 15, 24}, {"Flare Blitz", "Fire", "Physical", 120, 100, 15, 40}
		};
		newpokeSkills();
	}
};

class Bulbasaur : public Pokemon {
public:
	Bulbasaur(Player* p) {
		owner = p; name = "이상해씨"; type = "Grass"; level = p->playerlevel;
		hp = 45.0f; attack = 49.0f; defense = 49.0f; specialAttack = 65.0f; specialDefense = 65.0f; speed = 45.0f;
		hpGrowth = ((2 * 45 + 100) / 100.0f + 10); attackGrowth = ((2 * 49) / 100.0f + 5);
		defenseGrowth = ((2 * 49) / 100.0f + 5); specialAttackGrowth = ((2 * 65) / 100.0f + 5);
		specialDefenseGrowth = ((2 * 65) / 100.0f + 5); speedGrowth = ((2 * 45) / 100.0f + 5);
		newpokescale(level);
		learnableSkills = {
			{"Tackle", "Normal", "Physical", 40, 100, 35, 1}, {"Vine Whip", "Grass", "Physical", 45, 100, 25, 3},
			{"Razor Leaf", "Grass", "Physical", 55, 95, 25, 12}, {"Solar Beam", "Grass", "Special", 120, 100, 10, 36}
		};
		newpokeSkills();
	}
};

class Snorlax : public Monster {
public:
	Snorlax(int lv) {
		name = "Snorlax"; type = "Normal"; hp = 160.0f; attack = 110.0f; defense = 65.0f;
		hpGrowth = 4.25f; attackGrowth = 3.15f; newpokescale(lv);
		learnableSkills = { {"Body Slam", "Normal", "Physical", 85, 100, 15, 0} }; newpokeSkills();
	}
};

class Gastly : public Monster {
public:
	Gastly(int lv) {
		name = "Gastly"; type = "Ghost"; hp = 30.0f; attack = 35.0f; defense = 30.0f;
		hpGrowth = 1.95f; attackGrowth = 2.31f; newpokescale(lv);
		learnableSkills = { {"Night Shade", "Ghost", "Special", 40, 100, 15, 0} }; newpokeSkills();
	}
};

class Magikarp : public Monster {
public:
	Magikarp(int lv) {
		name = "Magikarp"; type = "Water"; hp = 20.0f; attack = 10.0f; defense = 55.0f;
		hpGrowth = 1.25f; attackGrowth = 0.55f; newpokescale(lv);
		learnableSkills = { {"Splash", "Normal", "Status", 0, 100, 40, 0} }; newpokeSkills();
	}
};

inline unique_ptr<Monster> spawnEnemy(int floor) {
	int r = rand() % 3; int lv = floor + rand() % 3;
	if (r == 0) return make_unique<Snorlax>(lv);
	if (r == 1) return make_unique<Gastly>(lv);
	return make_unique<Magikarp>(lv);
}
#endif

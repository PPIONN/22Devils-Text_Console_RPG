#ifndef POKEMON_CORE_H
#define POKEMON_CORE_H
#include "Common.h"

class Pokemon {
public:
	string name; string type; int level;
	float hp, maxhp, attack, defense, specialAttack, specialDefense, speed;
	float hpGrowth, attackGrowth, defenseGrowth, specialAttackGrowth, specialDefenseGrowth, speedGrowth;
	float warattack, wardefense, warspecialAttack, warspecialDefense, warspeed;
	vector<Skill> currentSkills;
	vector<Skill> learnableSkills;
	class Player* owner;

	Pokemon();
	virtual ~Pokemon();
	void newpokescale(int level);
	void levelup();
	void newpokeSkills();
	void levelhp(int l); void levelattack(int l); void leveldefense(int l);
	void ShowInfo();
};

class Monster : public Pokemon {
public:
	int baseRewardExp; int baseRewardGold;
	Monster() : baseRewardExp(100), baseRewardGold(100) {}
	int getFinalExp() { return baseRewardExp + (level * 10); }
	int getFinalGold() { return baseRewardGold + (level * 5); }
};

class Player {
public:
	string playername;
	int money, playerlevel, playerexp, playermaxexp;
	const int maxlevel = 100;
	vector<string> inventory;
	vector<unique_ptr<Pokemon>> mypokemon;

	Player(string name = "플레이어");
	void setStatus(StatType type, int amount);
	void LevelUP();
	int setexp(int amount);
	int setmoney(int amount);
	void AddPokemon(unique_ptr<Pokemon> newp);
	bool isAllFainted() const;
	void MyPokemonUI();
	Pokemon* getLeadPokemon();
};

class Item {
public:
	static void RareCandy(Player& p);
	static void BuyHPPotion(Player& p);
	static void BuyFHPPotion(Player& p);
	static void BuyPowerPotion(Player& p);
	static void Buyrandomexp(Player& p);
	static void Userandomexp(Player& p);
	static void Buyrandomgold(Player& p);
	static void Userandomgold(Player& p);
};
#endif

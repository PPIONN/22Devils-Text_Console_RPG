#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 기술 구조체
struct Skill {
	string name; string type; string category;
	int power; int accuracy; int pp; int maxPp; int level;
};

// 포켓몬 클래스 (뼈대)
class Pokemon {
protected:
	string name; string type;
	float hp, maxHp, attack, defense, specialAttack, specialDefense, speed;
	float hpGrowth, attackGrowth, defenseGrowth, specialAttackGrowth, specialDefenseGrowth, speedGrowth;
	int level, exp;

public:
	vector<Skill> learnableSkills;
	vector<Skill> currentSkills;

	string getName() { return name; }
	int getlevel() { return level; }
	float gethp() { return hp; }
	void sethp(float h) { hp = (h > maxHp) ? maxHp : (h < 0 ? 0 : h); }
	float getmaxhp() { return maxHp; }
	float getattack() { return attack; }
	void setattack(float a) { attack = a; }
	float getdefense() { return defense; }
	float getspecialDefense() { return specialDefense; }

	void newpokescale(int targetLevel);
	void levelup();
	int useSkill(int skillIdx, Pokemon& target);
	void newpokeSkills(); // 이 이름으로 통일합니다.
	void gainExp(int amount);
};

class Monster : public Pokemon {};

class Player {
public:
	int money = 500;
	int level = 1;
	int exp = 0;
	vector<string> inventory;

	void gainExp(int amount);
	void ShowStatus();
	void InventoryUI();
	int getmoney() const { return money; }
	void setmoney(int m) { money += m; }
	void AddItem(string itemName);
	bool HasItem(string itemName);
	void RemoveItem(string itemName);
};

class Item {
public:
	static void RareCandy(Player& player);
	static void BuyHPPotion(Player& player);
	static void UseHPPotion(Player& player, Pokemon* poke);
	static void BuyFHPPotion(Player& player);
	static void UseFHPPotion(Player& player, Pokemon* poke);
	static void BuyPowerPotion(Player& player);
	static void UsePowerPotion(Player& player, Pokemon* poke);
	static void Userandomexp(Player& player);
	static void Userandomgold(Player& player);
	static void BuyMultiLens(Player& player);
};

// 전역 변수 선언 (외부 참조용)
extern Player g_player;
extern int g_playerGold;
void initSpawnPool();

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Skill {
	string name; string type; int pp, maxPp, power;
};

class Pokemon {
public:
	string name;
	int level, hp, maxHp, atk, def, spd, gold, exp;
	vector<Skill> skills;

	Pokemon(string n, int l, int h, int mh, int a, int d, int s, int g, int e)
		: name(n), level(l), hp(h), maxHp(mh), atk(a), def(d), spd(s), gold(g), exp(e) {
	}

	int gethp() { return hp; }
	int getmaxhp() { return maxHp; }
	int getattack() { return atk; }
	void sethp(int h) { hp = h; }
	void setattack(int a) { atk = a; }
};

class Player {
public:
	int money = 500, level = 1, exp = 0;
	vector<string> inventory;
	void setmoney(int m) { money += m; }
	int getmoney() { return money; }
	void setexp(int e) { exp += e; }
	void LevelUP() { level++; }
	void setcurrenthp(int h) { /* 필요 시 구현 */ }
	void AddItem(string item) { inventory.push_back(item); }
	bool HasItem(string item) { return find(inventory.begin(), inventory.end(), item) != inventory.end(); }
	void RemoveItem(string item) {
		auto it = find(inventory.begin(), inventory.end(), item);
		if (it != inventory.end()) inventory.erase(it);
	}
};

class Item {
public:
	static void ShowAllItems();
	static void RareCandy(Player& player);
	static void BuyHPPotion(Player& player);
	static void UseHPPotion(Player& player, Pokemon* poke);
	static void BuyFHPPotion(Player& player);
	static void UseFHPPotion(Player& player);
	static void BuyMultiLens(Player& player);
	static void BuyPowerPotion(Player& player);
	static void UsePowerPotion(Player& player, Pokemon* poke);
	static void Buyrandomexp(Player& player);
	static void Userandomexp(Player& player);
	static void Buyrandomgold(Player& player);
	static void Userandomgold(Player& player);
};

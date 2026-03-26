#pragma once
#include <string>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	Player* Selector();
	void StatusGrowth(int level);
	void setmaxhp(int level);
	void setcurrenthp(int DeltaHP);
	void setattack(int level);
	void setdefense(int level);
	void setspecialAttack(int level);
	void setspecialDefense(int level);
	void setspeed(int level);
	void setmaxexp(int level);
	void setmoney(int Deltamoney);
	void LevelUP();
	void ShowStatus() const;

protected:
	std::string name;
	int maxhp;
	int currenthp;
	int attack;
	int defense;
	int specialAttack;
	int specialDefense;
	int speed;
	int level;
	int exp;
	int money;
	int maxexp;
	int basehp;
	int baseattack;
	int basedefense;
	int basespecialAttack;
	int basespecialDefense;
	int basespeed;
};

class Charmander : public Player
{
public:
	Charmander();
};

class Squirtle : public Player
{
public:
	Squirtle();
};

class Bulbasaur : public Player
{
public:
	Bulbasaur();
};

class Pikachu : public Player
{
public:
	Pikachu();
};

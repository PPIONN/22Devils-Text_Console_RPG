#pragma once
#include <string>

class Player
{
public:
	Player();
	virtual ~Player();
	static Player* Selector();
	void setStatus(int level);
	void setmaxhp(int level);
	void setcurrenthp(int DeltaHP);
	void setattack(int level);
	void setdefense(int level);
	void setspecialAttack(int level);
	void setspecialDefense(int level);
	void setspeed(int level);
	void setmaxexp(int level);
	void setexp(int Deltaexp);
	void setmoney(int Deltamoney);
	void LevelUP();
	void ShowStatus() const;
	void getmoney() const;

protected:
	//스탯
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
	int maxexp;

	// 레벨 제한
	static const int maxlevel = 100;

	// 소지금
	int money;

	// 종족값
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

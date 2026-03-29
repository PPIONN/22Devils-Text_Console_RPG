#pragma once
#include <string>
#include <vector>

// 유기적인 스탯관리를 위한 Enum Class
enum class StatType
{
	MaxHP,
	Attack,
	Defense,
	SpecialAttack,
	SpecialDefense,
	Speed,
	CurrentHP,
	EXP,
	MaxEXP,
	Level,
	Money,
	DHP,
	DAtt,
	ADef,
	DSAtt,
	DSDef,
	DSpd,
	Name
};

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
	void Attack();
	int Damage();
	int getStatus(StatType type) const;
	int getmaxhp() const;
	int getcurrenthp() const;
	int getattack() const;
	int getdefense() const;
	int getspecialAttack() const;
	int getspecialDefense() const;
	int getspeed() const;
	int getmaxexp() const;
	int getexp() const;
	int getmoney() const;
	int getdhp() const;
	int getdatt() const;
	int getddef() const;
	int getdsatt() const;
	int getdsdef() const;
	int getdspd() const;
	void ModifyStat(StatType type, int amount);
	void GetDamaged(int dmg);

	//오채율 - AddItem 함수 추가(vector inventory에 아이템 명 추가)
	void AddItem(const std::string& itemName);
	//오채율 - HasItem 함수 추가(vector inventory에 아이템이 존재하는지 확인)
	bool HasItem(const std::string& itemName);
	//오채율 - RemoveItem 함수 추가(vector inventory에서 사용한 아이템 제거)
	void RemoveItem(const std::string& itemName);


protected:
	//오채율 - Inventory vector 추가
	std::vector<std::string> inventory;

	// 스탯
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
	// 외부 요인으로 인한 스탯 변경값
	int dhp = 0;
	int datt = 0;
	int ddef = 0;
	int dsatt = 0;
	int dsdef = 0;
	int dspd = 0;

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


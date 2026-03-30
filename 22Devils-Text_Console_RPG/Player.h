//Player.h

#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "pokemon.h"

// 유기적인 스탯관리를 위한 Enum Class
enum class StatType
{
	EXP,
	MaxEXP,
	Level,
	Money,
	PlayerName,
};

// ItemUse 함수 사용을 위한 Enum Class
enum class Itemname
{
	Null,
	RareCandy,
	HPPotion,
	FHPPotion,
	MultiLens,
	PowerPorion,
	randomexp,
	randomgold,
};

class Player
{
public:
	Player(std::string playername);
	virtual ~Player();
	void Selector();
	void LevelUP();
	void ShowStatus(); //const;
	int getexp() const;
	int getmoney() const;
	int getStatus(StatType type) const;
	int setexp(int amount);
	int setmoney(int amount);
	void setStatus(StatType type, int amount);
	void InventoryUI();
	Itemname ChangeItemEnum(const std::string& itemName); // item 관련 코드 enum class로 변경하기 전까지 사용할 임시 코드
	void ItemUse(Itemname item);
	void AddPokemon(std::unique_ptr<pokemon> newpokemon);
	void MyPokemonUI();
	pokemon* getLeadPokemon();

	//오채율 - AddItem 함수 추가(vector inventory에 아이템 명 추가)
	void AddItem(const std::string& itemName);
	//오채율 - HasItem 함수 추가(vector inventory에 아이템이 존재하는지 확인)
	bool HasItem(const std::string& itemName);
	//오채율 - RemoveItem 함수 추가(vector inventory에서 사용한 아이템 제거)
	void RemoveItem(const std::string& itemName);
	void PrintAllItems() const;
	void selectPokemon();
	void changePokemon();

	//public 변수
	int playerlevel;

protected:
	//오채율 - Inventory vector 추가
	std::vector<std::string> inventory;

	// 포켓몬 리스트
	std::vector<std::unique_ptr<pokemon>> mypokemon;

	// 스탯
	std::string playername;
	int playerexp;
	int playermaxexp;

	// 레벨 제한
	static const int maxlevel = 100;

	// 소지금
	int money;
};

class Charmander : public pokemon
{
public:
	Charmander(Player* player);
protected:
	Player* owner;
};

class Squirtle : public pokemon
{
public:
	Squirtle(Player* player);
protected:
	Player* owner;
};

class Bulbasaur : public pokemon
{
public:
	Bulbasaur(Player* player);
protected:
	Player* owner;
};

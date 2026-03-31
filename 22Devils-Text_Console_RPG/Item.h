#pragma once
#include "Player.h"

class Item
{
private:
	



public:

	void ShowAllItems();

	void RareCandy(Player& player);
	/*
	void HPPotion(Player& player);
	void FHPPotion(Player& player);
	void MultiLens(Player& player);
	void PowerPotion(Player& player);
	void randomexp(Player& player);
	void randomgold(Player& player);
	*/

	void BuyHPPotion(Player& player);
	void UseHPPotion(Player& player,pokemon* poke);
	void BuyFHPPotion(Player& player);
	void UseFHPPotion(Player& player);
	void BuyMultiLens(Player& player);
	void UseMultiLens(Player& player);
	void BuyPowerPotion(Player& player);
	void UsePowerPotion(Player& player, pokemon* poke);
	void Buyrandomexp(Player& player);
	void Userandomexp(Player& player);
	void Buyrandomgold(Player& player);
	void Userandomgold(Player& player);

};

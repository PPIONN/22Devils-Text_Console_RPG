#include "GameData.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//일단 아이템을 상점에서 구매하자마자 바로 사용되는 방식으로 만들고 있긴 한데
//Multi Lens같은 함수는 전투 중 사용할 수 있어야 할 것 같긴 해요.
//인벤토리 - 같은 아이템이 중복 표기되는건 제외하고 일단 넣기만 해
//클래스 상속?

void Item::ShowAllItems() // 호출시 아이템 리스트 전체 출력
{
	std::cout << "=== Item List ===" << std::endl;
	std::cout << "1. Rare Candy  - Instantly levels up the player (500G)" << std::endl;
	std::cout << "2. HPPotion    - Restores 20 HP (300G)" << std::endl;
	std::cout << "3. FHPPotion   - Fully restores HP (300G)" << std::endl;
	std::cout << "4. MultiLens   - Next attack hits twice (100G)" << std::endl;
	std::cout << "5. PowerPotion - Increase attack by 20 (200G)" << std::endl;
	std::cout << "6. randomexp   - Gain random EXP between 50~500 (100G)" << std::endl;
	std::cout << "7. randomgold  - Gain random Gold between 50~500 (100G)" << std::endl;
	std::cout << "0. Exit shop" << std::endl;
	std::cout << "=================" << std::endl;
}

void Item::RareCandy(Player& player)
{
	if (player.getmoney() < 500) { std::cout << "Not enough gold!" << std::endl; return; }
	player.setmoney(-500);
	player.LevelUP();
	std::cout << "Used RareCandy! EXP +100" << std::endl;
}

void Item::BuyHPPotion(Player& player)
{
	if (player.getmoney() < 100) { std::cout << "Not enough gold!" << std::endl; return; }
	player.setmoney(-100);
	player.AddItem("HPPotion");
}

void Item::UseHPPotion(Player& player, Pokemon* poke)
{
	if (player.HasItem("HPPotion"))
	{
		if (poke->maxHp == poke->hp) { player.RemoveItem("HPPotion"); }
		else {
			if ((poke->maxHp - poke->hp) >= 20) {
				poke->hp += 20; player.RemoveItem("HPPotion");
			}
			else {
				poke->hp = poke->maxHp; player.RemoveItem("HPPotion");
			}
		}
	}
}

void Item::BuyFHPPotion(Player& player)
{
	if (player.getmoney() < 100) { std::cout << "Not enough gold!" << std::endl; return; }
	player.setmoney(-100);
	player.AddItem("FHPPotion");
}

void Item::UseFHPPotion(Player& player)
{
	if (player.HasItem("FHPPotion")) {
		player.RemoveItem("FHPPotion");
	}
}

void Item::BuyMultiLens(Player& player)
{
	if (player.getmoney() < 200) { std::cout << "Not enough gold!" << std::endl; return; }
	player.setmoney(-200);
	player.AddItem("MultiLens");
}

void Item::BuyPowerPotion(Player& player)
{
	if (player.getmoney() < 100) { std::cout << "Not enough gold!" << std::endl; return; }
	player.setmoney(-100);
	player.AddItem("PowerPotion");
}

void Item::UsePowerPotion(Player& player, Pokemon* poke)
{
	if (player.HasItem("PowerPotion")) {
		poke->atk += 20;
		player.RemoveItem("PowerPotion");
	}
}

void Item::Buyrandomexp(Player& player)
{
	if (player.getmoney() < 100) return;
	player.setmoney(-100);
	player.AddItem("randomexp");
}

void Item::Userandomexp(Player& player)
{
	if (player.HasItem("randomexp")) {
		int EXP = rand() % 451 + 50;
		player.setexp(EXP);
		player.RemoveItem("randomexp");
		std::cout << "You got " << EXP << " EXP!" << std::endl;
	}
}

void Item::Buyrandomgold(Player& player)
{
	if (player.getmoney() < 100) return;
	player.setmoney(-100);
	player.AddItem("randomgold");
}

void Item::Userandomgold(Player& player)
{
	if (player.HasItem("randomgold")) {
		int gold = rand() % 451 + 50;
		player.setmoney(gold);
		player.RemoveItem("randomgold");
		std::cout << "You got " << gold << " gold!" << std::endl;
	}
}

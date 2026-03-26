//Item.cpp

#include <iostream>
#include "Item.h"
#include "Player.h"

//일단 아이템을 상점에서 구매하자마자 바로 사용되는 방식으로 만들고 있긴 한데
//Multi Lens같은 함수는 전투 중 사용할 수 있어야 할 것 같긴 해요.

void Item::RareCandy(Player& player)
{
	if (player.getmoney() < 500)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-500);
	player.setexp(100);
	std::cout << "Used RareCandy! EXP +100" << std::endl;
}

void Item::HPPotion(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.setcurrenthp(+20);
	std::cout << "HP increased by 20!" << std::endl;
}

void Item::FHPPotion(Player& player)
{
	if (player.getmoney() < 300)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-300);
	player.setcurrenthp(9999);
	std::cout << "HP has been fully restored!" << std::endl;
}

void Item::MultiLens(Player& player)
{
	//공격이 한 번 더 반복되는 아이템
	// 전투 시스템 완성 후 연결 필요
}

void Item::PowerPotion(Player& player)
{
	if (player.getmoney() < 200)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-200);
	//player.setattack(player.getattack() + 20);
	std::cout << "Power increased by 20!" << std::endl;
}

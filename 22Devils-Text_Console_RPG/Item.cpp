//Item.cpp

#include <iostream>
#include "Item.h"
#include "Player.h"
#include <cstdlib>

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
	std::cout << "5. PowerPorion - Increase attack by 20 (200G)" << std::endl;
	std::cout << "6. randomexp   - Gain random EXP between 50~500 (100G)" << std::endl;
	std::cout << "7. randomgold  - Gain random Gold between 50~500 (100G)" << std::endl;
	std::cout << "0. Exit shop" << std::endl;
	std::cout << "=================" << std::endl;

}



void Item::RareCandy(Player& player)
{
	if (player.getmoney() < 500)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-500);
	player.LevelUP();
	std::cout << "Used RareCandy! EXP +100" << std::endl;
}

//--------------------------------------------------------------

void Item::BuyHPPotion(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.AddItem("HPPotion");  // 여기서 문자열을 직접 넣어줌
}

void Item::UseHPPotion(Player& player)
{
	if (player.HasItem("HPPotion"))    // 인벤토리에 있는지 확인
	{
		player.setcurrenthp(+20);      // 효과 적용
		player.RemoveItem("HPPotion"); // 인벤토리에서 제거
	}
	else
	{
		std::cout << "You don't have HPPotion!" << std::endl;
	}
}

//------------------------------------------------------------

void Item::BuyFHPPotion(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.AddItem("FHPPotion");
}

void Item::UseFHPPotion(Player& player)
{
	if (player.HasItem("FHPPotion"))
	{
		player.setcurrenthp(9999);    
		player.RemoveItem("FHPPotion");
	}
	else
	{
		std::cout << "You don't have FHPPotion!" << std::endl;
	}
}

//-------------------------------------------------------------

void Item::BuyMultiLens(Player& player)
{
	if (player.getmoney() < 200)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-200);
	player.AddItem("MultiLens");
}
/*
void Item::UseMultiLens(Player& player)
{
	if (player.HasItem("MultiLens"))    
	{
		player.setcurrenthp(+20);     
		player.RemoveItem("MultiLens");
	}
	else
	{
		std::cout << "You don't have MultiLens!" << std::endl;
	}
}
*/

//------------------------------------------------------------

void Item::BuyPowerPotion(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.AddItem("PowerPotion");  
}

void Item::UsePowerPotion(Player& player)
{
	if (player.HasItem("PowerPotion"))  
	{
		player.setattack(+20);
		player.RemoveItem("PowerPotion"); 
	}
	else
	{
		std::cout << "You don't have PowerPotion!" << std::endl;
	}
}

//-----------------------------------------------------------------

void Item::Buyrandomexp(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.AddItem("randomxep");
}

void Item::Userandomexp(Player& player)
{
	if (player.HasItem("randomexp"))
	{
		int EXP = rand() % 451 + 50;  // 50 ~ 500
		player.setexp(EXP);
		player.RemoveItem("randomexp");
		std::cout << "You got " << EXP << " EXP!" << std::endl;
	}

}

//-------------------------------------------------------------------------
void Item::Buyrandomgold(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	player.AddItem("randomgold");
}

void Item::Userandomgold(Player& player)
{
	if (player.HasItem("randomgold"))
	{
		int gold = rand() % 451 + 50;  // 50 ~ 500
		player.setmoney(gold);
		std::cout << "You got " << gold << " gold!" << std::endl;
		player.RemoveItem("randomgold");
	
	}
}
//-------------------------------------------------------------


/*
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
*/  

/*
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
*/

/*
void Item::MultiLens(Player& player)
{
	//공격이 한 번 더 반복되는 아이템
	//예상 구현
	//player.h에 protected로 bool 변수 extraAttack = false; 추가
	//player.h - public에 getter/setter 추가
	//  bool getExtraAttack() const { return extraAttack; }
	//  void setExtraAttack(bool val) { extraAttack = val; }

	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);
	//player.setExtraAttack(true); -> 미래 구현 제안
	std::cout << "MultiLens activated! Next attack will hit twice!" << std::endl;
}
*/
/*
void Item::PowerPotion(Player& player)
{
	if (player.getmoney() < 200)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-200);
	player.setattack(player.getattack() + 20);
	std::cout << "Power increased by 20!" << std::endl;
}
*/

/*
void Item::randomexp(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);

	int EXP = rand() % 451 + 50;  // 50 ~ 500
	player.setexp(EXP);
	std::cout << "You got " << EXP << " EXP!" << std::endl;

}


void Item::randomgold(Player& player)
{
	if (player.getmoney() < 100)
	{
		std::cout << "Not enough gold!" << std::endl;
		return;
	}
	player.setmoney(-100);

	int gold = rand() % 451 + 50;  // 50 ~ 500
	player.setmoney(gold);
	std::cout << "You got " << gold << " gold!" << std::endl;
}
*/





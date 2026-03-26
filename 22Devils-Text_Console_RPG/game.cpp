#include <iostream>
#include <cstdlib>
#include "game.h"
#include "Player.h"

Player* player = nullptr; 

void GameStart() {
	int choice;

	if (player == nullptr) {
		player = (new Player())->Selector();
	}

	while (true) {
		std::cout << "\n[Game Start]" << std::endl;
		std::cout << "1. Fight\n2. Shop\n3. Return\n4. Exit\n5. Player Stat\n";
		std::cout << "Choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: std::cout << "Fight started!\n"; break;
		case 2: GameShop(); break;
		case 3: return;
		case 4: exit(0);
		case 5: PlayerStat(); break;
		default: std::cout << "Invalid choice!\n";
		}
	}
}

void PlayerStat() {
	int back;

	std::cout << "\n[ Player Stat ]\n";

	if (player)
		player->ShowStatus();
	else
		std::cout << "No character selected!\n";

	std::cout << "\nPress 1 to go back: ";
	std::cin >> back;
}

void GameRule() {
	std::cout << "RPG Game\n";
}

void GameDeveloper() {
	std::cout << "Developers\n";
}

void GameShop() {
	int choice;

	while (true) {
		std::cout << "\n[ SHOP ]\n";
		std::cout << "1. RareCandy\n2. HPPotion\n3. HPPotion\n4. MultiLens\n5. Booster\n0. Back\n";
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 0) return;

		int q;
		std::cout << "How many (1-10): ";
		std::cin >> q;

		if (q < 1 || q > 10) {
			std::cout << "Enter 1~10\n";
			continue;
		}

		std::cout << "Purchased " << q << " item(s)\n";
	}
}

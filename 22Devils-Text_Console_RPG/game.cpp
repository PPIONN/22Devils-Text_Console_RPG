#include <iostream>
#include <cstdlib>
#include "game.h"
#include "Player.h"
#include "Item.h"

Player* player = nullptr; 

void GameStart() {
	int choice;

	if (player == nullptr) {
		player = (new Player())->Selector();
	}

	while (true) {
		std::system("cls");
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

	std::system("cls");

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
	Item item;

	std::system("cls");

	while (true) {
		std::cout << "\n[ SHOP ]\n";
		item.ShowAllItems();  
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 0) return;

		int confirm;

		switch (choice) {
		case 1:
			std::cout << "Do you want to purchase 1 RareCandy? (1: Yes / 0: No): ";
			std::cin >> confirm;
			if (confirm == 1 && player)
				item.RareCandy(*player);
			break;

		case 2:
			std::cout << "Do you want to purchase 1 HPPotion? (1: Yes / 0: No): ";
			std::cin >> confirm;
			if (confirm == 1 && player)
				item.BuyHPPotion(*player);
			break;

		case 3:
			std::cout << "Do you want to purchase 1 FHPPotion? (1: Yes / 0: No): ";
			std::cin >> confirm;
			if (confirm == 1 && player)
				item.FHPPotion(*player);
			break;

		case 4:
			std::cout << "Do you want to purchase 1 MultiLens? (1: Yes / 0: No): ";
			std::cin >> confirm;
			if (confirm == 1 && player)
				item.MultiLens(*player);
			break;


		default:
			std::cout << "Invalid choice!\n";
		}
	}
}

#include <iostream>
#include <cstdlib>
#include "game.h"

// Game Start
void GameStart() {
	int choice;

	while (true) {
		std::cout << "\n[Game Start]" << std::endl;
		std::cout << "1. Fight" << std::endl;
		std::cout << "2. Shop" << std::endl;
		std::cout << "3. Return to Main Menu" << std::endl;
		std::cout << "4. Exit Game" << std::endl;
		std::cout << "5. Player Stat" << std::endl;
		std::cout << "Choice: ";

		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input!" << std::endl;
			continue;
		}

		switch (choice) {
		case 1:
			std::cout << "Fight started!" << std::endl;
			break;
		case 2:
			GameShop(); // 🔥 Shop 연결
			break;
		case 3:
			std::cout << "Returning to main menu..." << std::endl;
			return;
		case 4:
			std::cout << "Exiting game..." << std::endl;
			std::exit(0);
		case 5:
			PlayerStat(); // 🔥 여기서만 사용
			break;
		default:
			std::cout << "Invalid choice!" << std::endl;
		}
	}
}

// Game Rule
void GameRule() {
	int back;
	std::cout << "\n[Game Rule]" << std::endl;
	std::cout << "This game is an RPG where you grow stronger through battles." << std::endl;
	std::cout << "Defeat enemies, level up, and collect money!" << std::endl;

	std::cout << "\nPlease input 1 to go back: ";
	std::cin >> back;
	while (back != 1) {
		std::cout << "Please input 1 to go back: ";
		std::cin >> back;
	}
}

// Game Developer
void GameDeveloper() {
	int back;
	std::cout << "\n[Game Developers]" << std::endl;
	std::cout << "1. O Chaeyul\n2. Shin Gunho\n3. Lee Hyunjun\n4. Lee Chaeho\n5. Bae Geonwoo\n6. Noh Yongsoo" << std::endl;

	std::cout << "\nPlease input 1 to go back: ";
	std::cin >> back;
	while (back != 1) {
		std::cout << "Please input 1 to go back: ";
		std::cin >> back;
	}
}

// Player Stat
void PlayerStat() {
	int back;

	std::cout << "\n[ Player Stat ]" << std::endl;
	std::cout << "Level: 1" << std::endl;
	std::cout << "HP: 100" << std::endl;
	std::cout << "Gold: 0" << std::endl;

	std::cout << "\nPress 1 to go back: ";
	std::cin >> back;
	while (back != 1) {
		std::cout << "Press 1 to go back: ";
		std::cin >> back;
	}
}

// Game Shop
void GameShop() {
	int choice;

	while (true) {
		std::cout << "\n[ S H O P ]" << std::endl;
		std::cout << "1. RareCandy\n";
		std::cout << "2. HPPotion\n";
		std::cout << "3. HPPotion\n";
		std::cout << "4. MultiLens\n";
		std::cout << "5. Booster\n";
		std::cout << "0. Back\n";
		std::cout << "Choice: ";

		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input!" << std::endl;
			continue;
		}

		if (choice == 0) {
			std::cout << "Returning..." << std::endl;
			return;
		}

		if (choice < 1 || choice > 5) {
			std::cout << "Invalid choice!" << std::endl;
			continue;
		}

		int quantity;
		std::cout << "How many would you like to purchase? (1-10): ";

		if (!(std::cin >> quantity) || quantity < 1 || quantity > 10) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please enter between 1 and 10." << std::endl;
			continue;
		}

		std::cout << "You purchased " << quantity << " item(s)!" << std::endl;
	}
}

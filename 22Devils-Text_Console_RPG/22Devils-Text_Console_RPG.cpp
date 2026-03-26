#include <iostream>
#include "game.h"

int main() {
	int choice;

	while (true) {
		std::cout << "\n===== GAME MENU =====" << std::endl;
		std::cout << "1. Game Start" << std::endl;
		std::cout << "2. Game Rule" << std::endl;
		std::cout << "3. Game End" << std::endl;
		std::cout << "4. Game Developer" << std::endl;
		std::cout << "Select menu: ";

		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input!" << std::endl;
			continue;
		}

		switch (choice) {
		case 1:
			GameStart();
			break;
		case 2:
			GameRule();
			break;
		case 3:
			std::cout << "Game End" << std::endl;
			return 0;
		case 4:
			GameDeveloper();
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
		}
	}
}

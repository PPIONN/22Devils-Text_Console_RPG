#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include"pokemon.h"
#include"gastly.h"

int main() {
	int choice;

	/*std::system("cls");

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
	}*/

	gastly* myGhost = new gastly(35, "고옹이");
	gastly* enermyGhost = new gastly(20, "패롱이");
	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";

	myGhost->levelup();std::cout << "\n"; // 레벨 차면 알아서 스킬 배움

	myGhost->ShowInfo();std::cout << "\n";

	enermyGhost->ShowInfo();std::cout << "\n";
	enermyGhost->selectattack(myGhost, 2);

	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";

	std::cout << "\n";
	myGhost->levelup();
	std::cout << "\n";
	enermyGhost->ShowInfo();
	std::cout << "\n";
	enermyGhost->selectattack(myGhost,2);
	std::cout << "\n";
	enermyGhost->ShowInfo();
	std::cout << "\n";
	myGhost->selectattack(enermyGhost, 2);
	std::cout << "\n";
	enermyGhost->ShowInfo();





}

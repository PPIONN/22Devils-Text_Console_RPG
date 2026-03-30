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

	gastly* myGhost = new gastly(35, "고옹이"); // 내 포켓몬은 // gastly* myGhost = new gastly(플레이어레벨, "별명"); // 이렇게 구현해주셈
	gastly* enermyGhost = new gastly(20, "패롱이"); // 적 포켓몬은 알잘딱깔센
	myGhost->ShowInfo(); std::cout << "\n"; 
	enermyGhost->ShowInfo(); std::cout << "\n";

	myGhost->levelup();std::cout << "\n"; // 레벨 차면 알아서 스킬 배움 // 4개 이상 배우고있는 상태면 한개 지우고 한개 배움

	myGhost->ShowInfo();std::cout << "\n"; // 대충 능력치 보여줌

	enermyGhost->ShowInfo();std::cout << "\n";
	enermyGhost->selectattack(myGhost, 2); // enermyGhost->selectattack(myGhost, 2); // 공격하려는포켓몬->selectattack(공격받는포켓몬,스킬쓰고싶은거) 스킬쓰고싶은거 = 0~3 까지

	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";

	std::cout << "\n";
	myGhost->levelup();
	std::cout << "\n";
	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";
	std::cout << "\n";
	enermyGhost->selectattack(myGhost,2);
	std::cout << "\n";
	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";
	std::cout << "\n";
	myGhost->selectattack(enermyGhost, 2);
	std::cout << "\n";
	myGhost->ShowInfo(); std::cout << "\n";
	enermyGhost->ShowInfo(); std::cout << "\n";





}

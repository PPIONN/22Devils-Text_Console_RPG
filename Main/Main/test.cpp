#include <iostream>
#include <string>
#include <ctime>   // 랜덤 설정을 위한 헤더
#include <cstdlib> // rand() 함수 사용을 위한 헤더

int main()
{
	// 랜덤 시드 설정 (매번 다른 포켓몬이 나오게 함)
	srand(time(NULL));

	//포켓몬 선택 창
	int choice;
	std::cout << "===== Character List =====" << std::endl;
	std::cout << "1. Charmander" << std::endl;
	std::cout << "2. Squirtle" << std::endl;
	std::cout << "3. Bulbasaur" << std::endl;
	std::cout << "4. Pikachu" << std::endl;
	std::cout << "Choose your character (1-4): ";


	//만약 1~4중 선택시 해당 포켓몬 선택
	if (!(std::cin >> choice)) return 0;

	if (choice == 1) std::cout << "\nYou chose Charmander!" << std::endl;
	else if (choice == 2) std::cout << "\nYou chose Squirtle!" << std::endl;
	else if (choice == 3) std::cout << "\nYou chose Bulbasaur!" << std::endl;
	else if (choice == 4) std::cout << "\nYou chose Pikachu!" << std::endl;
	else {
		std::cout << "\nInvalid choice. Game Over." << std::endl;
		return 0;
	}

	//정말 이 포켓몬으로 하시겠습니까?
	//int startConfirm - 게임 시작 변수 (1,2중 입력)
	std::cout << "\nWould you like to start your adventure with this Pokemon? (1. Yes / 2. No): ";
	int startConfirm;
	std::cin >> startConfirm;

	//포켓몬 고를시 모험 시작
	if (startConfirm == 1) {
		std::cout << "\nStarting the adventure!" << std::endl;
		std::cout << "......" << std::endl;
		std::cout << "......" << std::endl;
	
	}
	else {
		std::cout << "\nYou decided to stay home." << std::endl;
	}

	//wildPokemons 배열
	std::string wildPokemons[] = { "Psyduck", "Gastly", "Wobbuffet", "Magikarp" };
	int randomIndex = rand() % 4; // 0~3 사이의 숫자 랜덤 생성

	std::cout << "A wild Pokemon" << wildPokemons[randomIndex] << " appeared!" << std::endl;

	std::cout << "...... (Battle in progress) ......" << std::endl;

	// 2. 승리 및 보상 출력 
	std::cout << "\nYou defeated the wild " << wildPokemons[randomIndex] << "!" << std::endl;

//아이템 변수 선언 int Hppotion


	// 랜덤 보상 수치 설정 
	int gold = 100 + (rand() % 50); // 100~149 골드
	int exp = 50 + (rand() % 20);   // 50~69 경험치

	std::cout << "You obtained " << gold << " Gold!" << std::endl;
	std::cout << "You obtained " << exp << " Experience!" << std::endl;

	std::cout << "\n---------- SHOP ----------" << std::endl;
		std::cout << "Please select an item to purchase." << std::endl;
		std::cout << "1. Potion" << std::endl;
		std::cout << "2. Pokeball" << std::endl;
		std::cout << "3. Great Ball" << std::endl;
		std::cout << "4. Antidote" << std::endl;
		std::cout << "5. Revive" << std::endl;
		std::cout << "6. Rare Candy" << std::endl;
		std::cout << "7. Skip (Exit Shop)" << std::endl;
		std::cout << "--------------------------" << std::endl;
		std::cout << "Select (1-7): ";

		int itemChoice;
		std::cin >> itemChoice;

		if (itemChoice >= 1 && itemChoice <= 6) {
			std::string items[] = { "Potion", "Pokeball", "Great Ball", "Antidote", "Revive", "Rare Candy" };
			std::cout << "\nYou purchased a " << items[itemChoice - 1] << "!" << std::endl;
		}
		else if (itemChoice == 7) {
			std::cout << "\nYou skipped the shop." << std::endl;
		}
		else {
			std::cout << "\nInvalid input. Leaving the shop." << std::endl;
		}



	// ---------------------------

	std::cout << "\nPress Enter to exit...";
	std::cin.ignore();
	std::cin.get();

	return 0;
}

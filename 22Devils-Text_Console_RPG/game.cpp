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
        std::cout << "Choice: ";

        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Fight started!" << std::endl;
            break;
        case 2:
            std::cout << "Entering shop..." << std::endl;
            break;
        case 3:
            std::cout << "Returning to main menu..." << std::endl;
            return; // main으로 돌아감
        case 4:
            std::cout << "Exiting game..." << std::endl;
            std::exit(0); // 프로그램 종료
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
    std::cout << "\nPlease input 1 to go back: " << std::endl;
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
    std::cout << "\nPlease input 1 to go back: " << std::endl;
    std::cin >> back;
    while (back != 1) {
        std::cout << "Please input 1 to go back: ";
        std::cin >> back;
    }
}
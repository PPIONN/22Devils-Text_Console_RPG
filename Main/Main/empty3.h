//신건호
//이현준
//오채율
//노용수
//
//배건우
//class Poketmon{
//    
//}
//class Player { 
//    
//}
//class 고옹이 {
//
//}
//class 고옹이 : public Poketmon{
//
//}
//class 고옹이 : public Poketmon{
//
//}
//class 고옹이 : public Poketmon{
//
//}
//class 고옹이 : public Poketmon{
//
//}
//class 고옹이 : public Poketmon{
//
//}
//
// 
//// <- 요렇게 만들건지 아니면 따로 따로해서 배열같은걸로 호출할건지 그게 궁금했습니다
//// "포켓몬" 이라 불러주세요 고오스클래스만들면서 -> 포켓몬클래스(부모가 되는)에서 만들 수 있는게 굉장히 많았거든요.
//// "플레이어"클래스 <- 플레이어는 포켓몬을 가지고있어야되고 플레이어 클래스는 포켓몬 클래스를 자식으로 둘건가? 아니면 플레이어에 따로 배열을 만들어서
////  포켓몬을 배열에 저장하고 꺼내낼건가.ㄹㅇㄴ(o)ㄹㅇㄹ
//
//
//
//// 포켓몬한테도 따로 레벨을 주고 그걸 레벨업 시켰음 1.
//// 포켓몬 레벨은 있긴한데 플레이어의 레벨을 따라간다. 
////  플레이어 레벨이 1이면 포켓몬레벨은 자동으로 1이되고
//// 플레이어의 경험치가 늘어서 플레이어가 레벨업을하면 포켓몬들도 -> 다 레벨업 2로 될수있께
//// 플레이어가 만약 15레벨에 -> 잡는다(구현?) -> 그 포켓몬 레벨이 15로 될수있게   2.
//// 
//
//
//포켓몬 << 플레이어 캐릭터든, 몬스터든, 
//
//포켓몬이 1~12있다. 
//
//1번포켓몬을 플레이어가 사용하겠다.
//
//1번부터 12번까지 
//
//
//
////main.cpp
//#include <iostream>
//#include "game.h"
//
//int main() {
//    int choice;
//
//    while (true) {
//        std::cout << "\n===== GAME MENU =====" << std::endl;
//        std::cout << "1. Game Start" << std::endl;
//        std::cout << "2. Game Rule" << std::endl;
//        std::cout << "3. Game End" << std::endl;
//        std::cout << "4. Game Developer" << std::endl;
//        std::cout << "Select menu: ";
//
//        std::cin >> choice;
//        std::cin.ignore();
//
//        switch (choice) {
//        case 1:
//            GameStart();
//            break;
//        case 2:
//            GameRule();
//            break;
//        case 3:
//            std::cout << "Game End" << std::endl;
//            return 0;
//        case 4:
//            GameDeveloper();
//            break;
//        default:
//            std::cout << "Invalid input! Please input it again." << std::endl;
//        }
//    }
//
//    return 0;
//}
//
//
////gmae.cpp
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include "game.h"
//
//// ------------------ Pokemon 함수 정의 ------------------
//Pokemon::Pokemon(std::string n, int h, int a)
//    : name(n), hp(h), maxHp(h), attackPower(a), level(1) {
//}
//
//bool Pokemon::isAlive() {
//    return hp > 0;
//}
//
//void Pokemon::attack(Pokemon& target) {
//    int damage = attackPower;
//    target.hp -= damage;
//    if (target.hp < 0) target.hp = 0;
//
//    std::cout << name << " attacks " << target.name
//        << " for " << damage << " damage!" << std::endl;
//    std::cout << target.name << "'s HP: " << target.hp << " / " << target.maxHp << std::endl;
//}
//
//void Pokemon::levelUp() {
//    level++;
//    maxHp += 10;
//    hp = maxHp;
//    attackPower += 2;
//
//    std::cout << name << " leveled up! Level: " << level
//        << ", HP: " << maxHp << ", Attack: " << attackPower << std::endl;
//}
//
//// ------------------ HP 표시 ------------------
//void DisplayHP(Pokemon& p) {
//    int totalBars = 10;
//    int filledBars = (p.hp * totalBars) / p.maxHp;
//    std::cout << "HP: ";
//    for (int i = 0; i < filledBars; i++) std::cout << "#";
//    for (int i = filledBars; i < totalBars; i++) std::cout << "-";
//    std::cout << " (" << p.hp << " / " << p.maxHp << ")" << std::endl;
//}
//
//// ------------------ 전투 ------------------
//void Battle(Pokemon& player, Pokemon& enemy) {
//    while (player.isAlive() && enemy.isAlive()) {
//        std::system("cls"); // 화면 초기화
//
//        std::cout << enemy.name << " Lv" << enemy.level << std::endl;
//        DisplayHP(enemy);
//        std::cout << "====================" << std::endl;
//        std::cout << player.name << " Lv" << player.level << std::endl;
//        DisplayHP(player);
//
//        std::cout << "\nChoose action: 1. Attack  2. Run" << std::endl;
//        int choice;
//        std::cin >> choice;
//        std::cin.ignore();
//
//        if (choice == 1) {
//            player.attack(enemy);
//            if (!enemy.isAlive()) {
//                std::cout << enemy.name << " has fainted! You win!" << std::endl;
//                player.levelUp();
//                std::cout << "Press enter to continue...";
//                std::cin.get();
//                break;
//            }
//            enemy.attack(player);
//            if (!player.isAlive()) {
//                std::cout << player.name << " has fainted! You lose!" << std::endl;
//                std::cout << "Press enter to continue...";
//                std::cin.get();
//                break;
//            }
//            std::cout << "Press enter to continue...";
//            std::cin.get();
//        }
//        else if (choice == 2) {
//            std::cout << "You ran away safely!" << std::endl;
//            std::cout << "Press enter to continue...";
//            std::cin.get();
//            break;
//        }
//        else {
//            std::cout << "Invalid choice! Try again." << std::endl;
//            std::cout << "Press enter to continue...";
//            std::cin.get();
//        }
//    }
//}
//
//// ------------------ 게임 시작 ------------------
//void GameStart() {
//    std::srand(static_cast<unsigned int>(std::time(0)));
//
//    // 4개 포켓몬 생성
//    Pokemon pokemonList[] = {
//        Pokemon("Pikachu", 50, 7),
//        Pokemon("Charmander", 45, 6),
//        Pokemon("Squirtle", 55, 5),
//        Pokemon("Bulbasaur", 48, 6)
//    };
//
//    // 플레이어 포켓몬 선택
//    int choice = 0;
//    while (true) {
//        std::cout << "\nChoose your Pokemon:\n";
//        for (int i = 0; i < 4; i++)
//            std::cout << i + 1 << ". " << pokemonList[i].name << "\n";
//        std::cout << "Choice: ";
//        std::cin >> choice;
//        if (choice >= 1 && choice <= 4) break;
//        std::cout << "Invalid choice! Try again.\n";
//    }
//
//    Pokemon player = pokemonList[choice - 1];
//    std::cout << "You chose " << player.name << "!\n";
//
//    // 게임 메뉴
//    while (true) {
//        std::cout << "\n[Game Menu]\n1. Fight\n2. Return to Main Menu\nChoice: ";
//        int menu;
//        std::cin >> menu;
//
//        if (menu == 1) {
//            // 상대 포켓몬 랜덤 선택 (플레이어 제외)
//            int enemyIndex;
//            do {
//                enemyIndex = std::rand() % 4;
//            } while (enemyIndex == (choice - 1));
//
//            Pokemon enemy = pokemonList[enemyIndex];
//            std::cout << "A wild " << enemy.name << " appeared!\n";
//
//            Battle(player, enemy);
//        }
//        else if (menu == 2) {
//            return; // 메인 메뉴로
//        }
//        else {
//            std::cout << "Invalid choice!\n";
//        }
//    }
//}
//
//// ------------------ 게임 규칙 ------------------
//void GameRule() {
//    int back;
//    std::cout << "\n[Game Rule]" << std::endl;
//    std::cout << "This game is an RPG where you grow stronger through battles." << std::endl;
//    std::cout << "Defeat enemies to gain levels and increase your HP and Attack!" << std::endl;
//    std::cout << "\nPlease input 1 to go back: ";
//    std::cin >> back;
//    while (back != 1) {
//        std::cout << "Please input 1 to go back: ";
//        std::cin >> back;
//    }
//}
//
//// ------------------ 개발자 정보 ------------------
//void GameDeveloper() {
//    int back;
//    std::cout << "\n[Game Developers]" << std::endl;
//    std::cout << "1. O Chaeyul\n2. Shin Gunho\n3. Lee Hyunjun\n4. Lee Chaeho\n5. Bae Geonwoo\n6. Noh Yongsoo" << std::endl;
//    std::cout << "\nPlease input 1 to go back: ";
//    std::cin >> back;
//    while (back != 1) {
//        std::cout << "Please input 1 to go back: ";
//        std::cin >> back;
//    }
//}
//
//game.h
//#pragma once
//#include <string>
//
//// ------------------ Pokemon 클래스 ------------------
//class Pokemon {
//public:
//    std::string name;
//    int hp;
//    int maxHp;
//    int attackPower;
//    int level;
//
//    Pokemon(std::string n, int h, int a);
//    bool isAlive();
//    void attack(Pokemon& target);
//    void levelUp();
//};
//
//// ------------------ 함수 선언 ------------------
//void GameStart();
//void GameRule();
//void GameDeveloper();
//void Battle(Pokemon& player, Pokemon& enemy);
//void DisplayHP(Pokemon& p);
//
//
//-------------------------------------------------
//class Pokemon {
//public:
//    std::string name;
//    int hp;
//    int maxHp;
//    int attackPower;
//    int level;
//
//    Pokemon(std::string n, int h, int a, int lvl = 1)
//        : name(n), hp(h), maxHp(h), attackPower(a), level(lvl) {}
//
//    bool isAlive() { return hp > 0; }
//
//    void attack(Pokemon& target) {
//        target.hp -= attackPower;
//        if (target.hp < 0) target.hp = 0;
//    }
//
//    void levelUp() {
//        level++;
//        maxHp += 10;
//        hp = maxHp;
//        attackPower += 2;
//    }
//};
//
//class Player : public Pokemon {
//public:
//    int money;
//    int exp;
//
//    Player(std::string n, int h, int a, int lvl = 1)
//        : Pokemon(n, h, a, lvl), money(0), exp(0) {}
//
//    void gainExp(int e) {
//        exp += e;
//        if (exp >= 100) {   
//            exp -= 100;
//            levelUp();       
//            money += 50;     
//        }
//    }
//};
//
//class Monster : public Pokemon {
//public:
//    std::string type;
//
//    Monster(std::string n, int h, int a, std::string t) : Pokemon(n, h, a), type(t) {}
//    void roar();
//};
//
//Poketmon allPoketmon[12] = {
//    Pokemon("Pikachu", 50, 7),
//    Pokemon("Charmander", 45, 6),
//    Pokemon("Squirtle", 55, 5),
//    Pokemon("Bulbasaur", 48, 6),
//    Pokemon("Eevee", 50, 6),
//    Pokemon("Jigglypuff", 60, 4),
//    Pokemon("Snorlax", 80, 8),
//    Pokemon("Gengar", 55, 9),
//    Pokemon("Mewtwo", 70, 12),
//    Pokemon("Vulpix", 40, 5),
//    Pokemon("Oddish", 45, 4),
//    Pokemon("Psyduck", 50, 6)
//}

#include "Poketmon.h"
#include "Player.h"
#include "Monster.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(std::time(0));

    std::vector<Poketmon> poketmonList = {
        Poketmon("Charmander", 7, 100, 50),
        Poketmon("Squirtle", 7, 100, 45),
        Poketmon("Bulbasaur", 7, 100, 48),
        Poketmon("Pikachu", 7, 100, 55)
    };

    std::cout << "Select your Poketmon:" << std::endl;
    for (int i = 0; i < poketmonList.size(); i++) {
        std::cout << i + 1 << ". " << poketmonList[i].GetName() << std::endl;
    }

    int choice;
    std::cin >> choice;
    choice -= 1;

    Player player(poketmonList[choice]);
    int randIndex = std::rand() % poketmonList.size();
    Monster monster(poketmonList[randIndex]);

    player.ShowPoketmon();
    monster.ShowPoketmon();

    std::cout << "\nAttack Demo:" << std::endl;
    player.Attack(player);
    monster.Attack(monster);

    std::cout << "\nAfter Level Up:" << std::endl;
    poketmonList[choice].SetLevel(10);
    player.ShowPoketmon();

    return 0;
}
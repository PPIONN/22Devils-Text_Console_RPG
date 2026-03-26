#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct Champion {
    std::string name;
    int hp;
    int power;
    int defense;
};

int main()
{
    std::srand(std::time(NULL)); 

    Champion champs[] =
    {
        {"Pikachu", 50, 20, 10},
        {"Charmander", 100, 15, 20},
        {"Squirtle", 80, 25, 15},
        {"Bulbasaur", 60, 30, 5},
    };

    int size = sizeof(champs) / sizeof(champs[0]);

    int randomIndex = std::rand() % size;

    Champion picked = champs[randomIndex];

    std::cout << "champion!\n";
    std::cout << "nickname: " << picked.name << std::endl;
    std::cout << "HP: " << picked.hp << std::endl;
    std::cout << "power: " << picked.power << std::endl;
    std::cout << "defense: " << picked.defense << std::endl;

    return 0;
}
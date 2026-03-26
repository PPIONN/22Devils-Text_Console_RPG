#include "Monster.h"
#include <iostream>

Monster::Monster(const Poketmon& p) : poketmon(p) {}

void Monster::ShowPoketmon() const {
    std::cout << "[Monster] ";
    poketmon.ShowInfo();
}

void Monster::Attack(Monster& target) {
    int damage = poketmon.GetPower();
    std::cout << "[Monster Attack] " << poketmon.GetName()
        << " deals damage: " << damage << std::endl;
}
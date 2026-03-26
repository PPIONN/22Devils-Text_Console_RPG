#include "Player.h"
#include <iostream>

Player::Player(const Poketmon& p) : poketmon(p) {}

void Player::ShowPoketmon() const {
    std::cout << "[Player] ";
    poketmon.ShowInfo();
}

void Player::Attack(Player& target) {
    int damage = poketmon.GetPower();
    std::cout << "[Player Attack] " << poketmon.GetName()
        << " deals damage: " << damage << std::endl;
}
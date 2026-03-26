#pragma once
#include "Poketmon.h"

class Player {
private:
    Poketmon poketmon;

public:
    Player(const Poketmon& p);
    void ShowPoketmon() const;
    void Attack(Player& target);
};
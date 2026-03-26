#pragma once
#include "Poketmon.h"

class Monster {
private:
    Poketmon poketmon;

public:
    Monster(const Poketmon& p);
    void ShowPoketmon() const;
    void Attack(Monster& target);
};
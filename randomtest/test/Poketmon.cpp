#include "Poketmon.h"

Poketmon::Poketmon(const std::string& n, int l, int h, int p)
    : name(n), level(l), hp(h), power(p), baseHP(h), basePower(p) {
}

std::string Poketmon::GetName() const { return name; }
int Poketmon::GetLevel() const { return level; }
int Poketmon::GetHP() const { return hp; }
int Poketmon::GetPower() const { return power; }

void Poketmon::SetLevel(int l) {
    level = l;
    hp = baseHP + (level - 1) * 10;
    power = basePower + (level - 1) * 5;
}

void Poketmon::ShowInfo() const {
    std::cout << name << " Level " << level
        << " HP " << hp
        << " Power " << power << std::endl;
}
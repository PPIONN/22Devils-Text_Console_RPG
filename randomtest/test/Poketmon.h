#pragma once
#include <string>
#include <iostream>

class Poketmon {
private:
    std::string name;
    int level;
    int hp;
    int power;
    int baseHP;
    int basePower;

public:
    Poketmon(const std::string& n, int l, int h, int p);
    std::string GetName() const;
    int GetLevel() const;
    int GetHP() const;
    int GetPower() const;
    void SetLevel(int l);
    void ShowInfo() const;
};
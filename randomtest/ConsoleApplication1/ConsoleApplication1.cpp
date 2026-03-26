// hyeonjoon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Gastly {
public:
    void levelscale(int level) {
        sethp(level);
        setattack(level);
        setdefense(level);
        setspecailAttack(level);
        setspecailDefense(level);
        setspeed(level);
    }

    int getSpecailDefense() const { 
        return specailDefense;
    }

private:
    void sethp(int level) { hp += hpGrowth * level; }
    void setattack(int level) { attack += attackGrowth * level; }
    void setdefense(int level) { defense = defenseGrowth * level; }
    void setspecailAttack(int level) { specailAttack = specailAttackGrowth * level; }
    void setspecailDefense(int level) { specailDefense = specailDefenseGrowth * level; }
    void setspeed(int level) { speed = speedGrowth * level; }

    int hp = 11;
    int attack = 6;
    int defense = 5;
    int specailAttack = 7;
    int specailDefense = 6;
    int speed = 6;

    int hpGrowth = 1;
    int attackGrowth = 1;
    int defenseGrowth = 1;
    int specailAttackGrowth = 3;
    int specailDefenseGrowth = 1;
    int speedGrowth = 2;
};

int main()
{
    Gastly g;
    int level = 5; // 원하는 레벨
    g.levelscale(level);

    std::cout << "Gastly's Special Defense at level " << level << " is "
        << g.getSpecailDefense() << std::endl;

    return 0;
}
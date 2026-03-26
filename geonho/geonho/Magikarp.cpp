//잉어킹

class Magikarp { // 잉어킹

public:


    void levelscale(int level) { // 레벨을 받아와서 레벨에 따른 스텟을 계산함
        sethp(level);
        setattack(level);
        setdefense(level);
        setspecailAttack(level);
        setspecailDefense(level);
        setspeed(level);
    }

    void sethp(int level) {
        hp += hpGrowth * level;
    }
    void setattack(int level) {
        attack += attackGrowth * level;
    }
    void setdefense(int level) {
        defense = defenseGrowth * level;
    }
    void setspecailAttack(int level) {
        specailAttack = specailAttackGrowth * level;
    }
    void setspecailDefense(int level) {
        specailDefense = specailDefenseGrowth * level;
    }
    void setspeed(int level) {
        speed = speedGrowth * level;
    }



private:
    int hp = 10;
    int attack = 5;
    int defense = 5;
    int specailAttack = 5;
    int specailDefense = 5;
    int speed = 5;
    int level = 0;
    int exp;

    float hpGrowth = 1.71;
    float attackGrowth = 0.51;
    float defenseGrowth = 1.41;
    float specailAttackGrowth = 0.61;
    float specailDefenseGrowth = 0.71;
    float speedGrowth = 1.91;
    std::string name = "Magikarp";


};
int main()
{

    return 0;
}

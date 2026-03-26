//고라파덕

class Psyduck { // 고라파덕

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


    //100레벨스텟-0레벨스텟)/100=레벨당 상승스텟.
private:
    int hp = 10;
    int attack = 5;
    int defense = 5;
    int specailAttack = 5;
    int specailDefense = 5;
    int speed = 5;
    int level = 0;
    int exp;

    float hpGrowth = 2.31;
    float attackGrowth = 1.35;
    float defenseGrowth = 1.27;
    float specailAttackGrowth = 1.61;
    float specailDefenseGrowth = 1.31;
    float speedGrowth = 1.41;
    std::string name = "Psyduck";


};
int main()
{

    return 0;
}

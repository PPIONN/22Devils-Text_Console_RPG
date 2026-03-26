// hyeonjoon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



class pokemon {


};
class Gastly { // 고오스

public:

    Gastly(int level) { levelscale(level); } // 생성자에 레벨을 매개변수로 넣어서 능력치 조정
    ~Gastly() {};
    void levelscale(int level) { // 레벨을 받아와서 레벨에 따른 스텟을 계산함
        sethp(level);
        setattack(level);
        setdefense(level);
        setspecailAttack(level);
        setspecailDefense(level);
        setspeed(level);
    }
    void levelup() { // 레벨업 시 레벨을 1 올려주고 레벨 및 스탯 출력
        setlevel(); 
        levelscale(1);
 
        std::cout << name << " grew to LV. " << getlevel() << " !" << std::endl;
        std::cout << "|| HP : " << gethp() << " || Attack : " << getattack() << " || Defense : " << getdefense() << " || SpecailAttack : " << getspecailAttack() << " || SpecailDefense : " << getspecailDefense() << " || Speed : " << getspeed() << std::endl;

    }
    void expgain() { // 적 포켓몬 처치시 경험치 획득 공식 추후 수정 예정

        //double part1 = (baseExp * enemyLevel) / (5.0 * share);

        //double part2 = (2.0 * enemyLevel + 10.0) /
        //    (enemyLevel + myLevel + 10.0);

        //double result = part1 * (pow(part2, 2.5) + 1.0);

        //result *= bonus;
    }

    void sethp(int level) {
        hp += hpGrowth * level;
    }
    void setattack(int level) {
        attack += attackGrowth * level;
    }
    void setdefense(int level) {
        defense += defenseGrowth * level;
    }
    void setspecailAttack(int level) {
        specailAttack += specailAttackGrowth * level;
    }
    void setspecailDefense(int level) {
        specailDefense += specailDefenseGrowth * level;
    }
    void setspeed(int level) {
        speed += speedGrowth * level;
    }
    void setlevel() {
        level += 1;
    }

    int gethp() {
        return (int)hp;
    }
    int getattack() {
        return (int)attack;
    }
    int getdefense() {
        return (int)defense;
    }
    int getspecailAttack() {
        return (int)specailAttack;
    }
    int getspecailDefense() {
        return (int)specailDefense ;
    }
    int getspeed() {
        return (int)speed;
    }

    int getlevel() {
        return level;
    }




private:
    float hp = 10.0f;
    float attack = 5.0f;
    float defense = 5.0f;
    float specailAttack = 5.0f;
    float specailDefense = 5.0f;
    float speed = 5.0f;
    int level = 1;
    int exp = 19;

    float hpGrowth = 1.95f;
    float attackGrowth = 1.01f;
    float defenseGrowth = 0.91f;
    float specailAttackGrowth = 2.31f;
    float specailDefenseGrowth = 1.91f;
    float speedGrowth = 1.91;
    std::string name = "Gastly";
    std::string personality;


};
int main()
{
    Gastly Gastly(10);
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();



    return 0;
}


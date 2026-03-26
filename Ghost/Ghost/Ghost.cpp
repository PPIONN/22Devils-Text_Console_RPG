// hyeonjoon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// 
#include <iostream>
#include <vector>
class pokemon {


};
struct Skill
{
    std::string name;
    std::string type;
    std::string category;
    int power;
    int accuracy;
    int pp;
    int level;
};

class Gastly { // 고오스

public:

    Gastly(int level) { // 레벨인자 받아오기
        newpokescale(level); //레벨에 맞는 스텟을 가져옴
        updateSkills(); // 레벨에 맞는 기술을 가져옴
    }

    ~Gastly() {};
    void newpokescale(int level) { // 포켓몬 출현 시 레벨에 따른 스텟을 계산함
        setlevel(level);
        sethp(level);
        setattack(level);
        setdefense(level);
        setspecailAttack(level);
        setspecailDefense(level);
        setspeed(level);
    }
    void levelscale(int level) { // 레벨업 시 올라갈 스텟을 계산함
        sethp(level);
        setattack(level);
        setdefense(level);
        setspecailAttack(level);
        setspecailDefense(level);
        setspeed(level);
    }

    void levelup() { // 레벨업 시 레벨을 1 올려주고 레벨 및 스탯 출력
        setlevel(getlevel() + 1);
        levelscale(1);

        std::cout << name << " grew to LV. " << getlevel() << " !" << std::endl;
        std::cout << "|| HP : " << gethp() << " || Attack : " << getattack() << " || Defense : " << getdefense() << " || SpecailAttack : " << getspecailAttack() << " || SpecailDefense : " << getspecailDefense() << " || Speed : " << getspeed() << std::endl;

    }
    void updateSkills()
    {
        currentSkills.clear();

        for (auto& skill : learnableSkills)
        {
            if (skill.level <= getlevel())
            {
                currentSkills.push_back(skill);

                // 4개 초과하면 가장 오래된 기술 삭제
                if (currentSkills.size() > 4)
                {
                    currentSkills.erase(currentSkills.begin());
                }
            }
        }
    }
    void removeSkill(int index) // 플레이어가 원하는 인자값으로 기술지우게 하기 index = 0 ~ 3
    {
        if (index < 0 || index >= currentSkills.size())
        {
            std::cout << "잘못된 인덱스입니다." << std::endl;
            return;
        }

        currentSkills.erase(currentSkills.begin() + index);
    }

    void expgain() { // 적 포켓몬 처치시 경험치 획득 공식 추후 수정 예정

        //double part1 = (baseExp * enemyLevel) / (5.0 * share);

        //double part2 = (2.0 * enemyLevel + 10.0) /
        //    (enemyLevel + myLevel + 10.0);

        //double result = part1 * (pow(part2, 2.5) + 1.0);

        //result *= bonus;
    }

    void sethp(int level) { // 레벨업을 상정하고 만든 능력치 set. 
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
    void setlevel(int level) {
        this->level = level;
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
        return (int)specailDefense;
    }
    int getspeed() {
        return (int)speed;
    }

    int getlevel() {
        return level;
    }


    void printskill() {
        std::cout << "Current Skills:" << std::endl;
        for (size_t i = 0; i < currentSkills.size(); ++i) {
            std::cout << i + 1 << ". " << currentSkills[i].name << " (Type: " << currentSkills[i].type
                << ", Category: " << currentSkills[i].category
                << ", Power: " << currentSkills[i].power
                << ", Accuracy: " << currentSkills[i].accuracy
                << ", PP: " << currentSkills[i].pp
                << ", Level Required: " << currentSkills[i].level
                << ")" << std::endl;
        }
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
    std::vector<Skill> learnableSkills = { { "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
    { "Lick", "Ghost", "Physical", 20, 100, 30, 0 },
    { "Spite", "Ghost", "Status", 0, 100, 10, 5 },
    { "Mean Look", "Normal", "Status", 0, -1, 5, 8 },
    { "Curse", "Unknown", "Status", 0, -1, 10, 12 },
    { "Night Shade", "Ghost", "Special", 0, 100, 15, 15 },
    { "Confuse Ray", "Ghost", "Status", 0, 100, 10, 19 },
    { "Sucker Punch", "Dark", "Physical", 80, 100, 5, 22 },
    { "Payback", "Dark", "Physical", 50, 100, 10, 26 },
    { "Shadow Ball", "Ghost", "Special", 80, 100, 15, 29 },
    { "Dream Eater", "Psychic", "Special", 100, 100, 15, 33 },
    { "Dark Pulse", "Dark", "Special", 80, 100, 15, 36 },
    { "Destiny Bond", "Ghost", "Status", 0, -1, 5, 40 },
    { "Nightmare", "Ghost", "Status", 0, -1, 15, 43 } };
    std::vector<Skill> currentSkills;   // 현재 기술 (최대 4개)

};




class Haunter : public Gastly {



};
int main()
{


    Gastly Gastly(20);
    Gastly.levelup();
    Gastly.levelup();
    Gastly.levelup();

    Gastly.printskill();



    return 0;
}


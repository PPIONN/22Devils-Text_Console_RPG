#pragma once
#include <string>
#include <vector>
// 포켓몬 클래스가 할수있는일 :
// 1. 포켓몬은 플레이어의 레벨을 따라간다. 능력치또한 레벨에 맞게 조정된다.






struct Skill // 포켓몬이 가지는 스킬
{
	std::string name; // 스킬이름
	std::string type; // 스킬 타입
	std::string category; // 스킬이 공격기술인지 변화기술(능력떨구기)인지 판별
	int power; // 스킬 대미지
	int accuracy; // 스킬 명중률
	int pp; // 스킬 사용 개수
	int level; // 해당 레벨 달성시 스킬 획득
};


class pokemon {
public:
	pokemon() : level(1), hp(0), maxhp(0), name("Unknown") {}
	virtual ~pokemon() {}

	// 생성자속에서 해볼만한 일
	void newpokescale(const int nowlevel); // 적, 우리 포켓몬 레벨에 따른 능력치조정
	void levelscale(const int nowlevel); // 플레이어의 레벨을 받아 포켓몬 스텟 조정
	void updateSkills(); // 포켓몬 레벨업시 스킬추가 혹은 4개 이상 소지면 삭제 후 스킬추가함
	void newSkills(const int index); // 포켓몬 생성시 자동으로 스킬 들어가게해줌

	void warstat(); // 전투스탯

	void levelup();



	inline void levelhp(const int level) { // 레벨업을 상정하고 만든 능력치 set. 
		hp += hpGrowth * level;
	}
	inline void levelattack(const int level) {
		attack += attackGrowth * level;
	}
	inline void leveldefense(const int level) {
		defense += defenseGrowth * level;
	}
	inline void levelspecialAttack(const int level) {
		specialAttack += specialAttackGrowth * level;
	}
	inline void levelspecialDefense(const int level) {
		specialDefense += specialDefenseGrowth * level;
	}
	inline void levelspeed(const int level) {
		speed += speedGrowth * level;
	}

	inline void setname(const std::string& name) { // 일반적인 set get 함수
		this->name = name;
	};
	inline void setrealname(const std::string& realname) {
		this->realname = realname;
	};
	inline void setlevel(const int level) {
		this->level = level;
	}
	inline void sethp(const int hp) {
		this->hp = hp;
	}
	inline void setattack(const int attack) {
		this->attack = attack;
	}
	inline void setdefense(const int defense) {
		this->defense = defense;
	}
	inline void setspecialAttack(const int specialAttack) {
		this->specialAttack = specialAttack;
	}
	inline void setspecialDefense(const int specialDefense) {
		this->specialDefense = specialDefense;
	}
	inline void setspeed(const int speed) {
		this->speed = speed;
	}

	inline int gethp() const {
		return static_cast<int>(hp);
	}
	inline int getattack() const {
		return static_cast<int>(attack);
	}
	inline int getdefense() const {
		return static_cast<int>(defense);
	}
	inline int getspecialAttack() const {
		return static_cast<int>(specialAttack);
	}
	inline int getspecialDefense() const {
		return static_cast<int>(specialDefense);
	}
	inline int getspeed() const {
		return static_cast<int>(speed);
	}

	inline int getlevel() const {
		return level;
	}


	//void selectattack(pokemon* poke, int index) {
	//	Skill& selected = currentSkills[index];
	//	//std::string sName = selected.name;   // 스킬 이름 (예: "Lick")
	//	//int sPower = selected.power;         // 위력 (예: 20)
	//	//std::string sCategory = selected.category; // 물리/특수/변화
	//	int randomNumber = rand() % 100; // 난수 생성
	//	if (selected.category == "Physical") {
	//		// 물리 공격 로직
	//		if (randomNumber < selected.accuracy) {
	//			// a가 60이면 0~59까지의 숫자가 나왔을 때 실행됨 (정확히 60%)
	//			std::cout << name <<"은 " << selected.name<<"" << std::endl;
	//		}
	//		else {
	//			std::cout << "기술이 빗나갔습니다..." << std::endl;
	//		}
	//	}
	//	else if (selected.category == "Special") {
	//		// 특수 공격 로직
	//	}
	//	else if (selected.category == "Status") { 
	//		// 변화기 로직
	//	}
	//}

	//void ShowInfo() const;



protected:
	std::string name;//포켓몬 별명
	std::string realname; //포켓몬 고유 이름
	float maxhp;
	float hp; // 기본 능력치
	float attack;
	float defense;
	float specialAttack;
	float specialDefense;
	float speed;
	int level;
	int exp;

	float warattack; // 전투시 변환시켜줄 능력치
	float wardefense;
	float warspecialAttack;
	float warspecialDefense;
	float warspeed;

	float hpGrowth; // 포켓몬이 가지는 레벨업 시 성장 능력치 수치
	float attackGrowth;
	float defenseGrowth;
	float specialAttackGrowth;
	float specialDefenseGrowth;
	float speedGrowth;

	std::vector<Skill> learnableSkills; // 포켓몬이 배울수 있는 기술
	std::vector<Skill> currentSkills; // 포켓몬이 배우고 있는 기술

};


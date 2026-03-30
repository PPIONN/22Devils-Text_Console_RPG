#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
// 포켓몬 클래스가 할수있는일 :
// 1. 포켓몬은 플레이어의 레벨을 따라간다. 능력치또한 레벨에 맞게 조정된다.
struct Nature {
	std::string name;
	std::string upStat;   // 1.1배 되는 스탯
	std::string downStat; // 0.9배 되는 스탯
};
static std::map<std::string, Nature> natureChart = {
	{"Hardy",   {"Hardy",   "", ""}},          // 변동 없음
	{"Lonely",  {"Lonely",  "attack", "defense"}},
	{"Brave",   {"Brave",   "attack", "speed"}},
	{"Adamant", {"Adamant", "attack", "specialAttack"}},
	{"Naughty", {"Naughty", "attack", "specialDefense"}},
	{"Bold",    {"Bold",    "defense", "attack"}},
	{"Docile",  {"Docile",  "", ""}},          // 변동 없음
	{"Relaxed", {"Relaxed", "defense", "speed"}},
	{"Impish",  {"Impish",  "defense", "specialAttack"}},
	{"Lax",     {"Lax",     "defense", "specialDefense"}},
	{"Timid",   {"Timid",   "speed", "attack"}},      // 고오스 추천 1 (스피드업)
	{"Hasty",   {"Hasty",   "speed", "defense"}},
	{"Serious", {"Serious", "", ""}},          // 변동 없음
	{"Jolly",   {"Jolly",   "speed", "specialAttack"}},
	{"Naive",   {"Naive",   "speed", "specialDefense"}},
	{"Modest",  {"Modest",  "specialAttack", "attack"}}, // 고오스 추천 2 (특공업)
	{"Mild",    {"Mild",    "specialAttack", "defense"}},
	{"Quiet",   {"Quiet",   "specialAttack", "speed"}},
	{"Bashful", {"Bashful", "", ""}},          // 변동 없음
	{"Rash",    {"Rash",    "specialAttack", "specialDefense"}},
	{"Calm",    {"Calm",    "specialDefense", "attack"}},
	{"Gentle",  {"Gentle",  "specialDefense", "defense"}},
	{"Sassy",   {"Sassy",   "specialDefense", "speed"}},
	{"Careful", {"Careful", "specialDefense", "specialAttack"}},
	{"Quirky",  {"Quirky",  "", ""}}           // 변동 없음
};

static std::map<std::string, std::map<std::string, float>> typeChart = {
	{"Normal",   {{"Rock", 0.5f}, {"Ghost", 0.0f}, {"Steel", 0.5f}}},
	{"Fire",     {{"Fire", 0.5f}, {"Water", 0.5f}, {"Grass", 2.0f}, {"Ice", 2.0f}, {"Bug", 2.0f}, {"Rock", 0.5f}, {"Dragon", 0.5f}, {"Steel", 2.0f}}},
	{"Water",    {{"Fire", 2.0f}, {"Water", 0.5f}, {"Grass", 0.5f}, {"Ground", 2.0f}, {"Rock", 2.0f}, {"Dragon", 0.5f}}},
	{"Electric", {{"Water", 2.0f}, {"Electric", 0.5f}, {"Grass", 0.5f}, {"Ground", 0.0f}, {"Dragon", 0.5f}}},
	{"Grass",    {{"Fire", 0.5f}, {"Water", 2.0f}, {"Grass", 0.5f}, {"Poison", 0.5f}, {"Ground", 2.0f}, {"Flying", 0.5f}, {"Bug", 0.5f}, {"Rock", 2.0f}, {"Dragon", 0.5f}, {"Steel", 0.5f}}},
	{"Ice",      {{"Fire", 0.5f}, {"Water", 0.5f}, {"Grass", 2.0f}, {"Ice", 0.5f}, {"Ground", 2.0f}, {"Flying", 2.0f}, {"Dragon", 2.0f}, {"Steel", 0.5f}}},
	{"Fighting", {{"Normal", 2.0f}, {"Ice", 2.0f}, {"Poison", 0.5f}, {"Flying", 0.5f}, {"Psychic", 0.5f}, {"Bug", 0.5f}, {"Rock", 2.0f}, {"Ghost", 0.0f}, {"Dark", 2.0f}, {"Steel", 2.0f}}},
	{"Poison",   {{"Grass", 2.0f}, {"Poison", 0.5f}, {"Ground", 0.5f}, {"Rock", 0.5f}, {"Ghost", 0.5f}, {"Steel", 0.0f}}},
	{"Ground",   {{"Fire", 2.0f}, {"Electric", 2.0f}, {"Grass", 0.5f}, {"Poison", 2.0f}, {"Flying", 0.0f}, {"Bug", 0.5f}, {"Rock", 2.0f}, {"Steel", 2.0f}}},
	{"Flying",   {{"Electric", 0.5f}, {"Grass", 2.0f}, {"Fighting", 2.0f}, {"Bug", 2.0f}, {"Rock", 0.5f}, {"Steel", 0.5f}}},
	{"Psychic",  {{"Fighting", 2.0f}, {"Poison", 2.0f}, {"Psychic", 0.5f}, {"Dark", 0.0f}, {"Steel", 0.5f}}},
	{"Bug",      {{"Fire", 0.5f}, {"Grass", 2.0f}, {"Fighting", 0.5f}, {"Poison", 0.5f}, {"Flying", 0.5f}, {"Psychic", 2.0f}, {"Ghost", 0.5f}, {"Dark", 2.0f}, {"Steel", 0.5f}}},
	{"Rock",     {{"Fire", 2.0f}, {"Ice", 2.0f}, {"Fighting", 0.5f}, {"Ground", 0.5f}, {"Flying", 2.0f}, {"Bug", 2.0f}, {"Steel", 0.5f}}},
	{"Ghost",    {{"Normal", 0.0f}, {"Psychic", 2.0f}, {"Ghost", 2.0f}, {"Dark", 0.5f}, {"Steel", 0.5f}}},
	{"Dragon",   {{"Dragon", 2.0f}, {"Steel", 0.5f}}},
	{"Dark",     {{"Fighting", 0.5f}, {"Psychic", 2.0f}, {"Ghost", 2.0f}, {"Dark", 0.5f}}},
	{"Steel",    {{"Fire", 0.5f}, {"Water", 0.5f}, {"Electric", 0.5f}, {"Ice", 2.0f}, {"Rock", 2.0f}, {"Steel", 0.5f}}}
};



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
	pokemon() {
		std::string randomNature = getRandomNature();
		applyNatureEffect(randomNature);
	}
	virtual ~pokemon() {}

	// 생성자속에서 해볼만한 일
	void newpokescale(const int nowlevel); // 적, 우리 포켓몬 레벨에 따른 능력치조정
	void levelscale(const int nowlevel); // 플레이어의 레벨을 받아 포켓몬 스텟 조정
	void updateSkills(); // 포켓몬 레벨업시 스킬추가 혹은 4개 이상 소지면 삭제 후 스킬추가함
	void newSkills(const int index); // 포켓몬 생성시 자동으로 스킬 들어가게해줌

	void warstat(); // 전투스탯

	void levelup();

	std::string getRandomNature() {
		// static을 사용하여 프로그램 실행 중 딱 한 번만 벡터를 채웁니다.
		static std::vector<std::string> natureNames;

		if (natureNames.empty()) {
			// 위에서 정의한 natureChart의 키값들을 가져옵니다.
			for (auto const& pair : natureChart) {
				natureNames.push_back(pair.first); // pair.first가 key(성격 이름)입니다.
			}
		}

		int randomIndex = rand() % natureNames.size();
		return natureNames[randomIndex];
	}

	void applyNatureEffect(std::string nName) {
		if (natureChart.find(nName) == natureChart.end()) return;

		Nature n = natureChart[nName];

		// 상승 스탯 보정 (1.1배)
		if (n.upStat == "attack") this->attack *= 1.1f;
		else if (n.upStat == "defense") this->defense *= 1.1f;
		else if (n.upStat == "specialAttack") this->specialAttack *= 1.1f;
		else if (n.upStat == "specialDefense") this->specialDefense *= 1.1f;
		else if (n.upStat == "speed") this->speed *= 1.1f;

		// 하강 스탯 보정 (0.9배)
		if (n.downStat == "attack") this->attack *= 0.9f;
		else if (n.downStat == "defense") this->defense *= 0.9f;
		else if (n.downStat == "specialAttack") this->specialAttack *= 0.9f;
		else if (n.downStat == "specialDefense") this->specialDefense *= 0.9f;
		else if (n.downStat == "speed") this->speed *= 0.9f;

		std::cout << nName << " 성격이 적용되었습니다!\n";
	}



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
	inline void sethp(const float hp) {
		this->hp = hp;
	}
	inline void setattack(const float attack) {
		this->attack = attack;
	}
	inline void setdefense(const float defense) {
		this->defense = defense;
	}
	inline void setspecialAttack(const float specialAttack) {
		this->specialAttack = specialAttack;
	}
	inline void setspecialDefense(const float specialDefense) {
		this->specialDefense = specialDefense;
	}
	inline void setspeed(const float speed) {
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



	//void ShowInfo() const;
	void selectattack(pokemon* enemy, int index) {
		Skill& selected = currentSkills[index];

		// 1. 명중률 체크
		int randomNumber = rand() % 100;
		if (selected.accuracy != -1 && randomNumber >= selected.accuracy) {
			std::cout << this->name << "의 " << selected.name << " 기술이 빗나갔다!" << std::endl;
			return;
		}

		std::cout << this->name << "은(는) " << selected.name << "을 사용했다!" << std::endl;

		// 2. 변화기(Status) 처리
		if (selected.category == "Status") {
			std::cout << "효과는 미미했다... (변화기 로직 미구현)" << std::endl;
			return;
		}

		// 3. 상성 계산 (std::vector<std::string> 기반)
		float effectiveness = 1.0f;
		for (const std::string& enemyType : enemy->type) { // enemy의 vector<string> 순회
			if (typeChart.count(selected.type) && typeChart[selected.type].count(enemyType)) {
				effectiveness *= typeChart[selected.type][enemyType];
			}
		}

		// 4. 공격력/방어력 결정 (Physical vs Special)
		float A = (selected.category == "Physical") ? this->attack : this->specialAttack;
		float D = (selected.category == "Physical") ? enemy->defense : enemy->specialDefense;

		// 5. 데미지 공식 적용
		int finalDamage = 0;
		if (selected.power > 0) {
			// 4세대 공식: ((((2 * Level / 5) + 2) * Power * A / D) / 50) + 2
			float baseDamage = ((((2.0f * (float)this->level) / 5.0f) + 2.0f) * (float)selected.power * (A / D)) / 50.0f;
			baseDamage += 2.0f;

			// 자속 보정(STAB): 공격자 타입 중 기술 타입이 포함되어 있으면 1.5배
			float stab = 1.0f;
			for (const std::string& myType : this->type) {
				if (myType == selected.type) {
					stab = 1.5f;
					break;
				}
			}

			// 최종 데미지 = 기본 * 자속 * 상성
			finalDamage = static_cast<int>(baseDamage * stab * effectiveness);
		}
		else if (selected.name == "Night Shade") {
			// 나이트헤드: 레벨만큼 고정 피해 (노말 타입 상성 0배 적용)
			finalDamage = (effectiveness == 0.0f) ? 0 : this->level;
		}

		// 6. 결과 출력 및 적용
		enemy->hp -= finalDamage;
		if (enemy->hp < 0) enemy->hp = 0;

		if (effectiveness >= 2.0f) std::cout << "효과가 굉장했다!" << std::endl;
		else if (effectiveness > 0.0f && effectiveness <= 0.5f) std::cout << "효과가 별로인 듯하다..." << std::endl;
		else if (effectiveness == 0.0f) std::cout << "효과가 없는 것 같다." << std::endl;

		std::cout << enemy->name << "에게 " << finalDamage << "의 피해를 입혔다!" << std::endl;
	}


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

	std::vector<std::string> type;
	std::vector<Skill> learnableSkills; // 포켓몬이 배울수 있는 기술
	std::vector<Skill> currentSkills; // 포켓몬이 배우고 있는 기술

};


#include "Common.h"
#include "TypeChart.h"
#include "GameData.h"

// 1. 경험치 획득 로직
void Pokemon::gainExp(int amount) {
	exp += amount;
	cout << "\n" << name << "은(는) " << amount << "의 경험치를 얻었다!" << endl;

	int nextLevelExp = level * 50;
	while (exp >= nextLevelExp) {
		exp -= nextLevelExp;
		levelup();
		nextLevelExp = level * 50;
	}
}

// 2. 기술 사용 및 데미지 계산
int Pokemon::useSkill(int skillIdx, Pokemon& target) {
	if (skillIdx < 0 || skillIdx >= (int)currentSkills.size()) return 0;
	Skill& skill = currentSkills[skillIdx];

	if (skill.pp <= 0) {
		cout << skill.name << "은(는) 기력이 부족하다!" << endl;
		return 0;
	}

	skill.pp--;
	cout << name << "의 " << skill.name << "!" << endl;

	if (skill.accuracy != -1 && (rand() % 100) + 1 > skill.accuracy) {
		cout << "하지만 공격은 빗나갔다!" << endl;
		return 0;
	}

	float atkStat = (skill.category == "Special") ? specialAttack : attack;
	float defStat = (skill.category == "Special") ? target.getspecialDefense() : target.getdefense();

	float damage = (((2 * level / 5 + 2) * skill.power * (atkStat / defStat)) / 50) + 2;

	float eff = TypeChart::getEffectiveness(skill.type, target.type);
	damage *= eff;

	if (eff >= 2.0f) cout << "효과가 굉장했다!" << endl;
	else if (eff > 0.0f && eff <= 0.5f) cout << "효과가 별로인 듯하다..." << endl;
	else if (eff == 0.0f) cout << "효과가 없는 것 같다." << endl;

	damage *= (float)(rand() % 16 + 85) / 100.0f;

	return (int)damage;
}

// 3. 스탯 스케일링 (처음 생성 시)
void Pokemon::newpokescale(int targetLevel) {
	level = targetLevel;
	hp += hpGrowth * level;
	maxHp = hp;
	attack += attackGrowth * level;
	defense += defenseGrowth * level;
	specialAttack += specialAttackGrowth * level;
	specialDefense += specialDefenseGrowth * level;
	speed += speedGrowth * level;
	newpokeSkills(); // [수정] updateSkills -> newpokeSkills
}

// 4. 레벨업 시 스탯 상승
void Pokemon::levelup() {
	level++;
	hp += hpGrowth;
	maxHp += hpGrowth;
	attack += attackGrowth;
	defense += defenseGrowth;
	specialAttack += specialAttackGrowth;
	specialDefense += specialDefenseGrowth;
	speed += speedGrowth;

	cout << "\n" << name << "은(는) LV." << level << "(으)로 올랐다!" << endl;
	newpokeSkills(); // [수정] updateSkills -> newpokeSkills
}

// 5. 기술 습득 시스템
void Pokemon::newpokeSkills() {
	currentSkills.clear();
	for (auto& skill : learnableSkills) {
		if (skill.level <= level) {
			currentSkills.push_back(skill);
			if (currentSkills.size() > 4) {
				currentSkills.erase(currentSkills.begin());
			}
		}
	}
}

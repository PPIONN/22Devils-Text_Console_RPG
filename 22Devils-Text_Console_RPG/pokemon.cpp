#include"pokemon.h"
#include <iostream>




void pokemon::newpokescale(const int level) {
	setlevel(level);
	levelhp(level);
	levelattack(level);
	leveldefense(level);
	levelspecialAttack(level);
	levelspecialDefense(level);
	levelspeed(level);
}
void pokemon::levelscale(const int nowlevel) { // 플레이어의 레벨을 받아 포켓몬 스텟 조정
	if (this->level != nowlevel) {
		levelhp(nowlevel);
		levelattack(nowlevel);
		leveldefense(nowlevel);
		levelspecialAttack(nowlevel);
		levelspecialDefense(nowlevel);
		levelspeed(nowlevel);
	}
}

void pokemon::levelup() {
	setlevel(getlevel() + 1);
	levelscale(getlevel());
}

void pokemon::warstat() {
	warattack = attack; // 기본 능력치
	wardefense = defense;
	warspecialAttack = specialAttack;
	warspecialDefense = specialDefense;
	warspeed = speed;
}

void pokemon::newSkills(const int index) // 포켓몬이 레벨업할때마다 원하는 스킬 변경
{
	for (const auto& skill : learnableSkills)
	{

			// 원하는 인덱스의 스킬 삭제
			if (currentSkills.size() > 4)
			{
				currentSkills.erase(currentSkills.begin()+index);
				currentSkills.push_back(skill);

			}

	}
}
void pokemon::updateSkills() // 포켓몬 생성 및 출현시 자동 스킬입력
{
	currentSkills.clear();

	for (auto& skill : learnableSkills)
	{
		if (skill.level == getlevel())
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



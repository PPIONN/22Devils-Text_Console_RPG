#pragma once
#include"pokemon.h"
#include <cstdlib> // rand(), srand() 사용
#include <ctime>   // time() 사용
class gastly : public pokemon {
public:
	gastly(const int nowlevel, const std::string& name) { // 현재레벨 , 별명 ex) 고옹이 ()
		// 1. 고오스 고유의 기초 스탯 설정 (부모 변수들에 대입)
		maxhp = gethp();
		hp = 10.0f;
		attack = 5.0f;
		defense = 5.0f;
		specialAttack = 5.0f;
		specialDefense = 5.0f;
		speed = 5.0f;

		hpGrowth = 1.95f;
		attackGrowth = 1.01f;
		defenseGrowth = 0.91f;
		specialAttackGrowth = 2.31f;
		specialDefenseGrowth = 1.91f;
		speedGrowth = 1.91f;
		setrealname("Gastly");
		type = { "Poison", "Ghost" };
		learnableSkills = {
	{ "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
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
		// 2. 레벨에 따른 스탯 확장
		newpokescale(nowlevel);
		warstat();
		// 3. 성격 적용 (레벨업 스케일링이 끝난 최종 스탯에 곱해줘야 함)

		std::string nature = applyNatureEffect(getRandomNature());

		updateSkills();
		setname(name);
	}
	// private에 변수들을 중복 선언(float attack 등)하지 마세요! 제거해야 합니다.
};



#pragma once
#include"pokemon.h"
#include <cstdlib> // rand(), srand() 사용
#include <ctime>   // time() 사용
class gastly : public pokemon {
public:
	gastly(const int nowlevel, const std::string& name) { // 현재레벨 , 별명 ex) 고옹이 ()
		// 1. 고오스 고유의 기초 스탯 설정 (부모 변수들에 대입)
		maxhp = gethp(); // ***********이부분 수정 /////////////// 최대 hp
		hp = 10.0f; // ***********이부분 수정 /////////////// 현재hp
		attack = 5.0f; // ***********이부분 수정 /////////////// 공
		defense = 5.0f; // ***********이부분 수정 /////////////// 방
		specialAttack = 5.0f; // ***********이부분 수정 /////////////// 특공
		specialDefense = 5.0f; // ***********이부분 수정 /////////////// 특방
		speed = 5.0f; // ***********이부분 수정 /////////////// 스피드

		hpGrowth = 1.95f; // ***********이부분 수정 /////////////// 성장체력
		attackGrowth = 1.01f; // ***********이부분 수정 /////////////// 성장공
		defenseGrowth = 0.91f; // ***********이부분 수정 /////////////// 성장방
		specialAttackGrowth = 2.31f; // ***********이부분 수정 ///////////////성특공
		specialDefenseGrowth = 1.91f;// ***********이부분 수정 ///////////////성특방
		speedGrowth = 1.91f;// ***********이부분 수정 ///////////////성스
		setrealname("Gastly"); // ***********이부분 수정 ///////////////  고유 포켓몬 이름 // 별명아님 !!
 		type = { "Poison", "Ghost" }; // ***********이부분 수정 /////////////// 타입. 단일 타입일시 // type = { "Poison" }; 처럼 수정
		learnableSkills = { // ***********이부분 수정 /////////////// 배울수잇는 모든 스킬
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
		newpokescale(nowlevel); // 신경쓰지마셈 // 레벨에따라 능력 조정
		warstat(); // 신경쓰지마셈 // 전투용 스텟
		// 3. 성격 적용 (레벨업 스케일링이 끝난 최종 스탯에 곱해줘야 함)

		std::string nature = applyNatureEffect(getRandomNature()); // 신경쓰지마셈 // 랜덤씨드 받아서 성격넣기

		newpokeSkills(); // 신경쓰지마셈 레벨 확인 후 스킬 획득함 
		setname(name); // 신경쓰지마셈 별명 
	}
	// private에 변수들을 중복 선언(float attack 등)하지 마세요! 제거해야 합니다.
};



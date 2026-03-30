#include"pokemon.h"
#include <iostream>




void pokemon::newpokescale(const int level) { // 매개변수 : 플레이어.getlevel() // 처음 등장한 포켓몬의 능력치 조정
	setlevel(level);
	levelhp(level);
	setmaxhp(gethp());
	levelattack(level);
	leveldefense(level);
	levelspecialAttack(level);
	levelspecialDefense(level);
	levelspeed(level);
}
void pokemon::levelscale(const int nowlevel) { // 매개변수 : 포켓몬.getlevel()+1  // 플레이어의 레벨을 받아 포켓몬 스텟 조정
	if (this->level != nowlevel) {

		levelhp(nowlevel);
		levelmaxhp(nowlevel);
		levelattack(nowlevel);
		leveldefense(nowlevel);
		levelspecialAttack(nowlevel);
		levelspecialDefense(nowlevel);
		levelspeed(nowlevel);
	}
}

void pokemon::levelup() {
	// 1. 레벨 수치 증가 및 능력치 스케일링
	setlevel(getlevel() + 1);
	levelscale(getlevel());

	std::cout << "\n레벨이 " << getlevel() << "로 올랐다!" << std::endl;

	// 2. 새로운 기술이 있는지 확인 (learnableSkills 순회)
	// iterator를 써야 배운 기술을 목록에서 삭제(erase)할 수 있습니다.
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level <= getlevel()) {

			// 현재 배운 기술이 4개 미만이면 자동으로 배움
			if (currentSkills.size() < 4) {
				std::cout << name << "은(는) " << it->name << " 기술을 새로 배웠다!" << std::endl;
				currentSkills.push_back(*it);
				it = learnableSkills.erase(it); // 목록에서 제거
				// 여러 개를 배울 수도 있으니 계속 진행
			}
			else {
				// 기술이 이미 4개라면 사용자 선택이 필요함
				std::cout << name << "은(는) " << it->name << "을(를) 배우고 싶다..." << std::endl;
				std::cout << "하지만 기술을 이미 4개 알고 있다! 하나를 잊게 하겠습니까? (0~3번 선택, 배우지 않으려면 -1)" << std::endl;

				// 기술 목록 보여주기
				for (int i = 0; i < currentSkills.size(); ++i) {
					std::cout << i << ". " << currentSkills[i].name << "  ";
				}
				std::cout << std::endl;

				int choice;
				std::cin >> choice;

				if (choice >= 0 && choice < 4) {
					// 선택한 번호의 기술 교체
					newSkills(choice); // it->level 체크 로직이 포함된 newSkills 호출
					// newSkills 안에서 erase를 처리하므로 여기서는 iterator 관리에 주의해야 합니다.
					// 간단하게 하기 위해 이번 루프를 종료하고 다시 체크하거나 루프를 조정합니다.
					it = learnableSkills.begin(); // 목록이 변했으므로 처음부터 다시 확인
				}
				else {
					std::cout << it->name << " 배우기를 포기했다." << std::endl;
					it = learnableSkills.erase(it); // 배우지 않기로 했으므로 목록에서 제거
				}
			}
		}
		else {
			++it; // 현재 레벨보다 높은 레벨의 기술은 패스
		}
	}
}

void pokemon::warstat() {
	warattack = attack; // 기본 능력치
	wardefense = defense;
	warspecialAttack = specialAttack;
	warspecialDefense = specialDefense;
	warspeed = speed;
}

void pokemon::newSkills(const int index) {
	// learnableSkills의 맨 앞(이미 레벨 조건이 맞아서 들어온 기술)을 사용
	if (!learnableSkills.empty()) {
		auto& newSkill = learnableSkills.front();

		std::cout << currentSkills[index].name << "을(를) 잊고... "
			<< newSkill.name << "을(를) 배웠다!" << std::endl;

		currentSkills[index] = newSkill; // 교체
		learnableSkills.erase(learnableSkills.begin()); // 목록에서 제거
	}
}

void pokemon::updateSkills() {
	// 1. 레벨에 맞는 기술들을 찾아서 습득
	// iterator를 사용해야 순회 중에 안전하게 삭제(erase)가 가능합니다.
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level <= getlevel()) {
			// 현재 기술이 4개 미만이면 바로 추가
			if (currentSkills.size() < 4) {
				currentSkills.push_back(*it);
				it = learnableSkills.erase(it); // 배운 기술은 전체 목록에서 삭제
			}
			else {
				// 이미 4개라면 더 이상 자동으로 배우지 않고 다음으로 넘김
				// (나중에 레벨업 시 newSkills를 통해 교체해야 함)
				++it;
			}
		}
		else {
			++it;
		}
	}
}


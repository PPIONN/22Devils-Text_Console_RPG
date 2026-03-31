#include "Common.h"
#include "PokemonData.h"
#include "BossData.h"
#include <random>
// 외부 전역 변수 참조
extern Pokemon* g_playerPoke;
extern Player g_player;
extern vector<string> g_normalPool;
extern vector<string> g_legendaryPool;

// --- [적 스폰 함수] ---
// 아까 추가한 엠페르트, 루카리오, 가디안, 한카리아스, 마기라스 등이 모두 등장하도록 수정했습니다.
unique_ptr<Monster> spawnEnemy(int floor) { // 
	string name = "";
	int lv = floor + 2;

	// 5층 단위 보스 스폰
	if (floor % 5 == 0 && !g_legendaryPool.empty()) {
		name = g_legendaryPool.back();
		g_legendaryPool.pop_back();
	}
	else if (!g_normalPool.empty()) {
		name = g_normalPool.back();
		g_normalPool.pop_back();
	}

	// 이름에 맞춰 실제 객체 생성 (PokemonData.h의 클래스명과 일치)
	if (name == "Rayquaza") return make_unique<Rayquaza>(lv + 5);
	if (name == "Suicune")  return make_unique<Suicune>(lv + 2);
	if (name == "Lugia")    return make_unique<Lugia>(lv + 3);
	if (name == "Gardevoir") return make_unique<Gardevoir>(lv);
	if (name == "Garchomp")  return make_unique<Garchomp>(lv);
	if (name == "Tyranitar") return make_unique<Tyranitar>(lv);
	if (name == "Lucario")   return make_unique<Lucario>(lv);
	if (name == "Empoleon")  return make_unique<Empoleon>(lv);
	if (name == "Gastly")    return make_unique<Gastly>(lv);
	if (name == "Snorlax")   return make_unique<Snorlax>(lv);
	if (name == "Cyndaquil") return make_unique<Cyndaquil>(lv);

	return make_unique<Magikarp>(lv); // 기본값
}

// --- [메인 배틀 로직] ---
void scene4() {
	if (g_playerPoke == nullptr) return;
	std::random_device rd; // 이현준 추가 수정사항 - 랜덤씨드 생성
	std::mt19937 gen(rd()); // 이현준 추가 수정사항 - 랜덤씨드 생성
	std::uniform_int_distribution<int> dis(0, 99); // 이현준 추가 수정사항 - 랜덤씨드 생성

	// 1. 적 스폰 및 초기 메시지
	unique_ptr<Monster> enemy = spawnEnemy(g_currentFloor);
	talk("시스템", enemy->getName() + "이(가) 나타났다! (LV." + to_string(enemy->getlevel()) + ")");

	while (g_playerPoke->gethp() > 0 && enemy->gethp() > 0) {
		system("cls");
		cout << "\n================ [ BATTLE ] ================" << endl;
		cout << " [적] " << enemy->getName() << " (HP: " << (int)enemy->gethp() << " / " << (int)enemy->getmaxhp() << ")" << endl;
		cout << "--------------------------------------------" << endl;
		cout << " [나] " << g_playerPoke->getName() << " (HP: " << (int)g_playerPoke->gethp() << " / " << (int)g_playerPoke->getmaxhp() << ")" << endl;
		cout << "============================================" << endl;
		cout << " 1. 싸운다  2. 가방  3. 도망친다" << endl;
		cout << " 선택: ";

		int menu; cin >> menu;

		if (menu == 1) { // [싸운다]
			cout << "\n--- 기술 목록 ---" << endl;
			for (int i = 0; i < (int)g_playerPoke->currentSkills.size(); i++) {
				cout << i + 1 << ". " << g_playerPoke->currentSkills[i].name << " (PP: " << g_playerPoke->currentSkills[i].pp << ")" << endl;
			}
			cout << "0. 취소" << endl;
			cout << " 선택: ";
			int sIdx; cin >> sIdx;

			if (sIdx == 0) continue;
			if (sIdx >= 1 && sIdx <= (int)g_playerPoke->currentSkills.size()) {
				// 플레이어 공격 (Setter 사용으로 에러 해결)
				int damage = g_playerPoke->useSkill(sIdx - 1, *enemy);
				enemy->sethp(enemy->gethp() - (float)damage);
				cout << "\n" << g_playerPoke->getName() << "의 공격! " << damage << "의 데미지!" << endl;
				Sleep(1000);

				if (enemy->gethp() <= 0) {
					talk("시스템", enemy->getName() + "은(는) 쓰러졌다! 승리했습니다.");

					// 경험치 및 골드 보상
					int expReward = enemy->getlevel() * 30;
					g_playerPoke->gainExp(expReward);
					g_player.setmoney(g_currentFloor * 100);
					return;
				}
			}
		}
		else if (menu == 2) { // [가방]
			g_player.InventoryUI(); // 전투 중 아이템 사용
			continue;
		}
		else if (menu == 3) { // [도망] ///
			if (g_currentFloor % 5 == 0) {
				talk("시스템", "보스에게서 도망칠 수 없다!");
				continue;
			}
			/// 여기까지 아래로 수정사항 - 이현준


			// 3. 랜덤 숫자 하나 생성
			int randomNumber = dis(gen);

			// 4. 30% 확률 체크 (0~29까지 나오면 당첨!)
			if (randomNumber < 30) {
				talk("시스템", "도망치지 못했다...");
			}
			else {
				talk("시스템", "무사히 도망쳤다!");
				return;
			}

			// 여기까지 위로 수정사항
			//talk("시스템", "무사히 도망쳤다!");
			//return;
		}

		// --- 적의 턴 ---
		if (enemy->gethp() > 0) {
			int eSkillIdx = rand() % enemy->currentSkills.size();
			int eDamage = enemy->useSkill(eSkillIdx, *g_playerPoke);
			g_playerPoke->sethp(g_playerPoke->gethp() - (float)eDamage); // Setter 사용

			cout << "\n" << enemy->getName() << "의 공격! " << eDamage << "의 데미지!" << endl;
			Sleep(1500);

			if (g_playerPoke->gethp() <= 0) {
				talk("시스템", g_playerPoke->getName() + "은(는) 쓰러졌다... 눈앞이 캄캄해졌다!");
				return;
			}
		}
	}
}

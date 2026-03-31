#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "Player.h"
#include "gastly.h"

using namespace std;

// [도구] main.cpp에서 정의된 공통 함수 가져오기
extern void goToXY(int x, int y);
extern void setFontSize(int size);
extern Player* player;
extern int g_currentfloor;

struct Pokemon {
	string name;
	int level;
	int hp, maxHp;
	int atk, spd;
	int gold, exp;
};

// HP바 동적 계산 (유니코드 블록 활용)
wstring getHPBar(int hp, int maxHp, int length) {
	if (hp <= 0) return wstring(length, L'░');
	if (maxHp <= 0) maxHp = 1; // 0 나누기 방지
	int filled = (hp * length) / maxHp;
	wstring bar = L"";
	for (int i = 0; i < length; i++) {
		if (i < filled) bar += L"█"; else bar += L"░";
	}
	return bar;
}

// [핵심] 현재 전투 상황을 실시간으로 그리는 UI 함수
void renderBattleUI(pokemon* p, pokemon* e, string message)
{
	system("cls");
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);

	// pokemon 클래스에 정의된 변수로 변경
	string pNameStr = p->getname();
	string eNameStr = e->getname();
	wstring wP(pNameStr.begin(), pNameStr.end());
	wstring wE(eNameStr.begin(), eNameStr.end());
	wstring wMsg(message.begin(), message.end());

	wcout << L"  포켓몬 탑 - " << g_currentfloor << L"층                                                                 P" << player->getStatus(StatType::Money) << endl;
	wcout << L"  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
	wcout << L"    ╔══════════════════════════════════╗" << endl;
	wcout << L"    ║ " << wE << L" ♂           Lv." << e->getlevel() << L"        ║" << endl;
	wcout << L"    ║ HP  [" << getHPBar(e->gethp(), e->getmaxhp(), 20) << L"]     ║" << endl;
	wcout << L"    ╚══════════════════════════════════╝              " << endl;

	wcout << LR"(                                                       ,---.
                                                      /  _  \
                                                   __/_ ( )  |
                                                 /  _  _    /


                                                |  / \/ \  /
                                                |  \____/  \
                                                 \_________/--.
                                                  /__/  /__/ 
                 _.._
               .'    `.
              /   __   \
           ,  |  /  \  |  ,
           \'. \      / .'/    ╔══════════════════════════════════════════════════╗
            '. \`----' / .'    ║ )" << wP << L" ♂                        Lv." << p->getlevel() << L"           ║" << endl;
	wcout << L"          _.-'  '----'  '-._   ║ HP  [" << getHPBar(p->gethp(), p->getmaxhp(), 26) << L"]  " << p->gethp() << L" / " << p->getmaxhp() << L"        ║" << endl;
	wcout << LR"(        .'        __        `. ║ EXP [▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░]                   ║
       /      _.-'  '-._      \╚══════════════════════════════════════════════════╝

  ╔═══════════════════════════════════════════════════╦════════════════════════════════╗
  ║                                                   ║                                ║
  ║  )" << wMsg << LR"( ║    ▶ 1.싸운다          2.가방    ║
  ║                                                   ║      3.포켓몬          4.도망    ║
  ╚═══════════════════════════════════════════════════╩════════════════════════════════╝)" << endl;

	_setmode(_fileno(stdout), oldMode);
}

void scene4() {
	srand((unsigned int)time(NULL));
	setFontSize(18);

	// 1. 전투 준비
	pokemon* MyPokemon = player->getLeadPokemon();
	if (MyPokemon == nullptr) {
		cout << "전투 가능한 포켓몬이 없습니다." << endl;
		return;
	}

	gastly* EnemyPokemon = new gastly(g_currentfloor, "Gastly");
	string currentMsg = MyPokemon->getname() + "은(는) 무엇을 할까?";

	// 2. 전투 루프
	while (MyPokemon->gethp() > 0 && EnemyPokemon->gethp() > 0) {
		renderBattleUI(MyPokemon, EnemyPokemon, currentMsg);

		_setmode(_fileno(stdout), _O_TEXT);
		int choice;
		cout << "  선택: ";
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		bool turnUsed = false; // 턴 소모 여부 체크

		if (choice == 4) { // 도망
			renderBattleUI(MyPokemon, EnemyPokemon, "무사히 도망쳤다!                    ");
			Sleep(1000);
			delete EnemyPokemon;
			return;
		}
		else if (choice == 1) // 싸운다
		{
			system("cls");
			cout << "\n[ " << MyPokemon->getname() << "의 기술 선택 ]" << endl;
			cout << "------------------------------------" << endl;
			// Skill 구조체에 접근할 수 있는 getter가 없으므로 번호로 안내합니다. 기술 3개 이하일 때 입력값에 따라 크래시 위험 있음.
			cout << "1. 첫 번째 기술" << endl;
			cout << "2. 두 번째 기술" << endl;
			cout << "3. 세 번째 기술" << endl;
			cout << "4. 네 번째 기술" << endl;
			cout << "0. 취소" << endl;
			cout << "------------------------------------" << endl;
			cout << "번호 선택: ";

			int skillIdx;
			if (!(cin >> skillIdx) || skillIdx == 0) continue;

			// 인덱스 보정 (1~4 -> 0~3)
			skillIdx -= 1;

			// 전투 시작
			system("cls");
			// 1. 선후공 결정
			pokemon* first = (MyPokemon->getspeed() >= EnemyPokemon->getspeed()) ? MyPokemon : EnemyPokemon;
			pokemon* second = (MyPokemon->getspeed() >= EnemyPokemon->getspeed()) ? EnemyPokemon : MyPokemon;

			for (int i = 0; i < 2; i++) {
				pokemon* attacker = (i == 0) ? first : second;
				pokemon* defender = (i == 0) ? second : first;

				if (attacker->gethp() <= 0 || defender->gethp() <= 0) break;

				cout << "\n====================================\n";
				if (attacker == MyPokemon) {
					// 사용자가 선택한 기술 번호 전달
					attacker->selectattack(defender, skillIdx);
				}
				else {
					// 적은 0번 기술을 쓰거나 랜덤하게 사용
					int enemySkill = rand() % 2;
					attacker->selectattack(defender, enemySkill);
				}
				cout << "====================================\n";
				Sleep(1500);
			}
			currentMsg = MyPokemon->getname() + "은(는) 무엇을 할까?";
		}
		else if (choice == 2) { // 가방
			player->InventoryUI();
			turnUsed = true;
		}
		else if (choice == 3) { // 포켓몬 교체
			pokemon* oldPokemon = MyPokemon;

			player->selectPokemon(true);
			MyPokemon = player->getLeadPokemon(); // 선두 갱신

			if (oldPokemon != MyPokemon) {
				// 교체 성공 시: 적의 공격 페이즈로 강제 진입
				currentMsg = MyPokemon->getname() + "로 교체되었다!";
				renderBattleUI(MyPokemon, EnemyPokemon, currentMsg);
				Sleep(1000);

				// [적의 반격] 플레이어는 교체하느라 턴을 썼으므로 적만 공격
				system("cls");
				cout << "\n[상대방의 턴!]\n";
				cout << "====================================\n";
				EnemyPokemon->selectattack(MyPokemon, 0);
				cout << "====================================\n";
				Sleep(1500);
			}
		}
	}

	// 3. 전투 결과 처리 (동일)
	system("cls");
	if (EnemyPokemon->gethp() <= 0) {
		int earnedGold = g_currentfloor * 50;
		int earnedExp = g_currentfloor * 30;

		cout << "\n\n  [전투 승리!] " << EnemyPokemon->getname() << "을(를) 물리쳤습니다!" << endl;
		cout << "  >> 보상: " << earnedGold << " Gold와 " << earnedExp << " EXP를 획득했습니다." << endl;

		player->setStatus(StatType::Money, earnedGold);
		player->setStatus(StatType::EXP, earnedExp);
	}
	else {
		cout << "\n\n  [패배] 눈앞이 캄캄해졌다..." << endl;
	}

	delete EnemyPokemon;
	system("pause");
}

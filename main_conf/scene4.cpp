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

	// 1. 전투 시작 전

	//선두 포켓몬 출전
	pokemon* MyPokemon = player->getLeadPokemon();
	if (MyPokemon == nullptr)
	{
		cout << "Not Exist Pokemon for Fight" << endl;
		return;
	}

	//임시로 채워둔 적 포켓몬 등장 로직
	gastly* EnemyPokemon = new gastly(g_currentfloor, "Gastly");

	// 이 부분 이름 getter 함수 없어서 테스트할 때는 	inline std::string getname() const { return name; } 임의로 만들어서 사용했음
	string currentMsg = MyPokemon->getname() + "은(는) 무엇을 할까?           ";

	// 3. 전투 루프
	while (MyPokemon->gethp() > 0 && EnemyPokemon->gethp() > 0) {
		renderBattleUI(MyPokemon, EnemyPokemon, currentMsg);

		_setmode(_fileno(stdout), _O_TEXT);
		int choice;
		cout << "  선택: ";
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		if (choice == 4) { // 도망
			renderBattleUI(MyPokemon, EnemyPokemon, "무사히 도망쳤다!                    ");
			Sleep(1000);
			delete EnemyPokemon;
			return;
		}
		else if (choice == 1) { // 싸운다
			system("cls");
			// 속도 비교를 통한 선후공 판정
			pokemon* first = (MyPokemon->getspeed() >= EnemyPokemon->getspeed()) ? MyPokemon : EnemyPokemon;
			pokemon* second = (MyPokemon->getspeed() >= EnemyPokemon->getspeed()) ? EnemyPokemon : MyPokemon;

			// 첫 번째 공격
			cout << "\n====================================\n";
			first->selectattack(second, 0); // 임시로 0번 스킬 사용
			cout << "====================================\n";
			Sleep(1500);

			// 두 번째 공격 (첫 번째 공격으로 죽지 않았을 경우)
			if (second->gethp() > 0) {
				cout << "\n====================================\n";
				second->selectattack(first, 0);
				cout << "====================================\n";
				Sleep(1500);
			}
			currentMsg = MyPokemon->getname() + "은(는) 무엇을 할까?           ";
		}
		else if (choice == 2) {
			player->InventoryUI();
		}
	}

	// 4. 전투 결과 처리
	system("cls");
	if (EnemyPokemon->gethp() <= 0) {
		int earnedGold = g_currentfloor * 50;
		int earnedExp = g_currentfloor * 30;

		cout << "\n\n  [전투 승리!] " << EnemyPokemon->getname() << "을(를) 물리쳤습니다!" << endl;
		cout << "  >> 보상: " << earnedGold << " Gold와 " << earnedExp << " EXP를 획득했습니다." << endl;

		// 실제 플레이어 스탯에 반영
		player->setStatus(StatType::Money, earnedGold);
		player->setStatus(StatType::EXP, earnedExp);
	}
	else {
		cout << "\n\n  [패배] 눈앞이 캄캄해졌다..." << endl;
	}

	delete EnemyPokemon;
	system("pause");
}

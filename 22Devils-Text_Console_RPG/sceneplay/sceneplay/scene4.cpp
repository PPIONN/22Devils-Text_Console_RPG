#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <windows.h>



using namespace std;

// [도구] main.cpp에서 정의된 공통 함수 가져오기
extern void goToXY(int x, int y);
extern void setFontSize(int size);
extern string g_playerName;
extern string g_starterName;

struct Pokemon {
	string name;
	int level;
	int hp, maxHp;
	int atk, spd;
	int gold, exp;
};

// HP바 동적 계산 (유니코드 블록 활용)
wstring getHPBar(int hp, int maxHp, int length) {
	if (hp < 0) hp = 0;
	int filled = (hp * length) / maxHp;
	wstring bar = L"";
	for (int i = 0; i < length; i++) {
		if (i < filled) bar += L"█"; else bar += L"░";
	}
	return bar;
}

// [핵심] 현재 전투 상황을 실시간으로 그리는 UI 함수
void renderBattleUI(Pokemon& p, Pokemon& e, string message) {
	system("cls");
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);

	wstring wP(p.name.begin(), p.name.end());
	wstring wE(e.name.begin(), e.name.end());
	wstring wMsg(message.begin(), message.end());

	wcout << L"  포켓몬 탑 - 1층                                                                 P" << p.gold << endl;
	wcout << L"  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
	wcout << L"    ╔══════════════════════════════════╗" << endl;
	wcout << L"    ║ " << wE << L" ♂           Lv." << e.level << L"        ║" << endl;
	wcout << L"    ║ HP  [" << getHPBar(e.hp, e.maxHp, 20) << L"]     ║" << endl;
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
            '. \`----' / .'    ║ )" << wP << L" ♂                        Lv." << p.level << L"           ║" << endl;
	wcout << L"          _.-'  '----'  '-._   ║ HP  [" << getHPBar(p.hp, p.maxHp, 26) << L"]  " << p.hp << L" / " << p.maxHp << L"        ║" << endl;
	wcout << LR"(        .'        __        `. ║ EXP [▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░]                   ║
       /      _.-'  '-._      \╚══════════════════════════════════════════════════╝

  ╔═══════════════════════════════════════════════════╦════════════════════════════════╗
  ║                                                   ║                                ║
  ║  )" << wMsg << LR"( ║    ▶ 1.싸운다          2.기술    ║
  ║                                                   ║      3.포켓몬          4.도망    ║
  ╚═══════════════════════════════════════════════════╩════════════════════════════════╝)" << endl;

	_setmode(_fileno(stdout), oldMode);
}

void scene4() {
	srand((unsigned int)time(NULL));
	setFontSize(18);

	// 1. 캐릭터 스탯 초기화
	Pokemon player = { g_starterName, 1, 50, 50, 15, 50, 0, 0 };
	Pokemon enemy = { "화살꼬빈", 2, 40, 40, 8, 45, 100, 60 };

	string currentMsg = player.name + "은(는) 무엇을 할까?           ";

	// 2. 전투 루프 시작
	while (player.hp > 0 && enemy.hp > 0) {
		// UI 출력 및 명령 대기
		renderBattleUI(player, enemy, currentMsg);

		_setmode(_fileno(stdout), _O_TEXT);
		int choice;
		cout << "  선택: ";
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		if (choice == 4) { // 도망 로직
			renderBattleUI(player, enemy, "무사히 도망쳤다!                    ");
			Sleep(1000);
			return;
		}

		// 3. 선공/후공 결정 (스피드 비교)
		Pokemon* first = (player.spd >= enemy.spd) ? &player : &enemy;
		Pokemon* second = (player.spd >= enemy.spd) ? &enemy : &player;

		for (int i = 0; i < 2; i++) {
			Pokemon* attacker = (i == 0) ? first : second;
			Pokemon* defender = (i == 0) ? second : first;

			if (attacker->hp <= 0 || defender->hp <= 0) break;

			if (attacker->name == player.name) {
				// 플레이어 공격 시각화
				int damage = attacker->atk + (rand() % 5);
				defender->hp -= damage;
				renderBattleUI(player, enemy, attacker->name + "의 공격! " + to_string(damage) + " 데미지!      ");
			}
			else {
				// 적의 반격 시각화
				int damage = attacker->atk + (rand() % 3);
				defender->hp -= damage;
				renderBattleUI(player, enemy, attacker->name + "의 반격! " + to_string(damage) + " 데미지!      ");
			}
			Sleep(1000); // 연출을 위해 대기
		}

		currentMsg = player.name + "은(는) 무엇을 할까?           ";
	}

	// 4. 전투 결과 처리
	system("cls");
	if (enemy.hp <= 0) {
		cout << "\n\n  [전투 승리!] " << enemy.name << "을(를) 물리쳤습니다!" << endl;
		cout << "  >> 보상: " << enemy.gold << " Gold와 " << enemy.exp << " EXP를 획득했습니다." << endl;
		player.exp += enemy.exp;
		if (player.exp >= 100) cout << "  >> ★ 레벨 업! ★" << endl;
	}
	else {
		cout << "\n\n  [패배] " << player.name << "은(는) 눈앞이 캄캄해졌다..." << endl;
	}
	system("pause");
}

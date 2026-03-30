#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

using namespace std;

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

// [추가] 한글 string을 wstring으로 안전하게 변환하는 함수
wstring s2ws(const string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}

// HP바 계산
wstring getHPBar(int hp, int maxHp, int length) {
	if (hp < 0) hp = 0;
	int filled = (hp * length) / maxHp;
	wstring bar = L"";
	for (int i = 0; i < length; i++) {
		if (i < filled) bar += L"■"; else bar += L" ";
	}
	return bar;
}

void renderBattleUI(Pokemon& p, Pokemon& e, string message) {
	system("cls");
	// 출력을 위해 유니코드 모드로 전환
	_setmode(_fileno(stdout), _O_U16TEXT);

	wstring wP = s2ws(p.name);
	wstring wE = s2ws(e.name);
	wstring wMsg = s2ws(message);

	wcout << L"\n  포켓몬 탑 - 1층" << endl;
	wcout << L"  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;

	// 적 UI
	wcout << L"    ┌──────────────────────────────────┐" << endl;
	wcout << L"    │ " << wE << L" Lv." << e.level << L"                     │" << endl;
	wcout << L"    │ HP  [" << getHPBar(e.hp, e.maxHp, 20) << L"]         │" << endl;
	wcout << L"    └──────────────────────────────────┘" << endl;

	// 아스키 아트 (위치 조정)
	wcout << LR"(
                                           /|      __
                                          / | __  /  \

                                         |  |/  \|    |
                                         |  |    |    |
                                          \ |    |    /
                                           \|____|___/ 
    )" << endl;

	// 플레이어 UI
	wcout << L"                                     ┌──────────────────────────────────────────┐" << endl;
	wcout << L"                                     │ " << wP << L" Lv." << p.level << L"                          │" << endl;
	wcout << L"                                     │ HP  [" << getHPBar(p.hp, p.maxHp, 20) << L"]  " << p.hp << L" / " << p.maxHp << L"   │" << endl;
	wcout << L"                                     └──────────────────────────────────────────┘" << endl;

	// 하단 메시지 및 메뉴박스
	wcout << L"\n  ┌──────────────────────────────────────────────┬──────────────────────────────┐" << endl;
	wcout << L"  │                                              │                              │" << endl;
	wcout << L"  │ " << (wMsg.length() > 20 ? wMsg.substr(0, 20) : wMsg); // 메시지 길이 제한

	// 메뉴 부분 (간격 조정)
	goToXY(51, 23); wcout << L"│  1.싸운다       2.기술   │";
	goToXY(51, 24); wcout << L"│  3.포켓몬       4.도망   │";
	goToXY(0, 25);
	wcout << L"  └──────────────────────────────────────────────┴──────────────────────────────┘" << endl;

	// 입력 받기 전 모드 복구
	_setmode(_fileno(stdout), _O_TEXT);
}

void scene4() {
	srand((unsigned int)time(NULL));
	// 폰트 크기가 너무 작으면 UI가 겹치니 20~24 권장
	setFontSize(24);

	Pokemon player = { g_starterName, 1, 50, 50, 15, 50, 0, 0 };
	Pokemon enemy = { "화살꼬빈", 2, 40, 40, 8, 45, 100, 60 };

	string currentMsg = player.name + "은(는) 무엇을 할까?";

	while (player.hp > 0 && enemy.hp > 0) {
		renderBattleUI(player, enemy, currentMsg);

		cout << "\n  선택: ";
		int choice;
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		if (choice == 4) {
			renderBattleUI(player, enemy, "무사히 도망쳤다!");
			Sleep(1000);
			return;
		}

		// 전투 로직 (데미지 계산 등)
		int damage = player.atk + (rand() % 5);
		enemy.hp -= damage;
		renderBattleUI(player, enemy, player.name + "의 공격! " + to_string(damage) + " 데미지!");
		Sleep(800);

		if (enemy.hp > 0) {
			int eDamage = enemy.atk + (rand() % 3);
			player.hp -= eDamage;
			renderBattleUI(player, enemy, enemy.name + "의 반격! " + to_string(eDamage) + " 데미지!");
			Sleep(800);
		}

		currentMsg = player.name + "은(는) 무엇을 할까?";
	}

	system("cls");
	if (enemy.hp <= 0) {
		cout << "\n\n  [전투 승리!] " << enemy.name << "을(를) 물리쳤습니다!" << endl;
	}
	else {
		cout << "\n\n  [패배] " << player.name << "은(는) 쓰러졌습니다..." << endl;
	}
	system("pause");
}

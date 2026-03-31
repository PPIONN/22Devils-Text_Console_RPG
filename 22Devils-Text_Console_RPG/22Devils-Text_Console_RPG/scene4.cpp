#include "Common.h"
#include "GameData.h"
#include <io.h>
#include <fcntl.h>

// 유니코드 변환 유틸 (에러 해결: &r[0] 사용)
wstring s2ws_battle(const string& s) {
	if (s.empty()) return L"";
	int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
	if (len <= 0) return L"";

	wstring r(len, 0);
	// [수정] &r 대신 &r[0]를 전달하여 실제 버퍼 주소를 넘겨야 합니다.
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &r[0], len);

	// 문자열 끝에 포함된 널 문자를 제거하여 깔끔하게 처리
	if (!r.empty() && r.back() == L'\0') r.pop_back();

	return r;
}

// UI 렌더링 함수 (기존 로직 유지)
void renderBattleFrame(Pokemon& p, Pokemon& e, string msg, int mode, int selSkillIdx = 0) {
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
	system("cls");

	wcout << L"\n  " << s2ws_battle(e.name) << L" Lv." << e.level << L"  HP: " << e.hp << L"/" << e.maxHp << endl;
	wcout << L"\n\n          [ 적 포켓몬 UI: " << s2ws_battle(e.name) << L" ]\n\n" << endl;
	wcout << L"  " << s2ws_battle(p.name) << L" Lv." << p.level << L"  HP: " << p.hp << L"/" << p.maxHp << endl;
	wcout << L"  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;

	if (mode == 0) { // 메인 메뉴
		goToXY(4, 18); wcout << s2ws_battle(msg);
		goToXY(51, 18); wcout << L"1.싸운다      2.볼";
		goToXY(51, 19); wcout << L"3.포켓몬      4.도망간다";
	}
	else if (mode == 1) { // 기술 선택
		for (int i = 0; i < 4; i++) {
			int tx = (i % 2 == 0) ? 4 : 28;
			int ty = (i < 2) ? 18 : 19;
			goToXY(tx, ty);
			if (i < (int)p.skills.size()) wcout << i + 1 << L"." << s2ws_battle(p.skills[i].name);
			else wcout << L"-";
		}
	}

	goToXY(4, 22);
	(void)_setmode(_fileno(stdout), _O_TEXT);
}

// 전투 시퀀스 (기존 로직 유지)
void scene4() {
	Pokemon player("리자몽", 36, 120, 120, 84, 78, 100, 0, 0);
	player.skills = {
		{"베어가르기", "NORMAL", 20, 20, 70},
		{"회오리불꽃", "FIRE", 15, 15, 35},
		{"화염방사", "FIRE", 15, 15, 90},
		{"에어슬래시", "FLY", 15, 15, 75}
	};

	Pokemon enemy("거북왕", 36, 130, 130, 85, 80, 78, 100, 100);

	while (player.hp > 0 && enemy.hp > 0) {
		renderBattleFrame(player, enemy, player.name + "은(는) 무엇을 할까?", 0);
		int menuChoice;
		cout << "선택: "; cin >> menuChoice;

		if (menuChoice == 1) { // 싸운다
			while (true) {
				renderBattleFrame(player, enemy, "", 1, 0);
				cout << "기술 번호(취소:0): ";
				int sIdx; cin >> sIdx;
				if (sIdx == 0) break;
				if (sIdx >= 1 && sIdx <= (int)player.skills.size()) {
					Skill& selected = player.skills[sIdx - 1];
					renderBattleFrame(player, enemy, player.name + "의 " + selected.name + "!", 0);
					Sleep(800);
					enemy.hp -= (selected.power / 2);
					if (enemy.hp <= 0) {
						talk("시스템", enemy.name + "은(는) 쓰러졌다!");
						return;
					}
					break;
				}
			}
		}
		else if (menuChoice == 4) return; // 도망
	}
}
